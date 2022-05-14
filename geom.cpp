#include "./geom.hpp"
#include "./math.hpp"

bool util::geom::point::operator== (const util::geom::point& point) const {
	return x == point.x && y == point.y;
}

bool util::geom::point::operator!= (const util::geom::point& point) const {
	return !(point == *this);
}

bool util::geom::line::operator== (const util::geom::line& line) const {
	return start == line.start && end == line.end;
}

bool util::geom::line::operator!= (const util::geom::line& line) const {
	return !(line == *this);
}

double util::geom::line::get_slope () const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::line::get_radians () const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + M_TAU, M_PI);
}

double util::geom::line::get_degrees () const {
	return util::math::rad_to_deg(get_radians());
}

std::optional<util::geom::point> util::geom::line::get_intersection (const util::geom::line& line) const {
	const double a = start.x - end.x;
	const double b = start.y - end.y;
	const double c = line.start.x - line.end.x;
	const double d = line.start.y - line.end.y;
	const double e = a * d - b * c;
	if (e) {
		const double f = start.x * end.y - start.y * end.x;
		const double g = line.start.x * line.end.y - line.start.y * line.end.x;
		const util::geom::point intersection { (c * f - a * g) / e, (d * f - b * g) / e };
		if (contains_point(intersection) && line.contains_point(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::line::contains_point (const util::geom::point& point) const {
	return util::math::approx_eq(point.y, point.x * get_slope() - start.x * get_slope() + start.y);
}
