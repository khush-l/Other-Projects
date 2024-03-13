
#include "AVLTree.h"
#include <iostream>

AVLTree::AVLTree()
{
	root = NULL;
}

AVLTree::~AVLTree()
{
}

struct node* AVLTree::get_node(int val)
{  
	struct node* new_node = new node;  
	new_node->left = NULL; 
	new_node->right = NULL;  
	new_node->key_value = val;  
	new_node->height = 1;			//Initial height of node is 1  
	return new_node;  
} 

int AVLTree::get_height(struct node* tree)
{  
   if(!tree)  
     return 0;  
   else  
     return tree->height;  
 }
 
int AVLTree::get_balance(struct node* tree)
{  
   if(!tree)  
     return 0;  
   return (get_height(tree->left) - get_height(tree->right));  
}
  
int AVLTree::max(int a, int b)
{  
   return (a > b) ? a : b;  
}
 
struct node* AVLTree::left_rotate(struct node* tree)
{  
   struct node* right = tree->right;  
   struct node* left = right->left;  
   //perform rotation  
   right->left = tree;  
   tree->right = left;  
 
   tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;  
   right->height = max(HEIGHT(right->left), HEIGHT(right->right)) + 1;  
   //return new tree  
   return right;  
 }


struct node* AVLTree::right_rotate(struct node* tree)
{  
   struct node* left = tree->left;  
   struct node* right = left->right;  
   //perform rotation  
   left ->right = tree;
   tree->left = right;
    //** <Your code here >
    tree->height = max(get_height(tree->left),HEIGHT(tree->right))+1;
  left->height = max(get_height(left->left), HEIGHT(left->right))+1;
   //return new tree  
   return left;  
 }  
 
 
struct node* AVLTree::insert(struct node* tree, int val)
{  
     //** <Your code here >
  if(tree==nullptr) {
    return get_node(val);
  }
  else if(val>tree->key_value) {
    tree->right = insert(tree->right,val);
  }
  else if (val<tree->key_value) {
    tree->left = insert(tree->left,val);
  }
  else{
    return tree;
  }
   //normal insertion  
   //update height of tree  
  tree->height=max(get_height(tree->left), get_height(tree->right))+1;
  int balance = get_balance(tree);
	//get_balance_tree(tree);

   //check for balancing  
   //left-left case  
   if(balance > 1 && tree->left->key_value < val){  

    //** <Your code here >

     tree->left = left_rotate(tree->left);  
     return right_rotate(tree);
   }  
   //right-right case  
   else if(balance < -1 && tree->right-> key_value > val){  
    //** <Your code here >
     tree->right = right_rotate(tree->right);
     return(left_rotate(tree));
   }  
   //left-right case  
   else if(balance > 1 && tree->left-> key_value > val){   
    //** <Your code here >
    return right_rotate(tree);
   }  
   //right-left case  
   else if(balance < -1 && tree->right->key_value < val){
    //** <Your code here >
    return left_rotate(tree);
   }
   return tree;  
 }  
 
 
 //utility function used in balancing of node  
 //in deletion operation  

struct node* AVLTree::balance_tree(struct node* tree)
{  
   struct node* x, *y;  

  // <Your code here >
 
   if(get_height(tree->right)>=get_height(tree->left)) {  
    x=tree->right;	
		if(get_height(tree->left)>get_height(tree->right))  {
      tree->right = right_rotate(tree->right);
      tree=left_rotate(tree);	
		} else { 
    tree=left_rotate(tree);
		}
	}
	else
   {
    x=tree->left;
     if (get_height(x->left)>=get_height(x->right)){
       tree = right_rotate(tree);
		} else {  
    tree->left = left_rotate(tree->left);
       tree = right_rotate(tree);
		}
   }
  
