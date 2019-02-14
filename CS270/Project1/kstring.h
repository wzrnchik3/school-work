#ifndef KSTRING_H_INCLUDED
#include <stddef.h> /* For size_t */

/* Allow C++ programs to link to this. */
#ifdef __cplusplus
extern "C" {
#endif
/* A structure representing a counted string of bytes.
 *
 * In general, a function working with a read-only kstring can take
 * its parameter by value.  A function that modifies a kstring's
 * length must take a pointer to the kstring.
 */
typedef struct
{
	char *data;
	size_t length;
} kstring;

/* If memory allocation fails at any point, the following functions
 * should print a message to stderr and call abort().
 */

/* Return the character at position pos in str. Aborts (by calling
 * abort()) if pos is beyond the bounds of the string.
 */
char kstrget(kstring str, size_t pos);

/* Changes the character at position pos in str. Aborts (by calling
 * abort()) if pos is beyond the bounds of the string.
 */
void kstrput(kstring str, size_t pos, char ch);

/* Return the length of str */
size_t kstrlen(kstring str);

/* Return a new kstring with length nbytes, consisting entirely of null
 * characters.  Memory is allocated for the new kstring's data.
 *
 * NOTE:
 * malloc and calloc with a length of 0 are allowed to return NULL:
 * you should either 1. always malloc at least one byte; or 2. handle
 * NULL data pointers for length-zero kstrings in all the other functions.
 */
kstring kstralloc(size_t nbytes);

/* Return a new kstring that contains the contents of the null-terminated
 * C string cstr, *including* the terminating '\0'.  Memory is allocated
 * for the new kstring's data.
 */
kstring kstrfrom(const char *cstr);

/* Free the buffer associated with a kstring.  Every kstring returned
 * by a function in this library must have kstrfree called on it
 * eventually, or the program will leak memory.
 *
 * It is an error to use str again after calling this function.
 */
void kstrfree(kstring str);

/* Modify the kstring pointed to by strp to be at least nbytes bytes long.
 * If strp->length was already nbytes or longer, does nothing.  Otherwise,
 * extends the memory allocation for strp->data to size nbytes, copies over
 * the old data if necessary, and fills the new indexes with null characters.
 * This function may modify both the length and the data pointer members of
 * *strp.
 */
void kstrextend(kstring *strp, size_t nbytes);

/* Appends a copy of the data in src to the data in *destp.  Extends dest
 * with kstrextend then copies the data.  If destp->length was originally
 * N, the new value of destp->length is (N + src.length).
 */
void kstrcat(kstring *destp, kstring src);

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif
