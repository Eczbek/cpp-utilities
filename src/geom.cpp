#include <util/geom.hpp>
#include <util/alg.hpp>
#include <util/math.hpp>
#include <util/num.hpp>


util::geom::Point::Point(const double x, const double y)
	: x(x), y(y)
{}

bool util::geom::Point::operator==(const util::geom::Point& other) const {
	return util::math::approxEqual(x, other.x) && util::math::approxEqual(y, other.y);
}

bool util::geom::Point::operator!=(const util::geom::Point& other) const {
	return !operator==(other);
}

util::geom::Point util::geom::Point::rotate(const util::geom::Point& origin, const double angle) const {
	return {
		origin.x + std::cos(angle) * (x - origin.x) - std::sin(angle) * (y - origin.y),
		origin.y + std::cos(angle) * (y - origin.y) + std::sin(angle) * (x - origin.x)
	};
}

util::geom::Line::Line(const util::geom::Point& start, const util::geom::Point& end)
	: start(start), end(end)
{}

util::geom::Line::Line(const util::geom::Point& start, const double angle)
	: start(start)
{
	if (util::math::approxEqual(std::fmod(angle + std::numbers::pi / 2, std::numbers::pi), 0.0))
		end = util::geom::Point(start.x, start.y - 1);
	else 
		end = util::geom::Point(start.x + 1, std::tan(angle));
}

bool util::geom::Line::operator==(const util::geom::Line& other) const {
	return slope() == other.slope() && contains(other.start);
}

bool util::geom::Line::operator!=(const util::geom::Line& other) const {
	return !operator==(other);
}

double util::geom::Line::slope() const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::Line::interceptX() const {
	return start.x - slope() * start.y;
}

double util::geom::Line::interceptY() const {
	return start.y - slope() * start.x;
}

double util::geom::Line::angle() const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + util::num::tau, std::numbers::pi);
}

