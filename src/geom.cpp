#include <util/geom.hpp>
#include <util/alg.hpp>
#include <util/math.hpp>
#include <util/num.hpp>


util::geom::point::point(const double x, const double y)
	: x(x), y(y)
{}

bool util::geom::point::operator==(const util::geom::point& other) const {
	return util::math::approx_equal(x, other.x) && util::math::approx_equal(y, other.y);
}

bool util::geom::point::operator!=(const util::geom::point& other) const {
	return !operator==(other);
}

util::geom::point util::geom::point::rotate(const util::geom::point& origin, const double angle) const {
	return {
		origin.x + std::cos(angle) * (x - origin.x) - std::sin(angle) * (y - origin.y),
		origin.y + std::cos(angle) * (y - origin.y) + std::sin(angle) * (x - origin.x)
	};
}

util::geom::line::line(const util::geom::point& start, const util::geom::point& end)
	: start(start), end(end)
{}

util::geom::line::line(const util::geom::point& start, const double angle)
	: start(start)
{
	if (util::math::approx_equal(std::fmod(angle + std::numbers::pi / 2, std::numbers::pi), 0.0))
		end = util::geom::point(start.x, start.y - 1);
	else 
		end = util::geom::point(start.x + 1, std::tan(angle));
}

bool util::geom::line::operator==(const util::geom::line& other) const {
	return slope() == other.slope() && contains(other.start);
}

bool util::geom::line::operator!=(const util::geom::line& other) const {
	return !operator==(other);
}

double util::geom::line::slope() const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::line::intercept_x() const {
	return start.x - slope() * start.y;
}

double util::geom::line::intercept_y() const {
	return start.y - slope() * start.x;
}

double util::geom::line::angle() const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + util::num::tau, std::numbers::pi);
}

std::optional<util::geom::point> util::geom::line::intersection(const util::geom::line& other) const {
	const double a = (start.x - end.x) * (other.start.y - other.end.y) - (start.y - end.y) * (other.start.x - other.end.x);
	if (a) {
		const util::geom::point intersection(((other.start.x - other.end.x) * (start.x * end.y - start.y * end.x) - (start.x - end.x) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a, ((other.start.y - other.end.y) * (start.x * end.y - start.y * end.x) - (start.y - end.y) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a);
		if (contains(intersection) && other.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::line::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y);
}

util::geom::ray::ray(const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

util::geom::ray::ray(const util::geom::point& start, const double angle)
	: util::geom::line(start, angle)
{}

bool util::geom::ray::operator==(const util::geom::ray& other) const {
	return start == other.start && contains(other.end);
}

bool util::geom::ray::operator!=(const util::geom::ray& other) const {
	return !operator==(other);
}

bool util::geom::ray::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
			&& slope < std::numeric_limits<double>::lowest()
				? other.y >= start.y
				: other.y <= start.y
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x <= end.x
				? other.x >= start.x
				: other.x <= start.x)
			&& (start.y <= end.y
				? other.y >= start.y
				: other.y <= start.y);
}

util::geom::segment::segment(const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::segment::operator==(const util::geom::segment& other) const {
	return start == other.start && end == other.end || start == other.end && end == other.start;
}

bool util::geom::segment::operator!=(const util::geom::segment& other) const {
	return !operator==(other);
}

double util::geom::segment::length() const {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::segment::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
			&& (other.y >= start.y && other.y <= end.y || other.y <= start.y && other.y >= end.y)
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x < end.x
				? other.x >= start.x && other.x <= end.x
				: other.x <= start.x && other.x >= end.x)
			&& (start.y < end.y
				? other.y >= start.y && other.y <= end.y
				: other.y <= start.y && other.y >= end.y);
}

util::geom::polygon::polygon(const std::vector<util::geom::point>& points)
	: points(points)
{}

bool util::geom::polygon::operator==(const util::geom::polygon& other) const {
	return util::alg::rotated_match(points.begin(), points.end(), other.points.begin(), other.points.end()) || util::alg::rotated_match(points.rbegin(), points.rend(), other.points.begin(), other.points.end());
}

bool util::geom::polygon::operator!=(const util::geom::polygon& other) const {
	return !operator==(other);
}

double util::geom::polygon::area() const {
	double area = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		area += current.x * next.y - next.x * current.y;
	}
	return area / 2;
}

double util::geom::polygon::perimeter() const {
	double perimeter = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		perimeter += std::hypot(current.x - next.x, current.y - next.y);
	}
	return perimeter;
}

