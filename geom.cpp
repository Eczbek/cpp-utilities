#include "./geom.hpp"

util::geom::point::point (double x, double y)
	: x(x), y(y)
{}

bool util::geom::point::operator== (const util::geom::point& point) const
{
	return x == point.x && y == point.y;
}

bool util::geom::point::operator!= (const util::geom::point& point) const
{
	return !(point == *this);
}


