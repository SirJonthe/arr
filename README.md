# arr
## Copyright
Copyright Jonathan Karlsson, 2023

github.com/SirJonthe

## About
`arr` is a minimalist library that introduces an array type to C++11 that encapsulates built-in C/C++ arrays and pointers.

## Design
Arrays in `arr` are intended to provide C++ with an array type that can be used as a stand-in for C/C++ built-in arrays without imposing too much functionality onto the user; Arrays can be allocated, indexed, and queried for size, but provides little more functionality to operate on them, leaving this work to routines provided by the user.

Arrays in `arr` are still compatible, implicitly and explicitly, with C/C++ arrays and pointers, making them, essentially, a drop-in replacement for built-in C/C++ arrays and pointers.

`arr` also introduces the concept of "slices", sub-arrays that do not own the referencing data themselves, 

## Usage
`arr` provies two essential classes; `array` and `slice`.

`array` is a template class that takes array type or array type and fixed-size as template parameters. Depending on the supplied arguments, the array may be a variable-sized array allocated on the heap, or a fixed-size array allocated on the stack. Memory is managed by the `array` class by default, i.e. memory is both allocated and deallocated automatically. However, more advanced behavior can be customized.

`slice` is a template class that takes the array type as template parameters. `slice` constitutes a view into an existing array or part thereof. Slices are useful when the programmer wants to deal with a subset of an array as if that subset were a full array. For maximum flexibility, it is a good idea to pass slices as paramters to functions rather than fixed or variable arrays. Since the slice does not own the data it views it is the programmer's responsibility to ensure that the underlying data is still valid at the time of view, e.g. not out of scope or otherwise deleted.

## Building
No special adjustments need to be made to build `arr` except enabling C++11 compatibility or above. Simply include the relevant headers in your code and make sure the headers and source files are available in your compiler search paths. Using `g++` as an example, building is no harder than:

```
g++ -std=c++11 code.cpp arr/arr.cpp
```

...where `code.cpp` is an example source file containing the user-defined code, such as program entry point.

## Examples
### Create a variable-sized array on the heap
Create an empty array:
```
#include "arr/arr.h"

int main()
{
	arr::array<int> arr;
	return 0;
}
```

Create an array with 16 elements:
```
#include "arr/arr.h"

int main()
{
	arr::array<int> arr(16);
	return 0;
}
```

Create an array with 16 elements:
```
#include "arr/arr.h"

int main()
{
	arr::array<int> arr;
	arr.create(16);
	return 0;
}
```

Create an array with 16 elements from a C array:
```
#include "arr/arr.h"

int main()
{
	int tmp[16];
	arr::array<int> arr(tmp);
	return 0;
}
```

Create and initialize an array with 16 elements from a C array:
```
#include "arr/arr.h"

int main()
{
	arr::array<int> arr({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
	return 0;
}
```

Create an array with 16 elements from a C pointer:
```
#include "arr/arr.h"

int main()
{
	int *tmp = new int[16];
	arr::array<int> arr(tmp, 16);
	return 0;
}
```

### Create a fixed-size array on the stack
Create an array with 16 elements:
```
#include "arr/arr.h"

int main()
{
	arr::array<int> arr(16);
	return 0;
}
```

Create an array with 16 elements from a C array:
```
#include "arr/arr.h"

int main()
{
	int tmp[16];
	arr::array<int,16> arr(tmp);
	return 0;
}
```

Create and initialize an array with 16 elements from a C array:
```
#include "arr/arr.h"

int main()
{
	arr::array<int,16> arr({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
	return 0;
}
```

### Accessing data
Accessing data from a variable length array:
```
#include <iostream>
#include "arr/arr.h"

int main()
{
	arr::array<int> a({1, 2, 3, 4});
	for (int i = 0; i < a.size() ++i) {
		std::cout << a[i] << std::endl;
	}
	return 0;
}
```

Accessing data from a fixed length array:
```
#include <iostream>
#include "arr/arr.h"

int main()
{
	arr::array<int,4> a({1, 2, 3, 4});
	for (int i = 0; i < a.size() ++i) {
		std::cout << a[i] << std::endl;
	}
	return 0;
}
```

Accessing data from a slice:
```
#include <iostream>
#include "arr/arr.h"

int main()
{
	arr::array<int,4> arr({1, 2, 3, 4});
	arr::slice<int> a(arr);
	for (int i = 0; i < a.size() ++i) {
		std::cout << a[i] << std::endl;
	}
	return 0;
}
```

### Passing arrays as parameters
`arr` arrays can of course be passed by copy or reference. Copied arrays will behave as expected (i.e. copied into a new array instance).
```
#include <iostream>
#include "arr/arr.h"

void pass_by_ref(const arr::array<int> &arr);
void pass_by_ref(const arr::array<int,16> &arr);

void pass_by_copy(arr::array<int> &arr);
void pass_by_copy(arr::array<int,16> &arr);

int main()
{
	arr::array<int> a1(32);
	pass_by_ref(a1);
	pass_by_copy(a1);

	arr::array<int,16> a2;
	pass_by_ref(a2);
	pass_by_copy(a2);

	return 0;
}
```

`arr` arrays can also implicitly be converted back to plain C pointers for compatibility with existing functionality. 
```
#include <iostream>
#include "arr/arr.h"

void fn(const int *arr, uint64_t size);

int main()
{
	arr::array<int> a1(32);
	fn(a1, a1.size());

	arr::array<int,16> a2;
	f(a2, a2.size());

	return 0;
}
```

The preferred method to pass arrays is via slices, especially if the parameter is constant, as slices offer the most compatibility between C pointers and arrays, and both variable and fixed size `arr` arrays. Slices also do not entail copying data as the underlying data inside slices are always passed by reference (more specifically, by pointer).
```
#include <iostream>
#include "arr/arr.h"

void pass_slice_ref_constref(const arr::slice<const int> &arr);
void pass_slice_by_ref(arr::slice<int> &arr);

int main()
{
	// pass variable-length array as slice.
	arr::array<int> a1(32);
	pass_slice_by_ref(a1);
	pass_slice_by_constref(a1);

	// pass fixed-length array as slice
	arr::array<int,16> a2;
	pass_slice_by_ref(a2);
	pass_slice_by_constref(a2);

	// pass slice of fixed-length array as slice
	arr::slice<int> a3(a2);
	pass_slice_by_ref(a3);
	pass_slice_by_constref(a3);

	return 0;
}
```

## Future work
`values` may come to be removed as `array` seems to have decent enough support for in-line array initialization.

The variable-length array may be reworked to remove pooling as this is a more advanced feature than what is needed for arrays to function. Pooling should instead be implemented by the user.