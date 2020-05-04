#ifndef LIST_H
#define LIST_H
struct List
{
	struct Node 
	{
		int data;
		Node *next = nullptr;
	};
	public:
		Node *head = nullptr;	
		
};
#endif //LIST_H
