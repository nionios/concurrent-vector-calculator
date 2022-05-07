/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Description   : Prompts for the TUI
 * Student Email : ice18390126@uniwa.gr
 * License       : GPLv3
 * Author        : Dionisis Nikolopoulos
 * Date Written  : April 2022
 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sanitary.h>
#include "../rpc/rpcvec.h"

#define BUFLEN 512

void
vector_info_prompt(struct sockaddr_in si_other, int slen, int s) {
    int input_size;
    int * sizep = &input_size;

    while(1) {
        fprintf(stdout,"\nPlease provide number of elements for vector: ");
        sanitary_int(&sizep);
        // If input is not valid, sanitary_int returns a null pointer
        if (!sizep) {
            fprintf(stderr,"\nError, invalid input type:"\
                    "Please input an integer value from 1 to 255");
        } else if (input_size < 1 || input_size > 255) {
            fprintf(stderr,"\nError, invalid input integer:"\
                    "Please input an integer value from 1 to 255");
            // If no problems occur, continue normally.
        } else break;
    }
    //Send vector size to RPC client
    send(s, &input_size, sizeof(int), 0);
    //Now lets start to read the elements of the array
    double input_val;
    double * input_valp = &input_val;

    for (int i=0; i<input_size; i++) {
        fprintf(stdout,"\nPlease provide element number %d of vector: ",i);
        sanitary_double(&input_valp);
        // If input is not valid, sanitary_double returns a null pointer
        if (!input_valp) {
            fprintf(stderr,"\nError, invalid input type:"\
                    "Please input a valid double value");
            //Repeat current step if the input is wrong
            i--;
        //Send value to RPC client
        } else send(s, &input_val, sizeof(double), 0);
    }
}

void
average_prompt(int choice, struct sockaddr_in si_other, int slen, int s) {
    fprintf(stdout,
           "\nYou chose to calculate the average of the vector."\
            "\n<== Sending info to server...");
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    // TODO: Receive results
    //recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
    //double *result = average_1(vector,clnt);
    // TODO: ON RPC CLIENT
    //if (result == (double *)NULL) {
    //    clnt_perror(clnt,"Call for average_1 function failed!");
    //    exit(1);
    //}
    //fprintf(stdout,"\n==> Average of vector is: %lf", *result);
}

void
minmax_prompt(int choice, struct sockaddr_in si_other, int slen, int s) {
    fprintf(stdout,
            "\nYou chose to calculate the minimum and maximum of the vector."\
            "\n<== Sending info to server...");
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    // TODO: Receive results
    //min_and_max *result;
   // recv();
    //if (result == (min_and_max *)NULL) {
    //    clnt_perror(clnt,"Call for minmax_1 function failed!");
    //    exit(1);
    //}
    //fprintf(stdout,"\n==> The minimum of the vector is: %lf"\
    //               "\n==> The maximum of the vector is: %lf",
    //               result->min, result->max);
}

void
product_prompt(int choice, struct sockaddr_in si_other, int slen, int s) {
    double number;
    fprintf(stdout,
            "\nYou chose to calculate the product of the vector with a number"
            "\n Please input the number you wish to multiply the vector with: "
            );
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    //TODO: error checking
    // TODO: Receive results
    //prod_and_num args;
    //args.number = number;
    //// Initialize the product vector with the elements of original vector
    //args.product = vector;
    //fprintf(stdout,"\n==> The product vector is:");
    //for (int i=0; i<args.product->vec_len; i++)
    //    fprintf(stdout,"\n product[%d] = %lf", i, args.product->vec_val[i]);
    //fprintf(stdout,"\n<== Sending info to server...");
    //args.product = product_1(&args,clnt);
    //if (args.product == (vec *)NULL) {
    //    clnt_perror(clnt,"Call for product_1 function failed!");
    //    exit(1);
    //}
    //vec product = *args.product;
    //fprintf(stdout,"\n==> The product vector is:");
    //for (int i=0; i<product.vec_len; i++)
    //    fprintf(stdout,"\n product[%d] = %lf",
    //            i, product.vec_val[i]);
}
