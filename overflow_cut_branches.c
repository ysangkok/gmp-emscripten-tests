
#include "gmp.h"
#include "gmp-impl.h"
#include <string.h>
#include <stdio.h>

mp_limb_t
my__gmpn_add_n (mp_ptr rp, mp_srcptr up, mp_srcptr vp, mp_size_t n)
{
  mp_limb_t ul, vl, sl, rl, cy, cy1, cy2;

  do { if (!(n >= 1)) __gmp_assert_fail ("mpn/add_n.c", 32, "n >= 1"); } while (0);
  do { if (!(((rp) <= (up) || ! ((rp) + (n) > (up) && (up) + (n) > (rp))))) __gmp_assert_fail ("mpn/add_n.c", 33, "((rp) <= (up) || ! ((rp) + (n) > (up) && (up) + (n) > (rp)))"); } while (0);
  do { if (!(((rp) <= (vp) || ! ((rp) + (n) > (vp) && (vp) + (n) > (rp))))) __gmp_assert_fail ("mpn/add_n.c", 34, "((rp) <= (vp) || ! ((rp) + (n) > (vp) && (vp) + (n) > (rp)))"); } while (0);

  cy = 0;
  do
    {
      ul = *up++;
      vl = *vp++;
      sl = ul + vl;
      cy1 = sl < ul;
      rl = sl + cy;
      cy2 = rl < sl;
      cy = cy1 | cy2;
      *rp++ = rl;

printf("\
ul = %lu\n\
vl = %lu\n\
sl = %lu\n\
rl = %lu\n\
cy = %lu\n\
cy1 = %lu\n\
cy2 = %lu\n\
*rp-1 = %lu\n\
*up-1 = %lu\n\
*vp-1 = %lu\n\
\n", ul, vl, sl, rl, cy, cy1, cy2, *(rp-1), *(up-1), *(vp-1));

    }
  while (--n != 0);

  return cy;
}

mp_limb_t
my__gmpn_add (mp_ptr __gmp_wp, mp_srcptr __gmp_xp, mp_srcptr __gmp_yp, mp_size_t __gmp_ysize)
{
    mp_size_t __gmp_i = (__gmp_ysize);;
/*
    if (__gmp_i != 0)
        if (my__gmpn_add_n (__gmp_wp, __gmp_xp, __gmp_yp, __gmp_i))
            if (__gmp_i >= (__gmp_xsize))
                (__gmp_c) = 1;
*/
    my__gmpn_add_n (__gmp_wp, __gmp_xp, __gmp_yp, __gmp_i);
    return 1;
}

void
my__gmpz_add (mpz_ptr w, mpz_srcptr u, mpz_srcptr v)
{
    mp_srcptr up, vp;
    mp_ptr wp;
    mp_size_t usize, vsize, wsize;
    mp_size_t abs_usize;
    mp_size_t abs_vsize;

    usize = u->_mp_size;
    vsize = v->_mp_size;
if (usize >= 0)
	abs_usize = usize;
else
	abs_usize = -usize;

if (vsize >= 0)
	abs_vsize = vsize;
else
	abs_vsize = -vsize;
//    abs_usize = ((usize) >= 0 ? (usize) : -(usize));
//    abs_vsize = ((vsize) >= 0 ? (vsize) : -(vsize));

    wsize = abs_usize + 1;
    //if (w->_mp_alloc < wsize)
        __gmpz_realloc (w, wsize);


    up = u->_mp_d;
    vp = v->_mp_d;
    wp = w->_mp_d;

    mp_limb_t cy_limb = my__gmpn_add (wp, up, vp, abs_vsize);
    wp[abs_usize] = cy_limb;
    wsize = abs_usize + cy_limb;

    w->_mp_size = wsize;
printf("wsize = %lu\n" , wsize);
}

int main() {

    char two1087[] =       "1658079259093488585543641880321370579349968074867852233579735924960709341741017881738939463282172923864572541864483323178105313176664420162494573772314529873277070739673631632297712908223227628267436176822048727601659965304215082587079502689477915085543915982949243040172715332527968276743670394950828083309016741815037909270528";
    char two1087minus1[] = "1658079259093488585543641880321370579349968074867852233579735924960709341741017881738939463282172923864572541864483323178105313176664420162494573772314529873277070739673631632297712908223227628267436176822048727601659965304215082587079502689477915085543915982949243040172715332527968276743670394950828083309016741815037909270527";
    char two1088[] = "3316158518186977171087283760642741158699936149735704467159471849921418683482035763477878926564345847729145083728966646356210626353328840324989147544629059746554141479347263264595425816446455256534872353644097455203319930608430165174159005378955830171087831965898486080345430665055936553487340789901656166618033483630075818541056";
    char* resultstr;

    mpz_t power_of_two;
    mpz_init(power_of_two);
    mpz_set_str(power_of_two, two1087, 10);

    mpz_t power_of_two_m1;
    mpz_init(power_of_two_m1);
    mpz_set_str(power_of_two_m1, two1087minus1, 10);

    mpz_t result;
    mpz_init(result);

#if 0
    char two1088minus1[] = "3316158518186977171087283760642741158699936149735704467159471849921418683482035763477878926564345847729145083728966646356210626353328840324989147544629059746554141479347263264595425816446455256534872353644097455203319930608430165174159005378955830171087831965898486080345430665055936553487340789901656166618033483630075818541055";

    mpz_add(result,power_of_two,power_of_two_m1);
    resultstr = mpz_get_str(NULL, 10, result);
    printf("%s\n", resultstr);

    if (strcmp(resultstr, two1088minus1) != 0) {
        puts("ERROR! 2^1087+2^1087-1 calculated incorrect.");
    } else {
        puts("2^1087+2^1087-1 calculated correct.");
    }
#endif

    my__gmpz_add(result,power_of_two,power_of_two);
    printf("size=%d alloc=%d\n", result->_mp_size, result->_mp_alloc);
    for (int i=0; i<result->_mp_size; i++) {
//	printf("%08x %08x\n", (int) result->_mp_d+(i*4), *( (int*) (((void*)result->_mp_d)+(i*4))));
	printf("%08x\n", *( (int*) (((void*)result->_mp_d)+(i*4))));
    }
    resultstr = mpz_get_str(NULL, 10, result);
    printf("%s\n", resultstr);

    if (strcmp(resultstr, two1088) != 0) {
        puts("ERROR! 2^1087+2^1087 calculated incorrect.");
    } else {
        puts("2^1087+2^1087 calculated correct.");
    }
}

