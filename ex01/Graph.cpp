#include <cmath>
#include <iomanip>
#include <new>
#include "Graph.hpp"

namespace
{
	const float	maxSize = 100.0f;

	// Written so that NaN and negative values give 0.
	float	clampSize(float value)
	{
		if (!(value > 0.0f))
			return (0.0f);
		if (value > maxSize)
			return (maxSize);
		return (value);
	}

	// The cell of the grid that is the closest to a coordinate.
	int	toCell(float value)
	{
		return (static_cast<int>(std::floor(value + 0.5f)));
	}

	int	countDigits(int value)
	{
		int	digits = 1;

		while (value >= 10)
		{
			value /= 10;
			++digits;
		}
		return (digits);
	}
}

Graph::Graph(const Vector2 &size) : _size(clampSize(size.x), clampSize(size.y))
{
}

const Vector2	&Graph::getSize() const
{
	return (_size);
}

const std::vector<Vector2>	&Graph::getPoints() const
{
	return (_points);
}

// Written so that NaN coordinates are refused too.
bool	Graph::addPoint(const Vector2 &point)
{
	if (!(point.x >= 0.0f && point.x <= _size.x))
		return (false);
	if (!(point.y >= 0.0f && point.y <= _size.y))
		return (false);
	try
	{
		_points.push_back(point);
	}
	catch (const std::bad_alloc &)
	{
		return (false);
	}
	return (true);
}

bool	Graph::hasPointAt(int x, int y) const
{
	std::vector<Vector2>::const_iterator	it;

	for (it = _points.begin(); it != _points.end(); ++it)
	{
		if (toCell(it->x) == x && toCell(it->y) == y)
			return (true);
	}
	return (false);
}

/*
** One line per Y value, from the top to the bottom, then the X axis.
** Every column has the width of the biggest label so the graph stays
** aligned when the size has two or three digits.
*/
void	Graph::print(std::ostream &os) const
{
	const int	maxX = toCell(_size.x);
	const int	maxY = toCell(_size.y);
	const int	width = countDigits(maxX > maxY ? maxX : maxY);

	for (int y = maxY; y >= 0; --y)
	{
		os << std::setw(width) << y;
		for (int x = 0; x <= maxX; ++x)
			os << ' ' << std::setw(width) << (hasPointAt(x, y) ? 'X' : '.');
		os << '\n';
	}
	os << std::setw(width) << "";
	for (int x = 0; x <= maxX; ++x)
		os << ' ' << std::setw(width) << x;
	os << std::endl;
}

std::ostream	&operator<<(std::ostream &os, const Graph &graph)
{
	graph.print(os);
	return (os);
}
