#include <iostream>
#include <vector>
#include <time.h>
#include "mergesort.h"

int main()
{

	/* test the mergesort function
	std::vector<int> v{1,3,5,7,9};
	std::vector<int> u{4,6,5,8};

	std::vector<int> w = merge(v, u);

	for(auto &x : w)
		std::cout << x << " ";
	std::cout << "." << std::endl;
	*/


	std::vector<int> v;
	int n = 0;

	while(std::cin >> n)
		v.push_back(n);

	clock_t t = clock();
	mergesort(v);
	t = clock() - t;
	printf("It took approximately %f seconds to sort the data: \n", static_cast<float>(t)/CLOCKS_PER_SEC);

	for(auto &x : v)
		std::cout << x << " ";
	std::cout << "." << std::endl;
}
