#include <string>
#include <iostream>
#include <cmath>

const int ALPHA = 26;
const int MODULUS = 492876847;

int hash(std::string s, int j, int m)
{

	int output = 0;
	for(int i = 0; i < m; ++i)
	{
		output += pow(ALPHA, m-(i+1)) * char(s[i+j]);
		output %= MODULUS;
	}

#ifndef NDEBUG
	std::cout << "Hash of first " << m << " characters of '" << s << "' : " << output << std::endl;
#endif

	return output;	
}

inline int mod(int a, int b) {int ret = a%b; return ret>=0? ret: ret+b; }

int findmatch(std::string p, std::string t)
{
	const int n = t.length();
	const int m = p.length();

	int val = hash(t, 0, m);
	int patternHash = hash(p, 0, m);

	if(patternHash == val && p == t.substr(0, m)) return 0;

	//use this value to compute H(t,j+1) from H(t,j) without 'actually' computing the former
	static const int conversionValue = static_cast<int>(pow(ALPHA, m-1)) % MODULUS;

	for(int j = 1; j < n - m + 1; ++j)
	{

		val = ALPHA*(val - conversionValue*char(t[j-1])) + char(t[j+m-1]);
		val = mod(val, MODULUS);
#ifndef NDEBUG
		std::cout << "Hash of '" << t.substr(j, m) << "' : " << val << std::endl;
#endif
		if(val == patternHash && t.substr(j, m) == p) return j;
	}	
	return -1;
}

int main()
{
	std::string t{"abc"};
	std::string p{"abc"};

	std::cout << findmatch(p, t) << std::endl;
}
