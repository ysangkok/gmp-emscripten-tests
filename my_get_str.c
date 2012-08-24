#include "my_tdiv_qr.c"

static unsigned char *
my_mpn_sb_get_str (unsigned char *str, size_t len,
mp_ptr up, mp_size_t un, int base)
{
	printf("len %d un %ld base %d\n",len,un,base);

	for (unsigned int i=0; i<un*sizeof(mp_limb_t); i+=sizeof(mp_limb_t))
	{
		printf("sb up dump %d: %08lx\n", i, *( (mp_limb_t*) (((void*) up)+(i))));
	}

	unsigned char* oldstr = str;
	mp_limb_t rl, ul;
	unsigned char *s;
	size_t l;
	unsigned char buf[(35 * 32 * 7 / 11)];

	mp_limb_t rp[35];

	if (base == 10)
	{

		if ((un) != 0)
		{
			mp_size_t __n = (un) - 1;
			mp_ptr __dst = (rp + 1);
			mp_srcptr __src = (up);
			mp_limb_t __x;
			__x = *__src++;
			if (__n != 0)
			{
				do
				{
//					printf("%d\n", sizeof(mp_limb_t));
					printf("__x %08lx\n", __x);
//					printf("__x 1 %08x\n", *((int*) (((void*)(&__x)) + 4)));
					*__dst++ = __x;
					__x = *__src++;
				}
				while (--__n);
			}
			*__dst++ = __x;
		}


		s = buf + (35 * 32 * 7 / 11);
		while (un > 1)
		{
			printf("rp[un] = %08lx\n", rp[un]);
			int i;
			mp_limb_t frac, digit;

			__gmpn_preinv_divrem_1(rp, (mp_size_t) 1, rp + 1, un, ((mp_limb_t) 0x3b9aca00L), ((mp_limb_t) 0x12e0be82L), 2);


			un -= rp[un] == 0;
			frac = (rp[0] + 1) << 0;
			s -= 9;

			i = 9;
			do
			{
				UWtype __x0, __x1, __x2, __x3;
				UHWtype __ul, __vl, __uh, __vh;
				UWtype __u = (frac), __v = (10);
				__ul = ((UWtype) (__u) & (((UWtype) 1 << (32 / 2)) - 1));
				printf("__ul = %u\n", __ul);
				__uh = ((UWtype) (__u) >> (32 / 2));
				printf("__uh = %u\n", __uh);
				__vl = ((UWtype) (__v) & (((UWtype) 1 << (32 / 2)) - 1));
				printf("__vl = %u\n", __vl);
				__vh = ((UWtype) (__v) >> (32 / 2));
				printf("__vh = %u\n", __vh);
				__x0 = (UWtype) __ul * __vl;
				__x1 = (UWtype) __ul * __vh;
				__x2 = (UWtype) __uh * __vl;
				__x3 = (UWtype) __uh * __vh;
				__x1 += ((UWtype) (__x0) >> (32 / 2));
				__x1 += __x2;
				if (__x1 < __x2) __x3 += ((UWtype) 1 << (32 / 2));
				(digit) = __x3 + ((UWtype) (__x1) >> (32 / 2));
				(frac) = (__x1 << 32/2) + ((UWtype) (__x0) & (((UWtype) 1 << (32 / 2)) - 1));
				
				printf("digit %lu\nfrac %lu\n", digit, frac);

				*s++ = digit;
			}
			while (--i);
			s -= 9;
		}

		ul = rp[1];
		while (ul != 0)
		{
			mp_limb_t __q = (ul) / (10);
			mp_limb_t __r = (ul) % (10);
			(ul) = __q;
			(rl) = __r;
			*--s = rl;
		}
	}

	l = buf + (35 * 32 * 7 / 11) - s;
	while (l < len)
	{
		*str++ = 0;
		len--;
	}
	while (l != 0)
	{
		*str++ = *s++;
		l--;
	}
	puts("sb");
	for (int i=0; i<(str-oldstr)/4; i+=4)
	{

		printf("%08x\n", *( (int*) (((void*)oldstr)+(i))));
	}
	puts("");
	return str;
}


static unsigned char *
my_mpn_dc_get_str (unsigned char *str, size_t len,
mp_ptr up, mp_size_t un,
const powers_t *powtab, mp_ptr tmp)
{
	printf("dc %d %ld\n", len, un);
	for (unsigned int i=0; i<un*sizeof(mp_limb_t); i+=sizeof(mp_limb_t))
	{
		printf("dc up dump %d: %08lx\n", i, *( (mp_limb_t*) (((void*) up)+(i))));
	}
	unsigned char * oldstr = str;
	if ((! ((18) == 0 || ((18) != (-(((long) ((~ (unsigned long) 0) ^ ((unsigned long) (~ (unsigned long) 0) >> 1)))+1)) && (un) >= (18)))))
	{
		str = my_mpn_sb_get_str (str, len, up, un, powtab->base);
	}
	else
	{
		mp_ptr pwp, qp, rp;
		mp_size_t pwn, qn;
		mp_size_t sn;

		pwp = powtab->p;
		pwn = powtab->n;
		sn = powtab->shift;

		{
			qp = tmp;
			rp = up;

	for (int i=0; i<un-sn; i+=1)
	{
		printf("up+sn %08x\n", *( (int*) (((void*)(up+sn))+(i*4))));
	}
			my__gmpn_tdiv_qr (qp, rp + sn, 0L, up + sn, un - sn, pwp, pwn);
			printf("qp %08lx pwp %ld pwn %ld sn %ld\n", *qp, *pwp, pwn, sn);
			qn = un - sn - pwn;
			qn += qp[qn] != 0;
	for (int i=0; i<qn; i+=1)
	{
		printf("qp %08x\n", *( (int*) (((void*)qp)+(i*4))));
	}

			if (len != 0)
				len = len - powtab->digits_in_base;

			str = my_mpn_dc_get_str (str, len, qp, qn, powtab - 1, tmp + qn);
			str = my_mpn_dc_get_str (str, powtab->digits_in_base, rp, pwn + sn, powtab - 1, tmp);
		}
	}
	puts("dc");
	for (int i=0; i<(str-oldstr)/4; i+=4)
	{
		printf("%08x\n", *( (int*) (((void*)oldstr)+(i))));
	}
	puts("");
	return str;
}


