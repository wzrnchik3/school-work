#include "kstring.h"

char kstrget(kstring str, size_t pos)
{
	return '\0';
}

void kstrput(kstring str, size_t pos, char ch)
{
}

size_t kstrlen(kstring str)
{
	return 0;
}

kstring kstralloc(size_t nbytes)
{
	kstring result = { NULL, 0 };
	return result;
}

kstring kstrfrom(const char *cstr)
{
	kstring result = { NULL, 0 };
	return result;
}

void kstrfree(kstring str)
{
}

void kstrextend(kstring *strp, size_t nbytes)
{
}

void kstrcat(kstring *destp, kstring src)
{
}
