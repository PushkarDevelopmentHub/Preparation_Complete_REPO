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

// L12. Find the intersection point of Y LinkedList
