// L8. Level Order Traversal of Binary Tree | BFS | C++ | Java
vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> ans;
    if(root == NULL) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> level;
        for(int i=0; i<size; i++){
            TreeNode* node = q.front();
            q.pop();
            if(node->left != NULL) q.push(node->left);
            if(node->right != NULL) q.push(node->right);
            level.push_back(node->val);
        }
        ans.push_back(level);
    }
    return ans;
}
//TC -> O(N) SC-> O(N)

// L9. Iterative Preorder Traversal in Binary Tree | C++ | Java | Stack
vector<int> PreOrderTraversal(TreeNode* root){
    vector<int> preorder;
    if(root == NULL) return preorder;
    stack<TreeNode*> st;
    st.push(root);
    while(!st.empty()){
        root = st.top();
        st.pop();
        preorder.push_back(root->val);
        if(root->right != NULL) st.push(root->right);
        if(root->left != NULL) st.push(root->left);
    }
    return preorder;
}

TC-> O(N) SC-> O(N)


//L10. iterative Inorder Traversal in Binary Tree | C++ | Java | Stack
vector<int> inorderTraversal(TreeNode* root){
    stack<TreeNode*> st;
    TreeNode* node = root;
    vector<int> inorder;
    while(true){
        if(node != NULL){
            st.push(node);
            node = node->left;
        }else{
            if(st.empty() == true) break;
            node = st.top();
            st.pop();
            inorder.push_back(node->val);
            node = node->right;
        }
    }
    return inorder;
}

TC-> O(N) SC-> O(N)


//L11. Iterative Postorder Traversal using 2 Stack | C++ | Java | Binary Tree
vector<int> postOrderTraversal(TreeNode* root){
    vector<int> postOrder;
    if(root == NULL) return postOrder;
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while(!st1.empty()) {
        root = st1.top();
        st1.pop();
        st2.push(root);
        if(root->left != NULL){
            st1.push(root->left);
        }
        if(root->right != NULL){
            st1.push(root->right);
        }
    }
    while(!st2.empty()){
        postOrder.push_back(st2.top()->val);
        st2.pop();
    }
    return postOrder;
}

//TC-> O(2N) SC-> O(2N)


// L12. Iterative Postorder Traversal using 1 Stack | C++ | Java | Binary Trees






//L14. Maximum Depth in Binary Tree | Height of Binary Tree | C++ | Java
int maxDepth(TreeNode* root){
    if(root == NULL) return 0;
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return max(lh, rh) + 1;
}

TC-> O(N) ,SC-> O(H)


//L15. Check for Balanced Binary Tree | C++ | Java
int isBalancedTree(TreeNode* root) {
    if(root == NULL) return true;
    int lh = maxDepth(root->left);
    int rh= maxDepth(root->right);

    if(abs(rh - lh) > 1) return false;

    bool left = isBalancedTree(root->left);
    bool right = isBalancedTree(root->right);
    if(!left || !right) return false;
    return true;
}
TC-> O(N^2) SC-> O(N)

//2nd Way
int isBalanced(TreeNode* root){
    return dfsHeight(root) != -1;
}
int dfsHeight(TreeNode* root){
    if(root == NULL) return 0;
    int lh = dfsHeight(root->left);
    if(lh == -1) return -1;
    int rh = dfsHeight(root->right);
    if(rh == -1) return -1;
    if(abs(lh - rh) > 1) return -1;
    return max(lh, rh) + 1; 
}
TC-> O(N) SC-> O(H)



// L16. Diameter of Binary Tree | C++ | Java
int height(TreeNode* root, int &diameter){
    if(!root) return 0;
    int lh = height(root->left, diameter);
    int rh = height(root->right, diameter);
    diameter = max(diameter, lh + rh);
    return max(lh, rh) + 1;
}
int diameterOfBinaryTree(TreeNode* root){
    int diameter = 0;
    height(root, diameter);
    return diameter;
}
TC-> O(N) SC-> O(H)



// L17. Maximum Path Sum in Binary Tree | C++ | Java
int maxPathSum(TreeNode* root){
    int maxi = INT_MIN;
    maxPathDown(root, maxi);
    return maxi;
}
int maxPathDown(TreeNode* node, int &maxi){
    if(node == nullptr) return 0;
    int left = max(0, maxPathDown(node->left, maxi));
    int right = max(0, maxPathDown(node->right, maxi));
    maxi = max(maxi, left + right + node->val);
    return max(left, right) + node->val;;
}
TC-> O(N) SC-> O(H)


//L18. Check it two trees are Identical or Not | C++ | Java
bool isSameTree(TreeNode* p, TreeNode* q){
    if(p == NULL || q == NULL) return p == q;
    return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
TC-> O(N) SC-> O(N)


// L19. Zig-Zag or Spiral Traversal in Binary Tree | C++ | Java
vector<vector<int>> zigzagLevelOrder(TreeNode* root){
    vector<vector<int>> result;
    if(root == NULL) return result;
    queue<TreeNode*> q;
    q.push(root);

    bool leftToRight = true;
    while(!q.empty()){
        int size = q.size();
        vector<int> row(size);
        for(int i=0; i<size; i++){
            TreeNode* node = q.front();
            q.pop();
            int index = (leftToRight) ? i : (size-1- i);
            row[index] = node->val;
            if(node->left){
                q.push(node->left);
            }
            if(node->right){
                q.push(node->right);
            }
        }
        leftToRight = !leftToRight;
        result.push_back(row);
    }
    return result;
}

TC-> O(N) SC-> O(N)


//L20. Boundary Traversal in Binary Tree | C++ | Java
bool isLeaf(TreeNode* node){
   return (node->left == NULL && node->right == NULL);
}

void addLeftBoundary(TreeNode* root, vector<int> &res){
    TreeNode* curr = root->left;
    while(curr){
        if(!isLeaf(curr)) res.push_back(curr->val);
        if(curr->left) curr = curr->left;
        else curr = curr->right;
    }
} 
void addRightBoundary(TreeNode* root, vector<int> &res){
    TreeNode* curr = root->right;
    vector<int> temp;
    while(curr) {
         if(!isLeaf(curr)) temp.push_back(curr->val);
         if(curr->right) curr = curr->right;
         else curr = curr->left;
    }
    for(int i=temp.size()-1; i>=0; i--){
        res.push_back(temp[i]);
    }
}
void addLeaves(TreeNode* root, vector<int> &res){
     if(isLeaf(root)){ 
        res.push_back(root->val);
        return;
    }
    if(root->left) addLeaves(root->left, res);
    if(root->right) addLeaves(root->right, res);
}
vector<int> printBoundary(TreeNode* root){
    vector<int> res;
    if(!root) return res;
    if(!isLeaf(root)) res.push_back(root->val);
    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);

    return res;
}

