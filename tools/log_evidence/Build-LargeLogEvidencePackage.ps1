[CmdletBinding()]
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$InputPath,

    [string]$OutputRoot = ".\research\derived",

    [int]$ContextBefore = 80,

    [int]$ContextAfter = 120,

    [int]$MaxOutputPartBytes = 120000,

    [string[]]$ExtraSignalPattern = @(),

    [string[]]$RequestedRange = @(),

    [switch]$Force
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

if ($ContextBefore -lt 0 -or $ContextAfter -lt 0)
{
    throw "ContextBefore and ContextAfter must be zero or greater."
}
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

$selectedFieldNames = @(
    "ElapsedMs",
    "Code",
    "Reason",
    "Event",
    "Actor",
    "Generation",
    "Status",
    "Source",
    "SourceAddress",
    "Side",
    "RequestedGroup",
    "BeforeGroup",
    "AfterGroup",
    "ActualGroup",
    "PhysicalCollisionChanged",
    "MarkerAction",
    "SetCollisionGroupAction",
    "CurrentAction",
    "CurrentAniPhase",
    "CurrentStateTime",
    "CurrentMovementAni",
    "PlayerAction",
    "PlayerAniPhase",
    "PlayerStateTime",
    "PlayerCurrentMovementAni"
)

$selectedFieldSet = @{}
foreach ($fieldName in $selectedFieldNames)
{
    $selectedFieldSet[$fieldName] = $true
}

$signalPatterns = [ordered]@{
    "C1_INVARIANT_WARNING" = "C1 INVARIANT WARNING"
    "WOULD_REPAIR" = "WOULD_REPAIR"
    "WARNING" = "(?i)\bWARNING\b"
    "ERROR_OR_EXCEPTION" = "(?i)\b(ERROR|EXCEPTION)\b"
    "FAILED_OR_FAILURE" = "(?i)\b(FAILED|FAILURE)\b"
    "MISMATCH_OR_DIVERGENCE" = "(?i)\b(MISMATCH|DIVERGENCE)\b"
    "STALE" = "(?i)\bSTALE\b"
    "UNRESOLVED_OR_ORPHAN" = "(?i)\b(UNRESOLVED|ORPHAN)\b"
    "BAD_OR_UNSAFE_SKIP" = "(?i)(BAD|UNSAFE|FAILED|STALE|MISMATCH).*(SKIP|SKIPPED)|(SKIP|SKIPPED).*(BAD|UNSAFE|FAILED|STALE|MISMATCH)"
    "OUTSTANDING_TRUE" = "(?i)\bOUTSTANDING\b.*(?:[:=]\s*(1|TRUE)\s*$)"
}

$extraIndex = 0
foreach ($pattern in $ExtraSignalPattern)
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

function Convert-EventToRow($eventRecord, [int]$endLine, [string[]]$fieldOrder)
{
    $summaryParts = New-Object System.Collections.Generic.List[string]
    foreach ($fieldName in $fieldOrder)
    {
        if ($eventRecord.Fields.ContainsKey($fieldName))
        {
            $summaryParts.Add(
                ("{0}={1}" -f $fieldName, (Escape-Tsv ([string]$eventRecord.Fields[$fieldName])))
            )
        }
    }

    return [PSCustomObject]@{
        StartLine = [int]$eventRecord.StartLine
        EndLine = $endLine
        Header = [string]$eventRecord.Header
        Summary = ($summaryParts -join " | ")
    }
}

