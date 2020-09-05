#ifndef DICT_H
#define DICT_H
#include <string>
#include <vector>
#include <iostream>
#include <utility>

//will hash names of people to phone numbers
class PhoneBook
{
	typedef std::pair<std::string, std::string> HashEntry;
	friend std::ostream &operator<<(std::ostream &, const PhoneBook &);

	public:
		PhoneBook();

		//requires keys/names to be unique	
		void insert(const std::string &name, const std::string &number);
		//get the value related to a key
		const std::string get(const std::string &) const;
		//does not require key to be in the hash table
		void remove(const std::string &);
	private:

		static const HashEntry deleted;
		static const HashEntry empty;

		int hash(const std::string &) const;

		//probes the table for a position to insert key 
		const int probeInsert(const std::string &key) const;

		//probes the table for a position where the HashEntry of key is located
		const int probeSearch(const std::string &key) const;

		int size;

		// table of key value pairs
		std::vector< HashEntry > table;

};

std::ostream &operator<<(std::ostream &, const PhoneBook &);

#endif //DICT_H
