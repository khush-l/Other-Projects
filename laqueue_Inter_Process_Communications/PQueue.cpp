/*
 * LaQueue
 * 
 * 
 * This is part of a series of labs for the Liberal Arts and Science Academy.
 * The series of labs provides a mockup of an POSIX Operating System
 * referred to as LA(SA)nix or LAnix.
 *  
 * (c) copyright 2018, James Shockey - all rights reserved
 * 
 * */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "PQueue.h"
using namespace std;


/*
 * Class Priority Queue
 */

		
/*
* Insert into Priority Queue
*/
void PQueue::push(void *item, int priority)
{
	node* val = new node;
  val->data=item;
  val->priority=priority;
  if(front == nullptr) {
    front = val;
  }
  else{
    node * temp = front;
    while (temp->link !=nullptr && priority < temp->link->priority) {
      temp = temp->link;
    }
    val->link = temp->link;
    temp->link =val;
  }
}

/*
 * Delete from Priority Queue
 */
void* PQueue::top()
{
	/* Your code here */
  if(front == nullptr){
    return nullptr;
  }
  return front->data;
}
/*
 * Delete from Priority Queue
 */
void PQueue::pop()
{
	/* Your code here */
  if(front->data==nullptr) {
    return;
  }
  front = front->link;
}

/*
 * Print Priority Queue
 */
void PQueue::display()
{

	/* Your code here */
	
	/* Use the following out command for the data */
  node* val = front;
  while(val!=nullptr){
	std::cout<<val->priority<<" "<<(char*)val->data<<std::endl;
  }

}
	