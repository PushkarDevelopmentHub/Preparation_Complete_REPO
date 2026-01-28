# GitHub DSA and LeetCode Problem Manager Script
# This script helps you push, merge, and create PRs for your DSA and LeetCode problems

# Define DSA Categories
$categories = @(
    "Sorting",
    "Arrays",
    "Binary Search",
    "Strings",
    "Linked List",
    "Recursion",
    "Bit Manipulation",
    "Interview Problems",
    "Advanced Maths",
    "Stack & Queues",
    "Sliding Window & Two Pointers",
    "Heaps",
    "Greedy Algorithms",
    "Binary Trees",
    "Binary Search Trees",
    "Graphs",
    "Dynamic Programming",
    "Tries",
    "Leetcode Daily Solve"
)

# Function to display menu and get user choice
function Show-Menu {
    param(
        [string]$Title,
        [string[]]$Options
    )
    
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host $Title -ForegroundColor Yellow
    Write-Host "========================================" -ForegroundColor Cyan
    
    for ($i = 0; $i -lt $Options.Count; $i++) {
        Write-Host "$($i + 1). $($Options[$i])" -ForegroundColor Green
    }
    Write-Host ""
}

# Function to get category selection
function Select-Category {
    Show-Menu -Title "Select Problem Category" -Options $categories
    
    $selection = Read-Host "Enter the number of your selection (or 0 to skip)"
    
    if ($selection -eq "0") {
        return "General Update"
    }
    
    $index = [int]$selection - 1
    if ($index -ge 0 -and $index -lt $categories.Count) {
        return $categories[$index]
    } else {
        Write-Host "Invalid selection. Using 'General Update'" -ForegroundColor Red
        return "General Update"
    }
}

# Function to select files
function Select-Files {
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "File Selection" -ForegroundColor Yellow
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "1. All files (.)" -ForegroundColor Green
    Write-Host "2. Specific file(s)" -ForegroundColor Green
    Write-Host "3. Specific folder" -ForegroundColor Green
    Write-Host ""
    
    $choice = Read-Host "Enter your choice (1-3)"
    
    switch ($choice) {
        "1" {
            return "."
        }
        "2" {
            $file = Read-Host "Enter the file path (e.g., Data_Structure_Algorithms/Array/Array.cpp)"
            return $file
        }
        "3" {
            $folder = Read-Host "Enter the folder path (e.g., Data_Structure_Algorithms/Array)"
            return $folder
        }
        default {
            Write-Host "Invalid choice. Using all files (.)" -ForegroundColor Red
            return "."
        }
    }
}

# Function to get commit message
function Get-CommitMessage {
    Write-Host ""
    $category = Select-Category
    Write-Host ""
    
    Write-Host "Enter commit message (or press Enter for auto-generated):" -ForegroundColor Yellow
    $customMessage = Read-Host
    
    if ([string]::IsNullOrWhiteSpace($customMessage)) {
        return "[$category] Solved DSA and LeetCode problems"
    } else {
        return "[$category] $customMessage"
    }
}

# Function to get comment
function Get-Comment {
    Write-Host ""
    Write-Host "Add a comment for your commit (optional, press Enter to skip):" -ForegroundColor Yellow
    $comment = Read-Host
    
    if ([string]::IsNullOrWhiteSpace($comment)) {
        return ""
    } else {
        return $comment
    }
}

# Function to push changes
function Push-Changes {
    param(
        [string]$Files,
        [string]$CommitMessage,
        [string]$Branch,
        [string]$Comment
    )
    
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Pushing Changes" -ForegroundColor Yellow
    Write-Host "========================================" -ForegroundColor Cyan
    
    try {
        Write-Host "Adding files: $Files" -ForegroundColor Cyan
        git add $Files
        
        $fullMessage = $CommitMessage
        if (-not [string]::IsNullOrWhiteSpace($Comment)) {
            $fullMessage = "$CommitMessage`n`nComment: $Comment"
        }
        
        Write-Host "Committing changes..." -ForegroundColor Cyan
        git commit -m "$fullMessage"
        
        Write-Host "Pushing to branch: $Branch" -ForegroundColor Cyan
        git push origin $Branch
        
        Write-Host "✓ Changes pushed successfully!" -ForegroundColor Green
        return $true
    }
    catch {
        Write-Host "✗ Error pushing changes: $_" -ForegroundColor Red
        return $false
    }
}

