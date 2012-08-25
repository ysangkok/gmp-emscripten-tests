#include <stdio.h>

#include "gmp.h"
#include "gmp-impl.h"
#include "longlong.h"

int main() {

gmp_pi1_t a;
unsigned long in[] = {0x7c2e09b7,0x847c9b5d};
invert_pi1(a, in[1], in[0]);
printf("%08lx\n", a.inv32);
return 0;

}
