#include <iostream>

// Declaring pointers
void declaring_pointers() {
	int x = 69;

	int * p1; // Holds memory address.
	const int * p2; // Read-only access to value pointed to by memory address.
	int * const p3 = &x; // Read/write access to a constant memory address;
	const int * const p4 = &x; // Read only access to a constant memory value;
	// Note: constant pointers must be initialized upon declaration.
}

// Declaring pointers of undetermined type (here as an arbitrary function argument).
// Inputs are (memory location pointing to undetermined type, integer)
void void_pointers(void * data, int size) {
	if (size == sizeof(char)) {
		char * pchar = (char*)data; // Cast the data pointer to type char*.
		++(*pchar);                 // Increment the value stored at the memory location.
	}
	else if (size == sizeof(int)) {
		int * pint = (int*)data;     // Cast the data pointer to type int*.
		++(*pint);          // Increment the value stored at the memory location.
	}
}

int main() {
	int x = 68;
	int * pint = &x;
	void_pointers(pint, sizeof(x));
	std::cout << x << "\n";

	char my_str = 'A';
	void_pointers(&my_str, sizeof(my_str));
	std::cout << my_str << "\n";
}

// Make a local copy of shape_in
// (const is redundant here, bc it is a copy)
void myfunc(const Shape shape_in) {
  shape_in.area();
}
// Pointer to shape_in (no copy)
// const makes only the pointer readonly
void myfunc(const Shape* shape_in) {
// pointer notation to access members
  shape_in->area();
// this notation is the same as
// (*shape_in).area()
}
// Reference to shape_in (no copy)
// const makes the object read only
void myfunc(const Shape& shape_in) {
// regular notation to access members
  shape_in.area();
}