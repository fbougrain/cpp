#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <ostream>
# include <vector>
# include "Vector2.hpp"

/*
** A graph going from (0, 0) to its size, with a list of points on it.
**
** The size and the points are private because the graph has a rule to keep:
** every stored point is inside the graph. addPoint() is the only way to add
** a point, and it refuses the ones that are outside.
*/
class Graph
{
public:
	// The size is forced between 0 and 100 on each axis.
	explicit Graph(const Vector2 &size);

	// Read-only access, by reference (no copy).
	const Vector2				&getSize() const;
	const std::vector<Vector2>	&getPoints() const;

	// Returns false (and stores nothing) if the point is outside the graph.
	bool	addPoint(const Vector2 &point);

	void	print(std::ostream &os) const;

private:
	bool	hasPointAt(int x, int y) const;

	Vector2					_size;
	std::vector<Vector2>	_points;
};

std::ostream	&operator<<(std::ostream &os, const Graph &graph);

#endif
