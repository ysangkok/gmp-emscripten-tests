#include "gmp.h"
#include "my_sbpi1_div_qr.c"

int main() {
unsigned long in[] = {
0x000000f7, // q
0x2bc618cd, // r1
0x2f94a009, // r0
0x2bc618cd, // n2
0x2f94a009, // n1
0x20df34e7, // n0
0x847c9b5d, // d1
0x7c2e09b7, // d0
0xeea92a61, // dinv
0x54953080, // _q0
0x00000077, // _t1
0xd06b5f91, // _t0
0xffffffff  // _mask
};

my_udiv_qr_3by2(&in[0],&in[1],&in[2],&in[3],&in[4],&in[5],&in[6],&in[7],&in[8],&in[9],&in[10],&in[11],&in[12]);
printf("%lx\n",in[0]);
}
