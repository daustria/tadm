#include <iostream>
#include <vector>
#include "heap.h"
int main()
{
	char c = 0;
	Heap h;
	while(std::cin >> c)
	{
		if(c == 'i') {
			int n = 0;
			std::cin >> n;
			h.insert(n);
		} else if (c == 'm') {
			std::cout << h.getMin() << std::endl;
		} else if (c == 'p') {
			std::cout << h << std::endl;	
		} else if (c == 'd') {
			h.deleteMin();	
		} else if (c == 's') {
			// heapsort:
			// insert the integers into a heap, and then put the data 
			// into a vector using deleteMin()
			int n = 0;
			std::vector<int> list; 
			while(std::cin >> n)
				h.insert(n);

			while(h.size() > 0)
				list.push_back(h.deleteMin());

			for(auto &x : list)
				std::cout << x << " ";
			std::cout << std::endl;

		} else if (c == 'k') {
			int x = 0;
			int k = 0;
			std::cin >> k >> x;
			std::cout << h.biggerThanKthSmallest(x, k) << std::endl;
		} else if (c == 'q') {
			break;
		}
	}
}
