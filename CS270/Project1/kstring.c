#include "kstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* These are the object definitions for the kstring class with the objects
 *   char *data // the data in the kstring
 *   size_t length // the length of the kstring
 */

/* Return the character at position pos in str. Aborts (by calling
 * abort()) if pos is beyond the bounds of the string.
 */
char kstrget(kstring str, size_t pos)
{
    if (str.length <= pos || pos < 0) // abort if pos is out of bounds
        abort();
    return str.data[pos]; // return the data in position pos
}

/* Changes the character at position pos in str. Aborts (by calling
 * abort()) if pos is beyond the bounds of the string.
 */
void kstrput(kstring str, size_t pos, char ch)
{
	if (str.length <= pos || pos < 0) // aborts if out of bounds
		abort();
	str.data[pos] = ch; // changes char at pos
}

/* Return the length of str */
size_t kstrlen(kstring str)
{
	return str.length;
}

/* Return a new kstring with length nbytes, consisting entirely of null
 * characters.  Memory is allocated for the new kstring's data.
 *
 * NOTE:
 * malloc and calloc with a length of 0 are allowed to return NULL:
 * you should either 1. always malloc at least one byte; or 2. handle
 * NULL data pointers for length-zero kstrings in all the other functions.
 */
kstring kstralloc(size_t nbytes)
{
	kstring result = { NULL, 0 };
	result.data = malloc(nbytes); // allocate nbytes of mem
	if (result.data == NULL && nbytes != 0)
	{
		printf("There has been an error allocating memory\n");
		abort();
	}
	result.length = (int)nbytes; // set length to int of nbytes
	memset(result.data, 0, nbytes); // set data to 0/NULL
	return result;
}

/* Return a new kstring that contains the contents of the null-terminated
 * C string cstr, *including* the terminating '\0'.  Memory is allocated
 * for the new kstring's data.
 */
kstring kstrfrom(const char *cstr)
{
	kstring result = { NULL, 0 };
	result = kstralloc(strlen(cstr)+1); // alloc mem
	memcpy(result.data, cstr, strlen(cstr)+1); // copy from cstr to result
	return result;
}

/* Free the buffer associated with a kstring.  Every kstring returned
 * by a function in this library must have kstrfree called on it
 * eventually, or the program will leak memory.
 *
 * It is an error to use str again after calling this function.
 */
void kstrfree(kstring str)
{
	free(str.data);
}

/* Modify the kstring pointed to by strp to be at least nbytes bytes long.
 * If strp->length was already nbytes or longer, does nothing.  Otherwise,
 * extends the memory allocation for strp->data to size nbytes, copies over
 * the old data if necessary, and fills the new indexes with null characters.
 * This function may modify both the length and the data pointer members of
 * *strp.
 */
void kstrextend(kstring *strp, size_t nbytes)
{
	if (strp->length >= nbytes) // do nothing if more than nbytes
		return;
	kstring temp = {strp->data, strp->length}; // set temp to have same as strp
	*strp = kstralloc(nbytes); // alloc using kstralloc funstion
	memcpy(strp->data, temp.data, temp.length); // copy from temp to strp after alloc to all null
	kstrfree(temp);
}

/* Appends a copy of the data in src to the data in *destp.  Extends dest
 * with kstrextend then copies the data.  If destp->length was originally
 * N, the new value of destp->length is (N + src.length).
 */
void kstrcat(kstring *destp, kstring src)
{
	size_t newLength = destp->length + src.length; // new temp size_t is both lengths together
	kstrextend(destp, newLength); // extend to length of both
	strcat(destp->data, src.data); // concat src to destp
}
