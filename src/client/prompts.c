/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Description   : Prompts for the TUI
 * Student Email : ice18390126@uniwa.gr
 * License       : GPLv3
 * Author        : Dionisis Nikolopoulos
 * Date Written  : April 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sanitary.h>
#include "../rpc/rpcvec.h"

#define BUFLEN 512

int
vector_info_prompt(int s) {
    int size;
    int * sizep = &size;

    while(1) {
        fprintf(stdout,"\nPlease provide number of elements for vector: ");
        sanitary_int(&sizep);
        // If input is not valid, sanitary_int returns a null pointer
        if (!sizep) {
            fprintf(stderr,"\nError, invalid input type:"\
                    "Please input an integer value from 1 to 255");
        } else if (size < 1 || size > 255) {
            fprintf(stderr,"\nError, invalid input integer:"\
                    "Please input an integer value from 1 to 255");
            // If no problems occur, continue normally.
        } else break;
    }
    //Send vector size to RPC client
    send(s, &size, sizeof(int), 0);
    //Now lets start to read the elements of the array
    double input_val;
    double * input_valp = &input_val;

    for (int i=0; i < size; i++) {
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
    return size;
}

void
average_prompt(int s, int choice) {
    fprintf(stdout,
           "\nYou chose to calculate the average of the vector."\
            "\n<== Sending info to server...");
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    // Receive results
    double result;
    if ( recv(s, &result, sizeof(double), 0) < 0 ) {
        fprintf(stderr,"\nError: Could not receive result");
        exit(3);
    } else fprintf(stdout, "\n==> Average of vector is %lf", result);
}

void
minmax_prompt(int s, int choice) {
    fprintf(stdout,
            "\nYou chose to calculate the minimum and maximum of the vector."\
            "\n<== Sending info to server...");
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    //Receive results
    min_and_max result;
    if ( recv(s, &result, sizeof(double)*2, 0) < 0 ) {
        fprintf(stderr,"\nError: Could not receive result");
        exit(4);
    } else {
        fprintf(stdout,"\n==> Minimum of vector is %lf",result.min);
        fprintf(stdout,"\n==> Maximum of vector is %lf",result.max);
    }
}

void
product_prompt(int choice, int s, int length) {
    //Send the choice number to RPC client
    send(s, &choice, sizeof(int), 0);
    double number;
    fprintf(stdout,
            "\nYou chose to calculate the product of the vector with a number"
            "\n Please input the number you wish to multiply the vector with: "
            );
    //Send the other number to RPC client
    send(s, &number, sizeof(double), 0);
    //Receive results
    vec product;
    if ( recv(s,&product,sizeof(double)*length,0) < 0 ) {
        fprintf(stderr,"\nError: Could not receive result");
        exit(4);
    } else {
        fprintf(stdout,"\n==> The product vector is:");
        for (int i=0; i<product.vec_len; i++)
            fprintf(stdout,"\n product[%d] = %lf",
                    i, product.vec_val[i]);
    }
}
