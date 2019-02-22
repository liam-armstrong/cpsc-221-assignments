#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  clear();
  delete head_;
  head_ = NULL;
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  Node * n = new Node(ndata);
  head_->prev->next = n;
  n->prev = head_->prev;
  head_->prev = n;
  n->next = head_;
  length_++;
}

/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length. 
 */
void Chain::moveBack(int startPos, int len, int dist){
  if(startPos + len - 1 + dist > length_){
    dist = length_ - startPos - len + 1;
  }
  Node * start = walk(head_, startPos);
  Node * end = walk(head_, startPos+len-1);
  start->prev->next = end->next;
  end->next->prev = start->prev;
  Node * ins = walk(start->prev, dist);
  start->prev = ins;
  end->next = ins->next;
  ins->next->prev = end;
  ins->next = start;
}

/**
 * Rolls the current Chain by k nodes: reorders the current list
 * so that the first k nodes are the (n-k+1)th, (n-k+2)th, ... , nth
 * nodes of the original list followed by the 1st, 2nd, ..., (n-k)th
 * nodes of the original list where n is the length.
 */
void Chain::roll(int k){
  Node * ins = walk(head_, (length_ - k + 1));
  head_->prev->next = head_->next;
  head_->next->prev = head_->prev;
  ins->prev->next = head_;
  head_->prev = ins->prev;
  head_->next = ins;
  ins->prev = head_;
}

/**
 * Modifies the current chain by reversing the sequence
 * of nodes from pos1 up to and including pos2. You may
 * assume that pos1 and pos2 exist in the given chain,
 * and pos1 <= pos2.
 * The positions are 1-based.
 */
void Chain::reverseSub(int pos1, int pos2){
  for(int i = (pos2-pos1); i >= 0; i--){
    moveBack(pos1, 1, i);
  }
}

/*
* Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  if(head_->next->data.width() != other.head_->next->data.width() || head_->next->data.height() != other.head_->next->data.height()){
    cout << "Block sizes differ." << endl;
    return;
  }

  Node *curr = head_;
  Node *nxt;

  do{
    nxt = curr->next;
    curr->next = other.head_->next;
    curr->next->prev = curr;

    curr->next->next->prev = other.head_;
    other.head_->next = curr->next->next;

    curr->next->next = nxt;
    nxt->prev = curr->next;
    curr = nxt;

    other.length_--;
    length_++;
  } while(!(other.length_ == 1) && curr != head_);
  
  if(!(other.length_ == 0)){
    head_->prev->next = other.head_->next;
    other.head_->next->prev = head_->prev;

    other.head_->prev->next = head_;
    head_->prev = other.head_->prev;

    length_ += other.length_;
    other.length_ = 0;
  }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  Node * curr = head_->next;
  Node * nxt;
  while(curr != head_){
    nxt = curr->next;
    delete curr;
    curr = nxt;
  }
  length_ = 0;
  head_->next = head_;
  head_->prev = head_;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  clear();
  Node * curr = other.head_->next;
  while(curr != other.head_){
    Block * b = new Block(curr->data);
    insertBack(*b);
    curr = curr->next;
  }
  width_ = other.width_;
  height_ = other.height_;
}
