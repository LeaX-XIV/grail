#ifndef UTILS_HEADER
#define UTILS_HEADER

// Returns the maximum between a and b
int max(int a, int b);
// Returns the minimum between a and b
int min(int a, int b);

// Shuffles the array in place: O(n)
void shuffle_array(unsigned int* array, size_t size);
// Reverses the array in place: O(n);
void reverse_array(unsigned int* array, size_t size);
// Swaps values of *a and *b without a temporary variable
void swap(unsigned int* a, unsigned int* b);

#endif	// UTILS_HEADER