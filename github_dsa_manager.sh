#!/bin/bash

# GitHub DSA and LeetCode Problem Manager

categories=(
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
)

select_category() {
    echo "========================================"
    echo "Select Problem Category"
    echo "========================================"
    for i in "${!categories[@]}"; do
        echo "$((i + 1)). ${categories[$i]}"
    done
    echo ""
    read -p "Enter the number (or 0 to skip): " selection
    
    if [ "$selection" = "0" ]; then
        echo "General Update"
    elif [ "$selection" -ge 1 ] && [ "$selection" -le ${#categories[@]} ]; then
        echo "${categories[$((selection - 1))]}"
    else
        echo "General Update"
    fi
}

select_files() {
    echo "========================================"
    echo "File Selection"
    echo "========================================"
    echo "1. All files (.)"
    echo "2. Choose from repository files (y/n per file, 'a' = All)"
    echo "3. Specific folder"
    echo ""
    read -p "Enter your choice (1-3): " choice

    case $choice in
        1)
            echo "."
            ;;
        2)
            # Gather repository candidate files (common code files)
            mapfile -t repo_files < <(find . -path './.git' -prune -o -type f \( -iname '*.cpp' -o -iname '*.c' -o -iname '*.h' -o -iname '*.hpp' -o -iname '*.py' -o -iname '*.java' -o -iname '*.js' -o -iname '*.md' \) -print)
            if [ ${#repo_files[@]} -eq 0 ]; then
                echo "."
                return
            fi

            selected_list=()
            for f in "${repo_files[@]}"; do
                # normalize path (remove leading ./)
                display_path="$f"
                if [[ "$display_path" == ./* ]]; then
                    display_path="${display_path:2}"
                fi
                while true; do
                    read -p "Send $display_path ? (y/n/a=All): " ans
                    case "$ans" in
                        [Yy])
                            selected_list+=("$display_path")
                            break
                            ;;
                        [Nn])
                            break
                            ;;
                        [Aa])
                            echo "."
                            return
                            ;;
                        *)
                            echo "Please answer y, n, or a"
                            ;;
                    esac
                done
            done

            if [ ${#selected_list[@]} -eq 0 ]; then
                # nothing selected -> default to all
                echo "."
            else
                # join selected files with space
                printf "%s " "${selected_list[@]}"
            fi
            ;;
        3)
            read -p "Enter the folder path (e.g., Data_Structure_Algorithms/Array): " folder
            # Collect files in folder and ask per-file
            if [ -z "$folder" ]; then
                echo "."
                return
            fi
            if [ ! -d "$folder" ]; then
                echo "${folder}" # return whatever user typed to allow existing behavior
                return
            fi

            mapfile -t folder_files < <(find "$folder" -type f \( -iname '*.cpp' -o -iname '*.c' -o -iname '*.h' -o -iname '*.hpp' -o -iname '*.py' -o -iname '*.java' -o -iname '*.js' -o -iname '*.md' \) -print)
            if [ ${#folder_files[@]} -eq 0 ]; then
                echo "$folder"
                return
            fi

            selected_list=()
            for f in "${folder_files[@]}"; do
                display_path="$f"
                if [[ "$display_path" == ./* ]]; then
                    display_path="${display_path:2}"
                fi
                while true; do
                    read -p "Send $display_path ? (y/n/a=All): " ans
                    case "$ans" in
                        [Yy])
                            selected_list+=("$display_path")
                            break
                            ;;
                        [Nn])
                            break
                            ;;
                        [Aa])
                            echo "."
                            return
                            ;;
                        *)
                            echo "Please answer y, n, or a"
                            ;;
                    esac
                done
            done

            if [ ${#selected_list[@]} -eq 0 ]; then
                echo "$folder"
            else
                printf "%s " "${selected_list[@]}"
            fi
            ;;
        *)
            echo "."
            ;;
    esac
}

main() {
    clear
    echo "╔════════════════════════════════════════╗"
    echo "║ GitHub DSA & LeetCode Problem Manager  ║"
    echo "╚════════════════════════════════════════╝"
    echo ""
    
    if ! git rev-parse --git-dir > /dev/null 2>&1; then
        echo "✗ This directory is not a Git repository!"
        exit 1
    fi
    
    echo "✓ Git repository detected"
    echo ""
    
    # Step 1: Select files
    files=$(select_files)
    
    # Step 2: Select category
    category=$(select_category)
    
    # Step 3: Commit message
    echo ""
    read -p "Enter commit message (press Enter for auto-generated): " custom_msg
    if [ -z "$custom_msg" ]; then
        commit_msg="[$category] Solved DSA and LeetCode problems"
    else
        commit_msg="[$category] $custom_msg"
    fi
    
    # Step 4: Comment
    echo ""
    read -p "Add a comment (optional, press Enter to skip): " comment
    
    # Step 5: Branch
    echo ""
    read -p "Enter branch to push (default: current branch): " branch
    if [ -z "$branch" ]; then
        branch=$(git rev-parse --abbrev-ref HEAD)
    fi
    
    # Step 6: Confirm
    echo ""
    echo "========================================"
    echo "Summary"
    echo "========================================"
    echo "Files to push: $files"
    echo "Category: $category"
    echo "Message: $commit_msg"
    [ -n "$comment" ] && echo "Comment: $comment"
    echo "Branch: $branch"
    echo ""
    read -p "Proceed? (y/n): " confirm
    
    if [ "$confirm" != "y" ]; then
        echo "Cancelled."
        exit 0
    fi
    
    # Step 7: Push
    echo ""
    echo "========================================"
    echo "Pushing Changes"
    echo "========================================"
    
    git add $files
    
    if [ -z "$comment" ]; then
        git commit -m "$commit_msg"
    else
        git commit -m "$commit_msg

Comment: $comment"
    fi
    
    git push origin $branch
    
    if [ $? -eq 0 ]; then
        echo "✓ Changes pushed successfully!"
    else
        echo "✗ Error pushing changes"
        exit 1
    fi
    
    # Step 8: PR (optional)
    echo ""
    read -p "Create a pull request? (y/n): " create_pr
    
    if [ "$create_pr" = "y" ]; then
        echo "========================================"
        echo "Creating Pull Request"
        echo "========================================"
        
        if command -v gh &> /dev/null; then
            current=$(git rev-parse --abbrev-ref HEAD)
            read -p "Enter target branch (default: DEV): " target
            target=${target:-DEV}
            
            gh pr create --base "$target" --head "$current" --title "$commit_msg" --body "Category: $commit_msg"
            echo "✓ Pull request created!"
        else
            echo "GitHub CLI not found."
            echo "Title: $commit_msg"
            echo "Description: Category: $commit_msg"
        fi
    fi
    
    echo ""
    echo "Done!"
    echo ""
}

main
