/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Student Email : ice18390126@uniwa.gr
 * Description   : RPC Client/Socket server for the concurrent vector
 *                 calculator. Acts as middleware for the RPC Server and the
 *                 Socket Client
 * License       : GPLv3
 * Date Written  : April 2022
 * Some code based on "Simple udp server" by Silver Moon (m00n.silv3r@gmail.com)
 */
#include<stdio.h>
#include<string.h> //for memset
#include<stdlib.h> //for exit();
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512  //Max length of buffer

#include "../rpc/rpcvec.h"
#include <prompts.h>
#include <checkalloc.h>

int
main(int argc, char *argv[]) {
    struct sockaddr_in si_me, si_other;
    int s, i, portno, slen = sizeof(si_other);
    int recv_size, choice;
    double recv_val;
    char *cur;
    char buf[BUFLEN];

    fprintf(stdout,"\n*** Concurrent Vector Calculator Middleware started ***");
    // Create a CLIENT struct and connect to the RPC server
    CLIENT *clnt = clnt_create("localhost", VEC_PROGRAM, VEC_VERS, "udp");
    if (!clnt) {
        fprintf(stderr,"\nError: Could not connect to the RPC server");
        exit(2);
    } else fprintf(stdout,"\n* Connected to the RPC server...");

    // Create a UDP socket
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) fprintf(stderr,"\nError: Socket could not be created");
    else fprintf(stdout,"\n* Socket created...");

    // Zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    // Check for arguments and store them if they are not provided
    if (argc < 2) {
        fprintf(stderr,
                "middleware - usage: %s [port_number] \n",
                argv[0]);
        exit(1);
    }

    portno = atoi(argv[1]);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //Bind socket to port
    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) < 0) {
        fprintf(stderr,"\nError: Socket could not be bound to port");
        exit(3);
    } else fprintf(stdout,"\n* Socket bound to port %d...", portno);

    //Start listening for data on maximum 6 clients
    if (listen(s, 6) == 0) fprintf(stdout,"\n* Listening to socket...");
    else {
        fprintf(stderr,"\nError: Could not listen to socket");
        exit(4);
    }

    while(1) {
        printf("\n* Waiting for data...");
        fflush(stdout);
        memset(buf,'\0', BUFLEN);
        // Try to receive the integer of vector size
        recv_size = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other,
                              &slen);
        fprintf(stdout,
                "==> Received size of vector from client side, size is %d",
                recv_size);
        // Create a vector object and a vector pointer
        vec vector;
        // Vector p needed in some cases (case 3)
        vec * vectorp = &vector;
        // Allocate memory based on the size of vector given by user
        vector.vec_val = (double*)malloc(sizeof(double) * recv_size);
        checkalloc(vector.vec_val);
        vector.vec_len = recv_size;

        for (int i=0; i<vector.vec_len; i++) {
            //TODO: Try to receive values in double
            recv_val = recvfrom(s, buf, BUFLEN, 0,
                                (struct sockaddr *) &si_other,
                                &slen);
            //Put the received value on the vector's array
            vector.vec_val[i] = recv_val;
        }
        choice = recvfrom(s, buf, BUFLEN, 0,
                          (struct sockaddr *) &si_other,
                          &slen);
        switch (choice) {
            case 1:
                double *result_1 = average_1(&vector, clnt);
                if (result_1 == (double *)NULL) {
                    clnt_perror(clnt,"Call for average_1 function failed!");
                    exit(5);
                }
                fprintf(stdout,"\n==> Average of vector is: %lf", *result_1);
                break;
            case 2:
                min_and_max *result_2 = minmax_1(&vector, clnt);
                if (result_2 == (min_and_max *)NULL) {
                    clnt_perror(clnt,"Call for minmax_1 function failed!");
                    exit(6);
                } fprintf(stdout,"\n==> The minimum of the vector is: %lf"\
                        "\n==> The maximum of the vector is: %lf",
                        result_2->min, result_2->max);
                break;
            case 3:
                // Try to receive the number that will multiply the vector
                double number = recvfrom(s, buf, BUFLEN, 0,
                                         (struct sockaddr *) &si_other,
                                         &slen);
                prod_and_num args;
                args.number = number;
                // Initialize the product vector with the elements of original vector
                args.product = vectorp;
                fprintf(stdout,"\n==> The product vector is:");
                for (int i=0; i<args.product->vec_len; i++)
                    fprintf(stdout,"\n product[%d] = %lf", i, args.product->vec_val[i]);
                fprintf(stdout,"\n<== Sending info to server...");
                args.product = product_1(&args,clnt);
                if (args.product == (vec *)NULL) {
                    clnt_perror(clnt,"Call for product_1 function failed!");
                    exit(7);
                }
                vec product = *args.product;
                fprintf(stdout,"\n==> The product vector is:");
                for (int i=0; i<product.vec_len; i++)
                    fprintf(stdout,"\n product[%d] = %lf",
                            i, product.vec_val[i]);

                break;
            default:
        }

        //TODO: continue rework from here, make it call the RPC Server

        ////print details of the client/peer and the data received
        //printf("Received packet from %s:%d\n",
        //        inet_ntoa(si_other.sin_addr),
        //        ntohs(si_other.sin_port));

        //testint = strtol(buf, &cur, 10);
        //testfloat = strtof(cur, &cur);
        //printf("Data: %d %f\n", testint, testfloat);

        ////now reply the client with the same numbers multiplied by 5
        //testint = testint * 5;
        //testfloat = testfloat * 5;
        //sprintf(buf, "%d %f", testint, testfloat);
        //sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen);
    }

    close(s);
    return 0;
}