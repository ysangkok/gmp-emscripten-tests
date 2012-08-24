#include <stdlib.h>

#include "gmp.h"

#include "my_tdiv_qr.c"

int main()
{

	int np[] =
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000001
	};

	int nn = sizeof(np)/sizeof(int);

	int dp[] =
	{
		0x22b2e800, 0x63a20b83, 0x49c93743, 0x0e5c2170,
		0x66641a56, 0x449ff973, 0x0f83b12f, 0xd60f1628,
		0x22d25e4c, 0x6bfd75b4, 0x6ed32ac2, 0xbaf85c13,
		0x0108f936
	};
	int dn = sizeof(dp)/sizeof(int);
	int qxn = 0;
	int* qp = calloc(1,1000000);
	int* rp = calloc(1,1000000);
	my__gmpn_tdiv_qr((mp_ptr) qp,(mp_ptr) rp,qxn,(mp_srcptr) &np,nn,(mp_srcptr) &dp,dn);
	for (int i=0; i<17; i++)
	{
		printf("%08x\n", *( (int*) (((void*)qp)+(i*4))));
	}
	return 0;

}
