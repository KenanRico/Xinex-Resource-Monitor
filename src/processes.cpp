#include <processes.h>
#include <process.h>
#include <flags.h>

#include <array>
#include <stdlib.h>
#include <algorithm>


#define OK 0x0
#define INSUF_TCP_BUFFER 0x1
#define QUERY_MEMORY_FAILURE 0x2


Processes::Processes(): attrib_count(0), status(OK){
}


Processes::~Processes(){
}




void Processes::GenProfiles(const std::array<bool, Flags::X>& flags){
	/*load functions required for requested flags*/
	LoadFunctions(flags);
	/*for each process, call functions to generate corresponding profile*/
	for(unsigned int p=0; p<processes.size(); ++p){
		for(unsigned int i=0; i<attrib_count; ++i){
			(this->*proc_func[i])(&(processes[p]));
		}
	}

}


void Processes::CleanUp(){

}


std::string Processes::Display() const{

	std::stringstream ss;
	for (unsigned int p = 0; p < processes.size(); ++p) {
		ss << processes[p].GetDisplay();
	}

	return ss.str();

}



void Processes::LoadFunctions(const std::array<bool, Flags::X>& enabled){
	for(unsigned int i=0; i<Flags::X; ++i){
		if(enabled[i]){
			++attrib_count;
			switch(i){
				case Flags::CPU:
					proc_func.push_back(&Processes::GenerateCPUProfile);
					break;
				case Flags::MEMORY:
					proc_func.push_back(&Processes::GenerateMemoryProfile);
					break;
				case Flags::FILES:
					proc_func.push_back(&Processes::GenerateOpenFileProfile);
					break;
				case Flags::PORTS:
					proc_func.push_back(&Processes::GenerateOpenPortProfile);
					break;
				default: break;
			}
		}
	}

}









