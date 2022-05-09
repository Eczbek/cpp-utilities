#include "./geom.hpp"

#include "./math.hpp"

util::geom::point::point (double x, double y)
	: x(x), y(y)
{}

util::geom::point::point ()
	: valid(false)
{}

bool util::geom::point::operator== (const util::geom::point& point) const {
	return util::math::approx_eq(x, point.x) && util::math::approx_eq(y, point.y);
}

bool util::geom::point::operator!= (const util::geom::point& point) const {
	return !operator==(point);
}
