make:
	cp src/human/rpcvec.x src/rpc/
# This calls a second Makefile in src/rpc/ to rpcgen the rpc files
	$(MAKE) -C src/rpc rpc_files
# This calls a third Makefile in src/human/ to compile the human written files
	$(MAKE) -C src/human human_files
