#include "phonebook.h"
#include <iostream>
int main()
{
	char c;
	std::string key;
	std::string number;
	PhoneBook book;

	while (std::cin >> c)
	{
		if(c == 'i') {
			std::cin >> key >> number;
			book.insert(key, number);
		} else if (c == 'd') {
			std::cin >> key;
			book.remove(key);
		} else if (c == 'p') {
			std::cout << book << std::endl;
		} else if (c == 'q') {
			break;
		}
	}
}
