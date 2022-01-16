//Johannes Ferm & Molham Srour

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

tree *init(tree *t) //initializer
{
	t->root = NULL;
	return t;
}

void insert(tree *t, int val)
{
	nod *ny = malloc(sizeof(nod)); //create new node
	ny->val = val;
	if(t->root == NULL) //if the tree is empty new node becomes root
	{
		t->root = ny;
		t->root->parent = NULL;
		t->root->Lchild = NULL;
		t->root->Rchild = NULL;
	}
	else
	{
		nod *temp = t->root; //temporary node set to root
		while(temp != NULL)
		{
			if(temp->Rchild == NULL && temp->val < ny->val) //condition for stopping, if we're at the end of the tree
			{												//and the value of the new node is bigger than temps val
				temp->Rchild = ny;							//the new node becomes the right child of temp
				ny->parent = temp;
				ny->Lchild = NULL;
				ny->Rchild = NULL;
				break;
			}
			if(temp->Lchild == NULL && temp->val > ny->val)//same as the one above but with left child. 
			{
				temp->Lchild = ny;
				ny->parent = temp;
				ny->Lchild = NULL;
				ny->Rchild = NULL;
				break;
			}
			if(ny->val < temp->val) //if value is smaller than current move left
			{
				temp = temp->Lchild;
			}
			else                    //else move right
			{
				temp = temp->Rchild;
			}
		}
	}
}

nod *max(tree *t) //Finds the right-most node
{
	nod *temp = t->root;
	while(temp->Rchild != NULL)
	{
		temp = temp->Rchild;
	}
	return temp;
}

nod *min(tree *t) //Finds the left-most node
{
	nod *temp = t->root;
	while(temp->Lchild != NULL)
	{
		temp = temp->Lchild;
	}
	return temp;
}

nod *search(tree *t, int key)
{
	nod *temp = t->root;
	while(temp != NULL) 
	{
		if(key == temp->val) //if we find the value
		{
			return temp;
		}
		if(key < temp->val) //if we find a bigger value, move to smaller values
		{
			temp = temp->Lchild;
			continue;
		}
		if(key > temp->val) //if we find a smaller value we move to bigger values
		{
			temp = temp->Rchild;
			continue;
		}
	}
	return NULL;
}

nod *successor(tree *t, nod *x)
{
	nod *temp = x;
	if(temp->Rchild != NULL)
	{
		temp = temp->Rchild;
		while(temp->Lchild != NULL)//finding min of right subtree
		{
			temp = temp->Lchild;
		}
		return temp;
	}
	else
	{
		nod *z = temp->parent;
		while(z != NULL && temp == z->Rchild)//stepping backwards and finding the (left) subtree where x is maximum. 
		{
			temp = z;
			z = z->parent;
		}
		return z;
	}
	return NULL;
}

nod *predecessor(tree *t, nod *x)
{
	nod *temp = x;
	if(temp->Lchild != NULL) //finding max of left subtree
	{
		temp = temp->Lchild;
		while(temp->Rchild != NULL)
		{
			temp = temp->Rchild;
		}
		return temp;
	}
	else
	{
		nod *z = temp->parent;
		while(z != NULL && temp == z->Lchild) //stepping backwards making both nodes their parents to find the
		{									  //(right) subtree where x is the minimum. 
			temp = z;
			z = z->parent;
		}
		return z;
	}
	return NULL;
}

void transplant(tree *t, nod *x, nod *y)
{
	if(x->parent == NULL) //if x is the root of the tree
	{
		t->root = y;      //replace root with node y. 
	}
	else if(x->parent->Lchild == x) //if x is the left child
	{
		x->parent->Lchild = y; //replace parents left child with y 
	}
	else
	{	
		x->parent->Rchild = y; //replace right child with y
	}
	if(y != NULL)
	{
		y->parent = x->parent; //make the parent of x the parent of y. 
	}
}

void delete(tree *t, nod *x)
{
	if(x->Lchild == NULL) //no left child
	{
		transplant(t, x, x->Rchild); //transplant the right child into x's place. 
	}
	else if(x->Rchild == NULL)//no left child, other way around
	{
		transplant(t, x, x->Lchild);
	}
	else                        //if both children exist
	{							
		nod *y = successor(t, x); //find the successor of x
		if(y->parent != x)        //if x is not the direct child of its successor
		{
			transplant(t, y, y->Rchild); //transplant the right child of y in place of y
			y->Rchild = x->Rchild;		 //set right child(y) to right child(x)
			y->Rchild->parent = y;		 //set y to the right child.  
		}
		transplant(t, x, y);			 //transplant y into the place of x
		y->Lchild = x->Lchild;			 //same as with Rchild
		y->Lchild->parent = y;			 //same as with Rchild
	}
	free(x); //this line hasn't been properly tested
}

void print_tree(tree *t)
{
	nod *temp = min(t);
	while(temp != NULL)
	{
		printf("%d ", temp->val);
		temp = successor(t, temp);
	}
}

int depth(nod *x) //from the internet( https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/), if this is not allowed, change it. But it seems like this recursion is
{				
	if(x == NULL) //base case
	{
		return 0;
	}
	else
	{
		if(depth(x->Rchild) > depth(x->Lchild)) //if the right subtree is "deeper" than the left
			return depth(x->Rchild) + 1;        //return the depth of right subtree(recursive call) + 1
		else
			return depth(x->Lchild) + 1;
	}
}
//The recursion works by splitting it up so higher levels become the max of lower levels. So that the root
//is the max depth of the two children, and the two children have the max depth of their two subtrees and so on.
//Eventually we reach the base case and return 0 to the higher levels(which is why we need to + 1), then we compare
//the two children of the root and the max depth of these two + 1 becomes the depth at the top, which is the depth
//of the tree.
