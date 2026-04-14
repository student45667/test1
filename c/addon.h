/*
 * addon.h
 *
 *  Created on: Apr 6, 2026
 *      Author: alexchiomny
 *
 *  Declarations for the arithmetic helper functions defined in addon.c.
 *  Any .c file that calls add() or multiply() must include this header
 *  so the compiler knows the function signatures before it sees the calls.
 */

/* Include guard — stops the compiler processing this header twice */
#ifndef ADDON_H_
#define ADDON_H_

/*
 * add(a, b)
 *   Returns the sum of two integers.
 */
int add(int a, int b);

/*
 * multiply(a, b)
 *   Returns the product of two integers.
 */
int multiply(int a, int b);

#endif /* ADDON_H_ */
