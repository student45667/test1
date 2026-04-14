/*
 * addon.c
 *
 *  Created on: Apr 6, 2026
 *      Author: alexchiomny
 *
 *  Implements the arithmetic helpers declared in addon.h.
 *  Keeping implementations in their own .c file (separate from main.c)
 *  is good practice — it lets you reuse or swap out these functions
 *  without touching the rest of the program.
 */

#include "addon.h"   /* include our own header to confirm signatures match */

/*
 * add — returns the sum of a and b.
 * Example: add(10, 5) → 15
 */
int add(int a, int b) {
    return a + b;
}

/*
 * multiply — returns the product of a and b.
 * Example: multiply(10, 5) → 50
 */
int multiply(int a, int b) {
    return a * b;
}
