// L4. Reverse a DLL | Multiple Approaches
2 PAss solution 
Node* reverseDDL(Node* head){
  set<Node*> st;
  Node* curr = head;
  while(curr != NULL){
    st.insert(curr->data);
    curr= curr->next;
  }
  curr= head;
  while(curr != nullptr){
    temp->data = st.top();
    st.pop();
    temp = temp->next;
  }
}
TC-> O(2N) sc-> O(n)

//swapping the next and prev pointer of each node
Node* reverseDDL(Node* head){
  if(head==NULL || head->next == nullptr){
    return head;
  }
  Node* prev = nullptr;
  Node* curr = head;
  while(curr != NULL){
    prev = curr->prev;
    curr->prev = curr->next;
    curr->next = prev;
    curr= curr->prev;
  }
  return prev->prev;
}
TC -> O(n) SC-> O(1)

//L5. Add 2 numbers in LinkedList | Dummy Node Approach
TC-> (max(N1, N2)) SC-> O(max(N1, N2))
Node* addTwoNumbers(Node* num1, Node* num2){
  Node* dummyNode = new Node(-1);
  Node* curr = dummyNode;
  Node* temp1 = num1;
  Node* temp2 = num2;
  int carry = 0;
  while(temp1 != NULL || temp2 != NULL){
    int sum = carry;
    if(temp1) sum += temp1->data;
    if(temp2) sum += temp2->data;
    Node* newNode = new Node(sum%10);
    carry = sum/10;
    curr->next = newNode;
    curr = curr->next;

    if(temp1) temp1= temp1->next;
    if(temp2) temp2= temp2->next;
  }

  if(carry){
    Node* newNode = new Node(carry);
    curr->next = newNode;
  }
  return dummyNode->next;
}

//L6. Odd Even Linked List | Multiple Approaches
Node* oddEvenList(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* odd = head;
  Node* even = head->next;
  Node* evenHead = even;

  while(even != NULL && even->next != NULL){
    odd->next = odd->next->next;
    even->next = even->next->next;
    
    odd = odd->next;
    even = even->next;
  }
  odd->next = evenHead;
  return head;
}
TC-> O(n) SC-> O(1)


//L7. Sort a LinkedList of 0's, 1's and 2's | Multiple Approaches
Node* SortList(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* zeroHead = new Node(-1);
  Node* zeroTail = zeroHead;
  Node* oneHead = new Node(-1);
  Node* oneTail = one Head;
  Node* twoHead = new Node(-1); 
  Node* twoTail = twoHead;

  Node* temp = head;
  while(temp != NULL){
    if(temp->data == 0){
      zeroTail->next = temp;
      zeroTail = temp;
    }
    else if(temp->data == 1){
      oneTail->next = temp;
      oneTail = temp;
    }
    else{
      towTail->next = temp;
      twoTail = temp;
    }
    temp = temp->next;
  }

  zeroTail=>next = (oneHead->next) ? oneHead->next : twoHead->next;
  Node* newHead = zeroHead->next;
  delete zeroHead;
  delete oneHead;
  delete twoHead;
  return newHead;
}
TC-> O(N) SC-> O(1)

//L8. Remove Nth Node from the end of the LinkedList | Multiple Approaches
Node* removeKthNode(Node* head, int k){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* fast = head;
  Node* slow = head;
  for(int i=0; i<k; i++){
    fast = fast->next;
  }
  while(fast->next != NULL){
    fast = fast->next;
    slow = slow->next;
  }
  Node* delNode = slow->next;
  slow->next = slow->next->next;
  delete delNode;
  return head;
}
TC-> O(length of LL) SC-> O(1)

//L9. Reverse a LinkedList | Iterative and Recursive
Node* reverseLL(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* prev = NULL;
  Node* temp = head;
  while(temp != NULL){
    Node* front = temp->next;
    temp->next = prev;
    prev = temp;
    temp = front;
  }
  return prev;
}
//recursive
Node* reverseLLinRecursion(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* newHead = reverseLLinRecursion(head->next);
  head->next->next = head;
  head->next = NULL;
  return newHead;
}