function Write-TextParts(
    [System.Collections.Generic.List[string]]$rows,
    [string]$header,
    [string]$outputDir,
    [string]$filePrefix,
    [string]$extension,
    [int]$maxBytes,
    [System.Text.Encoding]$encoding)
{
    $files = New-Object System.Collections.Generic.List[string]
    $partNumber = 0
    $writer = $null
    $partBytes = 0
    $rowCountInPart = 0

    try
    {
        foreach ($row in $rows)
        {
            $rowBytes = $encoding.GetByteCount($row + [Environment]::NewLine)
            $headerBytes = $encoding.GetByteCount($header + [Environment]::NewLine)

            if ($null -eq $writer -or
                ($rowCountInPart -gt 0 -and ($partBytes + $rowBytes) -gt $maxBytes))
            {
                if ($null -ne $writer)
                {
                    $writer.Dispose()
                    $writer = $null
                }

                ++$partNumber
                $fileName = "{0}_part_{1:D3}.{2}" -f $filePrefix, $partNumber, $extension
                $filePath = Join-Path $outputDir $fileName
                $writer = New-Object System.IO.StreamWriter -ArgumentList @($filePath, $false, $encoding)
                $writer.WriteLine($header)
                $partBytes = $headerBytes
                $rowCountInPart = 0
                $files.Add($fileName)
            }

            $writer.WriteLine($row)
            $partBytes += $rowBytes
            ++$rowCountInPart
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

function Merge-LineRanges([object[]]$ranges)
{
    $merged = New-Object System.Collections.Generic.List[object]
    if ($null -eq $ranges -or $ranges.Count -eq 0)
    {
        return $merged
    }

    $ordered = $ranges | Sort-Object Start, End
    $currentStart = [int]$ordered[0].Start
    $currentEnd = [int]$ordered[0].End

    for ($i = 1; $i -lt $ordered.Count; ++$i)
    {
        $nextStart = [int]$ordered[$i].Start
        $nextEnd = [int]$ordered[$i].End
        if ($nextStart -le ($currentEnd + 1))
        {
            if ($nextEnd -gt $currentEnd)
            {
                $currentEnd = $nextEnd
            }
            continue
        }

        $merged.Add([PSCustomObject]@{ Start = $currentStart; End = $currentEnd })
        $currentStart = $nextStart
        $currentEnd = $nextEnd
    }

    $merged.Add([PSCustomObject]@{ Start = $currentStart; End = $currentEnd })
    return $merged
}

function Write-SourceRangesToParts(
    [string]$sourcePath,
    [object[]]$ranges,
    [string]$outputDir,
    [string]$filePrefix,
    [int]$maxBytes,
    [System.Text.Encoding]$encoding)
{
    $files = New-Object System.Collections.Generic.List[string]
    if ($null -eq $ranges -or $ranges.Count -eq 0)
    {
        return $files
    }

    $orderedRanges = $ranges | Sort-Object Start, End
    $reader = New-Object System.IO.StreamReader -ArgumentList @($sourcePath, [System.Text.Encoding]::UTF8, $true)
    $writer = $null
    $partNumber = 0
    $partBytes = 0
    $lineNumber = 0
    $rangeIndex = 0
    $enteredRange = $false

    try
    {
        while (($line = $reader.ReadLine()) -ne $null -and $rangeIndex -lt $orderedRanges.Count)
        {
            ++$lineNumber
            $range = $orderedRanges[$rangeIndex]

            while ($rangeIndex -lt $orderedRanges.Count -and $lineNumber -gt [int]$range.End)
            {
                ++$rangeIndex
                $enteredRange = $false
                if ($rangeIndex -lt $orderedRanges.Count)
                {
                    $range = $orderedRanges[$rangeIndex]
                }
            }

            if ($rangeIndex -ge $orderedRanges.Count)
            {
                break
            }

            if ($lineNumber -lt [int]$range.Start)
            {
                continue
            }

            if (-not $enteredRange)
            {
                $rangeHeader = "===== SOURCE RANGE {0}-{1} =====" -f $range.Start, $range.End
                $rangeHeaderBytes = $encoding.GetByteCount($rangeHeader + [Environment]::NewLine)

                if ($null -eq $writer -or
                    ($partBytes -gt 0 -and ($partBytes + $rangeHeaderBytes) -gt $maxBytes))
                {
                    if ($null -ne $writer)
                    {
                        $writer.Dispose()
                        $writer = $null
                    }
                    ++$partNumber
                    $fileName = "{0}_part_{1:D3}.txt" -f $filePrefix, $partNumber
                    $filePath = Join-Path $outputDir $fileName
                    $writer = New-Object System.IO.StreamWriter -ArgumentList @($filePath, $false, $encoding)
                    $files.Add($fileName)
                    $partBytes = 0
                }

                $writer.WriteLine($rangeHeader)
                $partBytes += $rangeHeaderBytes
                $enteredRange = $true
            }

            $outputLine = "{0:D8}: {1}" -f $lineNumber, $line
            $outputBytes = $encoding.GetByteCount($outputLine + [Environment]::NewLine)

            if ($partBytes -gt 0 -and ($partBytes + $outputBytes) -gt $maxBytes)
            {
                $writer.Dispose()
                $writer = $null
                ++$partNumber
                $fileName = "{0}_part_{1:D3}.txt" -f $filePrefix, $partNumber
                $filePath = Join-Path $outputDir $fileName
                $writer = New-Object System.IO.StreamWriter -ArgumentList @($filePath, $false, $encoding)
                $files.Add($fileName)
                $partBytes = 0
            }

            $writer.WriteLine($outputLine)
            $partBytes += $outputBytes
        }
    }
    finally
    {
        $reader.Dispose()
        if ($null -ne $writer)
        {
            $writer.Dispose()
        }
    }

    return $files
}

$events = New-Object System.Collections.Generic.List[object]
$signals = New-Object System.Collections.Generic.List[object]
$eventCounts = @{}
$currentEvent = $null
$currentHeader = "<none>"
$lineNumber = 0

$reader = New-Object System.IO.StreamReader -ArgumentList @($inputItem.FullName, [System.Text.Encoding]::UTF8, $true)
try
{
    while (($line = $reader.ReadLine()) -ne $null)
    {
        ++$lineNumber

        $headerMatch = [regex]::Match($line, "^\s*=+\s+(.+?)\s+=+\s*$")
        if ($headerMatch.Success)
        {
            if ($null -ne $currentEvent)
            {
                $events.Add((Convert-EventToRow $currentEvent ($lineNumber - 1) $selectedFieldNames))
            }

            $currentHeader = $headerMatch.Groups[1].Value.Trim()
            if ($eventCounts.ContainsKey($currentHeader))
            {
                ++$eventCounts[$currentHeader]
            }
            else
            {
                $eventCounts[$currentHeader] = 1
            }

            $currentEvent = @{
                StartLine = $lineNumber
                Header = $currentHeader
                Fields = @{}
            }
        }
        elseif ($null -ne $currentEvent)
        {
            $fieldMatch = [regex]::Match($line, "^([^:]{1,80}):\s*(.*)$")
            if ($fieldMatch.Success)
            {
                $fieldName = $fieldMatch.Groups[1].Value.Trim()
                if ($selectedFieldSet.ContainsKey($fieldName) -and
                    -not $currentEvent.Fields.ContainsKey($fieldName))
                {
                    $currentEvent.Fields[$fieldName] = $fieldMatch.Groups[2].Value.Trim()
                }
            }
        }

        foreach ($signalName in $signalPatterns.Keys)
        {
            if ([regex]::IsMatch($line, [string]$signalPatterns[$signalName]))
            {
                $signals.Add([PSCustomObject]@{
                    Line = $lineNumber
                    Event = $currentHeader
                    Signal = $signalName
                    Text = $line
                })
            }
        }
    }
}
finally
{
    $reader.Dispose()
}

if ($null -ne $currentEvent)
{
    $events.Add((Convert-EventToRow $currentEvent $lineNumber $selectedFieldNames))
}

$lineCount = $lineNumber

$eventCountRows = New-Object System.Collections.Generic.List[string]
foreach ($entry in ($eventCounts.GetEnumerator() | Sort-Object Name))
{
    $eventCountRows.Add(("{0}`t{1}" -f (Escape-Tsv ([string]$entry.Name)), [int]$entry.Value))
}
$eventCountPath = Join-Path $outputDirectory "event_counts.tsv"
$eventCountWriter = New-Object System.IO.StreamWriter -ArgumentList @($eventCountPath, $false, $utf8NoBom)
try
{
    $eventCountWriter.WriteLine("Event`tCount")
    foreach ($row in $eventCountRows)
    {
        $eventCountWriter.WriteLine($row)
    }
}
finally
{
    $eventCountWriter.Dispose()
}

$eventRows = New-Object System.Collections.Generic.List[string]
foreach ($eventRecord in $events)
{
    $eventRows.Add(("{0}`t{1}`t{2}`t{3}" -f
        $eventRecord.StartLine,
        $eventRecord.EndLine,
        (Escape-Tsv $eventRecord.Header),
        (Escape-Tsv $eventRecord.Summary)))
}
$eventPartFiles = @(Write-TextParts $eventRows "StartLine`tEndLine`tEvent`tSelectedFields" $outputDirectory "event_timeline" "tsv" $MaxOutputPartBytes $utf8NoBom)

$signalRows = New-Object System.Collections.Generic.List[string]
foreach ($signal in $signals)
{
    $signalRows.Add(("{0}`t{1}`t{2}`t{3}" -f
        $signal.Line,
        (Escape-Tsv $signal.Event),
        (Escape-Tsv $signal.Signal),
        (Escape-Tsv $signal.Text)))
}
$signalPartFiles = @(Write-TextParts $signalRows "Line`tEvent`tSignal`tText" $outputDirectory "signals" "tsv" $MaxOutputPartBytes $utf8NoBom)

$signalLineNumbers = @($signals | Select-Object -ExpandProperty Line -Unique | Sort-Object)
$signalRanges = New-Object System.Collections.Generic.List[object]
foreach ($signalLine in $signalLineNumbers)
{
    $start = [Math]::Max(1, ([int]$signalLine - $ContextBefore))
    $end = [Math]::Min($lineCount, ([int]$signalLine + $ContextAfter))
    $signalRanges.Add([PSCustomObject]@{ Start = $start; End = $end })
}
$mergedSignalRanges = @(Merge-LineRanges $signalRanges)
$signalContextFiles = @(Write-SourceRangesToParts $inputItem.FullName $mergedSignalRanges $outputDirectory "signal_context" $MaxOutputPartBytes $utf8NoBom)

$requestedRanges = New-Object System.Collections.Generic.List[object]
foreach ($rangeText in $RequestedRange)
{
    if ([string]::IsNullOrWhiteSpace($rangeText))
    {
        continue
    }

    $rangeMatch = [regex]::Match($rangeText, "^\s*(\d+)(?:\s*-\s*(\d+))?\s*$")
    if (-not $rangeMatch.Success)
    {
        throw "Invalid RequestedRange '$rangeText'. Use START-END or a single line number."
    }

    $start = [int]$rangeMatch.Groups[1].Value
    $end = $start
    if ($rangeMatch.Groups[2].Success)
    {
        $end = [int]$rangeMatch.Groups[2].Value
    }

    if ($start -lt 1 -or $end -lt $start)
    {
        throw "Invalid RequestedRange '$rangeText'."
    }
    if ($start -gt $lineCount)
    {
        throw "RequestedRange '$rangeText' starts after the end of the source log ($lineCount lines)."
    }

    $end = [Math]::Min($end, $lineCount)
    $requestedRanges.Add([PSCustomObject]@{ Start = $start; End = $end })
}

$mergedRequestedRanges = @(Merge-LineRanges $requestedRanges)
$requestedRangeFiles = @(Write-SourceRangesToParts $inputItem.FullName $mergedRequestedRanges $outputDirectory "requested_ranges" $MaxOutputPartBytes $utf8NoBom)

$manifestPath = Join-Path $outputDirectory "manifest.txt"
$manifestWriter = New-Object System.IO.StreamWriter -ArgumentList @($manifestPath, $false, $utf8NoBom)
try
{
    $manifestWriter.WriteLine("LARGE LOG EVIDENCE PACKAGE")
    $manifestWriter.WriteLine("ToolVersion: 1")
    $manifestWriter.WriteLine("SourceInput: $InputPath")
    $manifestWriter.WriteLine("SourceFileName: $($inputItem.Name)")
    $manifestWriter.WriteLine("SourceSHA256: $sourceHash")
    $manifestWriter.WriteLine("SourceBytes: $($inputItem.Length)")
    $manifestWriter.WriteLine("SourceLineCount: $lineCount")
    $manifestWriter.WriteLine("EventBlockCount: $($events.Count)")
    $manifestWriter.WriteLine("DistinctEventTypes: $($eventCounts.Count)")
    $manifestWriter.WriteLine("SignalMatchCount: $($signals.Count)")
    $manifestWriter.WriteLine("DistinctSignalLines: $($signalLineNumbers.Count)")
    $manifestWriter.WriteLine("SignalContextBefore: $ContextBefore")
    $manifestWriter.WriteLine("SignalContextAfter: $ContextAfter")
    $manifestWriter.WriteLine("MergedSignalContextRanges: $($mergedSignalRanges.Count)")
    $manifestWriter.WriteLine("MaxOutputPartBytes: $MaxOutputPartBytes")
    $manifestWriter.WriteLine("EventTimelineParts: $($eventPartFiles.Count)")
    $manifestWriter.WriteLine("SignalIndexParts: $($signalPartFiles.Count)")
    $manifestWriter.WriteLine("SignalContextParts: $($signalContextFiles.Count)")
    $manifestWriter.WriteLine("RequestedRangeCount: $($mergedRequestedRanges.Count)")
    $manifestWriter.WriteLine("RequestedRangeParts: $($requestedRangeFiles.Count)")
    $manifestWriter.WriteLine("")
    $manifestWriter.WriteLine("SignalPatterns:")
    foreach ($signalName in $signalPatterns.Keys)
    {
        $manifestWriter.WriteLine("- $signalName = $($signalPatterns[$signalName])")
    }
    $manifestWriter.WriteLine("")
    $manifestWriter.WriteLine("Files:")
    $manifestWriter.WriteLine("- event_counts.tsv")
    foreach ($file in $eventPartFiles)
    {
        $manifestWriter.WriteLine("- $file")
    }
    foreach ($file in $signalPartFiles)
    {
        $manifestWriter.WriteLine("- $file")
    }
    foreach ($file in $signalContextFiles)
    {
        $manifestWriter.WriteLine("- $file")
    }
    foreach ($file in $requestedRangeFiles)
    {
        $manifestWriter.WriteLine("- $file")
    }
}
finally
{
    $manifestWriter.Dispose()
}

Write-Host "Large-log evidence package created."
Write-Host "Source: $($inputItem.FullName)"
Write-Host "SHA256: $sourceHash"
Write-Host "Lines: $lineCount"
Write-Host "Events: $($events.Count)"
Write-Host "Signals: $($signals.Count)"
Write-Host "Output: $outputDirectory"
