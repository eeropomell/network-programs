#include <stdio.h>

int
main()
{
  int n = 1000;
  unsigned char x = 0;
  while (n--) {
    printf("%d ", x++);
  }
}
