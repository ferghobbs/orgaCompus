#include <stdint.h>
#include <assert.h>

#include "hash.h"

void
string_hash_init(string_hash *h)
{
	h->flag = STRING_HASH_INIT;
	h->hash = 0;
	h->size = 0;
}

void
string_hash_more(string_hash *sh, char *str, size_t len)
{
	assert(sh->flag == STRING_HASH_INIT || sh->flag == STRING_HASH_MORE);

	if (sh->flag == STRING_HASH_INIT) {
		sh->flag = STRING_HASH_MORE;
		sh->hash = (*str) << 7;
	}

	while ((*str) != 0 && len--) {
		sh->hash = (1000003 * sh->hash) ^ *str++;
		sh->size++;
	}
}

void
string_hash_done(string_hash *sh)
{
	assert(sh->flag == STRING_HASH_INIT || sh->flag == STRING_HASH_MORE);

	if ((sh->hash ^= sh->size) == -1)
		sh->hash = -2;

	sh->flag = STRING_HASH_DONE;
}

int32_t
string_hash_value(string_hash *sh)
{
	return sh->hash;
}

#if 0
static long string_hash(PyStringObject *a)
{
    register Py_ssize_t len;
    register unsigned char *p;
    register long x;

    if (a->ob_shash != -1)
        return a->ob_shash;
    len = Py_SIZE(a);
    p = (unsigned char *) a->ob_sval;
    x = *p << 7;
    while (--len >= 0)
        x = (1000003*x) ^ *p++;
    x ^= Py_SIZE(a);
    if (x == -1)
        x = -2;
    a->ob_shash = x;
    return x;
}
#endif
