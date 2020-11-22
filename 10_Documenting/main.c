/** @file main.c
 * Main file
 *
 */

#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define _(STRING) gettext((STRING))

#define MANUAL _("Program for guessing numbers. May operate in Roman and Arabic numbers.\n \
\n\
Usage: main [OPTION]\n\
\n\
    --help              print this help, then exit\n\
    --version           print version, then exit\n\
    -r                  use roman numbers instead of arabic\n\
\n\
The program will attempt to guess user number by inetracting with him\n")


/** Pair
*/
typedef struct pair {
    int x;
    unsigned char y;
} pair;

pair nums[5] = {{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}};

void add_num(int *write_idx, pair *pair, char *buf, int bufsize) {
    if (pair == NULL || *write_idx == bufsize) {
        return;
    }
    buf[*write_idx] = pair->y;
    (*write_idx)++;
}

int min(int a, int b) {
    return a < b ? a : b;
}


/**
 * Convert @p val into roman system, write to @p buf, but no more than @p bufsize - 1 symbols
 *
 * @param val number to be converted
 * @param buf buffer where to write
 * @param bufsize length of buffer
 * @returns void
 */
void convert_to_roman(int val, char *buf, int bufsize) {
    int nums_cnt = sizeof(nums) / sizeof(*nums);
    int write_idx = 0;
    while (val > 0) {
        int best_diff = val;
        pair *best_a = NULL, *best_b = NULL;
        for (int i = 0; i < nums_cnt; i++) {
            int diff = val - nums[i].x;
            if (diff >= 0 && diff < best_diff) {
                best_a = nums + i;
                best_diff = diff;
            }
        }
        for (int i = 1; i < nums_cnt; i++) {
            pair *cur_b = NULL;
            if (nums[i].x / nums[i - 1].x == 5) {
                cur_b = nums + i - 1;
            } else {
                cur_b = nums + i - 2;
            }
            int diff = val - (nums[i].x - cur_b->x);
            if (diff >= 0 && diff < best_diff) {
                best_a = nums + i;
                best_b = cur_b;
                best_diff = diff;
            }
        }
        add_num(&write_idx, best_b, buf, bufsize);
        add_num(&write_idx, best_a, buf, bufsize);
        val = best_diff;
    }
    buf[min(bufsize - 1, write_idx)] = 0;
};


/**
 * Convert @p num from roman system
 *
 * @param num number to be converted
 * @returns numeric value
 */
int convert_from_roman(char *num) {
    pair *prev = NULL;
    int nums_cnt = sizeof(nums) / sizeof(*nums);
    int ans = 0;
    while (*num) {
        for (int i = 0; i < nums_cnt; i++) {
            if (*num == nums[i].y) {
                if (prev == NULL) {
                    prev = nums + i;
                } else if ((prev->x * 5 == nums[i].x) || (prev->x * 10 == nums[i].x)) {
                    ans += nums[i].x - prev->x;
                    prev = NULL;
                } else {
                    ans += prev->x;
                    prev = nums + i;
                }
            }
        }
        num++;
    }
    if (prev != NULL) {
        ans += prev->x;
    }
    return ans;
}


int use_roman = 0;

void print_num(int num) {
    char buf[64];
    if (use_roman) {
        convert_to_roman(num, buf, 64);
        printf("%s", buf);
    } else {
        printf("%d", num);
    }
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("main", ".");
    textdomain("main");
    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-r", 3)) {
            use_roman = 1;
        } else if (!strncmp(argv[i], "--help", 7)) {
            printf("%s\n", MANUAL);
            return 0;
        } else if (!strncmp(argv[i], "--version", 10)) {
            printf("1.0\n");
            return 0;
        } else {
            printf("%s\n", _(MANUAL));
            return 1;
        }
    }

    printf("%s\n", _("Come up with a number from 1 to 100, and I'll try to guess it!"));
    int l = 0, r = 100;
    while (l < r) {
        int m = (l + r) / 2;
        printf("%s ", _("Is the number greater (1), equal (0) or less (-1) than"));
        print_num(m);
        printf("?\n");
        int a;
        scanf("%d", &a);
        if (a < 0) {
            r = m;
        } else if (a > 0) {
            l = m;
        } else {
            break;
        }
    }
    printf("%s ", _("Your number was"));
    print_num((l + r) / 2);
    printf("\n");
}
