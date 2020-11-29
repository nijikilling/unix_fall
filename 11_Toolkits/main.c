#include <glib.h>
#include <stdio.h>

GHashTable *table;

int comparator(const void *a, const void *b) {
    int c1 = g_hash_table_lookup(table, a), c2 = g_hash_table_lookup(table, b);
    if (c1 != c2) {
        return c1 < c2 ? -1 : 1;
    }
    return 0;
}

void print_my(const char *a) {
    if (a) {
        int c1 = g_hash_table_lookup(table, a);
        printf("%80s: %4d\n", a, c1);

    }
}

int main() {
    table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    
    char line[81];

    while (fgets(line, 80, stdin)) {
        char **spl = g_strsplit_set(line, " \t\r\n", 0);
        
        char **p = spl;
        while (*p) {
            g_hash_table_insert(table, *p, g_hash_table_lookup(table, *p) + 1);
            p++;
        }
        g_free(spl);
    }  
    
    GList *keys_restricted = g_hash_table_get_keys(table);
    GList *keys_our = g_list_copy(keys_restricted);
    
    g_list_sort(keys_our, comparator);

    g_list_foreach(keys_our, print_my, NULL);
    
    g_list_free(keys_our);
    g_list_free(keys_restricted);
    g_hash_table_destroy(table);
    
}
