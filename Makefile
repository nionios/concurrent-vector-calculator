make:
# This calls a second Makefile in src/rpc/ to rpcgen the rpc files
	$(MAKE) -C src/rpc make_rpc_files
# This calls a third Makefile in src/ to compile all files into 2 binaries
	$(MAKE) -C src/ make_c_files
