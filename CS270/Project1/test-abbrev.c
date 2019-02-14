#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kstring.h"

static int t_kstralloc_free(void)
{
	kstring a = kstralloc(1024);
	kstrfree(a);
	return 1;
}

static int t_kstralloc_zeroed(void)
{
	int result = 1;
	size_t i;
	kstring a = kstralloc(1024);

	for (i = 0; i < 1024; ++i)
		if (a.data[i] != '\0')
			result = 0;

	kstrfree(a);
	return result;
}

static int t_kstralloc_length(void)
{
	kstring a = kstralloc(1024);
	int result = a.length == 1024;
	kstrfree(a);
	return result;
}

static int t_kstralloc_length_zero(void)
{
	kstring a = kstralloc(0);
	int result = a.length == 0;
	kstrfree(a);
	return result;
}

static int t_kstrlen(void)
{
	kstring a = kstralloc(1024);
	int result = kstrlen(a) == 1024;
	kstrfree(a);
	return result;
}

static int t_kstrfrom_length(void)
{
	const char *msg = "hello, world!";
	kstring a = kstrfrom(msg);
	int result = kstrlen(a) == 1 + strlen(msg);
	kstrfree(a);
	return result;
}

static int t_kstrfrom_null(void)
{
	const char *msg = "hello, world!";
	kstring a = kstrfrom(msg);
	int result = a.data[kstrlen(a) - 1] == '\0';
	kstrfree(a);
	return result;
}

static int t_kstrget(void)
{
	size_t i;
	int result = 1;

	char msg[] = "hello, world!";
	kstring a = kstrfrom(msg);

	for (i = 0; i < a.length; ++i)
		if (kstrget(a, i) != msg[i])
			result = 0;

	kstrfree(a);
	return result;
}

static int t_kstrput(void)
{
	size_t i;

	kstring a = kstralloc(16);

	for (i = 0; i < 15; ++i)
		kstrput(a, i, '!');
	kstrput(a, 15, '\0');

	int result = strcmp(a.data, "!!!!!!!!!!!!!!!") == 0;

	kstrfree(a);
	return result;
}

static int t_kstrextend_longer(void)
{
	kstring a = kstralloc(12);
	kstrextend(&a, 16);
	a.data[15] = '!';

	int result = a.length == 16;
	kstrfree(a);
	return result;
}

static int t_kstrextend_shorter(void)
{
	kstring a = kstralloc(12);
	kstrextend(&a, 8);
	a.data[11] = '!';

	int result = a.length == 12;
	kstrfree(a);
	return result;
}

static int t_kstrcat_with_empty(void)
{
	kstring a = kstrfrom("hello");
	kstring b = kstralloc(0);
	kstrcat(&a, b);

	int result = a.length == 6 && strcmp(a.data, "hello") == 0;
	kstrfree(a);
	kstrfree(b);
	return result;
}

static int t_kstrcat_nonempty(void)
{
	kstring a = kstralloc(1);
	kstring b = kstralloc(1);
	a.data[0] = 'A';
	b.data[0] = 'B';
	kstrcat(&a, b);

	int result = a.length == 2 && a.data[0] == 'A' && a.data[1] == 'B';
	kstrfree(a);
	kstrfree(b);
	return result;
}

struct testcase
{
	int (*fn)(void);
	const char *description;
};

struct testcase Tests[] = {
	{ t_kstralloc_free,        "kstralloc + kstrfree" },
	{ t_kstralloc_zeroed,      "kstralloc initializes memory to 0" },
	{ t_kstralloc_length,      "kstralloc sets length" },
	{ t_kstralloc_length_zero, "kstralloc sets length (0 bytes)" },
	{ t_kstrlen,               "kstrlen matches allocation" },
	{ t_kstrfrom_length,       "kstrfrom gives correct length" },
	{ t_kstrfrom_null,         "kstrfrom contains null byte" },
	{ t_kstrget,               "kstrget fetches all indices correctly" },
	{ t_kstrput,               "kstrput sets all indices correctly" },
	{ t_kstrextend_longer,     "kstrextend lengthens kstring" },
	{ t_kstrextend_shorter,    "kstrextend does not shorten kstring" },
	{ t_kstrcat_with_empty,    "kstrcat with empty kstring" },
	{ t_kstrcat_nonempty,      "kstrcat has correct data" },
};

int main(void)
{
	int i;
	int numtests = sizeof(Tests) / sizeof(struct testcase);
	int successes = 0;
	int skips = 0;

	for (i = 0; i < numtests; ++i)
	{
		printf("Test %3d/%3d: %-50s ",
		       i, numtests, Tests[i].description);
		fflush(stdout);
		int success = (Tests[i].fn)();
		if (success > 0)
		{
			++successes;
			printf("\033[32;1msucceeded\033[0m (%d)\n", success);
		}
		else if (success < 0)
		{
			++skips;
			printf("\033[33;1mskipped\033[0m (%d)\n", success);
		}
		else
			printf("\033[31;1mfailed\033[0m\n");
	}

	printf("\nRESULTS: %d / %d tests passed, %d skipped, %d failed\n",
	       successes, numtests, skips, numtests - successes - skips);

	/* Return value from main is "backwards": 0 for success */
	return successes != numtests - skips;
}
