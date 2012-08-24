#include <stdio.h>

typedef unsigned long mp_limb_t;
typedef struct {mp_limb_t inv32;} gmp_pi1_t;

typedef unsigned int USItype    __attribute__ ((mode (SI)));
typedef mp_limb_t UWtype;
typedef unsigned int UHWtype;

#define GMP_LIMB_BITS                      32
#define W_TYPE_SIZE GMP_LIMB_BITS

#define __ll_lowpart(t) ((UWtype) (t) & (__ll_B - 1))
#define __ll_highpart(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))
#define __ll_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#define umul_ppmm(w1, w0, u, v)						\
  do {									\
    UWtype __x0, __x1, __x2, __x3;					\
    UHWtype __ul, __vl, __uh, __vh;					\
    UWtype __u = (u), __v = (v);					\
									\
    __ul = __ll_lowpart (__u);						\
    __uh = __ll_highpart (__u);						\
    __vl = __ll_lowpart (__v);						\
    __vh = __ll_highpart (__v);						\
									\
    __x0 = (UWtype) __ul * __vl;					\
    __x1 = (UWtype) __ul * __vh;					\
    __x2 = (UWtype) __uh * __vl;					\
    __x3 = (UWtype) __uh * __vh;					\
									\
    __x1 += __ll_highpart (__x0);/* this can't give carry */		\
    __x1 += __x2;		/* but this indeed can */		\
    if (__x1 < __x2)		/* did we get it? */			\
      __x3 += __ll_B;		/* yes, add it in the proper pos. */	\
									\
    (w1) = __x3 + __ll_highpart (__x1);					\
    (w0) = (__x1 << W_TYPE_SIZE/2) + __ll_lowpart (__x0);		\
  } while (0)

#define __udiv_qrnnd_c(q, r, n1, n0, d) \
  do {									\
    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;			\
									\
    ASSERT ((d) != 0);							\
    ASSERT ((n1) < (d));						\
									\
    __d1 = __ll_highpart (d);						\
    __d0 = __ll_lowpart (d);						\
									\
    __q1 = (n1) / __d1;							\
    __r1 = (n1) - __q1 * __d1;						\
    __m = __q1 * __d0;							\
    __r1 = __r1 * __ll_B | __ll_highpart (n0);				\
    if (__r1 < __m)							\
      {									\
	__q1--, __r1 += (d);						\
	if (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */\
	  if (__r1 < __m)						\
	    __q1--, __r1 += (d);					\
      }									\
    __r1 -= __m;							\
									\
    __q0 = __r1 / __d1;							\
    __r0 = __r1  - __q0 * __d1;						\
    __m = __q0 * __d0;							\
    __r0 = __r0 * __ll_B | __ll_lowpart (n0);				\
    if (__r0 < __m)							\
      {									\
	__q0--, __r0 += (d);						\
	if (__r0 >= (d))						\
	  if (__r0 < __m)						\
	    __q0--, __r0 += (d);					\
      }									\
    __r0 -= __m;							\
									\
    (q) = __q1 * __ll_B | __q0;						\
    (r) = __r0;								\
  } while (0)

#define udiv_qrnnd __udiv_qrnnd_c

#ifdef USE_EXPECT
#define UNLIKELY(cond) __builtin_expect ((cond) != 0, 0)
#else
#define UNLIKELY(cond)  (cond)
#endif

#define ASSERT(expr)   do {} while (0)

#define CNST_LIMB(C) ((mp_limb_t) C##L)

#define invert_limb(invxl,xl)                   \
  do {                                          \
    mp_limb_t dummy;                            \
    ASSERT ((xl) != 0);                         \
    udiv_qrnnd (invxl, dummy, ~(xl), ~CNST_LIMB(0), xl);  \
  } while (0)

#define invert_pi1(dinv, d1, d0)                                \
  do {                                                          \
    mp_limb_t v, p, t1, t0, mask;                               \
    invert_limb (v, d1);                                        \
    p = d1 * v;                                                 \
    p += d0;                                                    \
    if (p < d0)                                                 \
      {                                                         \
        v--;                                                    \
        mask = -(p >= d1);                                      \
        p -= d1;                                                \
        v += mask;                                              \
        p -= mask & d1;                                         \
      }                                                         \
    umul_ppmm (t1, t0, d0, v);                                  \
    p += t1;                                                    \
    if (p < t1)                                                 \
      {                                                         \
        v--;                                                    \
        if (UNLIKELY (p >= d1))                                 \
          {                                                     \
            if (p > d1 || t0 >= d0)                             \
              v--;                                              \
          }                                                     \
      }                                                         \
    (dinv).inv32 = v;                                           \
  } while (0)



int main() {

gmp_pi1_t a;
unsigned long in[] = {0x7c2e09b7,0x847c9b5d};
invert_pi1(a, in[1], in[0]);
printf("%08lx\n", a.inv32);
return 0;

}
