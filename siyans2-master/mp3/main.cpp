#include "List.h"
#include <iostream>

using namespace std;

int main() {
  List<unsigned> list;
  List<unsigned> list2;
  for (unsigned i = 0; i < 40; i++) { list.insertBack(i); }
  list2.insertBack(0);
  list2.insertBack(4);
  list2.insertBack(9);
  list2.insertBack(6);
  list2.insertBack(12);
  list2.insertBack(2);
  list2.insertBack(4);
  list2.insertBack(1);
  //List<unsigned>::ListIterator iter = list.begin();
  cout<<"Original list1: "<<endl;
  list.print(cout);
  //cout<<"Original list2: "<<endl;
  //list2.print(cout);
  cout<<" "<<endl;
  //list.merge(list.head_, list2.head_);
  list.reverseNth(14);
  cout<<"New List: "<<endl;
  list.print(cout);
  return 0;
}

/*head_ = newnode;
newnode->prev = head_;
newnode->next = oldnode;
oldnode->prev = newnode;*/
