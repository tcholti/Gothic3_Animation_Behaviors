[CmdletBinding()]
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$InputPath,

    [string]$OutputRoot = ".\research\derived",

    [int]$MaxOutputPartBytes = 60000,

    [string[]]$ExtraSignalPattern = @(),

    [switch]$Force
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

if ($MaxOutputPartBytes -lt 20000)
{
    throw "MaxOutputPartBytes must be at least 20000."
}

$resolvedInput = Resolve-Path -LiteralPath $InputPath
$inputItem = Get-Item -LiteralPath $resolvedInput.Path
if ($inputItem.PSIsContainer)
{
    throw "InputPath must name a file."
}

$baseName = [System.IO.Path]::GetFileNameWithoutExtension($inputItem.Name)
$outputDirectory = Join-Path $OutputRoot ($baseName + "_large_log")
if (Test-Path -LiteralPath $outputDirectory)
{
    if (-not $Force)
    {
        throw "Output directory already exists: $outputDirectory. Re-run with -Force to rebuild it."
    }
    Remove-Item -LiteralPath $outputDirectory -Recurse -Force
}
New-Item -ItemType Directory -Path $outputDirectory -Force | Out-Null

$utf8NoBom = New-Object System.Text.UTF8Encoding -ArgumentList $false
$sourceHash = (Get-FileHash -LiteralPath $inputItem.FullName -Algorithm SHA256).Hash

$signalPatterns = [ordered]@{
    "C1_INVARIANT_WARNING" = "C1 INVARIANT WARNING"
    "WOULD_REPAIR" = "WOULD_REPAIR"
    "WARNING" = "(?i)\bWARNING\b"
    "ERROR_OR_EXCEPTION" = "(?i)\b(ERROR|EXCEPTION)\b"
    "MISMATCH_OR_DIVERGENCE" = "(?i)\b(MISMATCH|DIVERGENCE)\b"
    "OUTSTANDING_TRUE" = "(?i)\bOUTSTANDING\b.*(?:[:=]\s*(1|TRUE)\s*$)"
    "RAW55_CALLBACK_BOUNDARY" = "RAW55_[A-Z0-9_]*CALLBACK_BOUNDARY"
    "RAW55_GROUP_SUPPRESSION" = "RAW55_[A-Z0-9_]*GROUP_SUPPRESSION"
    "FIST_ACTIVATION" = "(?i)ACTIVATE_FIST\s*[:=]\s*1"
    "AUTHORED_FIST_MARKER" = "G3AB_COL_FIST"
    "CLEAR_TRIGGERED_LIST" = "(?i)CLEARTRIGGEREDLIST|ClearTriggeredList"
    "ON_DAMAGE" = "(?i)\bONDAMAGE\b|OnDamage"
    "COLLISION_GROUP" = "CORE COLLISION_GROUP"
    "C1_CLEANUP_FULFILLED" = "C1 CLEANUP FULFILLED"
    "C1_FINAL" = "C1_FINAL|C1 FINAL"
    "REPAIRED_TO_ITEM_EQUIPPED" = "REPAIRED_TO_ITEM_EQUIPPED"
    "REPAIR_DIVERGED_FROM_ITEM_EQUIPPED" = "REPAIR_DIVERGED_FROM_ITEM_EQUIPPED"
}

$extraIndex = 0
foreach ($pattern in @($ExtraSignalPattern))
{
    if ([string]::IsNullOrWhiteSpace($pattern))
    {
        continue
    }
    ++$extraIndex
    $signalPatterns[("EXTRA_{0:D2}" -f $extraIndex)] = $pattern
}

function Escape-Tsv([string]$value)
{
    if ($null -eq $value)
    {
        return ""
    }
    return $value.Replace("`t", " ").Replace("`r", " ").Replace("`n", " ")
}

