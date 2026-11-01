#include "strtools.h"

#include <stdio.h>

static int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static char to_lower_char(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

/* ---------- measuring and copying ---------- */

size_t str_len(const char *s) {
    const char *p = s;
    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - s);
}

int str_copy(char *dst, size_t dst_size, const char *src) {
    if (str_len(src) + 1 > dst_size) {
        return -1;
    }
    while ((*dst++ = *src++) != '\0') {
        /* the assignment copies each character, including the final '\0' */
    }
    return 0;
}

int str_concat(char *dst, size_t dst_size, const char *src) {
    size_t used = str_len(dst);
    if (used + str_len(src) + 1 > dst_size) {
        return -1;
    }
    dst += used;                                   /* jump to the end of dst, then copy */
    while ((*dst++ = *src++) != '\0') {
    }
    return 0;
}

/* ---------- in-place transformations ---------- */

void str_reverse(char *s) {
    char *start = s;
    char *end = s + str_len(s);
    if (end == start) {
        return;                                    /* empty string: nothing to do (and no end-- below) */
    }
    end--;
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

void str_to_upper(char *s) {
    for (; *s != '\0'; s++) {
        if (*s >= 'a' && *s <= 'z') {
            *s = (char)(*s - ('a' - 'A'));
        }
    }
}

void str_remove_spaces(char *s) {
    char *write = s;                               /* "scribe": where the next kept char goes */
    for (char *read = s; *read != '\0'; read++) {  /* "scout": looks at every char            */
        if (*read != ' ') {
            *write++ = *read;
        }
    }
    *write = '\0';
}

void str_remove_duplicates(char *s) {
    size_t seen[256] = {0};
    char *write = s;
    for (char *read = s; *read != '\0'; read++) {
        unsigned char c = (unsigned char)*read;
        if (!seen[c]) {
            seen[c] = 1;
            *write++ = *read;
        }
    }
    *write = '\0';
}

/* ---------- counting ---------- */

size_t str_count_char(const char *s, char target) {
    size_t count = 0;
    for (; *s != '\0'; s++) {
        if (*s == target) {
            count++;
        }
    }
    return count;
}

size_t str_count_vowels(const char *s) {
    size_t count = 0;
    for (; *s != '\0'; s++) {
        char c = to_lower_char(*s);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

size_t str_longest_run(const char *s) {
    if (*s == '\0') {
        return 0;
    }
    size_t best = 1;
    size_t current = 1;
    for (size_t i = 1; s[i] != '\0'; i++) {
        if (s[i] == s[i - 1]) {
            current++;
        } else {
            current = 1;
        }
        if (current > best) {
            best = current;
        }
    }
    return best;
}

void str_char_frequency(const char *s, size_t counts[256]) {
    for (int i = 0; i < 256; i++) {
        counts[i] = 0;
    }
    for (; *s != '\0'; s++) {
        counts[(unsigned char)*s]++;               /* the character's code is the array index */
    }
}

/* ---------- searching and comparing ---------- */

int str_find(const char *text, const char *pattern) {
    for (size_t i = 0; ; i++) {
        size_t j = 0;
        while (pattern[j] != '\0' && text[i + j] == pattern[j]) {
            j++;
        }
        if (pattern[j] == '\0') {
            return (int)i;                         /* whole pattern matched at position i */
        }
        if (text[i] == '\0') {
            return -1;                             /* ran out of text */
        }
    }
}

int str_is_palindrome(const char *s) {
    const char *start = s;
    const char *end = s + str_len(s);
    if (end == start) {
        return 1;
    }
    end--;
    while (start < end) {
        if (*start++ != *end--) {
            return 0;
        }
    }
    return 1;
}

static int palindrome_helper(const char *s, size_t start, size_t end) {
    if (start >= end) {
        return 1;                                  /* base case: met in the middle */
    }
    if (s[start] != s[end]) {
        return 0;
    }
    return palindrome_helper(s, start + 1, end - 1);
}

int str_is_palindrome_recursive(const char *s) {
    size_t len = str_len(s);
    if (len == 0) {
        return 1;
    }
    return palindrome_helper(s, 0, len - 1);
}

int str_are_anagrams(const char *a, const char *b) {
    int balance[26] = {0};
    for (; *a != '\0'; a++) {
        if (is_letter(*a)) {
            balance[to_lower_char(*a) - 'a']++;
        }
    }
    for (; *b != '\0'; b++) {
        if (is_letter(*b)) {
            balance[to_lower_char(*b) - 'a']--;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (balance[i] != 0) {
            return 0;                              /* some letter appears a different number of times */
        }
    }
    return 1;
}

/* ---------- words ---------- */

const char *str_longest_word(const char *s, size_t *length) {
    const char *best = NULL;
    size_t best_len = 0;

    while (*s != '\0') {
        while (*s == ' ') {
            s++;                                   /* skip separators */
        }
        const char *word = s;
        while (*s != '\0' && *s != ' ') {
            s++;
        }
        size_t len = (size_t)(s - word);
        if (len > best_len) {
            best_len = len;
            best = word;
        }
    }
    if (length != NULL) {
        *length = best_len;
    }
    return best;
}

/* ---------- run-length encoding ---------- */

int str_rle_compress(const char *s, char *out, size_t out_size) {
    size_t pos = 0;
    size_t i = 0;

    while (s[i] != '\0') {
        char current = s[i];
        size_t count = 0;
        while (s[i] == current) {
            count++;
            i++;
        }
        if (pos + 1 >= out_size) {
            return -1;
        }
        out[pos++] = current;
        int written = snprintf(out + pos, out_size - pos, "%zu", count);
        if (written < 0 || (size_t)written >= out_size - pos) {
            return -1;                             /* digits (plus NUL) did not fit */
        }
        pos += (size_t)written;
    }

    if (out_size == 0) {
        return -1;
    }
    out[pos] = '\0';
    return 0;
}
