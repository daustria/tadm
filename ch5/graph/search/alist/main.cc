#include "alist.h"
#include <iostream>
int main()
{
	Graph g;
	char c = 0; 
	g.insert_vertex('a');
	g.insert_vertex('b');
	g.insert_vertex('c');
	g.insert_vertex('d');
	g.insert_vertex('e');
	g.insert_vertex('f');

	g.insert_edge('a', 'd');

	g.insert_edge('b', 'd');
	g.insert_edge('b', 'e');

	g.insert_edge('c', 'e');
	g.insert_edge('c', 'f');

	while(std::cin >> c)
	{
		if(c == 'e')
		{
			char a = 0;
			char b = 0;
			if(std::cin >> a >> b)
				g.insert_edge(a, b);
		}
		else if (c == 'i')
		{
			char v = 0;
			if(std::cin >> v)
				g.insert_vertex(v);
		}
		else if (c == 'p')
		{
			std::cout << g << std::endl;
		}
		else if (c == 'n')
		{
			char v = 0;
			if(std::cin >> v)
			{
				std::vector<char> neighbours = g.neighbours(v);
				for (const auto &neighbour : neighbours)
					std::cout << neighbour << " ";
				std::cout << std::endl;	
			}
		}
		else
		{
			return 0;
		}
	}
	
}
