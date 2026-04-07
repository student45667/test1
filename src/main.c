/*
 ============================================================================
 Name        : hello.c
 Author      : AlexC
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "addon.h"

int main(void) {

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

     	int x = 10, y = 5;
	    printf("Sum: %d\n", add(x, y));
	    printf("Product: %d\n", multiply(x, y));
	    return 0;


}
