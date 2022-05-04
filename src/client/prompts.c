/* Description: Prompts for the client side (part of tui)
 *  License: GPLv3
 * Author: Dionisis Nikolopoulos
 *  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

void
average_prompt(vec * vector, CLIENT *clnt) {
    fprintf(stdout,
           "\nYou chose to calculate the average of the vector."\
            "\n<== Sending info to server...");
    double *result = average_1(vector,clnt);
    if (result == (double *)NULL) {
        clnt_perror(clnt,"Call for average_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n==> Average of vector is: %lf", *result);
}

//FIXME: maximum is always 0
void
minmax_prompt(vec * vector, CLIENT *clnt) {
    fprintf(stdout,
            "\nYou chose to calculate the minimum and maximum of the vector."\
            "\n<== Sending info to server...");
    min_and_max *result = minmax_1(vector,clnt);
    if (result == (min_and_max *)NULL) {
        clnt_perror(clnt,"Call for minmax_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n==> The minimum of the vector is: %lf"\
                   "\n==> The maximum of the vector is: %lf",
                   result->min, result->max);
}

void
product_prompt(vec * vector, CLIENT *clnt) {
    double number;
    fprintf(stdout,
            "\nYou chose to calculate the product of the vector with a number"
            "\n Please input the number you wish to multiply the vector with: "
            );
    scanf("%lf",&number);
    prod_and_num args;
    args.number = number;
    // Initialize the product vector with the elements of original vector
    args.product = vector;
    fprintf(stdout,"\n==> The product vector is:");
    for (int i=0; i<args.product->vec_len; i++)
        fprintf(stdout,"\n product[%d] = %lf", i, args.product->vec_val[i]);
    fprintf(stdout,"\n<== Sending info to server...");
    args.product = product_1(&args,clnt);
    if (args.product == (vec *)NULL) {
        clnt_perror(clnt,"Call for product_1 function failed!");
        exit(1);
    }
    vec product = *args.product;
    fprintf(stdout,"\n==> The product vector is:");
    for (int i=0; i<product.vec_len; i++)
        fprintf(stdout,"\n product[%d] = %lf",
                i, product.vec_val[i]);
}
