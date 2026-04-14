/*
 * fileio.h
 *
 *  Created on: Apr 7, 2026
 *      Author: alexchiomny
 *
 *  Public interface for the file I/O helper module (fileio.c).
 *  Include this header in any .c file that needs to read or write
 *  text files through these helpers.
 */

/*
 * Include guard — prevents this header from being processed more than once
 * per translation unit, which would cause "duplicate declaration" errors.
 * The name FILEIO_H_ mirrors the filename by convention.
 */
#ifndef FILEIO_H_
#define FILEIO_H_

/*
 * write_text_file(path, text)
 *   Creates or overwrites the file at 'path' with the string 'text'.
 *   Returns  0 on success.
 *   Returns -1 on failure (error printed to stderr via perror).
 */
int write_text_file(const char *path, const char *text);

/*
 * read_text_file(path, buf, buf_size)
 *   Reads up to buf_size-1 bytes from the file at 'path' into 'buf'.
 *   Always null-terminates buf so it can be used as a C string.
 *   Returns the number of bytes read on success.
 *   Returns -1 on failure (error printed to stderr via perror).
 */
int read_text_file(const char *path, char *buf, int buf_size);

/*
 * append_text_file(path, text)
 *   Appends the string 'text' to the end of the file at 'path'.
 *   Creates the file if it does not already exist.
 *   Returns  0 on success.
 *   Returns -1 on failure (error printed to stderr via perror).
 */
int append_text_file(const char *path, const char *text);

#endif /* FILEIO_H_ */
