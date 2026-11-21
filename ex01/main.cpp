#include <iostream>
#include "Graph.hpp"

static void	add(Graph &graph, float x, float y)
{
	const bool	added = graph.addPoint(Vector2(x, y));

	std::cout << (added ? "[   OK   ] " : "[REFUSED ] ");
	std::cout << "add point " << x << "/" << y << std::endl;
}

int	main()
{
	Graph	graph(Vector2(5, 5));

	std::cout << "--- The example of the subject ---" << std::endl;
	add(graph, 0, 0);
	add(graph, 2, 2);
	add(graph, 4, 2);
	add(graph, 2, 4);
	std::cout << std::endl << graph << std::endl;

	std::cout << "--- Points outside the graph are refused ---" << std::endl;
	add(graph, 6, 1);
	add(graph, -1, 3);
	add(graph, 5, 5);
	std::cout << std::endl << graph << std::endl;

	/*
	** These lines do not compile: the points can only be changed by addPoint().
	**
	**	graph._points.clear();
	**	graph.getPoints().push_back(Vector2(50, 50));
	*/
	std::cout << "--- Reading the graph with the const getters ---" << std::endl;
	std::cout << "size   : " << graph.getSize().x << "/" << graph.getSize().y << std::endl;
	std::cout << "points : " << graph.getPoints().size() << std::endl;

	std::cout << std::endl << "--- A bigger graph stays aligned ---" << std::endl;
	Graph	big(Vector2(12, 3));
	add(big, 12, 3);
	add(big, 7.4f, 1.6f);
	std::cout << std::endl << big;
	return (0);
}
