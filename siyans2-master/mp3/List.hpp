/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include "List.h"
#include <stack>
#include <iostream>
/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* temp = head_;
  while(temp != NULL) {
    ListNode* next = temp->next;
    delete temp;
    temp = next;
  }
  head_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (head_ == NULL && tail_ == NULL) { //empty list case
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_++;
  }
  else { //non-empty list
    ListNode* oldnode = head_;
    ListNode* newnode = new ListNode(ndata);
    head_ = newnode;
    newnode->prev = head_;
    newnode->next = oldnode;
    oldnode->prev = newnode;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T> //TODO prints infinitely the last num. tail assigned to itself?
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (head_ == NULL && tail_ == NULL) { //empty list case
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_++;
  }
  else { //non-empty list
  ListNode* oldnode = tail_;
  ListNode* newnode = new ListNode(ndata);
  tail_ = newnode;
  newnode->prev = oldnode;
  //newnode->next = tail_;
  oldnode->next = newnode;
  length_++;
}
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
 template <typename T>
 void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
   ListNode* start = startPoint;
   for (int i = 0; i <this->size(); i++) {
     ListNode* temp = start->prev;
     start->prev = start->next;
     start->next = temp;
     start = start->prev; //go "forward" by going backward in reverse order
 }
 head_ = endPoint;
 tail_ = startPoint;
  for (int i = 0; i < this->size()-1; i++) {
   endPoint=endPoint->next;
 }
 endPoint->next = NULL;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  /* NOTE:
  Need to save the outer two numbers to switch their info
  if first loop, reassign head
//TODO TEST WITH EVEN/ODD LISTS AND DIFF NUMS
  */
  int timestorun = (this->size() / n);
  int leftover = (this->size() % n) + 0;
  ListNode* farnode = head_;
  ListNode* start = head_;
  ListNode* truestart = head_;
  for (int i = 0; i < timestorun; i++) {
    if (i == 0 ) {
     //<<"Running first loop"<<endl;
    for (int i = 0; i < n-1; i++) { //move farnode to last node that will be reversed
      farnode=farnode->next;
    }
    //FARNODE NOW POINTS TO OLD RIGHT NEW LEFT NODE
    for (int i = 0; i < n; i++) {
      ListNode* temp = start->prev;
      start->prev = start->next;
      start->next = temp;
      start = start->prev; //go "forward" by going backward in reverse order
  }
    head_ = farnode; //if first iteration, make head point to new first node
    farnode->prev = NULL; //DO FOR FIRST LOOP ONLY
    start->prev = truestart;
    truestart->next = start;
}
//--------------------------------------------MIDDLE ITERATIONS------------------------------------------
  else {
     //<<"Running normal loop"<<endl;
    farnode = start;
    truestart = start;
    ListNode* prevnode = start->prev;
    ListNode* temp = start->prev;


    for (int i = 0; i < n-1; i++) { //move farnode to last node that will be reversed
      farnode=farnode->next;
    }
    //FARNODE NOW POINTS TO OLD RIGHT NEW LEFT NODE
    for (int i = 0; i < n; i++) {
      temp = start->prev;
      start->prev = start->next;
      start->next = temp;
      if (start->prev != NULL)
        start = start->prev; //go "forward" by going backward in reverse order
  }
    prevnode->next = farnode;
    farnode->prev = prevnode;
     //<<"prevnode: "<<prevnode->data<<endl;
     //<<"farnode: "<<farnode->data<<endl;
     //<<"start: "<<start->data<<endl;
     //<<"truestart: "<<truestart->data<<endl;
    if (start->prev != NULL)
      start->prev = truestart; //invalid write size 8
    if (truestart->next != NULL)
      truestart->next = start;

}
}
//FINAL iteration
   //<<start->data<<endl;
  if (leftover == 0) {tail_ = truestart;
  truestart->next = NULL;}
  if (leftover > 1) {
     //<<"Running last loop"<<endl;

      farnode = start;
      truestart = start;
      ListNode* prevnode = start->prev;

      for (int i = 0; i < leftover-1; i++) { //move farnode to last node that will be reversed
        farnode=farnode->next;
      }

      //FARNODE NOW POINTS TO OLD RIGHT NEW LEFT NODE
      for (int i = 0; i < leftover; i++) {
        ListNode* temp = start->prev;
        start->prev = start->next;
        start->next = temp;
        if (start->prev == NULL) {
          start->prev = prevnode;
          prevnode->next = start;
          tail_ = start;
          truestart->next = NULL;
        }
        else {start = start->prev;} //go "forward" by going backward in reverse order
        }
        cout<<"TAIL POINTS TO: "<<tail_->data<<endl;
    }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {

  /// @todo Graded in MP3.1
  ListNode* start = head_;
  ListNode* end = tail_;
  while (start!= tail_->prev) {
    start=start->next; //ignore next node
    ListNode* nextinorder = start->next;
    //cout<<nextinorder->data<<endl;
    placeBack(start);
    if (nextinorder->next == tail_ || true) {start = nextinorder;} //set start to the next element in original order
  }
}

template <typename T>
void List<T>::placeBack(ListNode* node) {
  ListNode* before = node->prev;
  ListNode* after = node->next;
  //if (after->next == NULL) {cout<<"afters next is null"<<endl;}
  //std::cout << "before and after: " <<before->data<<after->data<< '\n';
  ListNode* oldlast = tail_;
  oldlast->next = node;
  node->next = NULL;
  node->prev = oldlast;
  tail_ = node;
  before->next = after;
  if (after != NULL) {after->prev = before;}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  for (int i = 0; i < splitPoint-1; i++) {
    start = start->next;
  }
  ListNode* newlister = start->next;
  start->next = NULL;
  newlister->prev = NULL;
  return newlister;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  //TODO insert into helper function (watch edge cases!)
  // Go thru first list, and find where to insert. Then call insertinto
  //NOTE NOTE NOTE NOTE NOTE REMEMBER TO PRIVATE FUNCS AGAIN NOTE NOTE NOTE NOTE NOTE
  ListNode* curr = first;
  ListNode* tocheck = second;
  while (tocheck != NULL) { //iterate
    //cout<<"looking to insert: "<<tocheck->data<<endl;
    if (tocheck->data < curr->data) {
      ListNode* nextup = tocheck->next;
      insertInto(curr->prev, curr, tocheck); //successfully inserts no matter what
      tocheck = nextup;
      //cout<<"Insert good, now looking at: "<<tocheck->data<<endl;
    }
    else {
      if (curr->next != NULL)
        curr = curr->next;
      else { //last element in first list, append rest of second
        curr->next = tocheck;
        tocheck->prev = curr;
        //need to set tail;
        while (curr->next != NULL) {
          curr = curr->next;
        }
        tail_ = curr;
        break;
      }
    }
  }
  return head_;
}


template <typename T>
void List<T>::insertInto(ListNode* insertafter, ListNode* insertbefore, ListNode* toinsert) {
  //NOTE toinsert is always the first node of second list, so treat accordingly
  if (head_ == insertbefore) { //insert as new first node
    //Stuff for first list
    head_ = toinsert;
    toinsert->prev = NULL;
    toinsert->next = insertbefore;
    insertbefore->prev = toinsert;
    //Stuff for second list

  }
  else if (tail_ == insertafter) { //insert as new last node
    //Stuff for first list
    tail_ = toinsert;
    toinsert->next = NULL;
    toinsert->prev = insertafter;
    insertafter->next = toinsert;
    //Stuff for second list

  }
  else { // middle node swap
    //Stuff for first list
    insertafter->next = toinsert;
    toinsert->next = insertbefore;
    insertbefore->prev = toinsert;
    toinsert->prev = insertafter;
    //Stuff for second list

  }

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.

 Base Case: A list of size 1 is sorted. Return.
Recursive Case:
Split the current list into two smaller, more manageable parts
Sort the two halves (this should be a recursive call)
Merge the two sorted halves back together into a single list
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1) {return head_;}
  List<T> second = split(chainLength/2); //returns second half
  sort();
  second.sort();
  mergeWith(second);
  return head_;
}
