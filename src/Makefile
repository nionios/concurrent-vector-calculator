# -I in compilation flags to include new location of rpc.h in some linux distros
#  (For example, without the flag -I this does not compile on my Arch Linux
#  machine.
#
make_c_files:
	cc $(CFILES_SERVER) -o $(OUTFILE_SERVER) $(CFLAGS)
	cc $(CFILES_MIDDLEWARE) -o $(OUTFILE_MIDDLEWARE) $(CFLAGS)
	cc $(CFILES_CLIENT) -o  $(OUTFILE_CLIENT) $(CFLAGS)
#Binary files are then moved to the bin directory
	mv $(OUTFILES) ../bin

CFILES_CLIENT=./client/tui.c ./client/prompts.c ./client/sanitary.c
CFILES_MIDDLEWARE=./middleware/middleware.c ./middleware/checkalloc.c\
./rpc/rpcvec_clnt.c ./rpc/rpcvec_xdr.c
CFILES_SERVER=./server/rpcvec_server.c ./rpc/rpcvec_svc.c ./rpc/rpcvec_xdr.c

OUTFILES= $(OUTFILE_CLIENT) $(OUTFILE_MIDDLEWARE) $(OUTFILE_SERVER)
OUTFILE_CLIENT=rpcvec_user_client
OUTFILE_MIDDLEWARE=rpcvec_middleware
OUTFILE_SERVER=rpcvec_server

CFLAGS+=-I /usr/include/tirpc/ -I ../include/ -ltirpc -lnsl
