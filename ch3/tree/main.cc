#include "tree.h"
#include <iostream>

int main()
{

	char c;
	BinaryTree bt;
	while(std::cin >> c)
	{
		switch(c)
		{
			case('i'):
				int n;
				if(std::cin >> n)
					bt.insert(n);
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
			default:
				break;
		}
	}
}
