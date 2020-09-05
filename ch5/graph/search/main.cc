#include "alist/alist.h"
#include <list>
#include <unordered_map>


void process(char vertex)
{
	std::cout << vertex << std::endl;
}

void addNeighbours(char vertex, std::list<char> &toProcess, Graph g)
{
	std::vector<char> neighbours = g.neighbours(vertex);
	for (char u : neighbours)
	{
		toProcess.push_back(u);
		g.mark(u, Graph::State::discovered);
	}
}

void bfs(Graph g, char root)
{
	std::list<char> toProcess;
	process(root);

	addNeighbours(root, toProcess, g);
	g.mark(root, Graph::State::processed);

	while(!toProcess.empty())
	{
		char next = toProcess.front();
		toProcess.pop_front();
		
		Graph::State state = g.state(next);

		if(state == Graph::State::undiscovered) {
			// add its children to process
			addNeighbours(next, toProcess, g);
			process(next);
			g.mark(next, Graph::State::processed);
		} else if(state == Graph::State::discovered) {
			process(next);
		} else if(state == Graph::State::processed) {
			//do nothing	
		}
			g.mark(next, Graph::State::processed);

	}


}

int main()
{

	Graph tree;
	tree.insert_vertex('a');
	tree.insert_vertex('b');
	tree.insert_vertex('c');
	tree.insert_vertex('d');
	tree.insert_vertex('e');
	tree.insert_vertex('f');
	tree.insert_vertex('f');
	tree.insert_vertex('g');
	tree.insert_vertex('h');

	tree.insert_edge('a', 'b');
	tree.insert_edge('b', 'c');
	tree.insert_edge('b', 'd');
	tree.insert_edge('c', 'e');
	tree.insert_edge('c', 'f');
	tree.insert_edge('d', 'g');
	tree.insert_edge('d', 'h');

	bfs(tree, 'a');

}
