#include <iostream>
#include <string>

// if string p occurs in string t as a substring, 
// returns the index of the first occurence of p in t.
// otherwise, returns -1
int findmatch(std::string p, std::string t)
{
	int n = p.length();
	int m = t.length();

	// if m > n, then the loop is not entered
	for(int i = 0; i < m - n + 1; ++i)
	{
		int found = 1;
		for(int j = 0; j < n; ++j)
			if (t[i+j] != p[j]) {
				found = 0;
				break;
			}

		if (found) return i;
	}

	return -1;
}

int main()
{
	std::string target{"Hello my name is dominic"};
	std::string pattern{"name"};
	std::cout << findmatch(pattern, target) << std::endl;
}
