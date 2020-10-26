#include <stdlib.h>

int main() {
    char *a = malloc(20048);
    free(a);
    free(a);
    return 0;
}
