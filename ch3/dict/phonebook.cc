#include "phonebook.h"
#include <cassert>
#include <cmath>

const PhoneBook::HashEntry PhoneBook::deleted = {"DELETED", "DELETED"};
const PhoneBook::HashEntry PhoneBook::empty = {"", ""};
//list size should be prime for open addressing
//TODO: implement a function to move to another hash table of a larger prime,  ideally twice the size of the older prime
PhoneBook::PhoneBook() : size(101), table(std::vector<PhoneBook::HashEntry>(size, PhoneBook::empty)) {}

int PhoneBook::hash(const std::string &key) const
{
	// treat letters in strings as 
	// digits in a base-26 number system
	const int alpha = 26;
	const int len = key.length();
	int value = 0;
	for(int i = 0; i < len; ++i)
	{
		int c = key.at(i);
		value += pow(alpha, i)*c; 
		value %= size; //prevent the values from getting too big
	}

#ifndef NDEBUG
	std::cout << "The hash of " << key << " is " << value << std::endl;
#endif

	return value;
}

const int PhoneBook::probeInsert(const std::string &key) const
{
	// search for a spot to insert the key, using linear probing
	// this is different from probeSearch because we can insert at DELETED or EMPTY spots
	int k = hash(key);
	int initialHash = k;

#ifndef NDEBUG
	std::cout << "Probe sequence to insert " << key << std::endl;
#endif

	while(1)
	{
#ifndef NDEBUG
		std::cout << k << " ";
#endif

		auto entry = table[k];

		// if the entry is empty, deleted return the index
		// if the entry contains the HashEntry for key, return the index also.
		if(entry == empty || entry == deleted || entry.first == key) break;

		// ensure we do not do more than size iterations
		k = (k+1) % size; 

		if(k == initialHash) {
			k = -1;
			break;
		}
	}
#ifndef NDEBUG
	std::cout << std::endl;
#endif

	return k;
}

const int PhoneBook::probeSearch(const std::string &key) const
{
	// search for key using linear probing
	// we stop when we find either an EMPTY slot or a slot with a hash entry
	int k = hash(key);
	// keep the initial hash to check if we already searched the entire hash table
	int initialHash = k;

#ifndef NDEBUG
	std::cout << "Probe sequence to search for " << key << std::endl;
#endif

	while(1)
	{
#ifndef NDEBUG
		std::cout << k << " ";
#endif
		auto entry = table[k];
		if(entry.first == key) break;

		k = (k+1) % size;
		if(k == initialHash) {
			k = -1;
			break;	
		}
	}

#ifndef NDEBUG
	std::cout << std::endl;
#endif
	return k;
}

void PhoneBook::insert(const std::string &name, const std::string &number)
{
	int index = probeInsert(name);
	table[index] = { name, number };
}

const std::string PhoneBook::get(const std::string &name) const
{
	int index = probeSearch(name);
	return table[index].second;
}

void PhoneBook::remove(const std::string &name)
{
	int index = probeSearch(name);
	table[index] = deleted;
}


std::ostream &operator<<(std::ostream &out, const PhoneBook &pb)
{
	int len = pb.table.size();

	for(int i = 0; i < len; ++i)
	{
		const PhoneBook::HashEntry entry = pb.table[i];
		if (entry != pb.empty) out << "index " << i << " : " << entry.first << "," << entry.second << std::endl;
	}

	return out;
}
