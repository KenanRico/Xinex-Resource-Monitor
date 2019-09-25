#include <attribs.h>
#include <order.h>

#include <stdint.h>
#include <string.h>




#define OK 0
#define NO_PARAM 1
#define INVALID_FLAG 2
#define INVALID_INPUT 3
uint8_t Input::Attribs::ParseAttribs(int argc, char** argv, std::array<bool, num_attribs>* attribs){
	
	if(argc<=1){
		return NO_PARAM;
	}

	for(int i=1; i<argc; ++i){
		if(argv[i][0]=='-'){
			bool match = false;
			for(int j=0; j<num_attribs; ++j){
				if(strcmp(&argv[i][1], table[j].c_str())==0){
					(*attribs)[j] = true;
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

unsigned int Input::Orientation::ParseOrientation(int argc, char** argv){

}

unsigned int Input::Order::ParseOrder(int argc, char** argv){

}
