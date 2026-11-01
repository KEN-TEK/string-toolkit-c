#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "strtools.h"

static void test_len_copy_concat(void) {
    assert(str_len("") == 0);
    assert(str_len("hello") == 5);

    char buf[8];
    assert(str_copy(buf, sizeof buf, "hello") == 0 && strcmp(buf, "hello") == 0);
    assert(str_copy(buf, sizeof buf, "1234567") == 0);        /* exactly fits with the NUL */
    assert(str_copy(buf, sizeof buf, "12345678") == -1);      /* one too many: refused */

    assert(str_copy(buf, sizeof buf, "ab") == 0);
    assert(str_concat(buf, sizeof buf, "cde") == 0 && strcmp(buf, "abcde") == 0);
    assert(str_concat(buf, sizeof buf, "fghi") == -1);        /* would overflow: refused */
    assert(strcmp(buf, "abcde") == 0);                        /* and left untouched */
}

static void test_reverse_upper(void) {
    char a[] = "hello";
    str_reverse(a);
    assert(strcmp(a, "olleh") == 0);

    char even[] = "abcd";
    str_reverse(even);
    assert(strcmp(even, "dcba") == 0);

    char empty[] = "";
    str_reverse(empty);                                       /* must not crash */
    assert(strcmp(empty, "") == 0);

    char one[] = "x";
    str_reverse(one);
    assert(strcmp(one, "x") == 0);

    char up[] = "Hello, World 42!";
    str_to_upper(up);
    assert(strcmp(up, "HELLO, WORLD 42!") == 0);
}

static void test_remove(void) {
    char s[] = " pro gram ming ";
    str_remove_spaces(s);
    assert(strcmp(s, "programming") == 0);

    char all[] = "   ";
    str_remove_spaces(all);
    assert(strcmp(all, "") == 0);

    char d[] = "mississippi";
    str_remove_duplicates(d);
    assert(strcmp(d, "misp") == 0);

    char e[] = "";
    str_remove_duplicates(e);
    assert(strcmp(e, "") == 0);
}

static void test_counting(void) {
    assert(str_count_char("banana", 'a') == 3);
    assert(str_count_char("banana", 'z') == 0);
    assert(str_count_vowels("Programming IS fun") == 5);
    assert(str_count_vowels("rhythm") == 0);

    assert(str_longest_run("") == 0);
    assert(str_longest_run("a") == 1);
    assert(str_longest_run("aabbbcc") == 3);
    assert(str_longest_run("abc") == 1);
    assert(str_longest_run("abccc") == 3);                    /* the longest run is at the very end */

    size_t f[256];
    str_char_frequency("hello", f);
    assert(f['l'] == 2 && f['h'] == 1 && f['z'] == 0);
}

static void test_find(void) {
    assert(str_find("algorithm", "gori") == 2);
    assert(str_find("algorithm", "algorithm") == 0);
    assert(str_find("algorithm", "thm") == 6);                /* match at the very end */
    assert(str_find("algorithm", "xyz") == -1);
    assert(str_find("abc", "abcd") == -1);                    /* pattern longer than text */
    assert(str_find("abc", "") == 0);
    assert(str_find("", "a") == -1);
}

static void test_palindromes(void) {
    assert(str_is_palindrome(""));
    assert(str_is_palindrome("a"));
    assert(str_is_palindrome("level"));
    assert(str_is_palindrome("abba"));
    assert(!str_is_palindrome("hello"));
    assert(!str_is_palindrome("Level"));                      /* exact comparison: case matters */

    assert(str_is_palindrome_recursive(""));
    assert(str_is_palindrome_recursive("level"));
    assert(str_is_palindrome_recursive("abba"));
    assert(!str_is_palindrome_recursive("hello"));
}

static void test_anagrams(void) {
    assert(str_are_anagrams("listen", "silent"));
    assert(str_are_anagrams("Dormitory", "dirty room"));
    assert(str_are_anagrams("", ""));
    assert(!str_are_anagrams("abc", "abd"));
    assert(!str_are_anagrams("aab", "abb"));
    assert(!str_are_anagrams("abc", "abcc"));
}

static void test_longest_word(void) {
    size_t len;
    const char *w = str_longest_word("the quick brown fox", &len);
    assert(w != NULL && len == 5 && strncmp(w, "quick", 5) == 0);   /* first of two 5-letter words */

    w = str_longest_word("  spaced   out  ", &len);
    assert(len == 6 && strncmp(w, "spaced", 6) == 0);

    assert(str_longest_word("", &len) == NULL && len == 0);
    assert(str_longest_word("   ", &len) == NULL);
    assert(str_longest_word("one", NULL) != NULL);                  /* length pointer is optional */
}

static void test_rle(void) {
    char out[64];
    assert(str_rle_compress("wwwwaaadexxxxxx", out, sizeof out) == 0);
    assert(strcmp(out, "w4a3d1e1x6") == 0);

    assert(str_rle_compress("", out, sizeof out) == 0 && strcmp(out, "") == 0);
    assert(str_rle_compress("a", out, sizeof out) == 0 && strcmp(out, "a1") == 0);
    assert(str_rle_compress("aaaaaaaaaaaa", out, sizeof out) == 0);
    assert(strcmp(out, "a12") == 0);                                /* multi-digit counts */

    char tiny[4];
    assert(str_rle_compress("abcdef", tiny, sizeof tiny) == -1);    /* too small: refused safely */
    assert(str_rle_compress("a", tiny, 0) == -1);
}

int main(void) {
    test_len_copy_concat();
    test_reverse_upper();
    test_remove();
    test_counting();
    test_find();
    test_palindromes();
    test_anagrams();
    test_longest_word();
    test_rle();
    printf("All tests passed.\n");
    return 0;
}
