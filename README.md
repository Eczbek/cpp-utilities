# cpp-utilities
C++ utility library

## Examples
```cpp
#include <util/math.hpp>

util::math::base_to(util::math::base_from("10", 16), 17)
// "g"
```
```cpp
#include <util/str.hpp>

util::str::trunc("Hello, world!", 8, "...");
// "Hello..."
```
```cpp
#include <util/evt.hpp>

util::evt::emitter e;
e.on("event", [](int x, char y) { std::cout << y << x << '\n'; });
e.emit("event", 17, 'h');
// h17
```
```cpp
#include <util/io.hpp>

util::io::style lock(util::io::style::FG_RED_BRIGHT);
std::cout << "Hello, world!\n";
```
```cpp
#include <util/mat.hpp>

util::matrix<int> a({ 2, 2 }, { 1, 2, 3, 4 });
a[{ 1, 0 }] // 3
```
```cpp
#include <util/vect.hpp>

util::vect::rotate_cw({
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

util::geom::line({ 0, 2 }, { 2, 0 })
	.intersection(util::geom::line({ 0, 0 }, util::math::deg_to_rad(45)))
// { 1, 1 }
```