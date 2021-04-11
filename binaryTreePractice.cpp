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

struct node{
	int data;
	node* left;
	node* right;
	int lcount;

	node(int value){
		data=value;
		left=right=NULL;
		lcount=0;
	}
};
class bst{
	node* root;
public:

	bst(){
		root=NULL;
	}
	node* insertUtil(node* n,int d){
		if(n==NULL)
			return(new node(d));
		if(d<n->data)
		{
			n->left=insertUtil(n->left,d);
			n->lcount++;
		}
		else
		{
			n->right=insertUtil(n->right,d);
		}
		return n;
	}

	void insert(int d)
	{
		root=insertUtil(root,d);
	}

	node* kthsmallest(node* n,int k)
	{
		if(n==NULL)
			return NULL;

		int count=n->lcount+1;
		if(count==k)
			return n;

		if(count>k)
			return kthsmallest(n->left,k);

		return kthsmallest(n->right,k-count);
	}

	void kthsmallestUtil(int k)
	{
		node* temp= kthsmallest(root,k);
		cout<<temp->data<<endl;
	}

	void sumPair(int sum)
	{
		stack<node*> s;
		node* curr=root;
		vector<int> v;

		while(curr!=NULL || s.empty()==false)
		{
			while(curr!=NULL)
			{
				s.push(curr);
				curr=curr->left;
			}
			curr=s.top();
			s.pop();

			v.push_back(curr->data);
			curr=curr->right;
		}

		auto it1=v.begin();
		auto it2=v.rbegin();

		while(it1!=v.end() && it2!=v.rend())
		{
			int tempsum=*it1+*it2;
			if(tempsum==sum)
			{
				cout<<"Got: "<<*it1<<" "<<*it2<<endl;
				it1++;
				it2++;
			}
			else if(tempsum<sum)
				it1++;
			else
				it2++;
		}

	}


	void reverse_inorder(node* root)
	{
	    //base case
	    if (root == NULL)
	        return;

	    //secondly traverse right sub tree
	    reverse_inorder(root->right);

	    //finally traverse current node
	    printf("%d ", root->data);

	    // fisrt traverse left sub tree
	    reverse_inorder(root->left);
	}

	void inorder(node* n)
	{
		if(n==NULL)
			return;
		inorder(n->left);
		cout<<n->data<<" ";
		inorder(n->right);
	}

	void swap(int* a,int* b){
		int t=*a;
		*a=*b;
		*b=t;
	}

	void findSwapped(node* n, node** prev,node** first,node** middle,node** last)
	{
		if(n==NULL)
			return;
		findSwapped(n->left,prev,first,middle,last);
		if(*prev!=NULL && n->data < (*prev)->data)
		{
			if(*first==NULL)
			{
				*first=*prev;
				*middle=n;
				//cout<<"swapped1: "<<(*prev)->data<<endl;
			}
			else
			{
				//cout<<"swapped2: "<<n->data<<endl;
				*last=n;
			}

		}
		*prev=n;
		findSwapped(n->right,prev,first,middle,last);
	}


	void findSwappedUtil(node* n)
	{
	    node *first, *middle, *last, *prev;
	    first = middle = last = prev = NULL;
		findSwapped(n, &prev, &first, &middle, &last);

		if( first && last )
		        swap( &(first->data), &(last->data) );
		else if( first && middle ) // Adjacent nodes swapped
		        swap( &(first->data), &(middle->data) );

	}
};



//alternate solution is stock span problem using stack
void prevGreater(){
    int arr[] = { 10, 5, 11, 10, 20, 12 };
    int n = sizeof(arr) / sizeof(arr[0]);

    set<int> s1;
    for(int i=0;i<n;i++)
    {
    	auto it=s1.lower_bound(arr[i]);
    	int lb;
    	if(it==s1.end())
    		lb=-1;
    	else
    		lb=*it;
    	cout<<arr[i]<<" "<< lb<<endl;
    	s1.insert(arr[i]);
    }
}

//Kth smallest
//Alternate solution is inorder traversal and maintaing count to print at k
void kthSmallest(int k){
	bst bs;
    int keys[] = { 20, 8, 22, 4, 12, 10, 14 };

    for (int x : keys)
       bs.insert(x);

    bs.kthsmallestUtil(k);
}

//another solution will be without vector/array
//inorder traversing bst from front  and end
void sumPair(int k){
	bst bs;
    int keys[] = { 20, 8, 22, 4, 12, 10, 14 };

    for (int x : keys)
       bs.insert(x);

    bs.sumPair(k);
}

void findswapped()
{
	bst bs;
    struct node *newroot = new node(5);
    newroot->left   = new node(3);
    newroot->right         = new node(4);
    newroot->left->left     = new node(1);
    newroot->left->right = new node(9);
    newroot->right->left     = new node(7);
    newroot->right->right = new node(10);

    bs.inorder(newroot);
    cout<<endl;

	bs.findSwappedUtil(newroot);

    bs.inorder(newroot);
    cout<<endl;


}

int main() {

	//prevGreater();

	//kthSmallest(3)

	//sumPair(18);

	findswapped();

	return 0;
}
 