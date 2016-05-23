#include <stdio.h>
#include "test.h"

/* http://stackoverflow.com/a/7603688/6167799 */
static int test_lfsr = 0xACE1u;

int
test_rand (void)
{
    return test_lfsr = (
        test_lfsr >> 1
    ) | ((((
        test_lfsr >> 0
    ) ^ (
        test_lfsr >> 2
    ) ^ (
        test_lfsr >> 3
    ) ^ (
        test_lfsr >> 5
    )) & 1) << 15);
}

int
test_should (const char *name, int b)
{
    const char *r = b ? "OK" : "KO";
    printf("[%s]: should %s\n", r, name);
    return b ? TEST_SUCCESS : TEST_FAILURE;
}

void
test_print_message (const char *msg)
{
    printf("[MSG]: %s\n", msg);
}

void
test_print_error (const char *err)
{
    printf("[ERR]: %s\n", err);
}

void
test_print_heading (int lvl, const char *name)
{
    char hashes[] = "######";
    hashes[lvl] = 0;
    printf("%s %s\n\n", hashes, name);
}

void
test_print_h2 (const char *name)
{
    test_print_heading(2, name);
}

void
test_print_rate (float rate)
{
    printf("Test rate: %0.0f%%\n\n", rate * 100);
}

void
test_print_intro (const char *desc)
{
    if (desc == NULL) {
        printf("This test...\n\n");
    } else {
        printf("%s...\n\n", desc);
    }
}

float
test_rate (int passed, int total)
{
    return ((float)passed) / ((float)total);
}

void
test_run (int n, test_t *tests)
{
    float rate;
    int i, ok = 0;
    for (i = 0; i < n; i++) {
        if (tests[i]()) ok++;
        printf("\n");
    }
    rate = test_rate(ok, n);
    test_print_rate(rate);
}

