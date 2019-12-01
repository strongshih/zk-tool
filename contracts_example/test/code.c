#include <ourcontract.h>

int contract_main(int argc, char **argv)
{
	if (str_cmp(argv[1], "init", 4) == 0) {
    	int b = vote_zk_init();
		err_printf("%d\n", b);
	} else if (str_cmp(argv[1], "verify", 6) == 0) {
    	int b = vote_zk_verify();
		err_printf("%d\n", b);
	}
	return 0;
}
