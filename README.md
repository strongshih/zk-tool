# zk-tool

- wrap libsnark tool for ourchain call function

## build steps

### build library

```
cd ourchain-release/src
git clone https://github.com/strongshih/zk-tool.git
cd zk-tool/
git submodule update --init --force --remote --recursive
mkdir build && cd build/
cmake ..
make
```

### recompile ourchain

- replace `ourcontract.h` and `libourcontract.c` with file under `ourcontract_modify`

```
cd ourchain-release
./autogen
./configure
make
sudo make install
```

### test

```
#include <ourcontract.h>
int contract_main(int argc, char **argv)
{
    int b = call_verify(123);
    err_printf("test verify %d\n", b);
    return 0;
}
```

- use `ourcontract-mkdll` to compile
- use `ourcontract-rt` to run, should add path to library, ex:
	- `OURZKLIB=/home/sam/ourchain-release/src/zk-tool/build/src/libourzklib.so`
