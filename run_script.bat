@echo offC:\Users\kpush\Documents\GitHubFiles\Preparation_Complete_REPO\push.bat
REM GitHub DSA Manager - Windows Batch Version
REM This script launches the PowerShell version

echo.
echo ╔════════════════════════════════════════╗
echo ║ GitHub DSA & LeetCode Problem Manager  ║
echo ╚════════════════════════════════════════╝
echo.

REM Check if PowerShell script exists
if not exist "github_dsa_manager.ps1" (
    echo Error: github_dsa_manager.ps1 not found in current directory!
    echo Make sure you're in the repository folder.
    pause
    exit /b 1
)

REM Run the PowerShell script
powershell -NoProfile -ExecutionPolicy Bypass -Command "& '.\github_dsa_manager.ps1'"

pause
