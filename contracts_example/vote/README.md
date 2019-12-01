# vote

- compile and prepare

	```
	cd /tmp/ourchain/src/zk-tool
	ourcontract-mkdll contracts_example vote
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	```

- trusted setup

	```
	ourcontract-rt contracts_example vote
	```
- sign_up

	```
	// first user
	python /tmp/ourchain/src/zk-tool/src/python_utils/generate_sha256_gadget_tests.py
	19     // age > 18
	101011 // random 0,1 string as password
	ourcontract-rt contracts_example vote sign_up user1 key1 2213957302 4252444682 4106745695 115720289 3740807415 2930180754 2532760760 2366027648
	
	// second user
	python /tmp/ourchain/src/zk-tool/src/python_utils/generate_sha256_gadget_tests.py
	17     // age < 18
	101011 // random 0,1 string as password
	ourcontract-rt contracts_example vote sign_up user2 key2 4191130733 4193462182 3670996701 3284815156 1199416470 270790498 2263772973 2118416833
	
	// third user
	python /tmp/ourchain/src/zk-tool/src/python_utils/generate_sha256_gadget_tests.py
	32     // age > 18
	1010111 // random 0,1 string as password
	ourcontract-rt contracts_example vote sign_up user3 key3 525658833 4232169087 1214571875 1802136526 825358060 3990037833 745772400 3650650508
	
	// check state
	cat contracts_example/vote/state
	```

- offline prove and online verify (vote)
	- user2 vote user3 (should not be able to vote)

		```
		python /tmp/ourchain/src/zk-tool/src/python_utils/generate_sha256_gadget_tests.py /tmp/ourchain/src/zk-tool/build/src/offline_proof /tmp/ourchain/src/zk-tool/contracts_example/vote/
		17     // age < 18
		101011 // random 0,1 string as password
		
		ourcontract-rt contracts_example vote vote user2 key2 user3
		```
	
	- user1 vote user3

		```
		python /tmp/ourchain/src/zk-tool/src/python_utils/generate_sha256_gadget_tests.py /tmp/ourchain/src/zk-tool/build/src/offline_proof /tmp/ourchain/src/zk-tool/contracts_example/vote/
		19     // age > 18
		101011 // random 0,1 string as password
		
		ourcontract-rt contracts_example vote vote user2 key2 user3
		```
		
- freeze and check

	```
	ourcontract-rt contracts_example vote freeze user1 key1
	cat contracts_example/vote/state
	cat contracts_example/vote/out
	```