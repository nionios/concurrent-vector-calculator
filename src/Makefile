# -I in compilation flags to include new location of rpc.h in some linux distros
#  (For example, without the flag -I this does not compile on my Arch Linux
#  machine.
make_c_files:
	cc $(CFILES_SERVER) $(OFLAGS_SERVER) $(CFLAGS)
	cc $(CFILES_CLIENT) $(OFLAGS_CLIENT) $(CFLAGS)
#Binary files are then moved to the bin directory
	mv ./rpcvec_client ./rpcvec_server ../bin

CFILES_CLIENT=./client/rpcvec_client.c ./client/prompts.c ./client/sanitary.c\
./rpc/rpcvec_clnt.c ./rpc/rpcvec_xdr.c

CFILES_SERVER=./server/rpcvec_server.c ./rpc/rpcvec_svc.c ./rpc/rpcvec_xdr.c

OFLAGS_CLIENT=-o rpcvec_client
OFLAGS_SERVER=-o rpcvec_server

CFLAGS+=-I /usr/include/tirpc/ -I ../include/ -ltirpc -lnsl