std::optional<util::geom::Point> util::geom::Line::intersection(const util::geom::Line& other) const {
	const double a = (start.x - end.x) * (other.start.y - other.end.y) - (start.y - end.y) * (other.start.x - other.end.x);
	if (a) {
		const util::geom::Point intersection(((other.start.x - other.end.x) * (start.x * end.y - start.y * end.x) - (start.x - end.x) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a, ((other.start.y - other.end.y) * (start.x * end.y - start.y * end.x) - (start.y - end.y) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a);
		if (contains(intersection) && other.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::Line::contains(const util::geom::Point& other) const {
	const double slope = this->slope();
	return std::isinf(slope)
		? util::math::approxEqual(other.x, start.x)
		: util::math::approxEqual(other.y, other.x * slope - start.x * slope + start.y);
}

util::geom::Ray::Ray(const util::geom::Point& start, const util::geom::Point& end)
	: util::geom::Line(start, end)
{}

util::geom::Ray::Ray(const util::geom::Point& start, const double angle)
	: util::geom::Line(start, angle)
{}

bool util::geom::Ray::operator==(const util::geom::Ray& other) const {
	return start == other.start && contains(other.end);
}

bool util::geom::Ray::operator!=(const util::geom::Ray& other) const {
	return !operator==(other);
}

bool util::geom::Ray::contains(const util::geom::Point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approxEqual(other.x, start.x)
			&& slope < std::numeric_limits<double>::lowest()
				? other.y >= start.y
				: other.y <= start.y
		: util::math::approxEqual(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x <= end.x
				? other.x >= start.x
				: other.x <= start.x)
			&& (start.y <= end.y
				? other.y >= start.y
				: other.y <= start.y);
}

util::geom::Segment::Segment(const util::geom::Point& start, const util::geom::Point& end)
	: util::geom::Line(start, end)
{}

bool util::geom::Segment::operator==(const util::geom::Segment& other) const {
	return start == other.start && end == other.end || start == other.end && end == other.start;
}

bool util::geom::Segment::operator!=(const util::geom::Segment& other) const {
	return !operator==(other);
}

double util::geom::Segment::length() const {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::Segment::contains(const util::geom::Point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approxEqual(other.x, start.x)
			&& (other.y >= start.y && other.y <= end.y || other.y <= start.y && other.y >= end.y)
		: util::math::approxEqual(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x < end.x
				? other.x >= start.x && other.x <= end.x
				: other.x <= start.x && other.x >= end.x)
			&& (start.y < end.y
				? other.y >= start.y && other.y <= end.y
				: other.y <= start.y && other.y >= end.y);
}

util::geom::Polygon::Polygon(const std::vector<util::geom::Point>& points)
	: points(points)
{}

bool util::geom::Polygon::operator==(const util::geom::Polygon& other) const {
	return util::alg::rotatedMatch(points.begin(), points.end(), other.points.begin(), other.points.end())
		|| util::alg::rotatedMatch(points.rbegin(), points.rend(), other.points.begin(), other.points.end());
}

bool util::geom::Polygon::operator!=(const util::geom::Polygon& other) const {
	return !operator==(other);
}

double util::geom::Polygon::area() const {
	double area = 0;
	for (const util::geom::Segment& side: sides())
		area += side.start.x * side.end.y - side.start.y * side.start.x;
	return area / 2;
}

double util::geom::Polygon::perimeter() const {
	double perimeter = 0;
	for (const util::geom::Segment& side: sides())
		perimeter += side.length();
	return perimeter;
}

std::vector<util::geom::Segment> util::geom::Polygon::sides() const {
	std::vector<util::geom::Segment> sides;
	for (std::size_t i = 0; i < points.size(); ++i)
		sides.push_back({ points[i], points[(i + 1) % points.size()] });
	return sides;
}

bool util::geom::Polygon::contains(const util::geom::Point& point) const {
	std::size_t intersections = 0;
	util::geom::Ray ray(point, 0);
	for (const util::geom::Segment& side: sides())
		intersections += ray.intersection(side).has_value();
	return intersections % 2;
}

util::geom::Ellipse::Ellipse(const util::geom::Point& center, const util::geom::Point& radius, const double rotation)
	: center(center), radius(radius), rotation(rotation)
{}

bool util::geom::Ellipse::operator==(const util::geom::Ellipse& other) const {
	return center == other.center && radius == other.radius && util::math::approxEqual(std::fmod(rotation, std::numbers::pi), std::fmod(other.rotation, std::numbers::pi));
}

bool util::geom::Ellipse::operator!=(const util::geom::Ellipse& other) const {
	return !operator==(other);
}

double util::geom::Ellipse::area() const {
	return std::numbers::pi * radius.x * radius.y;
}

double util::geom::Ellipse::perimiter() const {
	return std::numbers::pi * std::sqrt(2 * (radius.x * radius.x + radius.y * radius.y));
}

bool util::geom::Ellipse::contains(const util::geom::Point& point) const {
	const double a = std::cos(rotation) * (point.x - center.x) + std::sin(rotation) * (point.y - center.y);
	const double b = std::sin(rotation) * (point.x - center.x) - std::cos(rotation) * (point.y - center.y);
	return a * a / radius.x / radius.x + b * b / radius.y / radius.y <= 1;
}

std::vector<util::geom::Point> util::geom::Ellipse::intersections(const util::geom::Line& line) const {
	std::vector<util::geom::Point> intersections;
	const double a = radius.y * radius.y * line.end.x * line.end.x + radius.x * radius.x * line.end.y * line.end.y;
	const double b = radius.y * radius.y * line.start.x * line.end.x * 2 + radius.x * radius.x * line.start.y * line.end.y * 2;
	const double c = radius.y * radius.y * line.start.x * line.start.x + radius.x * radius.x * line.start.y * line.start.y - radius.x * radius.x * radius.y * radius.y;
	const double d = std::sqrt(b * b - 4 * a * c) / 2 / a;
	const double e = b * b - 4 * a * c;
	const bool f = util::math::approxEqual(e, 0.0);
	if (e > 0 || f) {
		const util::geom::Point g(center.x + line.start.x + (d - b) * (line.end.x - line.start.x), center.y + line.start.y + (d + b) * (line.end.y - line.start.y));
		if (line.contains(g))
			intersections.push_back(g);
		if (e > 0 && !f) {
			const util::geom::Point h(center.x - line.start.x - (d - b) * (line.end.x - line.start.x), center.y - line.start.y - (d + b) * (line.end.y - line.start.y));
			if (line.contains(h))
				intersections.push_back(h);
		}
	}
	return intersections;
}

std::vector<util::geom::Point> util::geom::Ellipse::intersections(const util::geom::Ellipse& other) const {
	return {}; // TODO
}

util::geom::Circle::Circle(const util::geom::Point& center, const double radius)
	: util::geom::Ellipse(center, { radius, radius })
{}

bool util::geom::Circle::operator==(const util::geom::Circle& other) const {
	return center == other.center && util::math::approxEqual(radius.x, other.radius.x);
}

bool util::geom::Circle::operator!=(const util::geom::Circle& other) const {
	return !operator==(other);
}

bool util::geom::Circle::contains(const util::geom::Point& point) const {
	return std::hypot(point.x - center.x, point.y - center.y) <= radius.x;
}

util::geom::Rectangle::Rectangle(const util::geom::Point& corner1, const util::geom::Point& corner2)
	: util::geom::Polygon({ corner1, { corner2.x, corner1.y }, corner2, { corner1.x, corner2.y } })
{}

util::geom::Rectangle::Rectangle(const util::geom::Segment& segment)
	: util::geom::Polygon({ segment.start, segment.end })
{}

util::geom::Rectangle::Rectangle(const util::geom::Polygon& polygon)
	: util::geom::Polygon({})
{
	if (!polygon.points.size())
		util::geom::Polygon({});
	util::geom::Point min = polygon.points[0];
	util::geom::Point max = polygon.points[0];
	for (std::size_t i = 1; i < polygon.points.size(); ++i) {
		const util::geom::Point& point = polygon.points[i];
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

util::geom::Rectangle::Rectangle(const util::geom::Ellipse& ellipse)
	: util::geom::Polygon({})
{
	const double a = std::sqrt(ellipse.radius.x * ellipse.radius.x  * std::cos(ellipse.rotation) * std::cos(ellipse.rotation) + ellipse.radius.y * ellipse.radius.y * std::cos(ellipse.rotation + std::numbers::pi / 2) * std::cos(ellipse.rotation + std::numbers::pi / 2));
	const double b = std::sqrt(ellipse.radius.x * ellipse.radius.x * std::sin(ellipse.rotation) * std::sin(ellipse.rotation) + ellipse.radius.y * ellipse.radius.y * std::sin(ellipse.rotation + std::numbers::pi / 2) * std::sin(ellipse.rotation + std::numbers::pi / 2));
	points = {
		{ ellipse.center.x - a, ellipse.center.y - b },
		{ ellipse.center.x + a, ellipse.center.y - b },
		{ ellipse.center.x + a, ellipse.center.y + b },
		{ ellipse.center.x - a, ellipse.center.y + b }
	};
}

bool util::geom::Rectangle::operator==(const util::geom::Rectangle& other) const {
	return points[0] == other.points[0] && points[2] == other.points[2] || points[0] == other.points[2] && points[2] == other.points[0];
}

bool util::geom::Rectangle::operator!=(const util::geom::Rectangle& other) const {
	return !operator==(other);
}

double util::geom::Rectangle::width() const {
	return std::fabs(points[0].x - points[2].x);
}

double util::geom::Rectangle::height() const {
	return std::fabs(points[0].y - points[2].y);
}

double util::geom::Rectangle::area() const {
	return width() * height();
}

double util::geom::Rectangle::perimeter() const {
	return (width() + height()) * 2;
}

bool util::geom::Rectangle::contains(const util::geom::Point& point) const {
	return (point.x >= points[0].x && point.x <= points[2].x || point.x <= points[0].x && point.x >= points[2].x)
		&& (point.y >= points[0].y && point.y <= points[2].y || point.y <= points[0].y && point.y >= points[2].y);
}