size_t
my_mpn_get_str (unsigned char *str, int base, mp_ptr up, mp_size_t un)
{
	for (unsigned int i=0; i<un*sizeof(mp_limb_t); i+=sizeof(mp_limb_t))
	{
		printf("mpn up dump %d: %08lx\n", i, *( (mp_limb_t*) (((void*) up)+(i))));
	}
	mp_ptr powtab_mem, powtab_mem_ptr;
	mp_limb_t big_base;
	size_t digits_in_base;
	powers_t powtab[32];
	int pi;
	mp_size_t n;
	mp_ptr p, t;
	size_t out_len;
	mp_ptr tmp;
	struct tmp_reentrant_t *__tmp_marker;

	if (un == 0)
	{
		str[0] = 0;
		return 1;
	}

	__tmp_marker = 0;

	powtab_mem = ((mp_limb_t *) __gmp_tmp_reentrant_alloc (&__tmp_marker, (((un) + 2 * 32)) * sizeof (mp_limb_t)));
	powtab_mem_ptr = powtab_mem;

	big_base = __gmpn_bases[base].big_base;
	digits_in_base = __gmpn_bases[base].chars_per_limb;

	{
		mp_size_t n_pows, xn, pn, exptab[32], bexp;
		mp_limb_t cy;
		mp_size_t shift;

		n_pows = 0;
		xn = 1 + un*(__gmpn_bases[base].chars_per_bit_exactly*(32 - 0))/__gmpn_bases[base].chars_per_limb;
		for (pn = xn; pn != 1; pn = (pn + 1) >> 1)
		{
			exptab[n_pows] = pn;
			n_pows++;
		}
		exptab[n_pows] = 1;

		powtab[0].p = &big_base;
		powtab[0].n = 1;
		powtab[0].digits_in_base = digits_in_base;
		powtab[0].base = base;
		powtab[0].shift = 0;

		powtab[1].p = powtab_mem_ptr;
		powtab_mem_ptr += 2;
		powtab[1].p[0] = big_base;
		powtab[1].n = 1;
		powtab[1].digits_in_base = digits_in_base;
		powtab[1].base = base;
		powtab[1].shift = 0;

		n = 1;
		p = &big_base;
		bexp = 1;
		shift = 0;
		for (pi = 2; pi < n_pows; pi++)
		{
			t = powtab_mem_ptr;
			powtab_mem_ptr += 2 * n + 2;

			if (!(powtab_mem_ptr < powtab_mem + ((un) + 2 * 32))) __gmp_assert_fail ("old_my_get_str.c", 325, "powtab_mem_ptr < powtab_mem + ((un) + 2 * 32)");

			__gmpn_sqr (t, p, n);

			digits_in_base *= 2;
			n *= 2;
			n -= t[n - 1] == 0;
			bexp *= 2;

			if (bexp + 1 < exptab[n_pows - pi])
			{
				digits_in_base += __gmpn_bases[base].chars_per_limb;
				cy = __gmpn_mul_1 (t, t, n, big_base);
				t[n] = cy;
				n += cy != 0;
				bexp += 1;
			}
			shift *= 2;

			while (t[0] == 0)
			{
				t++;
				n--;
				shift++;
			}
			p = t;
			powtab[pi].p = p;
			powtab[pi].n = n;
			powtab[pi].digits_in_base = digits_in_base;
			powtab[pi].base = base;
			powtab[pi].shift = shift;
		}

		for (pi = 1; pi < n_pows; pi++)
		{
			t = powtab[pi].p;
			n = powtab[pi].n;
			cy = __gmpn_mul_1 (t, t, n, big_base);
			t[n] = cy;
			n += cy != 0;
			powtab[pi].n = n;
			powtab[pi].digits_in_base += __gmpn_bases[base].chars_per_limb;
		}

		{
			int i;
			printf ("Computed table values for base=%d, un=%ld, xn=%ld:\n", base, un, xn);
			for (i = 0; i < n_pows; i++)
				printf ("%2d: %10ld %10ld %11zd %ld\n", i, exptab[n_pows-i], powtab[i].n, powtab[i].digits_in_base, powtab[i].shift);
		}

	}

	tmp = ((mp_limb_t *) __gmp_tmp_reentrant_alloc (&__tmp_marker, (((un) + 32)) * sizeof (mp_limb_t)));
	out_len = my_mpn_dc_get_str (str, 0, up, un, powtab - 1 + pi, tmp) - str;
	if (__builtin_expect ((__tmp_marker != 0) != 0, 0)) __gmp_tmp_reentrant_free (__tmp_marker);

	return out_len;
}
