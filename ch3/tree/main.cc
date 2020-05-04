#include "tree.h"
#include <iostream>

int main()
{

	char c = 0;
	int n = 0;
	BinaryTree bt;
	while(std::cin >> c)
	{
		switch(c)
		{
			case('i'):
				if(std::cin >> n) bt.insert(n);
				break;
			case('m'):
				std::cout << bt.findMin() << std::endl;
				break;
			case('M'):
				std::cout << bt.findMax() << std::endl;
				break;
			case('p'):
				std::cout << bt << std::endl;
				break;
			case('r'):
				if(std::cin >> n) bt.remove(n);
				break;
			default:
				break;
		}
	}
}
