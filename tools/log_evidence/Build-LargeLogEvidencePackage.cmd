@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..\..") do set "REPO_ROOT=%%~fI"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT_DIR%Build-LargeLogEvidencePackage.ps1" -OutputRoot "%REPO_ROOT%\research\derived" %*
exit /b %ERRORLEVEL%
