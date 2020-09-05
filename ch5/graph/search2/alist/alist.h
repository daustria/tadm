#ifndef ALIST_H
#define ALIST_H
#include <unordered_map>
#include <list>
#include <iostream>
#include <vector> 
#define NDEBUG

class Graph
{

	struct Vertex;

	friend std::ostream &operator<<(std::ostream &, const Graph &);

	public:
		enum class State{undiscovered, discovered, processed};

		State state(char v) const;
		void mark(char v, State state);
		unsigned int degree(char v) const;
		std::vector<char> neighbours(char v) const;	
		std::vector<char> nodes() const;

		void insert_vertex(const char v);
		void insert_edge(const char a, const char b);
	private:


		struct Vertex 
		{
			Vertex() = default;
			Vertex(char letter): letter(letter) {}
			char letter;
			State s = State::undiscovered;
		};

		//edge list of each vertex
		std::unordered_map<char, std::list<char>> adjList;
		//each vertex and its discovery state
		std::unordered_map<char, Vertex> vertices;
		unsigned int numVertices = 0;
		const bool directed = 0;
	
};

std::ostream &operator<<(std::ostream &, const Graph &);

#endif //ALIST_H
