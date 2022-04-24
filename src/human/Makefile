# -I in compilation flags to include new location of rpc.h in some linux distros
#  (For example, without the flag -I this does not compile on my Arch Linux
#  machine.
human_files:
	cc ./rpcvec_client.c ../rpc/rpcvec_clnt.c ../rpc/rpcvec_xdr.c $(CFLAGS)
	cc ./rpcvec_server.c ../rpc/rpcvec_svr.c ../rpc/rpcvec_xdr.c $(CFLAGS)
#Binary files are moved to the bin directory
	mv rpcvec_client rpcvec_server ../../bin

CFLAGS+=-lnsl -o rpcvec_client -I /usr/include/tirpc/ -ltirpc
