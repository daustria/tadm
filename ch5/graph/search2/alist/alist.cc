#include <algorithm>
#include "alist.h"


Graph::State Graph::state(char v) const 
{
	std::unordered_map<char, Vertex>::const_iterator it = vertices.find(v);
	if(it != vertices.cend())
	{
		return it->second.s;
	}
	//v does not exist as a vertex
#ifndef NDEBUG
	printf("%s | %c does not exist as a vertex\n", __func__, v);
#endif
	return State::undiscovered;
}

void Graph::mark(char v, Graph::State state)
{
	std::unordered_map<char, Vertex>::iterator it = vertices.find(v);
	it->second.s = state;
}

void Graph::insert_vertex(const char v)
{
	if(adjList.find(v) != adjList.end())
	{
#ifndef NDEBUG
		printf("%s | adjacency list already contains vertex %c\n", __func__, v);
		return;
#endif
	}

	//we can insert v since we know it is not a vertex yet
	std::list<char> edgelist;
	edgelist.push_back({v});
	adjList.insert({v, edgelist});

	vertices.insert({v, Vertex(v)});
}

void Graph::insert_edge(const char a, const char b)
{
	insert_vertex(a);
	insert_vertex(b);

	std::list<char> &edgelist = adjList[a];

	if(std::none_of(edgelist.cbegin(), edgelist.cend(),[b](Vertex v) { return b == v.letter; }))
	{
		edgelist.push_back({b});

#ifndef NDEBUG
		printf("%s | added (%c, %c) as an edge\n", __func__, a, b);
#endif
		// (b,a) is an edge as well for undirected graphs. should be in the list for b.
		if(!directed) insert_edge(b,a);
	}
	else
	{
#ifndef NDEBUG
		printf("%s | tried to add (%c, %c) but it is already an edge\n", __func__, a, b);
#endif
	}
}

std::vector<char> Graph::neighbours(char v) const
{
	//assume v is a vertex
	const std::list<char> &edgelist = adjList.find(v)->second;
	std::vector<char> neighbours_;

	//copy from edgelist.begin()+1 since the first entry contains the vertex for which we are trying to return
	//its neighbours
	std::copy(++edgelist.cbegin(), edgelist.cend(), std::back_inserter(neighbours_));
	return neighbours_;
}

std::vector<char> Graph::nodes() const
{
	std::vector<char> vec;

	for(auto it = vertices.begin(); it != vertices.end(); ++it)
	{
		vec.push_back(it->first);
	}
	return vec;
}

std::ostream &operator<<(std::ostream &out, const Graph &g)
{
	for(const auto &pair: g.adjList)
	{
		std::list<char>::const_iterator it = pair.second.cbegin();
		out << *it << ":";
		++it;
		//the vertex has no edges in its edgelist
		if(pair.second.size() == 1)
		{
			out << std::endl;
			continue;
		}
		while(it != pair.second.cend())
		{
			out << *it << " ";
			++it;
		}
		out << std::endl;
		
	}
	return out;
}


