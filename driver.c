#include <stdio.h>
#include "polynomial.h"

int main(void)
{
    polynomial *poly1 = term_create(2, 2);
    poly_add_term(&poly1, term_create(1, 2));
    poly_print(poly1);     printf("\n");

    printf("The result is %lf\n", poly_eval(poly1, 2));
    poly_destroy(poly1);

}
