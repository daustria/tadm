#include "list.h"
#include <iostream>

int main()
{
	Node *n0 = new Node{1, nullptr};
	Node *n1 = new Node{2, nullptr};
	Node *n2 = new Node{3, nullptr};

	List ll{n0};
	n0->
	Node *head = new Node{1, nullptr};
	head->next = new Node{2, nullptr};
	head->next->next = new Node{3, nullptr};

	std::cout << *head << std::endl;	
}
