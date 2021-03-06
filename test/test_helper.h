#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../hescape.h"

static int assertions, failures;

void
teardown()
{
  printf("\n\n%d assertions, %d failures\n\n", assertions, failures);
  exit(failures);
}

void
expect_str(const char *expected, const char *actual, const char *file, int line)
{
  assertions++;
  if (!strcmp(expected, actual)) {
    printf(".");
  } else {
    failures++;
    fflush(stdout);
    fprintf(stderr, "F\n\n%s:%d:\n", file, line);
    fprintf(stderr, "  Expected '%s' but got '%s'.", expected, actual);
    teardown();
  }
}

void
expect_int(int expected, int actual, const char *file, int line)
{
  assertions++;
  if (expected == actual) {
    printf(".");
  } else {
    failures++;
    fflush(stdout);
    fprintf(stderr, "F\n\n%s:%d:\n", file, line);
    fprintf(stderr, "  Expected '%d' but got '%d'.", expected, actual);
    teardown();
  }
}

#define TEST_RESULT(expected, src) { \
  uint8_t *dest = NULL; \
  size_t len = hesc_escape_html(&dest, src, strlen(src)); \
  expect_str(expected, dest, __FILE__, __LINE__); \
  expect_int(strlen(dest), len, __FILE__, __LINE__); \
}

void
setup()
{
  assertions = 0;
  failures   = 0;
  printf("\n# Running:\n\n");
}
