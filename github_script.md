#!/bin/bash

# GitHub Script for Managing DSA and LeetCode Problems

# Function to push changes to GitHub

push_changes() {
git add $1
git commit -m "$2"
git push origin $3
}

# Function to merge branches

merge_branches() {
git checkout $1
git merge $2
}

# Function to create a pull request

create_pull_request() {
gh pr create --base $1 --head $2 --title "$3" --body "$4"
}

# Main script execution

# Check if GitHub CLI is installed

if ! command -v gh &> /dev/null
then
echo "GitHub CLI could not be found. Please install it to use this script."
exit
fi

# User inputs

read -p "Enter the file(s) to send (or . for all files): " files_to_send
read -p "Enter commit message: " commit_message
read -p "Enter branch to push to: " push_branch
read -p "Enter target branch for merge: " target_branch
read -p "Enter source branch to merge: " source_branch
read -p "Enter title for pull request: " pr_title
read -p "Enter body for pull request: " pr_body

# Push changes

push_changes "$files_to_send" "$commit_message" "$push_branch"

# Merge branches

merge_branches "$target_branch" "$source_branch"

# Create pull request

create_pull_request "$target_branch" "$source_branch" "$pr_title" "$pr_body"

echo "Script executed successfully!"
