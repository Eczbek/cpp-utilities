# C++ utility library

### Examples
```cpp
#include <util/alg>
using namespace util::alg;

std::array<int, 3> a { 1, 2, 3 };
std::array<int, 3> b { 3, 1, 2 };
std::array<int, 3> c { 1, 3, 2 };

rotatedMatch(a.begin(), a.end(), b.begin(), b.end()) // true
rotatedMatch(a.begin(), a.end(), c.begin(), c.end()) // false
rotatedMatch(a.begin(), a.end(), c.end(), c.begin()) // true
```
```cpp
#include <util/fs>
using namespace util::fs;

write("something.txt", 4);
append("something.txt", 'd');

read("something.txt") // "4d"
```
```cpp
#include <util/map>

util::OrderedMap<char, bool> map;
map['a'] = true;

map['a'] // true
map['b'] // false
```
```cpp
#include <util/mat>

util::Matrix<int> matrix({ 2, 2 }, { 1, 2, 3, 4 });

matrix[{ 1, 0 }] // 3
```
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
#include <util/num>

util::num::tau // 6.28318
```
```cpp
#include <util/str>
using namespace util::str;

split("abc", "") // std::vector<std::string> { "a", "b", "c" }
split("a b c", ' ') // std::vector<std::string> { "a", "b", "c" }

trunc("0123456789", 8, "...") // "01234..."

trimLeft("aaaBaaa", '.') // "Baaa"
trimRight("aaaBaaa", '.') // "aaaB"

trimLeft("abaCbab", "ab") // "Cbab"
trimRight("abaCbab", "ab") // "abaC"
```
```cpp
#include <util/time>
using namespace util::time;

months[4] // "May"

week_days[2] // "Tuesday"

now<std::chrono::milliseconds>() // 1657814519827
```
```cpp
#include <util/vect>
using namespace util::vect;

group({ 1, 2, 3, 4 }, [](const int value) -> std::string {
	return (value > 2) ? "big" : "small";
}) /*
std::unordered_map<std::string, std::vector<int>> {
	{ "big", { 3, 4 } },
	{ "small", { 1, 2 } }
}
*/

std::vector<std::vector<int>> vector2D {
	{ 1, 2, 3 },
	{ 4, 5, 6 }
};

rotateCW(vector2D) /*
std::vector<std::vector<int>> {
	{ 4, 1 },
	{ 5, 2 },
	{ 6, 3 }
}
*/
rotateCCW(vector2D) /*
std::vector<std::vector<int>> {
	{ 3, 6 },
	{ 2, 5 },
	{ 1, 4 }
}
*/
```