std::vector<util::geom::segment> util::geom::polygon::sides() const {
	std::vector<util::geom::segment> sides;
	for (std::size_t i = 0; i < points.size(); ++i)
		sides.push_back({ points[i], points[(i + 1) % points.size()] });
	return sides;
}

bool util::geom::polygon::contains(const util::geom::point& point) const {
	util::geom::ray ray(point, { point.x + 1, point.y });
	std::size_t intersections = 0;
	for (const util::geom::segment& segment : sides())
		intersections += ray.intersection(segment).has_value();
	return intersections % 2;
}

util::geom::ellipse::ellipse(const util::geom::point& center, const util::geom::point& radius, const double rotation)
	: center(center), radius(radius), rotation(rotation)
{}

bool util::geom::ellipse::operator==(const util::geom::ellipse& other) const {
	return center == other.center && radius == other.radius && util::math::approx_equal(std::fmod(rotation, std::numbers::pi), std::fmod(other.rotation, std::numbers::pi));
}

bool util::geom::ellipse::operator!=(const util::geom::ellipse& other) const {
	return !operator==(other);
}

double util::geom::ellipse::area() const {
	return std::numbers::pi * radius.x * radius.y;
}

double util::geom::ellipse::perimiter() const {
	return std::numbers::pi * std::sqrt(2 * (radius.x * radius.x + radius.y * radius.y));
}

bool util::geom::ellipse::contains(const util::geom::point& point) const {
	const double a = std::cos(rotation) * (point.x - center.x) + std::sin(rotation) * (point.y - center.y);
	const double b = std::sin(rotation) * (point.x - center.x) - std::cos(rotation) * (point.y - center.y);
	return a * a / radius.x / radius.x + b * b / radius.y / radius.y <= 1;
}

std::pair<std::optional<util::geom::point>, std::optional<util::geom::point>> util::geom::ellipse::intersections(const util::geom::line& line) const {
	std::pair<std::optional<util::geom::point>, std::optional<util::geom::point>> intersections;
	const double a = radius.y * radius.y * line.end.x * line.end.x + radius.x * radius.x * line.end.y * line.end.y;
	const double b = 2 * radius.y * radius.y * line.start.x * line.end.x + 2 * radius.x * radius.x * line.start.y * line.end.y;
	const double c = radius.y * radius.y * line.start.x * line.start.x + radius.x * radius.x * line.start.y * line.start.y - radius.x * radius.x * radius.y * radius.y;
	const double d = std::sqrt(b * b - 4 * a * c) / 2 / a;
	const double e = b * b - 4 * a * c;
	const bool f = util::math::approx_equal(e, 0.0);
	if (e > 0 || f) {
		const util::geom::point g(center.x + line.start.x + (d - b) * (line.end.x - line.start.x), center.y + line.start.y + (d + b) * (line.end.y - line.start.y));
		if (line.contains(g))
			intersections.first = g;
		if (e > 0 && !f) {
			const util::geom::point h(center.x - line.start.x - (d - b) * (line.end.x - line.start.x), center.y - line.start.y - (d + b) * (line.end.y - line.start.y));
			if (line.contains(h))
				intersections.second = h;
		}
	}
	return intersections;
}

std::vector<util::geom::point> util::geom::ellipse::intersections(const util::geom::ellipse& other) const {
	return {}; // TODO
}

