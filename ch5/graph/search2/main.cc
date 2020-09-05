#include "alist/alist.h"
#include <list>
#include <unordered_map>
#include <vector>

//global variables arent nice, but im not really concerned with design

//these variables record information about the DFS traversal
std::unordered_map<char, char> parent; // tree edges
std::unordered_map<char, char> entryTime; 
std::unordered_map<char, char> exitTime;
int timer = 0;
std::unordered_map<char, char> reachable; // earliest reachable ancestor of a vertex, using a backedge
std::unordered_map<char, unsigned int> treeChildren; //number of children the node has in the DFS tree

//if we want to use pairs as keys, we need to provide a hash function. heres a basic and bad one.
struct pair_hash {
	template <class T, class U>
	std::size_t operator() (const std::pair<T,U> &p) const {
		auto h1 = std::hash<T>{}(p.first);
		auto h2 = std::hash<U>{}(p.second);
		return h1 ^ (37*h2);
	}
};
std::unordered_map<std::pair<char, char>, bool, pair_hash> treeEdge; // 1 if {u,v} is a tree edge, 0 otherwise



void process_early(char vertex)
{
	reachable[vertex] = vertex;
	treeChildren[vertex] = 0;
}

void process_late(Graph &g, char v)
{
	// we'll now see if vertex is a cut vertex or not.
	// we proved that if v is not the root, then v is a cut vertex if and only if:
	// 1) v is not a leaf vertex, it doesn't have degree 1
	// 2) reachable(v) = parent(v) OR v itself	

	std::vector<char> neighbours = g.neighbours(v);
	bool isRoot = parent.find(v) == parent.end();
	//first, we'll check if v is the root vertex
	if(isRoot)
	{
		//the root vertex is a cut vertex if it has more than two tree edges
		if(treeChildren[v] > 1)
			printf("%c is a cut vertex, and it is the root\n", v);
	}
	else
	{
		bool isLeaf = treeChildren[v] == 0;
		if(reachable[v] == v && !isLeaf)
		{
			printf("%c is a cut vertex because it is not a leaf, and it's earliest reachable ancestor is itself\n", v);
		}
		else if(reachable[v] == parent[v])
		{
			if(parent.find(parent[v]) != parent.end())
			{
				printf("%c is a cut vertex, and it is a parent of %c\n", parent[v], v);
			}
			if(!isLeaf)
			{
				printf("%c is a cut vertex, since it isn't a leaf and its earliest reachable ancestor is its parent %c\n", v, parent[v]);
			}
		}

		if(entryTime[reachable[parent[v]]] > entryTime[reachable[v]])
		{
			reachable[parent[v]] = reachable[v];
		}
	}
}



void process_edge(char v, char u)
{

}

void dfs(Graph &g, char v);

void dfs_core(Graph &g, char root)
{
	parent.clear();
	entryTime.clear();
	exitTime.clear();
	reachable.clear();
	treeEdge.clear();
	treeChildren.clear();
	timer = 0;

	dfs(g, root);
}

//DFS Search on undirected graphs
void dfs(Graph &g, char u)
{
	g.mark(u, Graph::State::discovered);
	//process u early, here, if desired
	process_early(u);
	//record entry time in u, if desired	
	++timer;
	entryTime[u] = timer;

	std::vector<char> neighbours = g.neighbours(u);
	for(const char v : neighbours)
	{
		//if v is discovered then we are already processing it as this is DFS
		//if it is processed, we dont need to do anything
		if(g.state(v) == Graph::State::undiscovered)
		{
			parent[v] = u;
			treeEdge[{u, v}] = 1;
			treeEdge[{v, u}] = 1;
			process_edge(u, v);
			treeChildren[u] += 1;

			dfs(g, v);
		}
		//back edge check
		if(treeEdge.find({u, v}) == treeEdge.end())
		{

			// if v is not undiscovered, then this is the second time we are looking
			// at the edge (v,u) since we already looked at it when processing v
			// this ensures we only look at each edge in the graph once

			// TODO: prove, at least informally, 
			// this algorithm works if we update reachable here and in process_late()
			if(entryTime[v] < entryTime[reachable[u]])
			{
				reachable[u] = reachable[v];
			}
		}
	}
	exitTime[u] = timer;
	++timer;
	//record exit time of u, if desired
	//process v late, here, if desired
	process_late(g, u);
	g.mark(u, Graph::State::processed);

}

int main()
{

	/*
	 *
	 * A     D
	 * | \ / |
	 * |  C  |
	 * | / \ |
	 * B     E
	 *
	 */
	// C is a cut vertex
	Graph g;
	g.insert_vertex('a');
	g.insert_vertex('b');
	g.insert_vertex('c');
	g.insert_vertex('d');
	g.insert_vertex('e');

	g.insert_edge('a','c');
	g.insert_edge('b','c');
	g.insert_edge('a','b');
	g.insert_edge('c', 'd');
	g.insert_edge('d', 'e');
	g.insert_edge('e', 'c');

	dfs_core(g, 'a');

}
