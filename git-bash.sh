#!/bin/bash

echo "========= DSA GITHUB AUTOMATION ========="

# -----------------------------
# FILE SELECTION
# -----------------------------

echo "Choose commit type:"
echo "1) Commit ALL files"
echo "2) Select files manually"
echo "3) Commit only staged files"

read -p "Enter option (1/2/3): " option

if [ "$option" == "1" ]; then
    git add .

elif [ "$option" == "2" ]; then
    echo "Select files you want to commit:"
    git status
    echo ""
    echo "Enter file names separated by space:"
    read files
    git add $files

elif [ "$option" == "3" ]; then
    echo "Using already staged files..."
else
    echo "Invalid option"
    exit 1
fi

# -----------------------------
# TOPIC SELECTION
# -----------------------------

topics=(
"Sorting"
"Arrays"
"Binary Search"
"Strings"
"Linked List"
"Recursion"
"Bit Manipulation"
"Interview Problems"
"Advanced Maths"
"Stack & Queues"
"Sliding Window & Two Pointers"
"Heaps"
"Greedy Algorithms"
"Binary Trees"
"Binary Search Trees"
"Graphs"
"Dynamic Programming"
"Tries"
"Leetcode Daily Solve"
"Custom"
)

echo ""
echo "Select Commit Topic:"

for i in "${!topics[@]}"; do
    echo "$((i+1))) ${topics[$i]}"
done

read -p "Enter number: " topic_num

topic=${topics[$((topic_num-1))]}

if [ "$topic" == "Custom" ]; then
    read -p "Enter custom topic: " topic
fi

# -----------------------------
# COMMIT MESSAGE
# -----------------------------

echo ""
read -p "Enter commit description: " desc

commit_msg="[$topic] $desc"

git commit -m "$commit_msg"

echo ""
echo "Committed Successfully ✅"

# -----------------------------
# PUSH
# -----------------------------

current_branch=$(git branch --show-current)

echo "Pushing to origin/$current_branch..."
git push origin "$current_branch"

echo "Push Complete 🚀"

# -----------------------------
# CREATE / MERGE PR
# -----------------------------

echo ""
echo "Checking for existing PR from this branch..."
existing_pr=$(gh pr list --head "$current_branch" --state open --json number,title,url --jq '.[0]')

if [ -n "$existing_pr" ]; then
    echo "⚠️ Existing PR found:"
    echo "$existing_pr" | jq
    echo ""
    read -p "Do you want to MERGE this existing PR? (y/n): " merge_existing_choice
    if [ "$merge_existing_choice" == "y" ]; then
        gh pr merge --auto --merge "$current_branch"
        echo "✅ Existing PR Merged 🎉"
    else
        echo "Skipping merge of existing PR."
    fi
else
    read -p "Do you want to create a new PR? (y/n): " pr_choice
    if [ "$pr_choice" == "y" ]; then

        echo ""
        echo "Fetching remote branches..."
        git fetch --quiet

        branches=($(git branch -r | grep -v HEAD | sed 's/origin\///'))

        echo ""
        echo "Select BASE branch:"

        for i in "${!branches[@]}"; do
            echo "$((i+1))) ${branches[$i]}"
        done

        echo ""
        read -p "Enter number: " branch_num

        base=${branches[$((branch_num-1))]}

        if [ -z "$base" ]; then
            echo "❌ Invalid selection!"
            exit 1
        fi

        echo ""
        echo "Creating PR: $base <- $current_branch"

        if gh pr create \
            --base "$base" \
            --head "$current_branch" \
            --title "$commit_msg" \
            --body "Automated PR via DSA script"; then

            echo "✅ PR Created Successfully"
        else
            echo "❌ PR Creation Failed!"
            exit 1
        fi

        # -----------------------------
        # MERGE NEW PR
        # -----------------------------

        read -p "Do you want to MERGE the PR? (y/n): " merge_choice
        if [ "$merge_choice" == "y" ]; then

            gh pr merge --auto --merge
            echo "PR Merged 🎉"
        fi
    fi
fi

# -----------------------------
# PULL FROM SELECTED BRANCH
# -----------------------------

echo ""
read -p "Do you want to pull latest changes from a branch? (y/n): " pull_choice

if [ "$pull_choice" == "y" ]; then
    echo ""
    echo "Fetching remote branches..."
    git fetch --quiet

    pull_branches=($(git branch -r | grep -v HEAD | sed 's/origin\///'))

    echo ""
    echo "Select branch to pull from:"

    for i in "${!pull_branches[@]}"; do
        echo "$((i+1))) ${pull_branches[$i]}"
    done

    echo ""
    read -p "Enter number: " pull_num

    pull_branch=${pull_branches[$((pull_num-1))]}

    if [ -z "$pull_branch" ]; then
        echo "❌ Invalid branch selection"
        exit 1
    fi

    echo ""
    echo "Pulling from origin/$pull_branch with --no-rebase..."
    git pull origin "$pull_branch" --no-rebase

    echo "✅ Pull completed"
fi

echo ""
echo "========= DONE ========="
