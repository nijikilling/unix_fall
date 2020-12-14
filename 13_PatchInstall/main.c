#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define _(STRING) gettext(STRING)

int main() {
    
    setlocale(LC_ALL, "");
    bindtextdomain("main", LDIR);
    textdomain("main");
    printf("%s\n", _("Come up with a number from 1 to 100, and I'll try to guess it!"));
    int l = 0, r = 100;
    while (l < r) {
        int m = (l + r) / 2;
        printf("%s %d?\n", _("Is the number greater (1), equal (0) or less (-1) than"), m);
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
    printf("%s %d\n", _("Your number was"), (l + r) / 2);
}
