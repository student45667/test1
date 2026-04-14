/*
 ============================================================================
 Name        : hello.c
 Author      : AlexC
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style.
               Demonstrates basic arithmetic via addon.c and file I/O
               via fileio.c. Temp files are stored in src/tempfiles/.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "addon.h"   /* provides add() and multiply() */
#include "fileio.h"  /* provides write_text_file(), read_text_file(), append_text_file() */

/*
 * Paths to the temp files used in the file I/O demo.
 * These are relative to the Eclipse project root (the "hello" folder),
 * which is the default working directory when you Run the project.
 *
 * temp.txt  - written and read back each run (overwritten each time)
 * log.txt   - entries are appended each run, so it grows over time
 */
#define TEMP_FILE  "src/tempfiles/temp.txt"
#define LOG_FILE   "src/tempfiles/log.txt"

int main(void) {

	/* ------------------------------------------------------------------ */
	/* Basic Hello World + arithmetic demo                                 */
	/* ------------------------------------------------------------------ */

	puts("!!!Hello World!!!");

	int x = 10, y = 5;

	/* add() and multiply() are defined in addon.c */
	printf("Sum: %d\n", add(x, y));
	printf("Product: %d\n", multiply(x, y));

	/* ------------------------------------------------------------------ */
	/* File I/O demo                                                        */
	/* ------------------------------------------------------------------ */

	printf("\n--- File I/O Demo ---\n");

	/*
	 * WRITE — open TEMP_FILE in "w" mode and write a string.
	 * If the file already exists it is overwritten from scratch.
	 * If it does not exist it is created automatically by fopen().
	 */
	if (write_text_file(TEMP_FILE, "Hello from fileio!\nThis is a temp file.\n") == 0)
		printf("Wrote to %s\n", TEMP_FILE);

	/*
	 * READ — open TEMP_FILE in "r" mode and load its contents into buf.
	 * buf is a fixed-size stack array; read_text_file() will never write
	 * more than sizeof(buf)-1 bytes into it, keeping it null-terminated.
	 * 'n' holds the number of bytes actually read (like strlen of buf).
	 */
	char buf[256];
	int n = read_text_file(TEMP_FILE, buf, sizeof(buf));
	if (n >= 0)
		printf("Read %d bytes from %s:\n%s", n, TEMP_FILE, buf);

	/*
	 * APPEND — open LOG_FILE in "a" mode.
	 * Unlike "w", append mode never erases existing content; the file
	 * pointer starts at the end of the file every time fopen() is called.
	 * Each program run therefore adds new lines rather than replacing old ones.
	 */
	if (append_text_file(LOG_FILE, "Run #1 complete\n") == 0)
		printf("Appended entry to %s\n", LOG_FILE);
	if (append_text_file(LOG_FILE, "Run #2 complete\n") == 0)
		printf("Appended entry to %s\n", LOG_FILE);

	/* Read the log back so we can see all accumulated entries */
	int m = read_text_file(LOG_FILE, buf, sizeof(buf));
	if (m >= 0)
		printf("Log contents:\n%s", buf);

	return 0;
}