function Write-TextParts(
    [System.Collections.Generic.List[string]]$rows,
    [string]$header,
    [string]$outputDir,
    [string]$filePrefix,
    [int]$maxBytes,
    [System.Text.Encoding]$encoding)
{
    $files = New-Object System.Collections.Generic.List[string]
    $writer = $null
    $partNumber = 0
    $partBytes = 0
    $rowCount = 0
    $headerBytes = $encoding.GetByteCount($header + [Environment]::NewLine)

    try
    {
        foreach ($row in $rows)
        {
            $rowBytes = $encoding.GetByteCount($row + [Environment]::NewLine)
            if ($null -eq $writer -or ($rowCount -gt 0 -and ($partBytes + $rowBytes) -gt $maxBytes))
            {
                if ($null -ne $writer)
                {
                    $writer.Dispose()
                    $writer = $null
                }

                ++$partNumber
                $fileName = "{0}_part_{1:D3}.tsv" -f $filePrefix, $partNumber
                $writer = New-Object System.IO.StreamWriter -ArgumentList @((Join-Path $outputDir $fileName), $false, $encoding)
                $writer.WriteLine($header)
                $files.Add($fileName)
                $partBytes = $headerBytes
                $rowCount = 0
            }

            $writer.WriteLine($row)
            $partBytes += $rowBytes
            ++$rowCount
        }
    }
    finally
    {
        if ($null -ne $writer)
        {
            $writer.Dispose()
        }
    }

    return $files
}

$eventCounts = @{}
$eventTimelineRows = New-Object System.Collections.Generic.List[string]
$signalRows = New-Object System.Collections.Generic.List[string]
$fullSourceIndexRows = New-Object System.Collections.Generic.List[string]
$fullSourceFiles = New-Object System.Collections.Generic.List[string]

$reader = New-Object System.IO.StreamReader -ArgumentList @($inputItem.FullName, [System.Text.Encoding]::UTF8, $true)
$sourceWriter = $null
$sourcePartNumber = 0
$sourcePartBytes = 0
$sourcePartStartLine = 0
$lineNumber = 0

try
{
    while (($line = $reader.ReadLine()) -ne $null)
    {
        ++$lineNumber
        $mirrorLine = "{0:D8}: {1}" -f $lineNumber, $line
        $mirrorBytes = $utf8NoBom.GetByteCount($mirrorLine + [Environment]::NewLine)

        if ($null -eq $sourceWriter -or ($sourcePartBytes -gt 0 -and ($sourcePartBytes + $mirrorBytes) -gt $MaxOutputPartBytes))
        {
            if ($null -ne $sourceWriter)
            {
                $sourceWriter.Dispose()
                $sourceWriter = $null
                $fullSourceIndexRows.Add(("{0}`t{1}`t{2}`t{3}" -f $fullSourceFiles[$fullSourceFiles.Count - 1], $sourcePartStartLine, ($lineNumber - 1), $sourcePartBytes))
            }

            ++$sourcePartNumber
            $sourceFileName = "full_source_part_{0:D3}.txt" -f $sourcePartNumber
            $sourceWriter = New-Object System.IO.StreamWriter -ArgumentList @((Join-Path $outputDirectory $sourceFileName), $false, $utf8NoBom)
            $fullSourceFiles.Add($sourceFileName)
            $sourcePartBytes = 0
            $sourcePartStartLine = $lineNumber
        }

        $sourceWriter.WriteLine($mirrorLine)
        $sourcePartBytes += $mirrorBytes

        $headerMatch = [regex]::Match($line, "^\s*=+\s+(.+?)\s+=+\s*$")
        if ($headerMatch.Success)
        {
            $eventName = $headerMatch.Groups[1].Value.Trim()
            $eventTimelineRows.Add(("{0}`t{1}" -f $lineNumber, (Escape-Tsv $eventName)))
            if ($eventCounts.ContainsKey($eventName))
            {
                ++$eventCounts[$eventName]
            }
            else
            {
                $eventCounts[$eventName] = 1
            }
        }

        foreach ($signalName in $signalPatterns.Keys)
        {
            if ([regex]::IsMatch($line, [string]$signalPatterns[$signalName]))
            {
                $signalRows.Add(("{0}`t{1}`t{2}" -f $lineNumber, $signalName, (Escape-Tsv $line)))
            }
        }
    }

    if ($null -ne $sourceWriter)
    {
        $fullSourceIndexRows.Add(("{0}`t{1}`t{2}`t{3}" -f $fullSourceFiles[$fullSourceFiles.Count - 1], $sourcePartStartLine, $lineNumber, $sourcePartBytes))
    }
}
finally
{
    $reader.Dispose()
    if ($null -ne $sourceWriter)
    {
        $sourceWriter.Dispose()
    }
}

