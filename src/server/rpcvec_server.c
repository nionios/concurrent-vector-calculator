/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Student Email : ice18390126@uniwa.gr
 * Description   : The RPC server side code of concurrent vector calculator
 * License       : GPLv3
 * Date Written  : April 2022
 */
#include <stdio.h>
#include <checkalloc.h>
#include "../rpc/rpcvec.h"

double *
average_1_svc(vec * input_vector, struct svc_req *req) {
    fprintf(stdout,"\n==> Call for function average_1_svc with rq_proc %d",req->rq_proc);
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
            "\n<== Return results...",average);
    return &average;
}

min_and_max *
minmax_1_svc(vec * input_vector, struct svc_req *req) {
    fprintf(stdout,
            "\n==> Call for function minmax_1_svc with rq_proc %d",
            req->rq_proc);
    static min_and_max minmax;
    double min,max;
    // min and max are assigned as the first element of array initially..
    min = input_vector->vec_val[0];
    max = input_vector->vec_val[0];
    //..so we start at 1 (second element)
    double current;
    for (int i=1; i<input_vector->vec_len; i++) {
        current = input_vector->vec_val[i];
        printf("\nCurrent is %lf",current);
        printf("\nChecking vec_val[%d] == %lf",i,current);
        if (current > max) max = current;
        else if (current < min) min = current;
    }
    // Min is first element, max in second
    minmax.min= min;
    minmax.max = max;
    fprintf(stdout,"\nMax is %lf"\
           "\nMin is %lf"\
           "\n<== Return results..."
           ,max,min);
    return &minmax;
}

vec *
product_1_svc(prod_and_num * input_args, struct svc_req *req) {
    fprintf(stdout,
            "\n==> Call for function product_1_svc with rq_proc %d",
            req->rq_proc);
    for (int i=0; i<=input_args->product->vec_len; i++) {
        input_args->product->vec_val[i] = input_args->product->vec_val[i]
                                        * input_args->number;
        fprintf(stdout, "\nCalculated input_args->product->vec_val[%d]=%lf",
                i, input_args->product->vec_val[i]);
    }
    fprintf(stdout, "\nProduct vector calculated!\n<==Return results...");
    return input_args->product;
}