util::geom::circle::circle(const util::geom::point& center, const double radius)
	: util::geom::ellipse(center, { radius, radius })
{}

bool util::geom::circle::operator==(const util::geom::circle& other) const {
	return center == other.center && util::math::approx_equal(radius.x, other.radius.x);
}

bool util::geom::circle::operator!=(const util::geom::circle& other) const {
	return !operator==(other);
}

bool util::geom::circle::contains(const util::geom::point& point) const {
	return std::hypot(point.x - center.x, point.y - center.y) <= radius.x;
}

std::pair<std::optional<util::geom::point>, std::optional<util::geom::point>> util::geom::circle::intersections(const util::geom::circle& other) const {
	return {}; // TODO
}

util::geom::rectangle::rectangle(const util::geom::point& corner1, const util::geom::point& corner2)
	: util::geom::polygon({ corner1, { corner2.x, corner1.y }, corner2, { corner1.x, corner2.y } })
{}

util::geom::rectangle::rectangle(const util::geom::segment& segment)
	: util::geom::polygon({ segment.start, segment.end })
{}

util::geom::rectangle::rectangle(const util::geom::polygon& polygon)
	: util::geom::polygon({})
{
	if (!polygon.points.size())
		util::geom::polygon({});
	util::geom::point min = polygon.points[0];
	util::geom::point max = polygon.points[0];
	for (std::size_t i = 1; i < polygon.points.size(); ++i) {
		const util::geom::point& point = polygon.points[i];
		if (point.x < min.x)
			min.x = point.x;
		else if (point.x > max.x)
			max.x = point.x;
		if (point.y < min.y)
			min.y = point.y;
		else if (point.y > max.y)
			max.y = point.y;
	}
	points = { min, { max.x, min.y }, max, { min.x, max.y } };
}

util::geom::rectangle::rectangle(const util::geom::ellipse& ellipse)
	: util::geom::polygon({})
{
	const double a = std::sqrt(ellipse.radius.x * ellipse.radius.x  * std::cos(ellipse.rotation) * std::cos(ellipse.rotation) + ellipse.radius.y * ellipse.radius.y * std::cos(ellipse.rotation + std::numbers::pi / 2) * std::cos(ellipse.rotation + std::numbers::pi / 2));
	const double b = std::sqrt(ellipse.radius.x * ellipse.radius.x * std::sin(ellipse.rotation) * std::sin(ellipse.rotation) + ellipse.radius.y * ellipse.radius.y * std::sin(ellipse.rotation + std::numbers::pi / 2) * std::sin(ellipse.rotation + std::numbers::pi / 2));
	points = { { ellipse.center.x - a, ellipse.center.y - b }, { ellipse.center.x + a, ellipse.center.y - b }, { ellipse.center.x + a, ellipse.center.y + b }, { ellipse.center.x - a, ellipse.center.y + b } };
}

bool util::geom::rectangle::operator==(const util::geom::rectangle& other) const {
	return points[0] == other.points[0] && points[2] == other.points[2] || points[0] == other.points[2] && points[2] == other.points[0];
}

bool util::geom::rectangle::operator!=(const util::geom::rectangle& other) const {
	return !operator==(other);
}

double util::geom::rectangle::width() const {
	return std::fabs(points[0].x - points[2].x);
}

double util::geom::rectangle::height() const {
	return std::fabs(points[0].y - points[2].y);
}

double util::geom::rectangle::area() const {
	return width() * height();
}

double util::geom::rectangle::perimeter() const {
	return (width() + height()) * 2;
}

bool util::geom::rectangle::contains(const util::geom::point& point) const {
	return (point.x >= points[0].x && point.x <= points[2].x || point.x <= points[0].x && point.x >= points[2].x) && (point.y >= points[0].y && point.y <= points[2].y || point.y <= points[0].y && point.y >= points[2].y);
}
