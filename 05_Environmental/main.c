#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <curses.h>
#include <pcre2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void gen_text(const char *pattern, const char *subject, WINDOW *w) {
    int errnum;
    int i, rc;
    char buf[1024];
    int sz = sizeof(buf) - 1;
    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;
    pcre2_code *re;
    pcre2_match_data *match_data;
#ifdef NO_UTF
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
#else
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
#endif
    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        wprintw(w, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        return;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            wprintw(w, "No match\n");
            break;
        default:
            wprintw(w, "Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return;
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++) {
        wprintw(w, "%2ld: %.*s", ovector[2*i], 
                 (int)(ovector[2*i+1] - ovector[2*i]),
                 subject + ovector[2*i]);
    }
    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */
}

int min(int x, int y) { return x < y ? x : y; }

int max(int x, int y) { return x > y ? x : y; }


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    char first_line[256], second_line[256];
    
    WINDOW *win = initscr();
    cbreak();

    int state = 0, write_pos = 0, backup_pos = 0;
    char *cur_arr = first_line;
    char *other_arr = second_line;
    memset(first_line, 0, sizeof(first_line));
    memset(second_line, 0, sizeof(second_line));
    
    int beg_x, beg_y, max_x, max_y;
    getbegyx(win, beg_y, beg_x);
    getmaxyx(win, max_y, max_x);

    int mid = (max_x - beg_x) / 2 - 4;

    WINDOW *first = newwin(3, mid, 3, 3);
    werase(first);
    box(first, 0, 0);
    WINDOW *second = newwin(3, mid, 3, max_x - 4 - mid);
    werase(second);
    box(second, 0, 0);
    
    WINDOW *log = newwin(max_y - 12 - beg_y, max_x - beg_x - 4, 9, 3);

    keypad(first, 1);
    keypad(second, 1);
    scrollok(log, 1);
    box(log, 0, 0);
    refresh();
    
    do {
        werase(first);
        box(first, 0, 0);
        wrefresh(first);
        mvwgetnstr(first, 1, 1, first_line, mid - 2);
        
        werase(second);
        box(second, 0, 0);
        wrefresh(second);
        mvwgetnstr(second, 1, 1, second_line, mid - 2);
        
        wprintw(log, "\n");
        gen_text(first_line, second_line, log);
        box(log, 0, 0);
        wrefresh(log);
    } while (first_line[0] && second_line[0]);
    endwin();
}
