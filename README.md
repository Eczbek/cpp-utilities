# cpp-utilities
C++ utility library

### Examples
```cpp
#include <util/math>
using namespace util::math;

wrap(6, 5, -3) // -2

approxEqual(0.1 + 0.2, 0.3) // true

sign(297580) // 1
sign(-6527395) // -1
sign(0) // 0

degToRad(180) // 3.14159
radToDeg(3.14159) // 180

baseTo(13, 16) // "d"
baseFrom("d", 16) // 16
```
```cpp
#include <util/str>
using namespace util::str;

split("abc", "") // { "a", "b", "c" }
split("a b c", ' ') // { "a", "b", "c" }

trunc("0123456789", 8, "...") // "01234..."

trimLeft("...a...", '.') // "a..."
trimRight("...a...", '.') // "...a"

trimLeft(".-.a-.-", ".-") // "a-.-"
trimRight(".-.a-.-", ".-") // ".-.a"
```
```cpp
#include <util/vect>
using namespace util::vect;

group({ 1, 2, 3, 4 }, [](const int value) -> std::string {
	return (value > 2) ? "big" : "small"
}) /* {
	"big": { 3, 4 },
	"small": { 1, 2 }
} */

std::vector<std::vector<int>> vector2D {
	{ 1, 2, 3 },
	{ 4, 5, 6 }
};

rotateCW(vector2D) /* {
	{ 4, 1 },
	{ 5, 2 },
	{ 6, 3 }
} */
rotateCCW(vector2D) /* {
	{ 3, 6 },
	{ 2, 5 },
	{ 1, 4 }
} */
```
```cpp
#include <util/fs>
using namespace util::fs;

write("something.txt", 4)
append("something.txt", 'd')

read("something.txt") // "4d"
```
