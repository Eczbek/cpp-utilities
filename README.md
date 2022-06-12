# cpp-utilities
C++ utility library

## Examples
```cpp
#include <util/math.hpp>

util::math::baseTo(util::math::baseFrom("10", 16), 17)
// "g"
```
```cpp
#include <util/str.hpp>

util::str::trunc("Hello, world!", 8, "...");
// "Hello..."
```
```cpp
#include <util/evt.hpp>

util::EventEmitter emitter;
emitter.on("event", [](const int x, const char y) {
	std::cout << y << x << '\n';
});
emitter.emit("event", 17, 'h');
// h17
```
```cpp
#include <util/io.hpp>

util::io::Style lock(util::io::Style::FG_RED_BRIGHT);
std::cout << "Hello, world!\n";
```
```cpp
#include <util/mat.hpp>

util::Matrix<int> matrix({ 2, 2 }, { 1, 2, 3, 4 });
matrix[{ 1, 0 }] // 3
```
```cpp
#include <util/vect.hpp>

util::vect::rotateCW({
	{ 1, 2, 3 },
	{ 4, 5, 6 }
})
/* {
	{ 4, 1 },
	{ 5, 2 },
	{ 6, 3 }
} */
```
```cpp
#include <util/geom.hpp>

util::geom::Line({ 0, 2 }, { 2, 0 })
	.intersection(util::geom::Line({ 0, 0 }, util::math::degToRad(45)))
// { 1, 1 }
```
```cpp
#include <util/fs.hpp>

util::fs::write("output.txt", 42);
util::fs::read("output.txt") // "42"
```