$eventCountPath = Join-Path $outputDirectory "event_counts.tsv"
$eventCountWriter = New-Object System.IO.StreamWriter -ArgumentList @($eventCountPath, $false, $utf8NoBom)
try
{
    $eventCountWriter.WriteLine("Event`tCount")
    foreach ($entry in ($eventCounts.GetEnumerator() | Sort-Object Name))
    {
        $eventCountWriter.WriteLine(("{0}`t{1}" -f (Escape-Tsv ([string]$entry.Name)), [int]$entry.Value))
    }
}
finally
{
    $eventCountWriter.Dispose()
}

$indexPath = Join-Path $outputDirectory "full_source_index.tsv"
$indexWriter = New-Object System.IO.StreamWriter -ArgumentList @($indexPath, $false, $utf8NoBom)
try
{
    $indexWriter.WriteLine("File`tStartLine`tEndLine`tBytes")
    foreach ($row in $fullSourceIndexRows)
    {
        $indexWriter.WriteLine($row)
    }
}
finally
{
    $indexWriter.Dispose()
}

$eventTimelineFiles = @(Write-TextParts $eventTimelineRows "Line`tEvent" $outputDirectory "event_timeline" $MaxOutputPartBytes $utf8NoBom)
$signalFiles = @(Write-TextParts $signalRows "Line`tSignal`tText" $outputDirectory "signals" $MaxOutputPartBytes $utf8NoBom)

$manifestPath = Join-Path $outputDirectory "manifest.txt"
$manifestWriter = New-Object System.IO.StreamWriter -ArgumentList @($manifestPath, $false, $utf8NoBom)
try
{
    $manifestWriter.WriteLine("CHAT-FRIENDLY LARGE LOG PACKAGE")
    $manifestWriter.WriteLine("ToolVersion: 1")
    $manifestWriter.WriteLine("SourceInput: $InputPath")
    $manifestWriter.WriteLine("SourceFileName: $($inputItem.Name)")
    $manifestWriter.WriteLine("SourceSHA256: $sourceHash")
    $manifestWriter.WriteLine("SourceBytes: $($inputItem.Length)")
    $manifestWriter.WriteLine("SourceLineCount: $lineNumber")
    $manifestWriter.WriteLine("DistinctEventTypes: $($eventCounts.Count)")
    $manifestWriter.WriteLine("EventTimelineRows: $($eventTimelineRows.Count)")
    $manifestWriter.WriteLine("SignalMatches: $($signalRows.Count)")
    $manifestWriter.WriteLine("MaxOutputPartBytes: $MaxOutputPartBytes")
    $manifestWriter.WriteLine("FullSourceParts: $($fullSourceFiles.Count)")
    $manifestWriter.WriteLine("EventTimelineParts: $($eventTimelineFiles.Count)")
    $manifestWriter.WriteLine("SignalParts: $($signalFiles.Count)")
    $manifestWriter.WriteLine("")
    $manifestWriter.WriteLine("SignalPatterns:")
    foreach ($signalName in $signalPatterns.Keys)
    {
        $manifestWriter.WriteLine("- $signalName = $($signalPatterns[$signalName])")
    }
    $manifestWriter.WriteLine("")
    $manifestWriter.WriteLine("Files:")
    $manifestWriter.WriteLine("- event_counts.tsv")
    $manifestWriter.WriteLine("- full_source_index.tsv")
    foreach ($file in $eventTimelineFiles) { $manifestWriter.WriteLine("- $file") }
    foreach ($file in $signalFiles) { $manifestWriter.WriteLine("- $file") }
    foreach ($file in $fullSourceFiles) { $manifestWriter.WriteLine("- $file") }
}
finally
{
    $manifestWriter.Dispose()
}

Write-Host "Chat-friendly large-log package created."
Write-Host "Source: $($inputItem.FullName)"
Write-Host "SHA256: $sourceHash"
Write-Host "Lines: $lineNumber"
Write-Host "Events: $($eventTimelineRows.Count)"
Write-Host "Signals: $($signalRows.Count)"
Write-Host "Full-source parts: $($fullSourceFiles.Count)"
Write-Host "Output: $outputDirectory"
