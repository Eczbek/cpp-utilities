# cpp-utilities
C++ utility library

### Examples
```cpp
#include <util/math>

util::math::baseTo(util::math::baseFrom("10", 16), 17) // "g"
```
```cpp
#include <util/str>

util::str::trunc("Hello, world!", 8, "...") // "Hello..."
```
```cpp
#include <util/evt>

util::EventEmitter emitter;
emitter.on("event", [](const int x, const char y) -> void {
	std::cout << y << x << '\n';
});
emitter.emit("event", 17, 'h');
// h17
```
```cpp
#include <util/io>

util::io::setStyle(util::io::style::fg::red_bright);
std::cout << "Hello, world!\n";
```
```cpp
#include <util/mat>

util::Matrix<int> matrix({ 2, 2 }, { 1, 2, 3, 4 });
matrix[{ 1, 0 }] // 3
```
```cpp
#include <util/vect>

util::vect::rotateCW({
	{ 1, 2, 3 },
	{ 4, 5, 6 }
}) /* {
	{ 4, 1 },
	{ 5, 2 },
	{ 6, 3 }
} */
```
```cpp
#include <util/geom>

util::geom::Line({ 0, 2 }, { 2, 0 })
	.intersection(util::geom::Line({ 0, 0 }, util::math::degToRad(45)))
// { 1, 1 }
```
```cpp
#include <util/fs>

util::fs::write("something.txt", 42);
util::fs::read("something.txt") // "42"
```
```cpp
#include <util/map>

util::OrderedMap<char, bool> map;
map['a'] = true;
map['m'] // false
```
```cpp
#include <util/time>

util::time::week_days[3] // "Wednesday"
```
