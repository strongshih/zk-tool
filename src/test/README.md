# test

- simple test for `x^3 + x + 5 == 35`

	```
	mkdir -p /tmp/contracts/test
	cp /tmp/ourchain/src/zk-tool/src/test/test_libsnark.c /tmp/contracts/test/code.c
	cd /tmp
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	ourcontract-mkdll contracts test
	ourcontract-rt contracts test
	```