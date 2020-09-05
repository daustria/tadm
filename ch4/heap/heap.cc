#include "heap.h"
#include <iostream>
#include <algorithm>
#include <cassert>

void Heap::insert(int n)
{
	/*
	 * Insert n into the next available position in the array.
	 * While the new element has a parent that does not dominate it,
	 * swap the element and its parent.
	 */

	// We simply insert at the next available position of the array	
	// its okay to have duplicates, we do not need to bother searching for n
	heap.push_back(n);

	// 'bubble up' the new element until the heap order is satisfied

	int index = heap.size() - 1; // index of newly inserted element

#ifndef NDEBUG
	std::cout << "inserting " << n << std::endl;
#endif
	while(1)
	{

		int parentIndex = (index - 1)/2;
		if (parentIndex < 0) break;

		std::vector<int>::iterator parentIt = heap.begin() + parentIndex;
		std::vector<int>::iterator it = heap.begin() + index;

		if(*parentIt > *it)
			// Bubble up the current element
			std::iter_swap(parentIt, it);
		else
			// The child is dominated by its parent
			// and the heap ordering is reachieved
			break;

#ifndef NDEBUG
		std::cout << "swapped " << *it << " with " << *parentIt << std::endl;
		std::cout << "heap after a bubble up: " << *this << std::endl;
#endif

		index = parentIndex;
	}
}

int Heap::getMin() const
{
	// with a heap, we get O(1) runtime for extracting the minimum element
	return heap[0];
}

int Heap::deleteMin()
{
	/*
	 * Replace the root element with the last element in the array, and pop
	 * off the last element.
	 *
	 * The heap order may be invalidated, so we 'bubble down' the new root until
	 * the heap order is satisfied
	 *
	 * deleteMin():
	 * 	Replace the first element with the last element of the heap, and pop off the last element.
	 * 	Let n represent this new root element.
	 *
	 * 	While n is not dominating its children:
	 * 		swap n and the smaller of its two children
	 */

	assert(size() > 0);

	int retval = heap[0];
	heap[0] = heap.back();
	heap.pop_back();

	int index = 0; // track the index of the new root while it bubbles down

#ifndef NDEBUG
	std::cout << "heap after deleting min: " << *this << std::endl;
#endif

	while(1)
	{
		int leftChildIndex = 2*index + 1;
		int rightChildIndex = 2*index + 2;

		//Now work case by case on whether the node has 0, 1, or 2 children
		if(leftChildIndex >= size() && rightChildIndex >= size()) {
			// 0 children, bubble down procedure has stopped
			break;

		} else if (rightChildIndex >= size()) {
			// 1 child, and by construction of heaps it must be the left one

			std::vector<int>::iterator childIt = heap.begin() + leftChildIndex;
			std::vector<int>::iterator it = heap.begin() + index;

			if(*it > *childIt) {
				std::iter_swap(childIt, it);
#ifndef NDEBUG
				std::cout << "swapped " << *it << " with " << *childIt << std::endl;
#endif

				//update the index of the element after it bubbles down
				index = leftChildIndex;
			} else break;


		} else {
			//2 children
			// IF we swap, we do it with the smaller of the two children	
			int indexToSwapWith = heap[leftChildIndex] <= heap[rightChildIndex] ? leftChildIndex : rightChildIndex;

			std::vector<int>::iterator childIt = heap.begin() + indexToSwapWith;
			std::vector<int>::iterator it = heap.begin() + index;

			if(*it > *childIt) {
				std::iter_swap(childIt, it);
#ifndef NDEBUG
				std::cout << "swapped " << *it << " with " << *childIt << std::endl;
#endif

				//update the index of the element after it bubbles down
				index = indexToSwapWith;
			} else break;

#ifndef NDEBUG
			std::cout << "swapped " << *it << " with " << *childIt << std::endl;
#endif

		}

#ifndef NDEBUG
		std::cout << "heap after a bubble down: " << *this << std::endl;
#endif
	}
	return retval;
}

//return true if the k-th smallest element in the heap is bigger than x, false otherwise
bool Heap::biggerThanKthSmallest(int x, int k) const
{
	//count the number of elements smaller than x, up to a maximum of k
	if(size() == 0) return false;

	// vector of indices of nodes to process in the heap.
	// this leverages the heap ordering so that we only process nodes smaller than x.
	// once a node is larger than x, we do not have to process it or any of its descendants
	std::vector<int> toProcess{0}; 
	int count = 0; //number of elements smaller than x

	while(!toProcess.empty())
	{
		//if there are k elements smaller than x,
		//then the k-th smallest element must be smaller than x
		if(count >= k) return false;

		int currentIndex = toProcess.back();
		toProcess.pop_back();

		if(currentIndex >= size()) continue;

		int current = heap[currentIndex];

		// If the current node is greater than x, then that is true for all of its children
		// so, we only process children of nodes smaller than x
		//
		// this block can only run k times, so in total we add a maximum of 3k indices to toProcess
		// hence this function has O(k) runtime and space requirements
		if(current < x)
		{
			++count;
			toProcess.push_back(2*currentIndex+1);
			toProcess.push_back(2*currentIndex+2);
		}
	}
	
	//if we cannot find k elements smaller than x,
	//the k-th smallest element must be larger
	return count < k;
}

std::ostream &operator<<(std::ostream &out, const Heap &h)
{
	for(auto &x : h.heap)
		out << x << " ";
	return out;
}
