# Mersenne Random Number

### C/C++ platform independent implementation of a random number generator using the Mersenne Twister algorithm


### What it does:
Generate a random number between 0 and CYB_RAND_MAX using a modified version of the Mersenne Twister algorithm.
This code was initially created for a project that needed a random number generator that produced the same sequence (when seeded with the same seed) across multiple hardware/OS platforms.
The implementation of the built-in rand() function can actually differ between compilers and platforms and thus doesn't gurantee the same number sequence for the same seed.
Along the way, some tweaks to the original Mersenne Twister algorithm were made to better suit the needs of the project.

### Returned random numbers:
The random numbers returned by the cyb_rand() function are unsigned 32-bit integers between 0 and CYB_RAND_MAX.
To get a normalized number between 0.0 and 1.0 simply divide the result by CYB_RAND_MAX.
```
#define		CYB_RAND_MAX	0x7FFFFFFF
...
uint32_t random_number = cyb_rand();
double normalized_number = (double)random_number / (double)CYB_RAND_MAX;
```

### Usage:
```
-seed %d        # Seed with a numerical value
-seed time      # Seed with the current system time (default)
-steps %d       # Generate x random numbers (default: 10)
```
