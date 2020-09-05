#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>
#include <vector>
#include <algorithm>

//quicksort: sorts the contents of v from the interval [low, high)
//time: O(n log n) on average
//space: O(1) sorts the vector in-place
void quicksort_core(std::vector<int> &v, std::vector<int>::iterator low, std::vector<int>::iterator high)
{
	// the array is already sorted in this interval [low, high)
	if(low == high) return;

	//first we partition the array, choosing the pivot to be
	//the last element
	std::vector<int>::iterator firsthigh = low;
	std::vector<int>::iterator pivot = high - 1;

#ifndef NDEBUG
	int t = low - v.begin();
	int s = high - v.begin();
	printf("%s | range: [%i, %i) | pivot: %i\n", __func__, t, s, *pivot);
#endif
	for(auto it = low; it != pivot; ++it)
	{
		/*
		 * we maintain two intervals:
		 *
		 * 1) [low, firstigh) to be less than the pivot element 
		 * 2) [firsthigh, i) to be bigger than the pivot element
		 *
		 * in a single pass, we can make these two intervals cover the entire range [low, high)
		 * so that in this range, everthing to the left of firsthigh is smaller than the pivot and
		 * everything to the right is greater than the pivot element.
		 * */

		if (*it < *pivot) {
			// we want elements to the right of firsthigh to be bigger than the pivot
			// so we swap it with the current element we are processing.
			// since everything to the left of firsthigh is already less than the pivot,
			// and the element AT firsthigh is now less than the pivot, 
			// the first element greater than the pivot will be one element to the right of firsthigh
			// so we increment firsthigh.
			std::iter_swap(firsthigh, it);
			++firsthigh;
		} 

		// in the case that the explored element is bigger than the pivot, it suffices to do nothing
		// because our intervals are maintained
	}	

	//now, firsthigh is the position of the pivot element when the array is sorted
	//so we swap the values at firsthigh and pivot
	std::iter_swap(firsthigh, pivot);
	pivot = firsthigh; // as a result of the swap, the pivot is now the element at firsthigh 

#ifndef NDEBUG
	std::cout << "after partitioning with pivot element : ";
	for(auto &x : v)
		std::cout << x << " ";
	std::cout << std::endl;

	int rangeLow = low - v.begin();
	int rangeHigh = high - v.begin();
	int pivotIndex = pivot - v.begin();

	printf("sorting ranges [%i, %i), [%i, %i)\n", rangeLow, pivotIndex, pivotIndex+1, rangeHigh);
#endif
	quicksort_core(v, low, pivot);
	quicksort_core(v, pivot+1, high);
}

void quicksort(std::vector<int> &v)
{
	// randomly permuting the elements can help to secure an average-case runtime,
	// which is great for quicksort
	std::random_shuffle(v.begin(), v.end());
	quicksort_core(v, v.begin(), v.end());
}
#endif //QUICKSORT_H
