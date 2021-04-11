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

void inorder(Node* root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}

void preorder(Node* root)
{
	if(root==NULL)
		return;
	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);
}

void postorder(Node* root)
{
	if(root==NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<" ";
}

void levelorder(Node* root)
{
	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		int size=q.size();
		cout<<endl;
		for(int i=0;i<size;i++)
		{
			struct Node* curr= q.front();
			q.pop();
			cout<<curr->data<<" ";
			if(curr->left)
				q.push(curr->left);
			if(curr->right)
				q.push(curr->right);
		}
		//Not Line by line
/*		struct Node* curr= q.front();
		q.pop();
		cout<<curr->data<<" ";
		if(curr->left)
			q.push(curr->left);
		if(curr->right)
			q.push(curr->right);*/

	}
}

void levelorderNew(Node* root,int h)
{
	if(root==NULL)
		return;
	if(h==1)
		cout<<root->data<<" ";
	else if(h>1)
	{
		levelorderNew(root->left,h-1);
		levelorderNew(root->right,h-1);
	}
}
int height(Node* root)
{
	if(root==NULL)
		return 0;

	int lh=height(root->left);
	int rh=height(root->right);

	return max(lh,rh)+1;
}

void levelOrderNew(Node* root)
{
	int h= height(root);

	for(int i=1;i<=h;i++)
	{
		levelorderNew(root,i);
		cout<<endl;
	}
}
int width(Node* root)
{
	int result=0;
	if(root==NULL)
		return 0;

	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		int size=q.size();
		result=max(result,size);
		for(int i=0;i<size;i++)
		{
			struct Node* curr= q.front();
			q.pop();
			if(curr->left)
				q.push(curr->left);
			if(curr->right)
				q.push(curr->right);
		}
	}
	return result;
}

void zigzagLevelorder(Node* root)
{
	queue<Node*> q;
	stack<int> s;
	bool flag=false;

	q.push(root);
	while(!q.empty())
	{
		int size=q.size();
		for(int i=0;i<size;i++)
		{
			struct Node* curr= q.front();
			q.pop();
			if(flag)
				s.push(curr->data);
			else
				cout<<curr->data<<" ";

			if(curr->left)
				q.push(curr->left);
			if(curr->right)
				q.push(curr->right);
		}
		while(!s.empty())
		{
			cout<<s.top()<<" ";
			s.pop();
		}
		flag=!flag;
	}
}

bool sumProperty(Node* root)
{
	int left_data=0,right_data=0;

	if(root==NULL || (root->left==NULL && root->right==NULL))
		return true;
	else
	{
		if(root->left!=NULL)
			left_data=root->left->data;
		if(root->right!=NULL)
			right_data=root->right->data;

		if(root->data==left_data+right_data &&
				sumProperty(root->left) &&
					sumProperty(root->right))
			return true;
		else
			return false;
	}
}

void kthlevel(Node* root,int k)
{
	if(root==NULL)
		return;
	if(k==1)
		cout<<root->data<<" ";
	else if(k>1)
	{
		kthlevel(root->left,k-1);
		kthlevel(root->right,k-1);
	}
}

bool isBalanced(Node* root)
{
	if(root==NULL)
		return true;

	int lh=height(root->left);
	int rh=height(root->right);

	if(abs(lh-rh)<=1 && isBalanced(root->left) && isBalanced(root->right))
		return true;

	return false;
}

bool isBalancedOptimized(Node* root, int* h)
{
	int lh=0,rh=0;
	bool l=false,r=false;
	if(root==NULL)
	{
		*h=0;
		return true;
	}

	l=isBalancedOptimized(root->left,&lh);
	r=isBalancedOptimized(root->right,&rh);

	*h=(lh>rh?lh:rh)+1;

	if(abs(lh-rh)<=1)
		return l&&r;
	else
		return false;
}

void MakeDLL(Node* root, Node** head)
{
	if(root==NULL)
		return;

	static Node* prev=NULL;

	MakeDLL(root->left,head);

	if(prev==NULL)
	{
		*head=root;
	}
	else
	{
		root->left=prev;
		prev->right=root;
	}
	prev=root;

	MakeDLL(root->right,head);

}

void bt2dll(Node* root)
{
	Node* head=NULL;
	MakeDLL(root,&head);

	Node* curr=head;
	while(curr->right!=NULL)
	{
		cout<<curr->data<<" ";
		curr= curr->right;
	}
	cout<<curr->data<<" ";
	cout<<endl;

	while(curr!=NULL)
	{
		cout<<curr->data<<" ";
		curr= curr->left;
	}
}

void maxSumRoot2Leaf(Node* root,int* maxSum, int currSum, Node** target)
{
	if(root==NULL)
		return;

	currSum=currSum+root->data;

	if(root->left==NULL && root->right==NULL )
	{
		if(currSum>*maxSum)
		{
			*maxSum=currSum;
			*target=root;
		}
	}

	maxSumRoot2Leaf(root->left,maxSum,currSum,target);
	maxSumRoot2Leaf(root->right,maxSum,currSum,target);
}
bool print2target(Node* root,Node* target)
{
	if(root==NULL)
		return false;

	if(root==target||print2target(root->left,target)||print2target(root->right,target))
	{
		cout<<root->data<<" ";
		return true;
	}
	return false;
}
void maxSumRoot2LeafMain(Node* root)
{
	Node* target=NULL;
	int maxSum=0;

	maxSumRoot2Leaf(root,&maxSum,0,&target);

	cout<<"MaxSum: "<<maxSum<<endl;

	print2target(root,target);
} 

