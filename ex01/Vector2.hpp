#ifndef VECTOR2_HPP
# define VECTOR2_HPP

/*
** A pair of coordinates.
**
** x and y are public on purpose: every pair of floats is a valid Vector2,
** so there is no rule to protect. A getter and a setter that only read and
** write the value would hide nothing.
*/
struct Vector2
{
	float	x;
	float	y;

	Vector2();
	Vector2(float p_x, float p_y);
};

#endif
