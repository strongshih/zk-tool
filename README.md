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

- replace `ourcontract.h` and `libourcontract.c` with files under `ourcontract_modify` (just add addtional implementation for user to call)
- recompile ourchain

```
cd ourchain-release
./autogen
./configure
make
sudo make install
```

## test

- test.c

```
#include <ourcontract.h>

int contract_main(int argc, char **argv)
{
    int b = test_libsnark(atoi(argv[1]));
    err_printf("Proof: x^3 + x + 5 == 35\n");
    if (b) {
        err_printf("Correct!!! x = %d\n", atoi(argv[1]));
    } else {
        err_printf("InCorrect!!! x != %d\n", atoi(argv[1]));
    }
    return 0;
}
```

```
mkdir -p contracts/test
// add test.c to contracts/test
ourcontract-mkdll contracts test
export OURZKLIB=/home/sam/ourchain-release/src/zk-tool/build/src/libourzklib.so
ourcontract-rt contracts test 3
```
