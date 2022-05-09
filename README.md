# cpp-utils
### Examples:
```cpp
std::array<int, 5> a { 0, 2, 4, 6, 8 };
util::alg::binary_search(a.begin(), a.end(), [](int b) { return b - 4; })
// 2
```
```cpp
util::math::to_base(17, util::math::from_base(16, "10"))
// "g"
```
```cpp
util::str::split("a-b-c-d", '-')
// { "a", "b", "c", "d" }
```
```cpp
util::vect::rotate_cw(std::vector<std::vector<int>> {
	{ 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 9 }
})
/*{
	{ 7, 4, 1 },
	{ 8, 5, 2 },
	{ 9, 6, 3 }
}*/
```