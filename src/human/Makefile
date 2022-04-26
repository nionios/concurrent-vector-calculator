# -I in compilation flags to include new location of rpc.h in some linux distros
#  (For example, without the flag -I this does not compile on my Arch Linux
#  machine.
human_files:
	cc ./rpcvec_server.c ../rpc/rpcvec_svc.c ../rpc/rpcvec_xdr.c $(OFLAGS_SERVER) $(CFLAGS)
	cc ./rpcvec_client.c ../rpc/rpcvec_clnt.c ../rpc/rpcvec_xdr.c $(OFLAGS_CLIENT) $(CFLAGS)
#Binary files are moved to the bin directory
	mv rpcvec_client rpcvec_server ../../bin

OFLAGS_CLIENT=-o rpcvec_client
OFLAGS_SERVER=-o rpcvec_server
CFLAGS+=-lnsl -I /usr/include/tirpc/ -ltirpc
