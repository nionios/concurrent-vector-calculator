# -I in compilation flags to include new location of rpc.h in some linux distros
#  (For example, without the flag -I this does not compile on my Arch Linux
#  machine.
#
#  TODO: Maybe remove the common folder if checkalloc is only used in client
make_c_files:
	cc $(CFILES_SERVER) $(CFILES_COMMON) -o $(OUTFILE_SERVER) $(CFLAGS)
	cc $(CFILES_MIDDLEWARE) $(CFILES_COMMON) -o $(OUTFILE_MIDDLEWARE) $(CFLAGS)
	cc $(CFILES_CLIENT) $(CFILES_COMMON) -o  $(OUTFILE_CLIENT) $(CFLAGS)
#Binary files are then moved to the bin directory
	mv $(OUTFILES) ../bin

CFILES_CLIENT=./client/tui.c ./client/prompts.c ./client/sanitary.c
CFILES_MIDDLEWARE=./middleware/middleware.c\
./rpc/rpcvec_clnt.c ./rpc/rpcvec_xdr.c
CFILES_COMMON=./common/checkalloc.c
CFILES_SERVER=./server/rpcvec_server.c ./rpc/rpcvec_svc.c ./rpc/rpcvec_xdr.c

OUTFILES= $(OUTFILE_CLIENT) $(OUTFILE_MIDDLEWARE) $(OUTFILE_SERVER)
OUTFILE_CLIENT=rpcvec_user_client
OUTFILE_MIDDLEWARE=rpcvec_middleware
OUTFILE_SERVER=rpcvec_server

CFLAGS+=-I /usr/include/tirpc/ -I ../include/ -ltirpc -lnsl
