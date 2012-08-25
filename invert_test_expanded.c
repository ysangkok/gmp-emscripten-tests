#include <stdio.h>
typedef unsigned long mp_limb_t;
typedef struct
{
    mp_limb_t inv32;
} gmp_pi1_t;

typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef mp_limb_t UWtype;
typedef unsigned int UHWtype;
int main()
{

    gmp_pi1_t a;
    unsigned long in[] = {0x7c2e09b7,0x847c9b5d};
    mp_limb_t v, p, t1, mask;
    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;
    __d1 = ((UWtype) (in[1]) >> (32 / 2));
    printf("%lx\n", __d1);
    __d0 = ((UWtype) (in[1]) & (((UWtype) 1 << (32 / 2)) - 1));
    printf("%lx\n", __d0);
    unsigned long tmp = (~(in[1]));
    printf("%lx\n", tmp);
    __q1 = tmp / __d1;
    printf("%lx\n", __q1);
    __r1 = (~(in[1])) - __q1 * __d1;
    printf("%lx\n", __r1);
    __m = __q1 * __d0;
    __r1 = __r1 * ((UWtype) 1 << (32 / 2)) | ((UWtype) (~((mp_limb_t) 0L)) >> (32 / 2));
    __q1--, __r1 += (in[1]);
    __r1 -= __m;
    __q0 = __r1 / __d1;
    __r0 = __r1 - __q0 * __d1;
    __m = __q0 * __d0;
    __r0 = __r0 * ((UWtype) 1 << (32 / 2)) | ((UWtype) (~((mp_limb_t) 0L)) & (((UWtype) 1 << (32 / 2)) - 1));
    __r0 -= __m;
    (v) = __q1 * ((UWtype) 1 << (32 / 2)) | __q0;
    p = in[1] * v;
    p += in[0];
    v--;
    mask = -(p >= in[1]);
    p -= in[1];
    v += mask;
    p -= mask & in[1];
    UWtype __x0, __x1, __x2, __x3;
    UHWtype __ul, __vl, __uh, __vh;
    UWtype __u = (in[0]), __v = (v);
    __ul = ((UWtype) (__u) & (((UWtype) 1 << (32 / 2)) - 1));
    __uh = ((UWtype) (__u) >> (32 / 2));
    __vl = ((UWtype) (__v) & (((UWtype) 1 << (32 / 2)) - 1));
    __vh = ((UWtype) (__v) >> (32 / 2));
    __x0 = (UWtype) __ul * __vl;
    __x1 = (UWtype) __ul * __vh;
    __x2 = (UWtype) __uh * __vl;
    __x3 = (UWtype) __uh * __vh;
    __x1 += ((UWtype) (__x0) >> (32 / 2));
    __x1 += __x2;
    (t1) = __x3 + ((UWtype) (__x1) >> (32 / 2));
    p += t1;
    if (p < t1)
    {
        v--;
    }
    (a).inv32 = v;
    printf("%08lx\n", a.inv32);
    return 0;

}
