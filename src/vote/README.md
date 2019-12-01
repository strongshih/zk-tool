# vote

- compile and prepare

	```
	mkdir -p /tmp/contracts/vote
	cp /tmp/ourchain/src/zk-tool/src/vote/vote.c /tmp/contracts/vote/code.c
	cd /tmp
	ourcontract-mkdll contracts test
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	```

- trusted setup

	```
	ourcontract-rt contracts test init
	```

- offline prove

	```
	python /tmp/ourchain/src/zk-tools/src/python_utils/generate_sha256_gadget_tests.py /tmp/ourchain/src/zk-tools/build/src/offline_proof /tmp/contracts/test
	19     // age > 18
	101011 // random 0,1 string as password
	```

- online verify

	```
	ourcontract-rt contracts test verify
	```