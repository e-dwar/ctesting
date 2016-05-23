#ifndef TEST_H
#define TEST_H

#define TEST_FAILURE 0
#define TEST_SUCCESS 1

typedef int (*test_t) (void);

int test_rand (void);
int test_should (const char *name, int b);
void test_print_message (const char *msg);
void test_print_error (const char *err);
void test_print_heading (int lvl, const char *name);
void test_print_h2 (const char *name);
void test_print_intro (const char *label);
void test_print_rate (float rate);
void test_run (int n, test_t *tests);
float test_rate (int passed, int total);

#endif
