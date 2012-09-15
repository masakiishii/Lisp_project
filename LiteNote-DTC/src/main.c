#include "ilisp.h"

int main(int argc, char **argv)
{
	if(argc < 2) {
		ilisp_shell();
	}else{
		ilisp_script(argv);
	}
	return 0;
}
