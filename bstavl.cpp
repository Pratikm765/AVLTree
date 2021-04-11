//============================================================================
// Name        : Data_Structures.cpp
// Author      : Pratik Mhatre
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
	int data;
	struct Node* left;
	struct Node* right;

	Node(int data){
		this->data=data;
		left=right=NULL;
	}
};

struct AVLNode{
	int data;
	struct AVLNode* left;
	struct AVLNode* right;
	int height;

	AVLNode(int data){
		this->data=data;
		left=right=NULL;
		this->height=1;
	}
};

class BST{
	Node* head;
public:
	BST()
	{
		head=NULL;
	}

	void addNode(int data)
	{
		Node* newnode= new Node(data);

		if(head==NULL)
			head=newnode;
		else
		{
			Node* curr=head;
			while(curr)
			{
				if(curr->data<data)
				{
					if(curr->right==NULL)
					{
						curr->right=newnode;
						break;
					}
					else
						curr=curr->right;
				}
				else
				{
					if(curr->left==NULL)
					{
						curr->left=newnode;
						break;
					}
					else
						curr=curr->left;
				}
			}
		}
	}

	void inorderUtil(Node* curr)
	{
		if(curr==NULL)
			return;
		inorderUtil(curr->left);
		cout<<curr->data<<" ";
		inorderUtil(curr->right);
	}

	void inorder()
	{
		inorderUtil(head);
	}

	bool searchNode(int data)
	{
		Node* curr=head;
		while(curr)
		{
			if(curr->data==data)
				return true;
			else if(curr->data<data)
				curr=curr->right;
			else
				curr=curr->left;

		}
		return false;
	}

	void deleteNode(int data)
	{
		Node* prev=NULL;
		Node* curr=head;

		while(curr!=NULL)
		{
			if(curr->data==data)
				break;
			else if(curr->data<data)
			{
				prev=curr;
				curr=curr->right;
			}
			else
			{
				prev=curr;
				curr=curr->left;
			}

		}

		if(curr!=NULL && curr->data==data)
		{
			if(curr->left==NULL && curr->right==NULL)
			{
				if(prev->left==curr)
					prev->left=NULL;
				else
					prev->right=NULL;
			}
			else if(curr->left==NULL)
			{
				if(prev->left==curr)
					prev->left=curr->right;
				else
					prev->right=curr->right;
			}
			else if(curr->right==NULL)
			{
				if(prev->left==curr)
					prev->left=curr->left;
				else
					prev->right=curr->left;
			}
			else
			{
				Node* temp=curr->right;
				Node* p=NULL;

				while(temp->left!=NULL)
				{
					p=temp;
					temp=temp->left;
				}

				if(p!=NULL)
					p->left=temp->right;
				else
					curr->right=temp->right;

				curr->data=temp->data;
				curr=temp;
			}
			delete curr;
		}
		else
		{
			cout<<"Not found"<<endl;
		}
	}

	int findfloor(int key)
	{
		Node* curr=head;
		int result=INT_MIN;
		if(curr==NULL)
			return 0;

		while(curr!=NULL)
		{
			if(curr->data==key)
			{
				result=key;
				break;
			}
			else if(curr->data>key)
			{
				curr=curr->left;
			}
			else
			{
				result=max(result,curr->data);
				curr=curr->right;
			}
		}
		return result;
	}

	int findceil(int key)
		{
			Node* curr=head;
			int result=INT_MAX;
			if(curr==NULL)
				return 0;

			while(curr!=NULL)
			{
				if(curr->data==key)
				{
					result=key;
					break;
				}
				else if(curr->data<key)
				{
					curr=curr->right;
				}
				else
				{
					result=min(result,curr->data);
					curr=curr->left;
				}
			}
			return result;
		}


};

class AVL{
	AVLNode* root;
public:
	AVL(){
		root=NULL;
	}

	int getBalance(AVLNode* node){
		if(node==NULL)
			return 0;
		return (height(node->left))-(height(node->right));
	}

	AVLNode* rightRotation(AVLNode* node){
		AVLNode* x= node->left;
		AVLNode* y= x->right;

		x->right=node;
		node->left=y;

		node->height= 1+max(height(node->left),height(node->right));
		x->height=1+max(height(x->left),height(x->right));

		return x;
	}

