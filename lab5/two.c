#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int z = 0, i = 0, j = 0, c = 0;

char a[25], ac[25], stk[25], act[25];

// Grammer
// E->+E+
// E->*E* 
// E->x
void checkAnyRulesMatch()
{
  strcpy(ac, "REDUCE TO E -> ");
  for (z = 0; z < c; z++)
  {
    // checking for producing rule E->4
    if (stk[z] == 'x')
    {
      printf("%sx", ac);
      stk[z] = 'E';
      stk[z + 1] = '\0';
      printf("\n$%s\t%s$\t", stk, a);
    }
  }

  for (z = 0; z < c - 2; z++)
  {
    if (stk[z] == '+' && stk[z + 1] == 'E' &&
        stk[z + 2] == '+')
    {
      printf("%s+E+", ac);
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 2] = '\0';
      printf("\n$%s\t%s$\t", stk, a);
      i = i - 2;
    }
  }

  for (z = 0; z < c - 2; z++)
  {
    if (stk[z] == '*' && stk[z + 1] == 'E' &&
        stk[z + 2] == '*')
    {
      printf("%s*E*", ac);
      stk[z] = 'E';
      stk[z + 1] = '\0';
      stk[z + 1] = '\0';
      printf("\n$%s\t%s$\t", stk, a);
      i = i - 2;
    }
  }
  return;
}

int main()
{
  printf("GRAMMAR-\nE->+E+ \nE->*E* \nE->x\n");
  strcpy(a, "*+x+*");
  c = strlen(a);
  strcpy(act, "SHIFT");
  printf("\nstack \t input \t action");
  printf("\n$\t%s$\t", a);
  for (i = 0; j < c; i++, j++)
  {
    printf("%s", act);
    stk[i] = a[j];
    stk[i + 1] = '\0';
    a[j] = ' ';
    printf("\n$%s\t%s$\t", stk, a);
    checkAnyRulesMatch();
  }
  checkAnyRulesMatch();
  if (stk[0] == 'E' && stk[1] == '\0')
    printf("Accept\n");
  else
    printf("Reject\n");
}