# Function to create pull request
function Create-PullRequest {
    param(
        [string]$Title,
        [string]$Description
    )
    
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Creating Pull Request" -ForegroundColor Yellow
    Write-Host "========================================" -ForegroundColor Cyan
    
    try {
        # Check if GitHub CLI is installed
        $ghInstalled = & {
            try {
                gh --version | Out-Null
                return $true
            }
            catch {
                return $false
            }
        }
        
        if ($ghInstalled) {
            Write-Host "Using GitHub CLI to create PR..." -ForegroundColor Cyan
            
            $currentBranch = git rev-parse --abbrev-ref HEAD
            Write-Host "Enter target branch (default: DEV):" -ForegroundColor Yellow
            $targetBranch = Read-Host
            if ([string]::IsNullOrWhiteSpace($targetBranch)) {
                $targetBranch = "DEV"
            }
            
            gh pr create --base $targetBranch --head $currentBranch --title $Title --body $Description
            Write-Host "✓ Pull request created successfully!" -ForegroundColor Green
        }
        else {
            Write-Host "GitHub CLI not installed. Here's your PR information:" -ForegroundColor Yellow
            Write-Host ""
            Write-Host "Title: $Title" -ForegroundColor Cyan
            Write-Host "Description: $Description" -ForegroundColor Cyan
            Write-Host ""
            Write-Host "Please create the PR manually on GitHub using this information." -ForegroundColor Yellow
        }
    }
    catch {
        Write-Host "✗ Error creating PR: $_" -ForegroundColor Red
    }
}

# Main Script Execution
function Main {
    Clear-Host
    Write-Host "╔════════════════════════════════════════╗" -ForegroundColor Cyan
    Write-Host "║ GitHub DSA & LeetCode Problem Manager  ║" -ForegroundColor Cyan
    Write-Host "╚════════════════════════════════════════╝" -ForegroundColor Cyan
    Write-Host ""
    
    # Check if we're in a git repository
    $gitCheck = & {
        try {
            git rev-parse --git-dir | Out-Null
            return $true
        }
        catch {
            return $false
        }
    }
    
    if (-not $gitCheck) {
        Write-Host "✗ This directory is not a Git repository!" -ForegroundColor Red
        return
    }
    
    Write-Host "✓ Git repository detected" -ForegroundColor Green
    Write-Host ""
    
    # Step 1: Select files
    $files = Select-Files
    
    # Step 2: Get commit message
    $commitMessage = Get-CommitMessage
    
    # Step 3: Get comment
    $comment = Get-Comment
    
    # Step 4: Get branch
    Write-Host ""
    Write-Host "Enter branch to push to (default: current branch):" -ForegroundColor Yellow
    $branch = Read-Host
    if ([string]::IsNullOrWhiteSpace($branch)) {
        $branch = git rev-parse --abbrev-ref HEAD
    }
    
    # Step 5: Confirm before pushing
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Summary" -ForegroundColor Yellow
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Files to push: $files" -ForegroundColor Green
    Write-Host "Commit message: $commitMessage" -ForegroundColor Green
    Write-Host "Branch: $branch" -ForegroundColor Green
    if (-not [string]::IsNullOrWhiteSpace($comment)) {
        Write-Host "Comment: $comment" -ForegroundColor Green
    }
    Write-Host ""
    
    $confirm = Read-Host "Proceed with push? (y/n)"
    if ($confirm -ne "y") {
        Write-Host "Operation cancelled." -ForegroundColor Yellow
        return
    }
    
    # Step 6: Push changes
    $pushSuccess = Push-Changes -Files $files -CommitMessage $commitMessage -Branch $branch -Comment $comment
    
    # Step 7: Ask if they want to create a PR
    if ($pushSuccess) {
        Write-Host ""
        $createPR = Read-Host "Create a pull request? (y/n)"
        
        if ($createPR -eq "y") {
            $prTitle = $commitMessage.Split("`n")[0]
            $prDescription = "Category: " + $commitMessage
            if (-not [string]::IsNullOrWhiteSpace($comment)) {
                $prDescription += "`n`nComment: $comment"
            }
            
            Create-PullRequest -Title $prTitle -Description $prDescription
        }
    }
    
    Write-Host ""
    Write-Host "Script execution completed!" -ForegroundColor Cyan
    Write-Host ""
}

# Run the main script
Main