//L10. Check if a LinkedList is Palindrome or Not | Multiple Approaches
Node* isPalindrome(Node* head){
  stack<int> st;
  Node* temp = head;
  while(temp != NULL){
    st.push(temp->data);
    temp = temp->next;
  }
  temp = head;
  while(temp != NULL){
    if(temp->data != st.top()){
      return false;
    }
    else{
      st.pop();
      temp = temp->next;
    }
  }
  return true;
}

// Optimal Approach
Node* revereseLinkendList(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* newHead = revereseLinkendList(head->next);
  Node* front = head->next;
  front->next = head;
  head->next = NULL;
  return newHead;
}
bool isPalindrome(Node* head){
  if(head == NULL || head->next == NULL){
    return true;
  }
  Node* slow = head;
  Node* fast = head;
  while(fast != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  Node* newHead = revereseLinkendList(slow->next);
  Node* first = head;
  Node* second = newHead;
  while(second != NULL){
    if(first->data != second->data){
      reverseLinkendList(newHead);
      return false;
    }
    first = first->next;
    second = second->next;
  }
  reverseLinkendList(newHead);
  return true;
}
//TC -> O(n) SC-> O(1)

//L11. Add 1 to a number represented by LinkedList
TC-> O(N) SC->O(N)
int addHelper(Node* temp){
  if(temp == NULL){
    return 1;
  }
  int carry = addHelper(temp->next);
  temp->data += carry;  
  if(temp->data < 10) return 0;
  temp->data = 0;
  return 1;
}
Node* addOne(Node* head){
  int carry = addHelper(head);
  if(carry == 1){
    Node* newNode = new Node(1);
    newNode->next = head;
    head = newNode;
  }
  return head;
}

//L12. Find the intersection point of Y LinkedList
Node* getIntersectionNode(Node* headA, Node* headB){
    map<Node*, int> mp;
    Node* temp = headA;
    while(temp != NULL){
        mp[temp]++;
        temp = temp->next;
    }
    temp = headB;
    while(temp != NULL){
        if(mp.find(temp) != mp.end()) return temp;
        temp = temp->next;
    }
    return NULL;
}
TC -> O(N*M), SC -> O(N)

//2nd way
Node* CollisionPoint(Node* headA, Node* headB, int diff){
    while(diff--){
        headB = headB->next;
    }
    while(headA != NULL && headB != NULL){
        if(headA == headB) return headA;
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
}
Node* getIntersectionNode(Node* headA, Node* headB){
     Node* t1 = headA;
     Node* t2 = headB;
     int N1 = 0, N2 = 0;
     while(t1 != NULL){
         N1++;
         t1 = t1->next;
     }
    while(t2 != NULL){
        N2++;
        t2 = t2->next;
    }
    
    if(N1 < N2){
        return CollisionPoint(headA, headB, N2-N1);
    }else{
        return CollisionPoint(headB, headA, N1-N2);
    }
}

TC-> O(N1+ N2) SC -> O(1)

//Optimal
Node* getIntersectionNode(Node* headA, Node* headB){
    if(headA == NULL || headB == NULL) return NULL;
    Node* temp1 = headA;
    Node* temp2 = headB;
    while(temp1 != temp2){
        temp1 = temp1->next;
        temp2 = temp2->next;

        if(temp1 == temp2) return temp1;
        if(temp1 == NULL) temp1 = headB;
        if(temp2 == NULL) temp2 = headA;
    }
    return temp1;
}
TC-> O(N1 + N2) SC -> O(1)


//L13. Find the middle element of the LinkedList | Multiple Approaches
Node* middleNode(Node* head){
    Node* temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    int middleNode = (count/2) + 1;
    temp = head;
    while(temp != NULL && middleNode > 1){
        temp = temp->next;
        middleNode--;
    }
    return temp;
}
TC -> O(N + N/2) SC -> O(1)

//Optimal - Using Slow and Fast Pointers
Node* middleNode(Node* head){
    Node* slow = head;
    Node* fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
TC -> O(N/2) SC -> O(1)

//L14. Detect a loop or cycle in LinkedList | With proof and Intuition
Node* detechLoop(Node* head){
    map<Node*, int> mp;
    Node* temp = head;
    while(temp != NULL){
        if(mp.find(temp) != mp.end()) return temp;
        mp[temp]++;
        temp = temp->next;
    }
    return NULL;
}
TC -> O(N) SC -> O(N)
//Optimal - Tortoise and Hare Algorithm
Node* detectLoop(Node* head){
    Node* slow = head;
    Node* fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}


//L15. Find the length of the Loop in LinkedList
Node* detectLengthofLoop(Node* head){
 map<Node* int> mp;
 Node* temp = head;
 int timer = 1;
 while(temp != NULL){
  if(mp.find(temp) != mp.end()){
    return timer - mp[temp];
  }
  mp[temp] = timer;
  timer++;
  temp = temp->next;
 }
 return 0;
}
TC -> O(N) SC -> O(N)
//Optimal - Tortoise and Hare Algorithm
int findLength(Node* slow, Node* fast){
  int cnt = 1;
  fast = fast->next;
  while(slow != fast){
    cnt++;
    fast = fast->next;
  }
  return cnt;
}
int detectLengthofLoop(Node* head){
  Node* slow = head;
  Node* fast = head;
  while(fast != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast) return findLength(slow, fast);

  }
  return 0;
}
TC -> O(N) SC -> O(1)


//L16. Delete the middle node of the LinkedList
Node* deleteMiddle(Node* head){
  if(head == NULL || head->next == NULL){
    return NULL;
  }
  Node* slow = head;
  Node* fast = head;
  fast = fast->next->next;
  while(fast != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  Node* delNode = slow->next;
  slow->next = slow->next->next;
  free(delNode);
  return head;
}
TC -> O(N/2) SC -> O(1)

//L17. Find the starting point of the Loop/Cycle in LinkedList | Multiple Approaches
Node* StartingPointofLoop(Node* head){
  map<Node*, int> mp;
  Node* temp = head;
  while(temp != NULL){
    if(mp.find(temp) != mp.end()) return temp;
    mp[temp]++;
    temp = temp->next;
  }
  return NULL;
}
//TC -> O(N) SC -> O(N)
//Optimal - Tortoise and Hare Algorithm
Node* StartingPointofLoop(Node* head){
  Node* slow = head;
  Node* fast = head;
  while(fast != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
    if(slow == fast){
       slow = head;
       while(slow != fast){
        slow = slow->next;
        fast = fast->next;
       }
       return slow;
    }
  }
  return NULL;
}
TC -> O(N) SC -> O(1)


 
//L18. Delete all occurrences of a Key in DLL
Node* deleteAllOccurences(Node* head, int key){
    Node* temp = head;
    while(temp != NULL){
        if(temp->data == key){
            if(temp == head){
                head = head->next;
            }
            Node* nextNode = temp->next;
            Node* prevNode = temp->prev;
            if(nextNode != NULL){
                nextNode->prev = prevNode;
            }
            if(prevNode != NULL){
                prevNode->next = nextNode;
            }
            free(temp);
            temp = nextNode;
        }else{
            temp = temp->next;
        }
    }
    return head;
}
TC -> O(N) SC -> O(1)


//L19. Find all Pairs with given sorted Sum in DLL
vector<pair<int, int>> findPairsWithGivenSum(Node* head, int sum){
    Node* temp1= head;
    set<pair<int, int>> pairs;
    while(temp1 != NULL){
        Node* temp2 = temp1->next;
        while(temp2 != NULL){
            if(temp1->data + temp2->data == sum){
                pairs.insert({temp1->data, temp2->data});
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return pairs;
}
TC-> O(N^2) SC -> O(N)

//2 pointer approach
Node* findTail(Node* head){
    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}
vector<pair<int, int>> findPairsWithGivenSum(Node* head, int sum){
    vector<pair<int, int>> ans;
    if(head == NULL) return ans;
    Node* left = head;
    Node* right = findTail(head);
    while(temp->data < right->data){
        if(temp->data + right->data == sum){
            ans.push_back({temp->data, right->data});
            left = left->next;
            right= right->prev;
        }else if(left->data + right->data < sum){
            left = left->next;
        }else{
            right = right->prev;
        }
    }
    return ans;
}
TC -> O(N) SC -> O(1)


//L20. Remove duplicates from sorted DLL
Node* removeDuplicates(Node* head){
    if(head == NULL) return head;
    Node* temp = head;
    Node* nextNode = temp->next;
    while(temp != NULL && temp->next != NULL){
        while(nextNode != NULL && nextNode->data == temp->data){
            Node* duplicate = nextNode;
            nextNode = nextNode->next;
            free(duplicate);
        }
        temp->next = nextNode;
        if(nextNode != NULL){
            nextNode->prev = temp;
        }
        temp = temp->next;
    }
    return head;
}
TC-> O(N) SC -> O(1)


//L21. Reverse Nodes in K Group Size of LinkedList
Node* findKthNode(Node* head, int k){
    Node* temp = head;
    while(temp != NULL && k > 1){
        temp = temp->next;
        k--;
    }
    return temp;
}
Node* reverseKGroup(Node* head, int k){
    Node* temp = head;
    Node* prevGroupTail = nullptr;
    while(temp != NULL){
    Node* kthNode = findKthNode(temp, k)
    if(kthNode == NULL){
        if(prevGroupTail){
            prevGroupTail->next = temp;
        }
        break;
    }
    Node* nextGroupHead = kthNode->next;
    kthNode->next = NULL;
    reverseLinkedList(temp);
    if(temp == head){
        head = kthNode;
    }else{
        prevGroupTail->next = kthNode;
    }
    prevGroupTail = temp;
    temp = nextGroupHead;
    }
    return head;
}


//L22. Rotate a LinkedList
Node* findNthNode(Node* head, int k){
  int cnt = 1;
  while(head != NULL){
    if(cnt == k) return head;
    cnt++;
    head = head->next;
  }
  return head;
}
Node* rotateRight(Node* head, int k){
  if(head == NULL || head->next == NULL || k == 0){
    return head;
  }
  Node* tail = head;
  int len =1;
  while(tail->next != NULL){
    tail = tail->next;
    len += 1;
  }
  if(k%len == 0) return head;

  k = k%len;

  tail->next= head;
  Node* newLastNode = findNthNode(head, len-k);
  head = newLastNode->next;
  newLastNode->next = NULL;

  return head;
}
TC -> O(2N) SC -> O(1)


//L23. Merge two sorted Linked Lists
Node* mergeTwoLists(Node* list1, Node* list2){
  if(list1 == NULL) return list2;
  if(list2 == NULL) return list1;
  Node<int>* t1 = list1;
  Node<int>* t2 = list2;
  Node<int>* dummyNode = new Node<int>(-1);
  Node<int>* temp = dummyNode;
  while(t1 != NULL && t2 != NULL){
    if(t1->data < t2->data){
      temp->next = t1;
      temp = t1;
      t1 = t1->next;
    }
    else{
      temp->next = t2;
      temp = t2;
      t2 = t2->next;
    }
  }
  if(t1){
    temp->next = t1;
  }else{
    temp->next = t2;
  }

  return dummyNode->next;
}


//L24. Flattening a LinkedList | Multiple Approaches with Dry Run
Node* convertArrayToLinkedListinVERTICAL(vector<int> arr){
   if(arr.size() == 0) return NULL;
  Node* head = new Node(arr[0]);
  Node* temp = head;
  for(int i=1; i<arr.size(); i++){
    Node* newNode = new Node(arr[i]);
    temp->child = newNode;
    temp = temp->child;
  }
  return head;
}
Node* flattenLinkedList(Node* head){
  Node* temp = head;
  vector<int> arr;
  while(temp != NULL){
    Node* t2 = temp;
    while(t2 != NULL){
      arr.push_back(t2->data);
      t2 = t2->child;
    }
    temp = temp->next;
  }
  sort(arr.begin(), arr.end());
  head = convertArrayToLinkedListinVERTICAL(arr);
  return head;
}
TC-> O(N*M) + O(xlogx) + O(x) SC-> O(n*m) where x is the total number of nodes in the linked list


//2nd way
Node* merge(Node* list1, Node* list2){
  Node* dummyNode = new Node(-1);
  Node* res = dummyNode;
  while(list1 != NULL && list2 != NULL){
    if(list1->data < list2->data){
      res->child = list1;
      res = list1;
      list1= list1->child;
    }else{
      res->child = list2;
      res = list2;
      list2= list2->child;
    }
    res->next = NULL;
  }
  if(list1) res->child = list1;
  else res->child = list2;
  if(dummyNode->child) dummyNode->child->next = NULL;
  returun dummyNode->child;
}
Node* flattenLinkedList(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* mergedHead = flattenLinkedList(head->next);
  head = merge(head, mergedHead);

  return head;
}
TC-> O(N*M) SC-> O(N) where N is the number of nodes in the linked list and M is the maximum number of child nodes in any node



//L25. Merge K Sorted Lists | Multiple Approaches
Node* mergeKLists(vector<Node*>& lists) {
    vector<int> arr;
    for(int i=0; i<lists.size(); i++){
      Node* temp = lists[i];
      while(temp != NULL){
        arr.push_back(temp->data);
        temp = temp->next;
      }
    }
    sort(arr.begin(), arr.end());
    Node* head = convertArrayToLinkedList(arr);
    return head;
}
TC-> O(N*k) + Mlog M + M SC-> O(M)+ O(M)

//2nd Way - Using Priority Queue
Node* mergeKList(vector<Node*>& lists) {
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>,
    greater<pair<int, Node*>>> pq;
    for(int i=0; i<lists.size(); i++){
      if(lists[i]){
        pq.push({lists[i]->data, lists[i]});
      }
    }
    Node* dummyNode = new Node(-1);
    Node* temp = dummyNode;
    while(!pq.empty()){
      auto it = pq.top();
      pq.pop();
      if(it.second->next){
        pq.push({it.second->next->data, it.second->next});
      }
      temp->next = it.second;
      temp = temp->next;
    }
    return dummyNode->next;
}

TC-> O(KlogK) + O(N*K*logK) SC= O(k)


//L26. Sort a Linked List | Merge Sort and Brute Force
Node* findMiddleforthisquestion(Node* head){
  Node* slow = head;
  Node* fast = head->next;
  while(fast != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
Node* sortaLinkedList(Node* head){
  if(head == NULL || head->next == NULL){
    return head;
  }
  Node* middle = findMiddleforthisquestion(head);
  Node* rightHead = middle->next;
  middle->next = NULL;
  Node* left = head;

  left = sortaLinkedList(left);
  rightHead = sortaLinkedList(rightHead);
  return mergeTwoLists(left, rightHead);
}
TC-> O(NlogN) SC-> O(1) for recursion stack


//L27. Clone a LinkedList with Next and Random Pointers | Copy List with Random Pointers
Node* CloneLinkedList(Node* head){
  if(head == NULL) return NULL;
  Node* temp = head;
  map<Node*, Node*> mp;
  while(temp != NULL){
    Node* newNode = new Node(temp->data);
    mp[temp] = newNode;
    temp = temp->next;
  }

  temp = head;
  while(temp != NULL){
    Node* copyNode = mp[temp];
    copyNode->next = mp[temp->next];
    copyNode->random = mp[temp->random];
    temp = temp->next;
  }
  return mp[head];
}

TC-> O(2N) SC-> O(N)

//2nd way - Without using extra space
1. Insert Copy Node in between the original nodes
2. connect the random pointer of the copy node
3. connect next poiner of the copy node and return the head of the copy linked list
Node* CloneLinkedList(Node* head){
  if(head == NULL) return NULL;
  Node* temp = head;
  while(temp != NULL){
    Node* copyNode = new Node(temp->data);
    copyNode->next = temp->next;
    temp->next = copyNode;
    temp = copyNode->next;
  }

  temp = head;
  while(temp != NULL){
    Node* copyNode = temp->next;
    if(temp->random){
      copyNode->random = temp->random->next;
    }else{
      copyNode->random = NULL;
    }
    temp = temp->next->next;
  }

  Node* dummyNode = new Node(-1);
  Node* res = dummyNode;
  temp = head;
  while(temp != NULL){
    res->next = temp->next;
    res = res->next;
    temp->next = temp->next->next;
    temp = temp->next;
  }
}

TC-> O(3N) SC-> O(N)


//L28. Design a Browser History | LinkedList Implementation
class Node{
  public:
  string data;
  Node *next;
  Node *back;
  Node() : data[0], next(NULL), baack(NULL);
  Node(string s): data(x), next(NULL), back(NULL);
  Node(string s, Node* next, Node* random) : data(x), next(next), back(random);
};

Class Browser{
  Node* currentPage;
  public:
  Broswer

}