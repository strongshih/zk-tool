# vote

- compile and prepare

	```
	cd /tmp/ourchain/src/zk-tool
	ourcontract-mkdll contracts_example vote
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	ourcontract-rt contracts_example vote
	```

- trusted setup

	```
	ourcontract-rt contracts_example vote init
	```

- offline prove

	```
	python /tmp/ourchain/src/zk-tools/src/python_utils/generate_sha256_gadget_tests.py /tmp/ourchain/src/zk-tools/build/src/offline_proof /tmp/ourchain/src/zk-tool/contracts_example/vote
	19     // age > 18
	101011 // random 0,1 string as password
	```

- online verify

	```
	ourcontract-rt contracts_example vote verify
	```