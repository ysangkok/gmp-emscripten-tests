#include <stdio.h>

#include "gmp.h"
#include "gmp-impl.h"
#include "longlong.h"

void my_udiv_qr_3by2 ( mp_limb_t* p_q, mp_limb_t* p_r1, mp_limb_t* p_r0, mp_limb_t* p_n2, mp_limb_t* p_n1, mp_limb_t* p_n0, mp_limb_t* p_d1, mp_limb_t* p_d0, mp_limb_t* p_dinv, mp_limb_t* p__q0, mp_limb_t* p__t1, mp_limb_t* p__t0, mp_limb_t* p__mask) {

/*
mp_limb_t q = *p_q;
mp_limb_t r0 = *p_r0;
mp_limb_t r1 = *p_r1;
mp_limb_t n0 = *p_n0;
mp_limb_t n1 = *p_n1;
mp_limb_t n2 = *p_n2;
mp_limb_t dinv = *p_dinv;
mp_limb_t d0 = *p_d0;
mp_limb_t d1 = *p_d1;
    mp_limb_t _q0, _t1, _t0, _mask;                                     
_q0 = *p__q0;
_t0 = *p__t0;
_t1 = *p__t1;
_mask = *p__mask;
*/
#define q (*p_q)
#define r0 (*p_r0)
#define r1 (*p_r1)
#define n0 (*p_n0)
#define n1 (*p_n1)
#define n2 (*p_n2)
#define dinv (*p_dinv)
#define d0 (*p_d0)
#define d1 (*p_d1)
#define _q0 (*p__q0)
#define _t0 (*p__t0)
#define _t1 (*p__t1)
#define _mask (*p__mask)

printf("n0 %08lx\n", n0);
printf("n1 %08lx\n", n1);
printf("n2 %08lx\n", n2);
printf("dinv %08lx\n", dinv);
printf("d0 %08lx\n", d0);
printf("d1 %08lx\n", d1);

    umul_ppmm ((q), _q0, (n2), (dinv));                                 
printf("q %08lx\n", q);
printf("_q0 %08lx\n", _q0);
    add_ssaaaa ((q), _q0, (q), _q0, (n2), (n1));                        
printf("q %08lx\n", q);
                                                                        
    /* Compute the two most significant limbs of n - q'd */             
    (r1) = (n1) - (d1) * (q);                                           
printf("r1 %08lx\n", r1);
    (r0) = (n0);                                                        
printf("r0 %08lx\n", r0);
    sub_ddmmss ((r1), (r0), (r1), (r0), (d1), (d0));                    
    umul_ppmm (_t1, _t0, (d0), (q));                                    
printf("_t0 %08lx\n", _t0);
printf("_t1 %08lx\n", _t1);
    sub_ddmmss ((r1), (r0), (r1), (r0), _t1, _t0);                      
    (q)++;                                                              
                                                                        
    /* Conditionally adjust q and the remainders */                     
    _mask = - (mp_limb_t) ((r1) >= _q0);                                
printf("_mask %08lx\n", _mask);
    (q) += _mask;                                                       
printf("q %08lx\n", q);
    add_ssaaaa ((r1), (r0), (r1), (r0), _mask & (d1), _mask & (d0));    
    if (UNLIKELY ((r1) >= (d1)))                                        
      {                                                                 
        if ((r1) > (d1) || (r0) >= (d0))                                
          {                                                             
            (q)++;                                                      
printf("q %08lx\n", q);
            sub_ddmmss ((r1), (r0), (r1), (r0), (d1), (d0));            
          }                                                             
      }                                                                 

#undef q
#undef r0
#undef r1
#undef n0
#undef n1
#undef n2
#undef dinv
#undef d0
#undef d1
#undef _q0
#undef _t1
#undef _t0
#undef _mask
}

mp_limb_t
my_mpn_sbpi1_div_qr (mp_ptr qp,
		  mp_ptr np, mp_size_t nn,
		  mp_srcptr dp, mp_size_t dn,
		  mp_limb_t dinv)
{
  mp_limb_t qh;
  mp_size_t i;
  mp_limb_t n1, n0;
  mp_limb_t d1, d0;
  mp_limb_t cy, cy1;
  mp_limb_t q;

  np += nn;

  qh = mpn_cmp (np - dn, dp, dn) >= 0;

  qp += nn - dn;

  dn -= 2;			/* offset dn by 2 for main division loops,
				   saving two iterations in mpn_submul_1.  */
  d1 = dp[dn + 1];
  d0 = dp[dn + 0];

  np -= 2;

  n1 = np[1];

  for (i = nn - (dn + 2); i > 0; i--)
    {
      np--;
	{
    mp_limb_t _q0, _t1, _t0, _mask;                                     
	  my_udiv_qr_3by2 (&q, &n1, &n0, &n1, &(np[1]), &(np[0]), &d1, &d0, &dinv, &_q0, &_t1, &_t0, &_mask);
	printf("my_udiv_qr_3by2 %08lx\n", q);


	  cy = mpn_submul_1 (np - dn, dp, dn, q);

	  cy1 = n0 < cy;
	  n0 = (n0 - cy) & GMP_NUMB_MASK;
	  cy = n1 < cy1;
	  n1 = (n1 - cy1) & GMP_NUMB_MASK;
	  np[0] = n0;

	}

      *--qp = q;
    }
  np[1] = n1;

  return qh;
}
