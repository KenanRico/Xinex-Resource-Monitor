#include <iostream>
#include <flags.h>
#include <iostream>


int main(int argc, char** argv){
	/*get flags*/
	Flags flags;
	flags.ParseFlags(argc, argv);
	if(flags.Invalid()){
		std::cout<<flags.ErrorMsg()<<"\n";
		exit(0);
	}
	return 0;
}