int diameter(Node* root,int* height)
{
	int lh=0,rh=0;
	int ld=0,rd=0;

	if(root==NULL)
	{
		*height=0;
		return 0;
	}
	ld=diameter(root->left,&lh);
	rd=diameter(root->right,&rh);

	*height=max(lh,rh)+1;

	return max(lh+rh+1,max(ld,rd));
}

Node* findLCA(Node* root,int n1,int n2)
{
	if(root==NULL)
		return NULL;
	if(root->data==n1 || root->data==n2)
		return root;

	Node* left_LCA=findLCA(root->left,n1,n2);
	Node* right_LCA=findLCA(root->right,n1,n2);

	if(left_LCA && right_LCA)
		return root;

	return left_LCA!=NULL?left_LCA:right_LCA;
}

bool isBSTUtil(Node* root,int min, int max)
{
	if(root==NULL)
		return true;
	if(root->data < min || root->data > max)
		return false;

	return isBSTUtil(root->left,min,root->data-1) &&
			isBSTUtil(root->right,root->data+1,max);
}
bool isBSTOptimized(Node* root, Node* prev)
{
	if(root)
	{
		if(!isBSTOptimized(root->left,prev))
			return false;
		if(prev!=NULL && root->data<=prev->data)
			return false;
		prev=root;

		return isBSTOptimized(root->right,prev);
	}
	return true;
}
bool isBST(Node* root)
{
	return isBSTUtil(root,INT_MIN,INT_MAX);
	//Node* prev=NULL;
	//return isBSTOptimized(root,prev);
}
Node* buildTreeUtil(int in[],int pre[],int start,int end,unordered_map<int,int> mp)
{
	static int precount=0;

	if(start>end)
		return NULL;

	int num=pre[precount++];
	Node* temp=new Node(num);

	if(start==end)
		return temp;

	int index=mp[num];
	temp->left=buildTreeUtil(in,pre,start,index-1,mp);
	temp->right=buildTreeUtil(in,pre,index+1,end,mp);

	return temp;
}
void buildTree()
{
	int in[]={8,4,9,2,10,5,11,1,12,6,20,13,3,14,7,15};
	int pre[]={1,2,4,8,9,5,10,11,3,6,12,13,20,7,14,15};

	unordered_map<int,int> mp;

	for(int i=0;i<16;i++)
		mp[in[i]]=i;

	Node* temp=buildTreeUtil(in,pre,0,15,mp);
	postorder(temp);
}

int main() {

    struct Node *root = new Node(1);
    root->left   = new Node(2);
    root->right         = new Node(3);
    root->left->left     = new Node(4);
    root->left->right = new Node(5);
    root->right->left     = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left  = new Node(8);
    root->left->left->right  = new Node(9);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(11);
    root->right->left->left    = new Node(12);
    root->right->left->right    = new Node(13);
    root->right->right->left = new Node(14);
    root->right->right->right = new Node(15);
    root->right->left->right->left    = new Node(20);

    struct Node *newroot = new Node(7);
    newroot->left   = new Node(3);
    newroot->right         = new Node(9);
    newroot->left->left     = new Node(1);
    newroot->left->right = new Node(4);

    cout<<"Inorder: ";
    inorder(root);
    cout<<endl;

    cout<<"Preorder: ";
    preorder(root);
    cout<<endl;

    cout<<"Postorder: ";
    postorder(root);
    cout<<endl;

    cout<<"Levelorder: ";
    levelorder(root);
    cout<<endl;

    cout<<"Height: "<<height(root)<<endl;

    cout<<"LevelorderNew: "<<endl;
    levelOrderNew(root);
    cout<<endl;

    cout<<"Width: "<<width(root)<<endl;

    cout<<"Zigzag: ";
    zigzagLevelorder(root);
    cout<<endl;

    cout<<"Sum Property: "<<sumProperty(root)<<endl;

    cout<<"kth level: ";
    kthlevel(root,3);
    cout<<endl;

    cout<<"isBalanced: "<<isBalanced(newroot)<<endl;

    int h=0;
    cout<<"isBalancedOptimized: "<<isBalancedOptimized(newroot,&h)<<endl;

    //cout<<"binary tree to DLL"<<endl;
    //bt2dll(root);

    maxSumRoot2LeafMain(root);

    int h1=0;
    cout<<"Diameter: "<<diameter(root,&h1)<<endl;

    cout<<"LCA: "<<findLCA(root,8,13)->data<<endl;

    cout<<"Is BST: "<<isBST(newroot)<<endl;

    cout<<"Building tree: "<<endl;
    buildTree();
	return 0;
}
