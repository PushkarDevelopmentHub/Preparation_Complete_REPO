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


//