   return tree;  
 }  
 //utility function to find inorder successor   
 //of a given node when it has a right child  
 struct node* AVLTree::inorder_succ_right_tree(struct node* tree)
 {  
   struct node* temp = tree->right;  
   while(temp->left){  
     temp = temp->left;  
   }  
   return temp;  
 }
 
 struct node* AVLTree::deletion(struct node* tree, int val)
 {
   if(!tree)
     return tree;
   if (val < tree->key_value) {
     tree->left= deletion(tree->left,val);
   } else if (val > tree->key_value) {
     tree->right = deletion(tree->right, val);
   } else {
     struct node* test;
     if (tree->left == nullptr || tree->right == nullptr) {
       test = tree->left ? tree->left: tree->right;
       if (test==nullptr) {
         test=tree;
         tree = nullptr;
       } else {
         tree =test;
       }
         delete test;
    } else {
       test = inorder_succ_right_tree(tree);
       tree->key_value = test->key_value;
       tree->right = deletion(tree->right, test->key_value);
       }
     }
    if (tree == nullptr)
       return tree;
   tree->height = max(get_height(tree->left),get_height(tree->right))+1;
   int balance = get_balance(tree);
   if(balance>1 && get_balance(tree->left)>=0) {
     return right_rotate(tree);
   } else if (balance>1 && get_balance(tree->left)<0) {
     tree->left = left_rotate(tree->left);
     return right_rotate(tree);
   } else if (balance<-1 && get_balance(root->right)<=0) {
     return left_rotate(root);
   } else if (balance<-1 && get_balance(root->right)>0) {
     root->right = right_rotate(root->right);
     return left_rotate(root);
   }
   return tree;
 }  
 //function for printing the pre-order of tree  
 void AVLTree::preorder(struct node* tree)
 {  
   if(!tree)  
     return;  
   printf("%d\t",tree->key_value);  
   preorder(tree->left);  
   preorder(tree->right);  
 }
 
 //function for printing the in-order of tree  
 int AVLTree::max_level(struct node* tree, int level, int max)
 {  
   int depth;
   if(!tree)  
     return level-1;  
   depth = max_level(tree->left, level+1, max);
   if (depth > max)
      max = depth;
   //printf("m%d[%d, %d]\t",tree->key_value, level, max);  
   depth = max_level(tree->right, level+1, max);
   if (depth > max)
      max = depth;
   return max;
 }

 //function for printing the in-order of tree  
 int AVLTree::min_level(struct node* tree, int level, int min)
 {  
    int depth;
    if((!tree->left) && (!tree->right)) 
      return  (level < min ? level : min);  
    if (tree->left)
      min = min_level(tree->left, level+1, min);

    //printf("m%d[%d, %d]\t",tree->key_value, level, min);  
    if (tree->right)
      min = min_level(tree->right, level+1, min);

   return min;
 }

 
 
 //function for printing the in-order of tree  
 void AVLTree::inorder_level(struct node* tree, int level)
 {  
   if(!tree)  
     return;  
   inorder_level(tree->left, level+1);  
   printf("%d[%d]\t",tree->key_value, level);  
   inorder_level(tree->right, level+1);  
 }


 //function for printing the in-order of tree  
 void AVLTree::inorder(struct node* tree)
 {  
    inorder_level(tree,0);
 }

  //function for  clearing tree  
 void AVLTree::clear(struct node* tree)
 {  
   if(!tree)  
     return;  
   clear(tree->left);   
   tree->left = NULL;
   clear(tree->right);
   tree->right = NULL;
   if (root == tree)
	   root = NULL;
	delete tree;
 }  
 
 
  //function for printing the in-order of tree  
 int AVLTree::sumorder(struct node* tree)
 {
	int sum=0;
   if(!tree)  
     return 0;  
	sum += sumorder(tree->left);  

	sum += sumorder(tree->right);
 
 	sum += tree->key_value;
	printf("<%2d, %4d>\t",tree->key_value, sum);  
 
	return sum;
 }  
 
 
 
 



/*
 * Display Tree Structure
 */
void AVLTree::display(node *ptr, int level, int dir)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->left, level+1, 1);
        std::cout<<std::endl;
        if (ptr == root)
            std::cout<<"Root->: ";
        else
        {
            for (i = 0;i < level+1;i++)
                std::cout<<"      ";
	      }
	      if (dir == 1)
	        std::cout << "/  ";
        else if(dir == 2)
	        std::cout << "\\  ";
        std::cout<<ptr->key_value;
        display(ptr->right, level+1, 2);
    }
}

