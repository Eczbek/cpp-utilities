#include <limits>
#include <util/alg>
#include <util/geom>
#include <util/math>
#include <util/num>


util::geom::Point::Point(const double x, const double y) noexcept
	: x(x), y(y)
{}

bool util::geom::Point::operator==(const util::geom::Point other) const noexcept {
	return util::math::approxEqual(x, other.x) && util::math::approxEqual(y, other.y);
}

bool util::geom::Point::operator!=(const util::geom::Point other) const noexcept {
	return !operator==(other);
}

util::geom::Point util::geom::Point::rotate(const double angle, const util::geom::Point pivot) const noexcept {
	return {
		pivot.x + std::cos(angle) * (x - pivot.x) - std::sin(angle) * (y - pivot.y),
		pivot.y + std::cos(angle) * (y - pivot.y) + std::sin(angle) * (x - pivot.x)
	};
}

util::geom::Line::Line(const util::geom::Point start, const util::geom::Point end) noexcept
	: start(start), end(end)
{}

util::geom::Line::Line(const util::geom::Point start, const double angle) noexcept
	: start(start)
{
	end = util::math::approxEqual(std::fmod(angle + std::numbers::pi / 2, std::numbers::pi), 0.0)
		? util::geom::Point(start.x, start.y - 1)
		: util::geom::Point(start.x + 1, std::tan(angle));
}

bool util::geom::Line::operator==(const util::geom::Line& other) const noexcept {
	return slope() == other.slope() && contains(other.start);
}

bool util::geom::Line::operator!=(const util::geom::Line& other) const noexcept {
	return !operator==(other);
}

double util::geom::Line::slope() const noexcept {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::Line::interceptX() const noexcept {
	return start.x - slope() * start.y;
}

double util::geom::Line::interceptY() const noexcept {
	return start.y - slope() * start.x;
}

double util::geom::Line::angle() const noexcept {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + util::num::tau, std::numbers::pi);
}

