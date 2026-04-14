/*
 * fileio.c
 *
 *  Created on: Apr 7, 2026
 *      Author: alexchiomny
 *
 *  Implementation of the file I/O helpers declared in fileio.h.
 *
 *  All three functions follow the same pattern:
 *    1. Open the file with fopen() using the appropriate mode.
 *    2. Do the read or write operation.
 *    3. Close the file with fclose() to flush buffers and release the handle.
 *    4. Return 0 for success or -1 for failure.
 *
 *  fopen() mode strings:
 *    "w"  — write   : create or overwrite, position at start
 *    "r"  — read    : file must exist, position at start
 *    "a"  — append  : create or open existing, position at end
 */

#include <stdio.h>    /* FILE, fopen, fclose, fputs, fread, perror */
#include <string.h>   /* included for potential future string utilities */
#include "fileio.h"

/* ------------------------------------------------------------------ */
/* write_text_file                                                      */
/* ------------------------------------------------------------------ */

/*
 * Opens 'path' in write mode ("w") and writes 'text' to it.
 *
 * "w" mode behaviour:
 *   - If the file does not exist, fopen creates it.
 *   - If the file already exists, its previous content is erased first.
 *
 * fputs() writes the string without adding an extra newline, so the caller
 * controls exactly what ends up in the file (including any '\n' characters).
 *
 * fclose() must always be called after fopen() succeeds, otherwise the
 * OS file handle leaks and buffered data may never reach the disk.
 */
int write_text_file(const char *path, const char *text) {
    FILE *fp = fopen(path, "w");  /* open for writing (overwrite) */
    if (fp == NULL) {
        /* fopen failed — perror prints the OS reason (e.g. "No such file or directory") */
        perror("write_text_file: fopen");
        return -1;
    }
    fputs(text, fp);   /* write the string to the file */
    fclose(fp);        /* flush and close */
    return 0;
}

/* ------------------------------------------------------------------ */
/* read_text_file                                                       */
/* ------------------------------------------------------------------ */

/*
 * Opens 'path' in read mode ("r") and reads up to buf_size-1 bytes into buf.
 *
 * fread() reads raw bytes and returns the number of bytes actually read,
 * which may be less than buf_size-1 if the file is smaller.
 *
 * We reserve one byte (buf_size - 1) so we can place a '\0' terminator
 * after the data, turning the buffer into a valid C string.
 *
 * The cast to (int) is safe here because buf_size is declared as int,
 * so the return value of fread will never exceed INT_MAX in this usage.
 */
int read_text_file(const char *path, char *buf, int buf_size) {
    FILE *fp = fopen(path, "r");  /* open for reading */
    if (fp == NULL) {
        perror("read_text_file: fopen");
        return -1;
    }

    /* fread(buffer, element_size, max_elements, stream) */
    int len = (int)fread(buf, 1, buf_size - 1, fp);  /* read up to buf_size-1 bytes */
    buf[len] = '\0';   /* null-terminate so buf is a proper C string */

    fclose(fp);
    return len;   /* number of bytes read */
}

/* ------------------------------------------------------------------ */
/* append_text_file                                                     */
/* ------------------------------------------------------------------ */

/*
 * Opens 'path' in append mode ("a") and writes 'text' at the end.
 *
 * "a" mode behaviour:
 *   - If the file does not exist, fopen creates it (same as "w").
 *   - If the file already exists, existing content is preserved and the
 *     file pointer is placed at the very end before every write.
 *
 * This makes "a" ideal for log files where each program run should add
 * new lines without losing the history from previous runs.
 */
int append_text_file(const char *path, const char *text) {
    FILE *fp = fopen(path, "a");  /* open for appending */
    if (fp == NULL) {
        perror("append_text_file: fopen");
        return -1;
    }
    fputs(text, fp);   /* write text at the end of the file */
    fclose(fp);
    return 0;
}
