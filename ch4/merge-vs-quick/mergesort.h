#ifndef MERGESORT_H
#define MERGESORT_H
// merge: returns a vector containing the data of v1 and v2 in sorted order
// requires: v1, v2 are sorted from smallest to largest
// time: O(min(n,m))
// space: O(n+m)
std::vector<int> merge(std::vector<int> &v1, std::vector<int> &v2)
{
	//container for the contents of v1 and v2
	//this buffer is necessary when sorting an array/vector
	std::vector<int> sorted{};
	sorted.reserve(v1.size() + v2.size());

	//iterate over the two lists in lockstep, add them to the new container
	std::vector<int>::iterator i1 = v1.begin();
	std::vector<int>::iterator i2 = v2.begin();

	while(1) 
	{
		if(i1 != v1.end() && i2 != v2.end()) {

			if(*i1 < *i2) {
				sorted.push_back(*i1);
				++i1;
			} else {
				sorted.push_back(*i2);
				++i2;
			}
		} else if (i2 != v2.end()) {
			sorted.push_back(*i2);
			++i2;
		} else if (i1 != v1.end()) {
			sorted.push_back(*i1);
			++i1;	
		} else {
			return sorted;
		}
	}
}

//mergesort: sorts the contents of v
//time: O(n log n) 
//each level in the tree requires linear work for merging
//space: O(n)  
//we can use geometric series to achieve a bound of 2n
void mergesort(std::vector<int> &v)
{
	int n = v.size();
	if(n <= 1) return;

	std::vector<int>::iterator mid = v.begin() + n/2;

	std::vector<int> lower{v.begin(), mid};
	std::vector<int> upper{mid, v.end()};

	//sort the two halves, and then merge them together
	mergesort(lower);
	mergesort(upper);

	v = merge(lower, upper);
}

#endif //MERGESORT_H
