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
ldconfig
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

- replace `ourcontract.h` and `libourcontract.c` with files under `ourcontract_modify` (just add addtional implementation for user to call)
- recompile ourchain

	```
	cd /tmp/ourchain
	./autogen
	./configure
	make
	sudo make install
	```

## test

- compile and prepare

	```
	mkdir -p /tmp/contracts/test
	cp /tmp/ourchain/src/zk-tool/src/vote/vote.c /tmp/contracts/test
	cd /tmp
	ourcontract-mkdll contracts test
	export OURZKLIB=/tmp/ourchain/src/zk-tool/build/src/libourzklib.so
	ourcontract-rt contracts test
	```
	
## others

- only add function into `ourcontract.h` and `libourcontract.c`, and add addtional folder `zk-tool` under `ourchain/src`