/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include <stack>
#include <queue>
#include <iostream>

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
/*    T first = s.top();
  //  if (count != 0 && s.front() == first) {return data;}
    // Your code here
    if (!s.empty()) { //if stack is not empty
      s.pop();
      T sum = first + sum(s);
      s.push(first);
      return sum;
    }
    else {
      return 0; */


  if(s.empty()) {return 0;} //if empty stack, sum is 0

    T top = s.top(); //track the top
    s.pop(); //remove top/last elemeny
    T total = top + sum(s); //run total of stack with one less element. Type of T to match the stack data
    s.push(top); //replace all popped elements
    return total;



//    return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    /*stack<char> stack;
    int left = 0;
    int right = 0;
    while (!input.empty()) {
      char temp = input.front();
      if (temp == '[') {left++;}
      if (left == 0 || (temp == ']' && right < left)) {right++;}
      input.pop();
    }
    if (left == right) {return true;}
    else {return false;} */
    stack<char> stack;
    int size = input.size();
    int pushes = 0;
    while (!input.empty()) {
      char temp = input.front();
      if (temp == '[' || temp == ']') {
        stack.push(temp);
        pushes++;
      }
      if (stack.size() >= 2) { //have to do this in while loop. if size is greater/equal to 2 then compare
        char top = stack.top();
        stack.pop();
        char bot = stack.top();
        stack.pop();
        if (!(top == ']' && bot == '[')) { //only works if last two elements is a pair
          stack.push(bot);
          stack.push(top);
        }
      }
      input.pop();
    }

    if (size > 0 && pushes == 0) {return false;}
    else if (input.empty() && stack.empty()) {return true;}
    else {return false;}
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
 template <typename T>
 void copynormal(queue<T>& q, queue<T>& q2, int num) {
   for (int i = 0; i < num; i++) {
    if (!q.empty()) {
       T temp = q.front();
       std::cout<<"Pushing to q2: "<<temp<<std::endl;
       q2.push(temp);
       q.pop();
     }
   }
 }

 template <typename T>
 void reverse(queue<T>& q, queue<T>& q2, stack<T> s, int num) {
   for (int i = 0; i < num; i++) {
    if (!q.empty()) {
       T temp = q.front();
       std::cout<<"Pushing to stack: "<<temp<<std::endl;
       s.push(temp);
       q.pop();
     }
   }
   for (int i = 0; i < num; i++) {
     while (!s.empty()) {
       T temp = s.top();
       std::cout<<"Pushing to q2: "<<temp<<std::endl;
       q2.push(temp);
       s.pop();
     }
   }
 }

 template <typename T>
 void filloriginal(queue<T>& q, queue<T>& q2) {
   if (q.empty()) {
     while (!q2.empty()) {
       T temp = q2.front();
       std::cout<<"Pushing to original: "<<temp<<std::endl;
       q.push(temp);
       q2.pop();
     }
   }
 }

template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    copynormal(q,q2,1);
    reverse(q,q2,s,2);
    copynormal(q,q2,3);
    reverse(q,q2,s,4);
    copynormal(q,q2,5);
    reverse(q,q2,s,6);
    filloriginal(q,q2);



/*
    copynormal(2);

    while (size != 0) { //perform scramble until empty
      q2.push(temp); //push first to q2
      q.pop();
      for (int i = 0; i < 2; i++) { //take next 2 onto stack
        temp = q.front();
        s.push(temp);
        q.pop();
        size--;
      }
      while (!s.empty()) { //reverse the order and put onto q2
        temp = s.top();
        q2.push(temp);
        s.pop();
      }
      for (int i = 0; i < 3; i++) {
        temp = q.front();
        q2.push(temp);
        q.pop();
        size--;
      }
      for (int i = 0; i < 4; i++) {
        temp = q.front();
        s.push(temp);
        q.pop();
        size--;
      }
      while (!s.empty()) { //reverse the order and put onto q2
        temp = s.top();
        q2.push(temp);
        s.pop();
      }
      for (int i = 0; i < 5; i++) {
        temp = q.front();
        q2.push(temp);
        q.pop();
      }
      for (int i = 0; i < 6; i++) {
        temp = q.front();
        s.push(temp);
        q.pop();
        size--;
      }
      while (!s.empty()) { //reverse the order and put onto q2
        temp = s.top();
        q2.push(temp);
        s.pop();
      }
    }
    while (!q2.empty()) { //refill original queue with new order
      temp = q2.front();
      q.push(temp);
      q2.pop();
    }
    // Your code here

*/
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    // Your code here


	if(s.empty()) {return true;}
  else {
    T temp = s.top(); //Each recursive run stores its own associated pop from stack
    s.pop();
    bool retval = verifySame(s, q); //run for smaller stack
    if (retval == true && temp == q.front()) {retval = true;}
    else {retval = false;}
    T first = q.front();
    q.pop();
    q.push(first); //cycle the queue
    s.push(temp); //add to stack the original value that we removed for the recursion

    return retval;
  }

}
