# zk-tool

- wrap libsnark tool for ourchain call function

## build steps

### install ourchain (skip if finished)

```
sudo apt-get update
sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils    
sudo apt-get install software-properties-common    
sudo add-apt-repository ppa:bitcoin/bitcoin 
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev
sudo apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
sudo apt-get install git
git clone -b test_version https://bitbucket.org/lab408/ourchain-release.git /tmp/ourchain
cd /tmp/ourchain/
./autogen.sh
./configure
make
sudo make install
sudo ldconfig
```

### build library

```
cd /tmp/ourchain/src
git clone https://github.com/strongshih/zk-tool.git
cd zk-tool/
git submodule update --init --force --remote --recursive
mkdir build && cd build/
cmake ..
make
```

### recompile ourchain

- replace `ourcontract.h` and `libourcontract.c` with files under `lib` (just add addtional implementation for user to call)

	```
	cp /tmp/ourchain/src/zk-tool/lib/ourcontract.h /tmp/ourchain/src/contract/
	cp /tmp/ourchain/src/zk-tool/lib/libourcontract.c /tmp/ourchain/src/contract/
	```

- recompile ourchain

	```
	cd /tmp/ourchain
	make
	sudo make install
	sudo ldconfig
	```

## test

- compile and prepare

	```
	cd /tmp/ourchain/src/zk-tool
	ourcontract-mkdll contracts_example test
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	ourcontract-rt contracts_example test
	```
	
## develop	
	
- call stack

	```
	ourcontract-rt contracts_example test
	                  |
	                  V
	main in ourcontract-rt.c 
	                  |
	                  V
	start_runtime in libourcontract.c
	                  |
	                  V
	call_contract in libourcontract.c
	                  |
	                  V
	contract_main in contracts_example/test/code.so using dlsym
	                  |
	                  V
	// (1) develop function call for contract
	test_libsnark in libourcontract.c
	                  |
	                  V
	// (2) using dynamic library to call c++ code in libsnark and provide function simultaneously
	test_libsnark in zk_tool/src/test/test_libsnark.cpp (by using path to OURZKLIB)
	                  |
	                  V
	using any libsnark libraries
	```	

- `(1)` and `(2)` are where we develop function call for user

## others

- only add function into `ourcontract.h` and `libourcontract.c`, and add addtional folder `zk-tool` under `ourchain/src`