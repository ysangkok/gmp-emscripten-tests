#include "gmp.h"
#include "gmp-impl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_get_str.c"

char *
my__gmpz_get_str (char *res_str, int base, mpz_srcptr x)
{
    mp_ptr xp;
    mp_size_t x_size = x->_mp_size;
    char *str;
    char *return_str;
    size_t str_size;
    size_t alloc_size = 0;
    char *num_to_text;
    int i;
    struct tmp_reentrant_t *__tmp_marker;

    if (base >= 0)
    {
        num_to_text = "0123456789abcdefghijklmnopqrstuvwxyz";
        if (base == 0)
            base = 10;
        else if (base > 36)
        {
            num_to_text = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            if (base > 62)
                return ((void *)0);
        }
    }
    else
    {
        base = -base;
        num_to_text = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }


    if (res_str == ((void *)0))
    {

            int __lb_base, __cnt;
            size_t __totbits;
            if ((((x_size) >= 0 ? (x_size) : -(x_size))) == 0) (alloc_size) = 1;
            else {
                    (__cnt) = __builtin_clzl ((((x)->_mp_d))[(((x_size) >= 0 ? (x_size) : -(x_size)))-1]);
                __totbits = (size_t) (((x_size) >= 0 ? (x_size) : -(x_size))) * (32 - 0) - (__cnt - 0);
                if ((((base) & ((base) - 1)) == 0)) {
                    __lb_base = __gmpn_bases[base].big_base;
                    (alloc_size) = (__totbits + __lb_base - 1) / __lb_base;
                }
                else (alloc_size) = (size_t) (__totbits * __gmpn_bases[base].chars_per_bit_exactly) + 1;
            }
        alloc_size += 1 + (x_size<0);
        res_str = (char *) (*__gmp_allocate_func) (alloc_size);
    }
    return_str = res_str;

    if (x_size < 0)
    {
        *res_str++ = '-';
        x_size = -x_size;
    }


    __tmp_marker = 0;
    xp = x->_mp_d;
    if (! (((base) & ((base) - 1)) == 0))
    {
        xp = ((mp_limb_t *) (__builtin_expect ((((x_size + 1) * sizeof (mp_limb_t)) < 65536) != 0, 1) ? __builtin_alloca((x_size + 1) * sizeof (mp_limb_t)) : __gmp_tmp_reentrant_alloc (&__tmp_marker, (x_size + 1) * sizeof (mp_limb_t))));
                if ((x_size) != 0) {
                    mp_size_t __n = (x_size) - 1;
                    mp_ptr __dst = (xp);
                    mp_srcptr __src = (x->_mp_d);
                    mp_limb_t __x;
                    __x = *__src++;
                    if (__n != 0) {
                        do {
                            *__dst++ = __x;
                            __x = *__src++;
                        }
                        while (--__n);
                    } *__dst++ = __x;
                }
    }

    str_size = my_mpn_get_str ((unsigned char *) res_str, base, xp, x_size);
    puts("gmpn_get_str result:");
    for (unsigned int i=0; i<str_size/4; i+=4) {
//	printf("%08x %08x\n", (int) result->_mp_d+(i*4), *( (int*) (((void*)result->_mp_d)+(i*4))));
	printf("%08x\n", *( (int*) (((void*)res_str)+(i))));
    }



    str = res_str;
    if (*res_str == 0 && str_size != 1)
    {
        str_size--;
        str++;
    }



    for (i = 0; i < str_size; i++)
        res_str[i] = num_to_text[(int) str[i]];
    res_str[str_size] = 0;

        if (__builtin_expect ((__tmp_marker != 0) != 0, 0)) __gmp_tmp_reentrant_free (__tmp_marker);


    if (alloc_size != 0)
    {
        size_t actual_size = str_size + 1 + (res_str - return_str);
            if ((alloc_size) != (actual_size)) (return_str) = (char *) (*__gmp_reallocate_func) (return_str, (alloc_size) * sizeof (char), (actual_size) * sizeof (char));
    }
    return return_str;
}

int main() {

    char two1088[] = "3316158518186977171087283760642741158699936149735704467159471849921418683482035763477878926564345847729145083728966646356210626353328840324989147544629059746554141479347263264595425816446455256534872353644097455203319930608430165174159005378955830171087831965898486080345430665055936553487340789901656166618033483630075818541056";
    char* resultstr;

    mpz_t result;

    int data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    if (!sizeof(data) == 35) abort();

    result->_mp_size = 35;
    result->_mp_alloc = 35;
    result->_mp_d = (mp_limb_t*) &data;

    printf("size=%d alloc=%d\n", result->_mp_size, result->_mp_alloc);
    for (int i=0; i<result->_mp_size; i++) {
//	printf("%08x %08x\n", (int) result->_mp_d+(i*4), *( (int*) (((void*)result->_mp_d)+(i*4))));
        printf("%08x\n", *( (int*) (((void*)result->_mp_d)+(i*4))));
    }
    resultstr = my__gmpz_get_str(NULL, 10, result);
    printf("%s\n", resultstr);

    if (strcmp(resultstr, two1088) != 0) {
        puts("ERROR! 2^1087+2^1087 calculated incorrect.");
    } else {
        puts("2^1087+2^1087 calculated correct.");
    }
    return 0;
}

