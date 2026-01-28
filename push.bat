@echo off
setlocal enabledelayedexpansion

color 0B
cls
echo.
echo ╔════════════════════════════════════════╗
echo ║ GitHub DSA ^& LeetCode Problem Manager  ║
echo ╚════════════════════════════════════════╝
echo.

REM Check if in git repo
git rev-parse --git-dir >nul 2>&1
if errorlevel 1 (
    echo ✗ This directory is not a Git repository!
    pause
    exit /b 1
)

echo ✓ Git repository detected
echo.

REM Step 1: File Selection
echo ========================================
echo File Selection
echo ========================================
echo 1. All files (.)
echo 2. Specific file
echo 3. Specific folder
echo.
set /p file_choice="Enter your choice (1-3): "

if "%file_choice%"=="1" set files=.
if "%file_choice%"=="2" (
    set /p files="Enter the file path: "
) else if "%file_choice%"=="3" (
    set /p files="Enter the folder path: "
) else (
    set files=.
)

REM Step 2: Category Selection
echo.
echo ========================================
echo Select Problem Category
echo ========================================
echo 1. Sorting
echo 2. Arrays
echo 3. Binary Search
echo 4. Strings
echo 5. Linked List
echo 6. Recursion
echo 7. Bit Manipulation
echo 8. Interview Problems
echo 9. Advanced Maths
echo 10. Stack ^& Queues
echo 11. Sliding Window ^& Two Pointers
echo 12. Heaps
echo 13. Greedy Algorithms
echo 14. Binary Trees
echo 15. Binary Search Trees
echo 16. Graphs
echo 17. Dynamic Programming
echo 18. Tries
echo 19. Leetcode Daily Solve
echo 0. Skip
echo.
set /p cat_choice="Enter the number (or 0 to skip): "

if "%cat_choice%"=="1" set category=Sorting
if "%cat_choice%"=="2" set category=Arrays
if "%cat_choice%"=="3" set category=Binary Search
if "%cat_choice%"=="4" set category=Strings
if "%cat_choice%"=="5" set category=Linked List
if "%cat_choice%"=="6" set category=Recursion
if "%cat_choice%"=="7" set category=Bit Manipulation
if "%cat_choice%"=="8" set category=Interview Problems
if "%cat_choice%"=="9" set category=Advanced Maths
if "%cat_choice%"=="10" set category=Stack ^& Queues
if "%cat_choice%"=="11" set category=Sliding Window ^& Two Pointers
if "%cat_choice%"=="12" set category=Heaps
if "%cat_choice%"=="13" set category=Greedy Algorithms
if "%cat_choice%"=="14" set category=Binary Trees
if "%cat_choice%"=="15" set category=Binary Search Trees
if "%cat_choice%"=="16" set category=Graphs
if "%cat_choice%"=="17" set category=Dynamic Programming
if "%cat_choice%"=="18" set category=Tries
if "%cat_choice%"=="19" set category=Leetcode Daily Solve
if "%cat_choice%"=="0" set category=General Update

REM Step 3: Commit Message
echo.
set /p custom_msg="Enter commit message (press Enter for auto): "

if "%custom_msg%"=="" (
    set commit_msg=[%category%] Solved DSA and LeetCode problems
) else (
    set commit_msg=[%category%] %custom_msg%
)

REM Step 4: Comment
echo.
set /p comment="Add a comment (optional, press Enter to skip): "

REM Step 5: Branch
echo.
for /f "tokens=*" %%i in ('git rev-parse --abbrev-ref HEAD') do set current_branch=%%i
set /p branch="Enter branch to push (default: %current_branch%): "

if "%branch%"=="" set branch=%current_branch%

REM Step 6: Confirm
echo.
echo ========================================
echo Summary
echo ========================================
echo Files to push: %files%
echo Category: %category%
echo Message: %commit_msg%
if not "%comment%"=="" echo Comment: %comment%
echo Branch: %branch%
echo.

set /p confirm="Proceed? (y/n): "

if not "%confirm%"=="y" (
    echo Cancelled.
    exit /b 0
)

REM Step 7: Push
echo.
echo ========================================
echo Pushing Changes
echo ========================================

git add %files%

if "%comment%"=="" (
    git commit -m "%commit_msg%"
) else (
    git commit -m "%commit_msg%

Comment: %comment%"
)

git push origin %branch%

if errorlevel 1 (
    echo ✗ Error pushing changes
    pause
    exit /b 1
) else (
    echo ✓ Changes pushed successfully!
)

REM Step 8: PR (optional)
echo.
set /p create_pr="Create a pull request? (y/n): "

if "%create_pr%"=="y" (
    echo ========================================
    echo Creating Pull Request
    echo ========================================
    
    where gh >nul 2>&1
    if errorlevel 1 (
        echo GitHub CLI not found.
        echo Title: %commit_msg%
        echo Description: Category: %commit_msg%
    ) else (
        set /p target="Enter target branch (default: DEV): "
        if "%target%"=="" set target=DEV
        
        gh pr create --base %target% --head %branch% --title "%commit_msg%" --body "Category: %commit_msg%"
        echo ✓ Pull request created!
    )
)

echo.
echo Done!
echo.
pause
