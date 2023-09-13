/*
 *
 * Simple example of how to use tlsh_from_tlsh_str (load hash from a string) and calculate diff score
 *
 */
#include <tlshc/tlsh.h>
#include <stdio.h>

int main() {
    int err_code;
    int diff;
    Tlsh* thash1 = tlsh_new();
    Tlsh* thash2 = tlsh_new();
    char *hash_1 = "T1F7D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD8551";
    char *hash_2 = "T1F7D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD4329";

    printf("stating program\n");
    err_code = tlsh_from_tlsh_str(thash1, hash_1);
    printf("Debug: err code of hash_1: %d\n", err_code);
    err_code = tlsh_from_tlsh_str(thash2, hash_2);
    printf("Debug: err code of hash_2: %d\n", err_code);
    diff = tlsh_total_diff(thash1, thash2, 0);
    printf("Diff value: %d\n", diff);
}