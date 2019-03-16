# libft
A homemade cross-platform standard library for C

What started as a necessary exercise for the 42 school quickly became a much more expansive project: whereas the 42 libft only requires a certain set of important memory/string/io functions, we decided to take it further.

The objective is to have one simple, well-documented, efficient open-source implementation of the C standard library, but with easier to use functions and types than what is offered by the ISO standards - mostly by removing undefined behaviors, and handling edge cases in a consistent, coherent way, so as to have code that is as little machine-specific as possible.
Furthermore there are other functions here that are not found in the ISO standard:
* convert: functions have replaced the wonky atoi/itoa/atof/... functions with more understandable type-specific conversion functions
* io: 
* color: functions for converting between different common color encodings, as well as other useful functions (like blending colors, etc)
* random: a set of simple functions for pseudo-random number generation
* list: linked lists (using a simple list type which only stores the 'next' pointer)
* stringarray: a set of functions used to manipulate a 2d/jagged array of characters, where the top-level pointer array is terminated by a NULL pointer

To ensure proper functionality of all these important functions in every edge case, a big testing program was implemented, featuring segfault handling and execution time comparison among other things.
You can test the libft by running 'make test': this wil compile the test program from the files found in the 'src' folder.