std::optional<util::geom::Point> util::geom::Line::intersection(const util::geom::Line& other) const noexcept {
	const double a = (start.x - end.x) * (other.start.y - other.end.y) - (start.y - end.y) * (other.start.x - other.end.x);
	if (!util::math::approxEqual(a, 0.0)) {
		const util::geom::Point intersection(((other.start.x - other.end.x) * (start.x * end.y - start.y * end.x) - (start.x - end.x) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a, ((other.start.y - other.end.y) * (start.x * end.y - start.y * end.x) - (start.y - end.y) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a);
		if (contains(intersection) && other.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::Line::contains(const util::geom::Point other) const noexcept {
	const double slope = this->slope();
	return std::isinf(slope)
		? util::math::approxEqual(other.x, start.x)
		: util::math::approxEqual(other.y, other.x * slope - start.x * slope + start.y);
}

util::geom::Line util::geom::Line::rotate(const double angle, const util::geom::Point pivot) {
	return {
		start.rotate(angle, pivot),
		end.rotate(angle, pivot)
	};
}

util::geom::Ray::Ray(const util::geom::Point start, const util::geom::Point end) noexcept
	: util::geom::Line(start, end)
{}

util::geom::Ray::Ray(const util::geom::Point start, const double angle) noexcept
	: util::geom::Line(start, angle)
{}

bool util::geom::Ray::operator==(const util::geom::Ray& other) const noexcept {
	return start == other.start && contains(other.end);
}

bool util::geom::Ray::operator!=(const util::geom::Ray& other) const noexcept {
	return !operator==(other);
}

bool util::geom::Ray::contains(const util::geom::Point other) const noexcept {
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

util::geom::Segment::Segment(const util::geom::Point start, const util::geom::Point end) noexcept
	: util::geom::Line(start, end)
{}

bool util::geom::Segment::operator==(const util::geom::Segment& other) const noexcept {
	return start == other.start && end == other.end || start == other.end && end == other.start;
}

bool util::geom::Segment::operator!=(const util::geom::Segment& other) const noexcept {
	return !operator==(other);
}

double util::geom::Segment::length() const noexcept {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::Segment::contains(const util::geom::Point other) const noexcept {
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

util::geom::Polygon::Polygon(const std::vector<util::geom::Point>& points) noexcept
	: points(points)
{}

bool util::geom::Polygon::operator==(const util::geom::Polygon& other) const noexcept {
	return util::alg::rotatedMatch(points.begin(), points.end(), other.points.begin(), other.points.end())
		|| util::alg::rotatedMatch(points.rbegin(), points.rend(), other.points.begin(), other.points.end());
}

bool util::geom::Polygon::operator!=(const util::geom::Polygon& other) const noexcept {
	return !operator==(other);
}

double util::geom::Polygon::area() const noexcept {
	double area = 0;
	for (const util::geom::Segment& side: sides())
		area += side.start.x * side.end.y - side.start.y * side.start.x;
	return area / 2;
}

double util::geom::Polygon::perimeter() const noexcept {
	double perimeter = 0;
	for (const util::geom::Segment& side: sides())
		perimeter += side.length();
	return perimeter;
}

std::vector<util::geom::Segment> util::geom::Polygon::sides() const noexcept {
	std::vector<util::geom::Segment> sides;
	for (std::size_t i = 0; i < points.size(); ++i)
		sides.push_back({ points[i], points[(i + 1) % points.size()] });
	return sides;
}

bool util::geom::Polygon::contains(const util::geom::Point point) const noexcept {
	std::size_t intersections = 0;
	util::geom::Ray ray(point, 0);
	for (const util::geom::Segment& side: sides())
		intersections += ray.intersection(side).has_value();
	return intersections % 2;
}

util::geom::Polygon util::geom::Polygon::rotate(const double angle, const util::geom::Point pivot) const noexcept {
	std::vector<util::geom::Point> rotatedPoints = points;
	for (std::size_t i = 0; i < points.size(); ++i)
		rotatedPoints[i] = points[i].rotate(angle, pivot);
	return { rotatedPoints };
}

util::geom::Polygon util::geom::Polygon::boundingBox() const noexcept {
	util::geom::Point min = points[0];
	util::geom::Point max = points[0];
	for (const util::geom::Point point: points) {
		if (point.x < min.x)
			min.x = point.x;
		if (point.x > max.x)
			max.x = point.x;
		if (point.y < min.y)
			min.y = point.y;
		if (point.y > max.y)
			max.y = point.y;
	}
	return { {
		min,
		{ max.x, min.y },
		max,
		{ min.x, max.y }
	} };
}

util::geom::Polygon util::geom::Polygon::boundingPolygon() const noexcept {
	std::vector<util::geom::Point> newPoints;
	util::geom::Point newPoint = points[0];
	util::geom::Point pointDiff;
	double oldAngle = util::num::tau * 5;
	double newAngle;
	double angleDiff;
	double minAngleDiff;
	for (const util::geom::Point point: points)
		if (point.y >= newPoint.y && point.x < newPoint.x)
			newPoint = point;
	for (long i = 0; !i || newPoint.x != newPoints[0].x || newPoint.y != newPoints[0].y; ++i) {
		newPoints.push_back(newPoint);
		minAngleDiff = util::num::tau;
		for (const util::geom::Point point: points) {
			pointDiff = { point.x - newPoints[i].x, point.y - newPoints[i].y };
			if (pointDiff.x || pointDiff.y) {
				double dist = std::sqrt(pointDiff.x * pointDiff.x + pointDiff.y * pointDiff.y);
				newAngle = (pointDiff.y >= 0)
					? std::acos(pointDiff.x / dist)
					: std::acos(-pointDiff.x / dist) + std::numbers::pi;
				angleDiff = oldAngle - newAngle;
				angleDiff = util::math::wrap(angleDiff, util::num::tau);
				if (angleDiff < minAngleDiff) {
					minAngleDiff = angleDiff;
					newPoint = point;
				}
			}
		}
		oldAngle += std::numbers::pi - minAngleDiff;
	}
	return { newPoints };
}

util::geom::Ellipse::Ellipse(const util::geom::Point center, const util::geom::Point radius, const double rotation) noexcept
	: center(center), radius(radius), rotation(rotation)
{}

bool util::geom::Ellipse::operator==(const util::geom::Ellipse& other) const noexcept {
	return center == other.center && radius == other.radius && util::math::approxEqual(std::fmod(rotation, std::numbers::pi), std::fmod(other.rotation, std::numbers::pi));
}

bool util::geom::Ellipse::operator!=(const util::geom::Ellipse& other) const noexcept {
	return !operator==(other);
}

double util::geom::Ellipse::area() const noexcept {
	return std::numbers::pi * radius.x * radius.y;
}

double util::geom::Ellipse::perimiter() const noexcept {
	return std::numbers::pi * std::sqrt(2 * (radius.x * radius.x + radius.y * radius.y));
}

bool util::geom::Ellipse::contains(const util::geom::Point point) const noexcept {
	const double a = std::cos(rotation) * (point.x - center.x) + std::sin(rotation) * (point.y - center.y);
	const double b = std::sin(rotation) * (point.x - center.x) - std::cos(rotation) * (point.y - center.y);
	return a * a / radius.x / radius.x + b * b / radius.y / radius.y <= 1;
}

std::vector<util::geom::Point> util::geom::Ellipse::intersections(const util::geom::Line& line) const noexcept {
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

std::vector<util::geom::Point> util::geom::Ellipse::intersections(const util::geom::Ellipse& other) const noexcept {
	return {}; // TODO
}

util::geom::Ellipse util::geom::Ellipse::rotate(const double angle, const util::geom::Point pivot) const noexcept {
	return {
		center.rotate(angle, pivot),
		radius,
		std::fmod(rotation + angle, util::num::tau)
	};
}

util::geom::Polygon util::geom::Ellipse::boundingBox() const noexcept {
	const double a = std::sqrt(radius.x * radius.x * std::cos(rotation) * std::cos(rotation) + radius.y * radius.y * std::cos(rotation + std::numbers::pi / 2) * std::cos(rotation + std::numbers::pi / 2));
	const double b = std::sqrt(radius.x * radius.x * std::sin(rotation) * std::sin(rotation) + radius.y * radius.y * std::sin(rotation + std::numbers::pi / 2) * std::sin(rotation + std::numbers::pi / 2));
	return { {
		{ center.x - a, center.y - b },
		{ center.x + a, center.y - b },
		{ center.x + a, center.y + b },
		{ center.x - a, center.y + b }
	} };
}

util::geom::Circle::Circle(const util::geom::Point center, const double radius) noexcept
	: util::geom::Ellipse(center, { radius, radius })
{}

bool util::geom::Circle::operator==(const util::geom::Circle& other) const noexcept {
	return center == other.center && util::math::approxEqual(radius.x, other.radius.x);
}

bool util::geom::Circle::operator!=(const util::geom::Circle& other) const noexcept {
	return !operator==(other);
}

bool util::geom::Circle::contains(const util::geom::Point point) const noexcept {
	return std::hypot(point.x - center.x, point.y - center.y) <= radius.x;
}

util::geom::Circle util::geom::Circle::rotate(const double angle, const util::geom::Point pivot) const noexcept {
	return { center.rotate(angle, pivot), radius.x };
}

util::geom::Polygon util::geom::Circle::boundingBox() const noexcept {
	return { {
		{ center.x - radius.x, center.y - radius.y },
		{ center.x + radius.x, center.y - radius.y },
		{ center.x + radius.x, center.y + radius.y },
		{ center.x - radius.x, center.y + radius.y }
	} };
}
