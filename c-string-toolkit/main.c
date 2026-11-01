#include <stdio.h>

#include "strtools.h"

/*
 * Usage:  ./demo                  analyses a sample sentence
 *         ./demo "your text"      analyses the text you pass in
 */
int main(int argc, char *argv[]) {
    const char *input = (argc > 1) ? argv[1] : "the quick brown fox jumps over the lazy dog";

    printf("Text: \"%s\"\n\n", input);
    printf("length          : %zu\n", str_len(input));
    printf("vowels          : %zu\n", str_count_vowels(input));
    printf("palindrome      : %s\n", str_is_palindrome(input) ? "yes" : "no");

    size_t word_len;
    const char *word = str_longest_word(input, &word_len);
    if (word != NULL) {
        printf("longest word    : %.*s (%zu letters)\n", (int)word_len, word, word_len);
    }

    char buf[256];

    if (str_copy(buf, sizeof buf, input) == 0) {
        str_reverse(buf);
        printf("reversed        : %s\n", buf);

        str_to_upper(buf);
        printf("upper (of rev.) : %s\n", buf);

        str_copy(buf, sizeof buf, input);
        str_remove_spaces(buf);
        printf("no spaces       : %s\n", buf);

        str_copy(buf, sizeof buf, input);
        str_remove_duplicates(buf);
        printf("unique chars    : %s\n", buf);
    } else {
        printf("(input too long for the demo buffer)\n");
    }

    printf("\nLetter frequency:\n");
    size_t freq[256];
    str_char_frequency(input, freq);
    for (int c = 'a'; c <= 'z'; c++) {
        if (freq[c] > 0) {
            printf("  %c -> %zu\n", c, freq[c]);
        }
    }

    printf("\nExtra checks\n");
    if (str_rle_compress("wwwwaaadexxxxxx", buf, sizeof buf) == 0) {
        printf("  run-length encoding of \"wwwwaaadexxxxxx\" : %s\n", buf);
    }
    printf("  \"listen\" / \"silent\" anagrams     : %s\n",
           str_are_anagrams("listen", "silent") ? "yes" : "no");
    printf("  \"Dormitory\" / \"dirty room\"       : %s\n",
           str_are_anagrams("Dormitory", "dirty room") ? "yes" : "no");
    printf("  index of \"gori\" in \"algorithm\"   : %d\n", str_find("algorithm", "gori"));
    return 0;
}
