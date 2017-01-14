#ifndef POLYNOMINAL_H
#define POLYNOMINAL_H

#define _GNU_SOURCE //Used for asprintf function

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct term
{
    int coeff;
    unsigned int exp;
    struct term *next;
};

typedef struct term polynomial;

/**	term_create() intializes a struct term based on the given coefficient and exponent values.
*		should be used to start any new polynomial equations or create any lose terms.
*/
struct term *
term_create( int, int );

/**	poly_destroy() goes through each struct term in a link and frees up memory
*       malloc'd during each term_create().  Use for each polynomial created in the program.		
*/
void
poly_destroy( polynomial * );

/**	poly_add_term() moves to the end of a polynomial equation and adds a new term to the end.
*       The first argument should be the address of the first term.
*       The second address will usually be a term returned from term_create()
*
*       ex: poly_add_term(&front, term_create(5, 5));		
*/
void
poly_add_term( polynomial **, struct term * );

/**	poly_print() takes the data from a polynomial and prints out the terms in order.
*/
void
poly_print( const polynomial * );

/**	poly_to_string() outputs a polynomial similar to poly_print() but returns a character pointer
*       instead of printing to stdout so the user can utilize the string for other purposes.
*
*       the function utilizes a GNU specific function asprintf() similar to snprintf but handles
*           memory.
*
*       The user is required to free the character pointer when finished with it to avoid
*           memory leaks.
*
*       TODO: implement snprintf() and malloc() to improve portability.
*/
char *
poly_to_string( const polynomial * );

/**	poly_add() returns a polynomial equation which is the sum of two other polynomials.
*/
polynomial *
poly_add( const polynomial *, const polynomial * );

/**	poly_sub() does the same thing as poly_add() but with subtraction.
*/
polynomial *
poly_sub( const polynomial *, const polynomial * );

/**	poly_equal() determines if two polynomials are equivalent to each other and returns the
*       the relative 1 ("true") or 0 ("false")
*/
int
poly_equal( const polynomial *, const polynomial * );

/**	poly_iterate() moves through each term in a polynomial and runs the function in the second
*        argument on it.
*/
void
poly_iterate( polynomial *, void (*)(struct term *) );

/**	test_print() is a boring function used to test poly_iterate.
*       All it does is print out the coefficient and exponent of a term.
*/
void
test_print( struct term * );

/**	poly_eval() evaluates each term in the polynomial using the provided double and keeps a
*       running total of each term which it returns at the end.
*/
double
poly_eval(const polynomial *, double );

#endif
