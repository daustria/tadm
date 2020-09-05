#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <iostream>

class Heap
{
	public:
		//default constructors are fine
		void insert(int);
		int getMin() const;
		int deleteMin();
		int size() const { return heap.size(); }
		//Returns true if the kth smallest element is at least x
		//Space: O(k)
		bool biggerThanKthSmallest(int x, int k) const;

		friend std::ostream &operator<<(std::ostream &, const Heap &);
	private:
		std::vector<int> heap;
		
};

#endif //HEAP_H
