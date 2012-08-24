#include "gmp.h"
#include "gmp-impl.h"
#include "longlong.h"

#include "my_sbpi1_div_qr.c"

void
my__gmpn_tdiv_qr (mp_ptr qp, mp_ptr rp, mp_size_t qxn,
mp_srcptr np, mp_size_t nn, mp_srcptr dp, mp_size_t dn)
{
	ASSERT_ALWAYS (qxn == 0);

	ASSERT (nn >= 0);
	ASSERT (dn >= 0);
	ASSERT (dn == 0 || dp[dn - 1] != 0);
	ASSERT (! MPN_OVERLAP_P (qp, nn - dn + 1 + qxn, np, nn));
	ASSERT (! MPN_OVERLAP_P (qp, nn - dn + 1 + qxn, dp, dn));

	int adjust;
	gmp_pi1_t dinv;
	TMP_DECL;
	TMP_MARK;
								 /* conservative tests for quotient size */
	adjust = np[nn - 1] >= dp[dn - 1];
	mp_ptr n2p, d2p;
	mp_limb_t cy;
	int cnt;

	qp[nn - dn] = 0;			 /* zero high quotient limb */
	count_leading_zeros (cnt, dp[dn - 1]);
	cnt -= GMP_NAIL_BITS;
	d2p = TMP_ALLOC_LIMBS (dn);
	mpn_lshift (d2p, dp, dn, cnt);

	for (int i=0; i<dn; i+=1)
	{
		printf("d2p %08x\n", *( (int*) (((void*)(d2p))+(i*4))));
	}


	n2p = TMP_ALLOC_LIMBS (nn + 1);
	cy = mpn_lshift (n2p, np, nn, cnt);
	for (int i=0; i<nn; i+=1)
	{
		printf("n2p %08x\n", *( (int*) (((void*)(n2p))+(i*4))));
	}
	n2p[nn] = cy;
	nn += adjust;

        printf("d2p[dn-1] = %08lx\nd2p[dn-2] = %08lx\n", d2p[dn-1], d2p[dn-2]);
	invert_pi1 (dinv, d2p[dn - 1], d2p[dn - 2]);
        printf("dinv %08lx\n", dinv.inv32);
	my_mpn_sbpi1_div_qr (qp, n2p, nn, d2p, dn, dinv.inv32);
	for (int i=0; i<nn; i+=1)
	{
		printf("inside qp %08x\n", *( (int*) (((void*)(qp))+(i*4))));
	}
	n2p[nn] = cy;

	mpn_rshift (rp, n2p, dn, cnt);
	TMP_FREE;
	return;

}
