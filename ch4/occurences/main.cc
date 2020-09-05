#include <vector>
#include <iostream>
#include "quicksort.h"

// binary_search(v, n): returns the index of n in v if it exists
// otherwise, returns the index of where search would be in v
// requires: v is sorted from smallest to largest
int binary_search(const std::vector<int> &v, double n)
{

#ifndef NDEBUG
	printf("%s, searching for %f\n", __FUNCTION__, n);
#endif
	//search in the range [low, high]
	int low = 0;
	int high = v.size() - 1;
	int mid;

	if(low == high) {
		return n == v[0] ? 0 : -1;
	}

	while(low<= high)
	{
		mid = (high + low) / 2;

#ifndef NDEBUG
		printf("low: %d | high: %d | mid: %d\n", low, high, mid);
#endif

		// unsuccessful searches cover intervals [low, mid), (mid, high] 
		if(n < v[mid]) {
			high = mid - 1;
		} else if (n > v[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}

	//in an unsuccessful search (which in this case is all the time) return
	//the index the element would be at if it was inserted into the sorted vector v
	if (n < v[mid]) {
		//target is smaller than the element we landed on.
		//if we were to insert the target, it would be at the index
		//of mid, and the current element would get pushed forward
		return mid;
	} else {
		//target is larger than the element we landed on
		//if we were to insert the target into the vector
		//it would be at the index of mid + 1 since we want it to come after
		//our current element
		return mid + 1;
	}

}
// num_occurences(v, n) returns the number of occurences of n in
// sorted integer vector v
// time: O(log n)
// space: O(1)
int num_occurences(const std::vector<int> &v, int n)
{
	const double target = n;
	const double error = 0.01;
	int high_index = binary_search(v, target+error);
	int low_index = binary_search(v, target-error);

#ifndef NDEBUG
	printf("%s | high_index: %d | low_index: %d\n", __FUNCTION__, high_index, low_index);
#endif
	return high_index - low_index;
}

int main()
{

	std::vector<int> v{1, 2, 3, 4, 4, 4, 4, 4, 6, 6, 7};
	int n = 0;
	while(std::cin >> n)
		printf("%d\n", num_occurences(v, n));
}
