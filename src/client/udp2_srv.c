/*
   Simple udp server
   Silver Moon (m00n.silv3r@gmail.com)
   */
#include<stdio.h>
#include<string.h> //for memset
#include<stdlib.h> //for exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512  //Max length of buffer

#include "../rpc/rpcvec.h"
#include <checkalloc.h>

int
main(int argc, char *argv[]) {
    struct sockaddr_in si_me, si_other;
    int s, i, portno, slen = sizeof(si_other);
    int recv_size, choice;
    double recv_val;
    char *cur;
    char buf[BUFLEN];

    //Create a UDP socket
    s=socket(AF_INET, SOCK_DGRAM, 0);

    //Zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    portno = atoi(argv[1]);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //Bind socket to port
    bind(s, (struct sockaddr*)&si_me, sizeof(si_me));

    //Start listening for data
    while(1) {
        printf("* Waiting for data...");
        fflush(stdout);
        memset(buf,'\0', BUFLEN);
        // Try to receive the integer of vector size
        recv_size = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other,
                              &slen);
        // Create a vector object
        vec vector;
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
