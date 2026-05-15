#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;

class Node
{
	Node* left = NULL;
	Node* right = NULL;
	int data = 0;
	Node(int data)
	{
		this -> data = data;
	}
	friend class Tree;
};

class Tree
{
		Node* root = NULL;
	public:
		void insert(Node* cur, int data)
		{
			Node* p = new Node(data);
			if(this -> root == NULL)
			{
				this->root = p;
				return;
			}

			if(cur -> data > data)
			{
				if(cur -> left)
					insert(cur -> left, data);
				else
					cur -> left = p;
			}
			else
				if(cur -> right)
					insert(cur -> right, data);
				else
					cur -> right = p;
		}

		void dfs(Node* root)
		{
			if(root)
			{
				dfs(root -> left);
				cout << root -> data << endl;
				dfs(root -> right);
			}
		}
		Node* getRoot()
		{
			return root;
		}

		void dfs_para(Node* root)
		{
			if(root)
			{
				#pragma omp critical
				cout << root -> data << endl;

				#pragma omp parallel sections
				{
					#pragma omp section
					dfs_para(root -> left);
					
					#pragma omp section
					dfs_para(root -> right);
				}
			}
		}
		void start_dfs()
		{
			#pragma omp parallel
			{
				#pragma omp single
				dfs_para(root);
			}
		}
};

int main()
{
	Tree t;
	t.insert(t.getRoot(),10);
	t.insert(t.getRoot(),20);
	t.insert(t.getRoot(),40);
	t.insert(t.getRoot(),30);
	t.insert(t.getRoot(),50);

	t.dfs(t.getRoot());

	cout << endl;
	t.bfs();

	return 0;
}

//       !g++ filename.cpp -o filename
//       !./filename