	AVLNode* leftRotation(AVLNode* node){
		AVLNode* x= node->right;
		AVLNode* y= x->left;

		x->left=node;
		node->right=y;

		node->height= 1+max(height(node->left),height(node->right));
		x->height=1+max(height(x->left),height(x->right));

		return x;
	}

	int height(AVLNode* node)
	{
		if(node==NULL)
			return 0;
		return node->height;
	}

	AVLNode* addNodeUtil(AVLNode* node,int data){
		if(node==NULL)
			return (new AVLNode(data));

		if(node->data<data)
			node->right=addNodeUtil(node->right,data);
		else if(node->data>data)
			node->left=addNodeUtil(node->left,data);
		else
		{
			cout<<"duplicates not allowed"<<endl;
			return node;
		}


		node->height=1+max(height(node->left),height(node->right));

		int bf= getBalance(node);

		if(bf>1 && data<node->left->data)
			return rightRotation(node);

		if(bf<-1 && data>node->right->data)
			return leftRotation(node);

		if(bf>1 && data>node->left->data)
		{
			node->left=leftRotation(node->left);
			return rightRotation(node);
		}

		if(bf<-1 && data<node->right->data)
		{
			node->right=rightRotation(node->right);
			return leftRotation(node);
		}

		return node;
	}

	void addNode(int data){
		root=addNodeUtil(root,data);
	}
	
	AVLNode * minValueNode(AVLNode* node) 
	{ 
	    AVLNode* current = node; 
	  
	    /* loop down to find the leftmost leaf */
	    while (current->left != NULL) 
	        current = current->left; 
	  
	    return current; 
	} 
	
	AVLNode* deleteNodeUtil(AVLNode* node,int data){
		if(node==NULL)
			return node;

		if(node->data>data)
			node->left=deleteNodeUtil(node->left,data);
		else if(node->data<data)
			node->right=deleteNodeUtil(node->right,data);
		else
		{
			if(node->left==NULL || node->right==NULL)
			{
				AVLNode* temp=node->left?node->left:node->right;
				
				if(temp==NULL)
				{
					temp=node;
					node=NULL;
				}
				else
					*node=*temp
					
				delete temp;
			}
			else
			{
				// node with two children: Get the inorder 
            	// successor (smallest in the right subtree) 
            	AVLNode* temp = minValueNode(node->right); 
            	
            	node->data=temp->data;
            	node->right=deleteNodeUtil(node->right,temp->data);
			}
		}
		
		if(node==NULL)
			return node;

		node->height=1+max(height(node->left),height(node->right));

		int bf= getBalance(node);

		if(bf>1 && data<node->left->data)
			return rightRotation(node);

		if(bf<-1 && data>node->right->data)
			return leftRotation(node);

		if(bf>1 && data>node->left->data)
		{
			node->left=leftRotation(node->left);
			return rightRotation(node);
		}

		if(bf<-1 && data<node->right->data)
		{
			node->right=rightRotation(node->right);
			return leftRotation(node);
		}

		return node;
	}

	void inorderUtil(AVLNode* curr)
	{
		if(curr==NULL)
			return;
		inorderUtil(curr->left);
		cout<<curr->data<<" "<<curr->height<<endl;
		inorderUtil(curr->right);
	}

	void inorder()
	{
		inorderUtil(root);
	}
};
int main() {

//	BST bs;
//
//	bs.addNode(30);
//	bs.addNode(15);
//	bs.addNode(35);
//	bs.addNode(45);
//	bs.addNode(25);
//	bs.addNode(10);
//	bs.addNode(50);
//	bs.addNode(20);
//
//	bs.inorder();
//	cout<<endl;
//
//	cout<<"Present: "<<bs.searchNode(17)<<endl;
//
//	bs.deleteNode(30);
//	bs.inorder();
//	cout<<endl;
//
//	cout<<"Floor: "<< bs.findfloor(34)<<endl;
//	cout<<"Ceil: "<< bs.findceil(34)<<endl;

	AVL av;

	av.addNode(10);
	av.addNode(20);
	av.addNode(30);
	av.addNode(40);
	av.addNode(20);
	av.addNode(50);
	av.addNode(25);

	cout<<"Added";
	av.inorder();


	return 0;
}
