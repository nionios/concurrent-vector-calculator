/* Author: Dionisis Nikolopoulos
*  Description: RPC Client for the concurrent vector calculator
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"
#include <checkalloc.h>
#include <prompts.h>
#include <sanitary.h>

void
client_side(CLIENT *clnt) {
    unsigned int choice;
    int input_size;
    int * sizep = &input_size;
    int flag=1;
    fprintf(stdout,"*** Concurrent Vector Calculator ***");
    while(flag) {
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
    vec vector;
    vector.vec_val = (double*)malloc(sizeof(double) * input_size);
    checkalloc(vector.vec_val);
    vector.vec_len = input_size;
    for (int i=0; i<vector.vec_len; i++) {
        //Set a pointer to current array position to feed into sanitary_double
        double * valp = &vector.vec_val[i];
        fprintf(stdout,"\nPlease provide element number %d of vector: ",i);
        sanitary_double(&valp);
        // If input is not valid, sanitary_double returns a null pointer
        if (!valp) {
            fprintf(stderr,"\nError, invalid input type:"\
                    "Please input a valid double value");
            //Repeat current step if the input is wrong
            i--;
        }
    }
    while (1) {
        fprintf(stdout,"\nPlease choose calculation to make or exit:"\
                "\n 0. Exit program"\
                "\n 1. Average of vector"\
                "\n 2. Minimum and Maximum element of vector"\
                "\n 3. Product of vector with a real number"\
                "\nChoice: ");
        scanf("%d",&choice);
        // Separate functions for prompting user for more info, depending on
        // choice.
        switch (choice) {
            case 0:
                return;
            case 1:
                average_prompt(&vector,clnt);
                break;
            case 2:
                minmax_prompt(&vector,clnt);
                break;
            case 3:
                product_prompt(&vector,clnt);
                break;
            default:
                fprintf(stdout,
                        "Your choice was not valid input, please try again...");
        }
    }
}

int
main(int argc,char **argv) {
    char * host;
    if (argc < 2) {
        fprintf(stderr,"rpcvec_client - usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    CLIENT *clnt = clnt_create(host, VEC_PROGRAM, VEC_VERS, "udp");
    // After it is ensured correct info has been given, begin client side
    client_side(clnt);
    return 0;
}
