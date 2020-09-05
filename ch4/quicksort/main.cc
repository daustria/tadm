#include <iostream>
#include <vector>
#include <time.h>
#include "quicksort.h"

int main()
{

	std::vector<int> v;
	int n = 0;

	while(std::cin >> n)
		v.push_back(n);

	clock_t t = clock();
	quicksort(v);
	t = clock() - t;

	printf("It took approximately %f seconds to sort the data: \n", static_cast<float>(t)/CLOCKS_PER_SEC);

	for(auto &x : v)
		std::cout << x << " ";
	std::cout << "." << std::endl;
}
