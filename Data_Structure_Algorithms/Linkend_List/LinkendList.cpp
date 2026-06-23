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
