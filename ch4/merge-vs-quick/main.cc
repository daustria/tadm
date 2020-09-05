#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <cassert>
#include <ctime>
#include "mergesort.h"
#include "quicksort.h"

int main(int argc, char **argv)
{

	if(argc != 2) {	
		std::cout << "put the sorting data size as the argument" << std::endl;
		return -1;
	}

	std::string s{argv[1]};
	int data_size = std::stoi(s);

	printf("generating an integer vector spanning the interval [0,%i)\n", data_size);

	std::vector<int> v(data_size);
	std::iota(std::begin(v), std::end(v), 0);	
	std::cout << "shuffling the vector..." << std::endl;
	std::random_shuffle(v.begin() ,v.end());
	std::cout << "making a copy of the vector..." << std::endl;
	std::vector<int> copy{v};
	std::cout << "done generating" << std::endl;

	time_t start;
	time_t done;
	double delta;

	time(&start);
	mergesort(v);
	time(&done);
	delta = difftime(done,start);

	printf("It took approximately %f seconds to sort the data using mergesort\n", delta);

	time(&start);
	quicksort(copy);
	time(&done);
	delta = difftime(done, start);

	printf("It took approximately %f seconds to sort the data using quicksort\n", delta);
}
