/* Author: Dionisis Nikolopoulos
*  Description: The server side code of concurrent vector calculator
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

//FIXME: only first element of array is able to be accessed, everything else is
// zero (0.000000)

double *
average_1_svc(vec * input_vector,struct svc_req *req)
{
    fprintf(stdout,"\n** Call for function average_1_svc with rq_proc %d",req->rq_proc);
    static double average;
    double sum = 0;
    for (int i=0; i<input_vector->vec_len; i++) {
        sum += input_vector->vec_val[i];
        fprintf(stdout,"\n* Iteration: %d:"\
                "\n=> input_vec_val[%d] == %lf\n"\
                "\n=> Sum == %lf"
                ,i,i,input_vector->vec_val[i],sum);
    }
    average = sum / input_vector->vec_len;
    fprintf(stdout,"\n==> Average is %lf"\
            "\n** Return results...",average);
    return &average;
}

double *
minmax_1_svc(vec * input_vector,struct svc_req *req)
{
    fprintf(stdout,"\n** Call for function minmax_1_svc with rq_proc %d",req->rq_proc);
    static double minmax_array[2];
    double min,max;
    // min and max are assigned as the first element of array initially..
    min = input_vector->vec_val[0];
    max = input_vector->vec_val[0];
    //..so we start at 1 (second element)
    double current;
    for (int i=1; i<input_vector->vec_len; i++)
    {
        current = input_vector->vec_val[i];
        printf("\nCurrent is %lf\n",current);
        printf("\nChecking vec_val[%d] == %lf\n",i,current);
        if (current > max) max = current;
        else if (current < min) min = current;
    }
    // Min is first element, max in second
    minmax_array[0] = min;
    minmax_array[1] = max;
    fprintf(stdout,"\nMax is %lf"\
           "\nMin is %lf"\
           "\n** Return results..."
           ,max,min);
    return minmax_array;
}

vec *
product_1_svc(vec_and_num * input_vector_pair,struct svc_req *req)
{
    fprintf(stdout,"\n** Call for function product_1_svc with rq_proc %d",req->rq_proc);
    static vec product;
    product.vec_len = input_vector_pair->vector.vec_len;
    product.vec_val = malloc(sizeof(double) * product.vec_len);
    for (int i=0; i<=input_vector_pair->vector.vec_len; i++)
        product.vec_val[i] = input_vector_pair->vector.vec_val[i]
                                * input_vector_pair->number;
    return &product;
}
