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
    fprintf(stdout,"\n==> Average of vector is: %lf",*result);
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
    vec_and_num pair;
    pair.number = number;
    pair.vector = *vector;
    fprintf(stdout,"\n<== Sending info to server...");
    vec *result = product_1(&pair,clnt);
    if (result == (vec *)NULL) {
        clnt_perror(clnt,"Call for product_1 function failed!");
        exit(1);
    }
    fprintf(stdout,"\n==> The product vector is:");
    for (int i=0; i<pair.vector.vec_len; i++)
        fprintf(stdout,"\n product[%d] = %lf",i,result->vec_val[i]);
}

