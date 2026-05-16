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

		void bfs()
		{
			if(root == NULL) return;
			
			vector<Node*> current;
			current.push_back(root);

			while(!current.empty())
			{
				vector<Node*> next;
				
				#pragma omp parallel
				{
					vector<Node*> localNext;

					#pragma omp for
					for(int i = 0; i < current.size(); i++)
					{
						Node* temp = current[i];

						#pragma omp critical
						{
							cout << "Thread : " << omp_get_thread_num() << " - "<< temp -> data << endl;
						}

						if(temp -> left)
							localNext.push_back(temp -> left);
						if(temp -> right)
							localNext.push_back(temp -> right);
					}
					#pragma omp critical
					{
						next.insert(next.end(), localNext.begin(), localNext.end());
					}
				}
				current = next;
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
//       !g++ -fopenmp filename.cpp -o filename
//       !./filename
