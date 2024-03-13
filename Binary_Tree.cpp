/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it 
 * tests
 */

 
#include <iostream>
#include <cstdlib>
#include "BSTree.h"

using namespace std;


 
/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */
 
 
void BST::find(int item_key, node **prnt, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *prnt = NULL;
        return;
    }
    if (item_key == root->key_value)
    {
        *loc = root;
        *prnt = NULL;
        return;
    }
    if (item_key < root->key_value)
        ptr = root->p_left;
    else
        ptr = root->p_right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item_key == ptr->key_value)
        {
            *loc = ptr;
            *prnt = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item_key < ptr->key_value)
            ptr = ptr->p_left;
	else
	    ptr = ptr->p_right;
    }
    *loc = NULL;
    *prnt = ptrsave;
}

bool BST::keyExists(node *curr, int key)
{
  if (curr == nullptr)
    return false;
  if (key==curr->key_value)
    return true;
  if (key < curr->key_value)
    return keyExists(curr->p_left,key);
  else
    return keyExists(curr->p_right,key);
}
 
/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
    if (tree == nullptr) //we are at root
    {
      root=newnode;
        // a single node for root to point to,
        //    with all the data in it.
    }
    else if (keyExists(tree,newnode->key_value))  //there is already a node with our key value
    {
        return;
    }
    else if (newnode->key_value < tree->key_value) //(the new node is less than the current node)
    {
        if (tree->p_left !=nullptr) //(see if something is already a child on the left)
        {
            // if so, the recurse insert at this subtree 	
          insert(tree->p_left, newnode);
      	}
      	else
      	{
            // otherwise the new node goes here as a leaf (ie no children)
            tree->p_left = newnode;
        }
    }
    else  // it must be to the right
    {
        if (tree->p_right !=nullptr)// (is there already a child on right?)
        {
             // if so, the recurse insert at this subtree 
          insert(tree->p_right, newnode);
        }
        else
        {
            // otherwise the new node goes here as a leaf (ie no children)
          tree->p_right = newnode;
        }	
    }
}
 
/*
 * Delete Element from the tree
 */
void BST::remove(int item)
{
    node *parent = nullptr;
    node *location = nullptr;
    if (root == nullptr)
    {
        cout<<"Tree empty"<<endl;
        return;
    }
    find(item, &parent, &location);
    if (location == nullptr)
    {
        cout<<"Item not present in tree"<<endl;
        return;
    }
    if (location->p_left == nullptr && location->p_right == nullptr) //(there is no child on left or right)
        case_0(parent,location);
    else if (location->p_left != nullptr && location->p_right==nullptr)  //(there is one child on left only)
    {
        case_1(parent,location);
    }
  else if (location->p_left == nullptr && location->p_right!=nullptr) //(there is one child on right only)
  {
        case_1(parent,location);
  }
  else if (location->p_left != nullptr && location->p_right !=nullptr) //(there are childred on left and right)
  {
        case_2(parent,location);
  }
    delete location;
}
 
/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(node *prnt, node *loc )
{
    if (prnt == root) //(we are at the root)
    {
        //update the root
      root=nullptr;
    }
    else
    {
      // otherwise simply remove node
      if (prnt->p_left ==loc)
        prnt->p_left = nullptr;
      else
        prnt->p_right = nullptr;
    }
}
 
/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(node *prnt, node *loc)
{
    node *child;
    if (loc->p_left != nullptr)//(the child is on the left?)
    {
        //point left
      child = loc->p_left;
    }
    else  // must be the right side has child
    {
      child=loc->p_right;
    }
        // point right
    if (loc==root) //(we are at the root handle specialy)
    {
       // update the root
      root = child;
    }
    else
    {
      if (prnt->p_left == loc) //(the node is left child of parent)
      {
            //promote the left
        prnt->p_left = child;
      }
      else // the node is right of parent
      {
        //    promote right
        prnt->p_right=child;
      }
    }
}
 
/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(node *prnt, node *loc)
{
  node *succesor = loc->p_right;
  
    // temporary pointers for node we are manipulating

    // Find successor: Step to the right child
    // Find the min of the subtree on parent's right
  while(succesor->p_left!= nullptr) {
    loc=succesor;
    succesor=succesor->p_left;
  }
    //if (found node has no children)
  if (succesor->p_left == nullptr && succesor->p_right == nullptr)
  {
      // Replace the target node with the successor node
    loc->key_value = succesor->key_value;
    case_0(loc, succesor);
  }
    else
  {
        // Temporarily remove the successor node by replacing it with
        // its right child, we will replace the node we are removing
        // with the successor we just removed.
    case_1(loc, succesor);
  }
        
    if (loc==root)//(we are at root)
    {
        //then update root
      root=succesor;
    }
    else
    {
        // Insert the successor node where the target node we
        //   are removing is located
      if (prnt->p_left == loc)
      {
        prnt->p_left = succesor;
      }
      else
      {
        prnt->p_right = succesor;
      }
    }
    // then update the successor child pointers to reflect the old 
    //     target's child pointers.
  succesor->p_left = loc->p_left;
  succesor->p_right = loc->p_right;
}
 

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->p_right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:  ";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
	}
        cout<<ptr->key_value;
        display(ptr->p_left, level+1);
    }
}

