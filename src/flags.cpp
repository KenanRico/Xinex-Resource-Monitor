#include <flags.h>
#include <cstring>

#define OK 0
#define INVALID_FLAG 1
#define INVALID_INPUT 2




Flags::Flags() : registered_flags({"p","mem","cpu"}), status(OK){
	memset(flags, 0, sizeof(bool)*flag_count);
}

Flags::~Flags(){

}

void Flags::ParseFlags(int argc, char** argv){
	if(argc<=1){
		return;
	}

	for(int i=1; i<argc; ++i){
		if(argv[i][0]=='-'){
			bool match = false;
			for(int j=0; j<flag_count; ++j){
				if(strcmp(&argv[i][1], registered_flags[j].c_str())==0){
					flags[j] = true;
					match = true;
					break;
				}
			}
			if(!match){
				HandleError(INVALID_FLAG, argv[i]);
				break;
			}
		}else{
			HandleError(INVALID_INPUT, argv[i]);
			break;
		}
	}
}

void Flags::HandleError(uint8_t code, char const * input){
	if(code==INVALID_FLAG){
		error_msg = std::string("Invalid flag: ") + std::string(input);
	}else if(code==INVALID_INPUT){
		error_msg = std::string("Invalid input: ") + std::string(input);
	}
	error_msg += std::string("\ntype Xinex -h for list of valid inputs");
	status = code;
}
