# This calls a second Makefile in src/rpc/ to rpcgen the rpc files
make:
	cp src/human/rpcvec.x src/rpc/
	$(MAKE) -C src/rpc rpc_files
