# String Toolkit in C

A library of string functions written from scratch with pointer arithmetic,
without relying on `<string.h>`, plus a demo program and tests. Standard C11, no
warnings under `-Wall -Wextra -Wpedantic`, and clean under AddressSanitizer and
UndefinedBehaviorSanitizer.

## What it demonstrates

| Concept | Where |
|---|---|
| Pointer arithmetic (walking and comparing `char *`) | `str_len`, `str_reverse`, `str_is_palindrome` |
| Two-pointer technique ("scout and scribe") for in-place edits | `str_remove_spaces`, `str_remove_duplicates` |
| Buffer-safe design: functions take the buffer size and refuse instead of overflowing | `str_copy`, `str_concat`, `str_rle_compress` |
| Frequency table indexed by character code (O(n) instead of O(n^2)) | `str_char_frequency`, `str_are_anagrams` |
| Recursion vs iteration for the same problem | `str_is_palindrome_recursive` |
| Run-length encoding with multi-digit counts | `str_rle_compress` |
| Command-line arguments (`argc` / `argv`) | `main.c` |
| Edge cases tested: empty string, one character, exact fit, one too long | `tests.c` |

## Functions

| Group | Functions |
|---|---|
| Measure and copy | `str_len`, `str_copy`, `str_concat` |
| Transform in place | `str_reverse`, `str_to_upper`, `str_remove_spaces`, `str_remove_duplicates` |
| Count | `str_count_char`, `str_count_vowels`, `str_longest_run`, `str_char_frequency` |
| Search and compare | `str_find`, `str_is_palindrome`, `str_is_palindrome_recursive`, `str_are_anagrams` |
| Words | `str_longest_word` |
| Encode | `str_rle_compress` |

## Build and run

```bash
make                          # builds ./demo and ./tests
./demo                        # analyses a sample sentence
./demo "any text you like"    # analyses your own text
make test                     # run the tests
make check                    # tests again with sanitizers
make clean
```

## Design notes

- **String literals are read-only.** `char s[] = "abc";` makes a modifiable copy, but
  `char *s = "abc";` points at read-only memory, so in-place functions like `str_reverse`
  would crash on it. The in-place functions are documented as needing arrays.
- **Why pass `dst_size`?** Without it, a copy function cannot know whether the result fits.
  Returning `-1` on overflow turns a silent memory bug into a handled error.
- **Why a frequency array instead of nested loops?** Counting each character once into
  `counts[(unsigned char)c]` is O(n). Re-counting every character against the rest is O(n^2).
  The `(unsigned char)` cast prevents a negative index for non-ASCII bytes.
- **Anagram check** keeps a signed balance per letter: add for the first word, subtract for
  the second, and every balance must end at zero.

## Possible next steps

- Case-insensitive `str_find`.
- Split a string into words and return an array of pointers.
- Handle UTF-8 instead of single-byte characters.
