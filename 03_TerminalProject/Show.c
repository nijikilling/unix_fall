#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MINIMAL_ALLOC = 30;

typedef struct data {
    char **mat;
    int n;
    int allocated;
} data;

int read_line_to_data(data *d, FILE *fin) {
    if (!d->mat) {
        d->mat = calloc(MINIMAL_ALLOC, sizeof(*d->mat));
        d->allocated = MINIMAL_ALLOC;
        d->n = 0;
    } else if (d->n == d->allocated) {
        d->allocated *= 2;
        d->mat = realloc(d->mat, sizeof(*d->mat) * d->allocated);
    }
    d->mat[d->n] = NULL;
    int ln = 0;
    int retcode = getline(&d->mat[d->n], &ln, fin);
    if (retcode != -1) {
        d->n += 1;
    }
}

void free_data(data *d) {
    if (d->mat == NULL) {
        return;
    }
    for (int i = 0; i < d->allocated; i++) {
        free(d->mat[i]);
    }
    free(d->mat);
}

int min(int x, int y) { return x < y ? x : y; }

int max(int x, int y) { return x > y ? x : y; }

void draw_text(WINDOW *win, data *d, char *fname, int off_x, int off_y) {
    int beg_x, beg_y, max_x, max_y;
    werase(win);
    getbegyx(win, beg_y, beg_x);
    getmaxyx(win, max_y, max_x);
    mvinch(beg_y, beg_x);
    int n = d->n;
    if ((max_x - beg_x < 15) || (max_y - beg_y < 10)) {
        printw("Window too small!");
        return;
    }
    printw("File: %s, Length: %d\n\n\n", fname, n);
    for (int i = 0; i < max_y - beg_y - 7; i++) {
        mvinch(beg_y + i + 4, beg_x + 4);
        if (off_y + i >= d->n) {
            clrtoeol();
            continue;
        }
        int ln = strlen(d->mat[off_y + i]);
        printw("%4d: %.*s", off_y + i, max_x - beg_x - 12,
               d->mat[off_y + i] + min(ln - 1, off_x));
    }
    int y1 = beg_y + 3, y2 = max_y - 3, x1 = beg_x + 3, x2 = max_x - 3;
    // Following 8 lines taken from Stackoverflow as it's super common task
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
    refresh();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./Show path_to_file");
        return 1;
    }

    FILE *inf = fopen(argv[1], "r");
    if (!inf) {
        printf("File open error!\n");
        return 1;
    }

    data d;
    memset(&d, 0, sizeof(data));
    while (read_line_to_data(&d, inf) != -1) {
    }
    fclose(inf);
    WINDOW *win = initscr();
    noecho();
    keypad(win, 1);

    int off_x = 0, off_y = 0;

    draw_text(win, &d, argv[1], off_x, off_y);

    int lastkey = getch();
    while (lastkey != 'q') {
        if (lastkey == KEY_UP) {
            off_y = max(off_y - 1, 0);
        } else if (lastkey == KEY_DOWN || lastkey == ' ') {
            off_y = min(off_y + 1, d.n);
        } else if (lastkey == KEY_LEFT) {
            off_x = max(off_x - 1, 0);
        } else if (lastkey == KEY_RIGHT) {
            off_x += 1;
        }
        draw_text(win, &d, argv[1], off_x, off_y);
        lastkey = getch();
    }

    free_data(&d);
    endwin();
}
