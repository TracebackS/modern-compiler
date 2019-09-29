#include "prog1.h"

#include <stdio.h>

#define printexpr(expr, spec) printf(#expr "=" spec "\n", expr)

int main()
{
  printexpr(maxargs(prog()), "%d");
  interp(prog());
  return 0;
}
