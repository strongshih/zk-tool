#include <ourcontract.h>

int contract_main(int argc, char **argv)
{
    if (test_libsnark(3)) {
        err_printf("correct\n");
    } else {
        err_printf("wrong\n");
    }
    return 0;
}