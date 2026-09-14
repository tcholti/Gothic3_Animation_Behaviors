@echo off
setlocal

if "%~1"=="" (
    echo Usage: Prepare-Log.cmd ^<path-to-log^>
    echo You can also drag a .log file onto this .cmd file.
    exit /b 2
)

set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..\..") do set "REPO_ROOT=%%~fI"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT_DIR%Prepare-Log.ps1" -InputPath "%~f1" -OutputRoot "%REPO_ROOT%\research\derived" -Force
exit /b %ERRORLEVEL%
