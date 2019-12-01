# test

- simple test for `x^3 + x + 5 == 35`

	```
	cd /tmp/ourchain/src/zk-tool
	ourcontract-mkdll contracts_example test
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	ourcontract-rt contracts_example test
	```