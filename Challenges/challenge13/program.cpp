// Andrew Bub CSE30872 - Challenge 13: Danny's Revenge
// October 22, 2017
#include <iostream>
#include <vector>

using namespace std;

// Global Variables ---------------------------------------------------------------------------------------
struct Node
{
	int val;
	Node *left;
	Node *right;
};

// Prototypes ---------------------------------------------------------------------------------------------
void Insert(Node* &, int);
int find_LCA(Node *, int, int);
bool find_path(Node *, vector<int> &, int);
void Delete(Node *);

// Main Execution -----------------------------------------------------------------------------------------
int main()
{
	int nodes, pairs; // number of nodes and pairs
	int val; // value of individual node
	int a, b; // individual values of pairs
	int lca; // Lowest Common Ancestor
	Node *root = NULL;

	cin >> nodes; // initial read in of nodes
	while(nodes != -1)
	{
//		cout << "Read in ";
		for(int i = 0; i < nodes; i++)
		{
			cin >> val;
//			cout << val << " ";
			Insert(root, val); // add node to BST	
		}
//		cout << endl;

		cin >> pairs;
		for(int i = 0; i < pairs; i++)
		{
			cin >> a >> b;
//			cout << "Pair (" << a << "," << b << ")" << endl;
			lca = find_LCA(root, a, b); // calculate LCA
			cout << lca << endl; // display LCA
		}
		
		Delete(root); // clear BST for next iteration

		cin >> nodes; // read in next number of nodes
	}

	return 0;
}

// Functions ----------------------------------------------------------------------------------------------
void Insert(Node* &node, int val)
{
	if(node == NULL)
	{
		Node *temp;
		temp = new Node;

		temp->val = val;
		temp->left = temp->right = NULL;
		node = temp;
	}else if(val <= (node->val))
	{
		Insert(node->left, val);		
	} else
	{
		Insert(node->right, val);
	}
}

int find_LCA(Node *root, int a, int b)
{
	vector<int> path_a;
	vector<int> path_b;

	// find paths from root to a and b
	// return -1 if a or b not in BST
	if(!find_path(root, path_a, a) || !find_path(root, path_b, b))
		return -1;

	int lca = 0;

	for(int i = 0; i < path_a.size() && i < path_b.size(); i++)
	{
//		cout << "A:" << path_a[i] << " B:" << path_b[i] << endl;
		if(path_a[i] == path_b[i])
			lca = path_a[i];
		else
			break;
	}
	
	path_a.clear();
	path_b.clear();

	return lca;
}

bool find_path(Node *root, vector<int> &path, int v)
{
	// base case
	if(root == NULL)
		return false;

	path.push_back(root->val); // add node to path
//	cout << "added " << root->val << " in path to " << v << endl;

	if(root->val == v) // if root is the node we're looking for
		return true;

	// Check if v is in left or right sub-tree
	if((root->left && find_path(root->left, path, v)) || (root->right && find_path(root->right, path, v)))
		return true;

	// remove node from path if v is not in subtree rooted with root
	path.pop_back();
//	cout << "removed " << root->val << " from path to " << v << endl;
	return false;
}

void Delete(Node *node)
{
	if(node == NULL)
		return;
	if(node->left != NULL)
		Delete(node->left);
	if(node->right != NULL)
		Delete(node->right);

	delete node;
	
	return;
}
