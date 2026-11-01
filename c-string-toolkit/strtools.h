#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <stddef.h>

/*
 * String functions written from scratch with pointer arithmetic.
 *
 * Functions that write into a caller's buffer take the buffer size and
 * return 0 on success or -1 if the result would not fit, so they can
 * never overflow the buffer.
 */

/* Measuring and copying */
size_t str_len(const char *s);
int    str_copy(char *dst, size_t dst_size, const char *src);
int    str_concat(char *dst, size_t dst_size, const char *src);

/* In-place transformations (the string must be a modifiable array, not a literal) */
void   str_reverse(char *s);
void   str_to_upper(char *s);
void   str_remove_spaces(char *s);
void   str_remove_duplicates(char *s);          /* keeps the first occurrence of each character */

/* Counting */
size_t str_count_char(const char *s, char target);
size_t str_count_vowels(const char *s);         /* a e i o u, either case */
size_t str_longest_run(const char *s);          /* longest block of one repeated character */
void   str_char_frequency(const char *s, size_t counts[256]);

/* Searching and comparing */
int    str_find(const char *text, const char *pattern);   /* index, or -1; empty pattern gives 0 */
int    str_is_palindrome(const char *s);                  /* exact comparison, iterative          */
int    str_is_palindrome_recursive(const char *s);        /* same result, recursive version       */
int    str_are_anagrams(const char *a, const char *b);    /* ignores case, spaces and punctuation */

/* Words */
const char *str_longest_word(const char *s, size_t *length); /* first longest word, or NULL */

/* Run-length encoding: "wwwaa" becomes "w3a2". Returns 0, or -1 if out is too small. */
int    str_rle_compress(const char *s, char *out, size_t out_size);

#endif
