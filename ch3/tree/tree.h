#ifndef TREE_H
#define TREE_H
#include <iostream>

class BinaryTree
{
	struct Node;
	public:
		BinaryTree();
		~BinaryTree();
		void insert(int);
		bool remove(int);		
		int findMin() const;
		int findMax() const;
		friend std::ostream &operator<<(std::ostream &, const BinaryTree &);
	private:
		Node *root;
		friend std::ostream &operator<<(std::ostream &, const Node *);
	
};

std::ostream &operator<<(std::ostream &, const BinaryTree &);


#endif //TREE_H