TC-> O(N) SC-> O(H)   


// L21. Vertical Order Traversal of Binary Tree | C++ | Java
vector<vector<int>> verticalTraversal(TreeNode* root){
    map<int, map<int, multiset<int>>> nodes;
    queue<pair<TreeNode*, pair<int, int>>> todo;
    todo.push({root, {0, 0}});
    while(!todo.empty()){
        auto p = todo.front();
        todo.pop();
        TreeNode* node = p.first;
        int x = p.second.first, y = p.second.second;
        nodes[x][y].insert(node->val);

        if(node->left){
            todo.push({node->left, {x-1, y+1}});
        }
        if(node->right){
            todo.push({node->right, {x+1, y+1}});
        }
    }
    vector<vector<int>> ans;
    for(auto p : nodes){
        vector<int> col;
        for(auto q : p.second){
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
        ans.push_back(col);
    }
    return ans;
}

TC-> O(N) SC-> O(N)



//L22. Top View of Binary Tree | C++ | Java
vector<int> topView(Node* root){
    vector<int> ans;
    if(root == nullptr) return ans;
    map<int, int> mpp;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while(!q.empty()){
        auto it = q.front();
        q.pop();
        Node* node = it.first;
        int line = it.second;
        if(mpp.find(line) == mpp.end()) mpp[line] = node->data;
        if(node->left != NULL){
            q.push({node->left, line -1});
        }
        if(node->right != nullptr){
            q.push({node-> right, line +1});
        }
    }
    for(auto it : mp){
        ans.push_back(it.second);
    }
    return ans;
}
TC-> O(N) SC-> O(N)  


//L23. Bottom View of Binary Tree | C++ | Java
vector<int> bottomView(TreeNode* root){
    vector<int> ans;
    if(root ==NULL) return ans;
    map<int, int> mpp;
    queue<pair<Node* , int>> q;
    q.push({root, 0});
    while(!q.empty()){
        auto it = q.front();
        q.pop();
        TreeNode* node = it.first();
        int line = it.second;
        mpp[line] = node->data;

        if(node->left != NULL){
            q.push({node->left, line -1});
        }
        if(node->right != nullptr){
            q.push({node-> right, line +1});
        }
    }
    for(auto it:mpp){
        ans.push_back(it.second);
    }
    return ans;
}


//L24. Right/Left View of Binary Tree | C++ | Java
vector<int> rightSideView(TreeNode* root){
    vector<int> res;
    recursion(root, 0, res);
    return res;
}
void recursion(TreeNode* root, int level, vector<int> &res){
    if(root == NULL) return;
    if(res.size() == level) res.push_back(root->val);
    recursion(root->right, level +1, res);
    recursion(root->left, level +1, res);
}

//Left view
vector<int> leftSideView(TreeNode* root){
    vector<int> res;
    recursion(root, 0, res);
    return res;
}
void recursion(TreeNode* root, int level, vector<int> &res){
    if(root == NULL) return;
    if(res.size() == level) res.push_back(root->val);
    recursion(root->left, level +1, res);
    recursion(root->right, level +1, res);
}

TC-> O(N) SC-> O(N)


//L25. Check for Symmetrical Binary Trees | C++ | Java
bool isSymmetric(TreeNode *root){
    return root == NULL || isSymmetricHelp(root->left, root->right);
}
bool isSymmetricHelp(TreeNode* left, TreeNode* right){
    if(left == NULL || right == NULL) return left == right;

    if(left->val != right->val) return false;
    return isSymmetricHelp(left->left, right->right) && (isSymmetricHelp(left->right, right->left));
}

TC-> O(N) SC-> O(N)


//L26. Print Root to Node Path in Binary Tree | C++ | Java
bool getPath(TreeNode* root, vector<int> &arr, int x){
    if(!root) return false;
    arr.push_back(root->val);
    if(root->val == x) return true;
    if(getPath(root->left, arr, x) || getPath(root->right, arr, x)) return true;

    arr.pop_back();
    return false;
}
vector<int> solve(TreeNode* A, int B){
    vector<int> arr;
    if(A == NULL){
        return arr;
    }
    getPath(A, arr, B);
    return arr;
}
TC-> O(N) SC-> O(N)


// L27. Lowest Common Ancestor in Binary Tree | LCA | C++ | Java
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
     if(root == NULL || root == p || root == q){
        return root;
     }
     TreeNode* left = lowestCommonAncestor(root->left, p, q);
     TreeNode* right = lowestCommonAncestor(root->right, p, q);

     if(left == NULL){
        return right;
     }else if(right == NULL){
        return left;
     }else{
        return root;
     }
}

TC-> O(N) SC-> O(1)


//L28. Maximum Width of Binary Tree | C++ | Java
