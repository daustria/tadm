#include "tree.h"
#include <assert.h>

struct BinaryTree::Node
{
	Node(int);
	~Node();
	friend std::ostream &operator<<(std::ostream &, const Node *);

	int data;
	Node *left;
	Node *right;
};

BinaryTree::Node::Node(int n): data(n), left(nullptr), right(nullptr) {}

BinaryTree::Node::~Node() 
{
	delete left;
	delete right;
}


BinaryTree::BinaryTree():root(nullptr) {}

BinaryTree::~BinaryTree()
{
	delete root;
}

int BinaryTree::findMin() const
{
	assert(root);

	Node *current = root;
	int minSoFar = root->data;
	while(current)
	{
		minSoFar = current->data;
		current = current->left;
	}
	return minSoFar;
}

int BinaryTree::findMax() const
{
	assert(root);

	Node *current = root;
	int maxSoFar = root->data;
	while(current)
	{
		maxSoFar = current->data;
		current = current->right;
	}
	return maxSoFar;
}

void BinaryTree::insert(int n)
{
	Node *current = root;
	Node *previous = nullptr;

	//Search for the spot to insert the new node
	while(current)
	{
		if (n == current->data) {
			return;
		}
		else if(n < current->data) {
			previous = current;
			current = current->left;
		}
		else {
			previous = current;
			current = current->right;
		}
	}

	//Insert the node
	current = new Node(n);

	if(!previous) {
		root = current;
	} else if (n < previous->data) {
		previous->left = current;
	} else {
		previous->right = current;
	}
}


void BinaryTree::remove(int n)
{
	//Assume the data exists in the tree
	assert(root);
	Node *current = root;
	Node *previous = nullptr;
	while(current)
	{
		if(n == current->data) {
			break;
		} else if(n < current->data) {
			previous = current;
			current = current->left;
		} else { 
			previous = current;
			current = current->right;
		}
	}

	//current points to the node to delete,
	//previous points to the parent of current.
	
	//search for the candidate to replace the node which will be deleted
	
	Node *candidate = current;
	Node *candidate_parent = previous;

	if(current->left) {

		candidate = current->left;
		while(candidate->right)
		{
			candidate_parent = candidate;
			candidate = candidate->right;
		}

		candidate_parent->right = candidate->left;
		candidate->left = nullptr;
		current->data = candidate->data;
		delete candidate;
	} else if(current->right) {

		candidate = current->right;
		while(candidate->left)
		{
			candidate_parent = candidate;
			candidate = candidate->left;
		}

		candidate_parent->left = candidate->right;
		candidate->right = nullptr;
		current->data = candidate->data;
		delete candidate;
	} else {
		Node *leaf = previous->left == current ? previous->left : previous->right;
		delete leaf;
	}
}
std::ostream &operator<<(std::ostream &out, const BinaryTree &bt)
{
	if(!bt.root)
		return out << "empty";
	return out << bt.root;
}

std::ostream &operator<<(std::ostream &out, const BinaryTree::Node *node)
{
	//prints the treenodes in a PREORDER traversal
	if(node)
	{
		out << node->data;
		if(node->left)
			out << "," << node->left;
		if(node->right)
			out << "," << node->right;
	}

	return out;
}
