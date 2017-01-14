#include <stdio.h>
#include "polynomial.h"

int main(void)
{
    polynomial *poly1 = term_create(5, 5);
    poly_add_term(&poly1, term_create(4, 4));
    poly_add_term(&poly1, term_create(3, 3));
    poly_add_term(&poly1, term_create(2, 2));
    poly_print(poly1);     printf("\n");

    char *string = poly_to_string(poly1);
    printf("%s\n", string);

    poly_destroy(poly1);
    free(string);
}
