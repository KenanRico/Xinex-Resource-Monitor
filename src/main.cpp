#include <flags.h>
#include <strfunc.h>

#include <array>
#include <stdint.h>
#include <iostream>


int main(int argc, char** argv){
	/*parse flags*/
	std::array<bool, Flags::X> enabled_flags;
	uint8_t status = ParseFlags(argc, argv, &enabled_flags);
	if(status!=0){
		std::cout<<"Error!\n";
		exit(0);
	}
	if(enabled_flags[Flags::HELP]){
		// print help page
	}

	/*
	std::vector<Process<Flags::num_attribs>> processes;
	GetProcesses(&processes);

	int proccount = processes.size();
	for(int i=0; i<proccount; ++i){
		Process& proc = processes[i];
		for(int j=0; j<Flags::X-1; ++j){
			if(enabled_flag[j]){
				proc.AppendAttrib(j);
			}
		}
	}

	std::string info = AssembleForDisplay(enabled_flags, processes);
	Display(info);
	*/

	return 0;
}
