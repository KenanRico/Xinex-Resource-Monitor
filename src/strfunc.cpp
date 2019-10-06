#include <strfunc.h>
#include <flags.h>

#include <stdint.h>
#include <string.h>

#define OK 0
#define NO_PARAM 1
#define INVALID_FLAG 2
#define INVALID_INPUT 3

uint8_t ParseFlags(int argc, char** argv, std::array<bool, Flags::X>* flags){
	
	if(argc<=1){
		return NO_PARAM;
	}

	for(int i=1; i<argc; ++i){
		if(argv[i][0]=='-'){
			bool match = false;
			for(unsigned int j=0; j<Flags::X; ++j){
				if(strcmp(&argv[i][1], Flags::table[j].c_str())==0){
					(*flags)[j] = true;
					match = true;
					break;
				}
			}
			if(!match){
				return INVALID_FLAG;
			}
		}else{
			return INVALID_INPUT;
		}
	}

	return OK;

}
