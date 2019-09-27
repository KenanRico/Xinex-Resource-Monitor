#include <flags.h>
#include <strfunc.h>
#include <process.h>

#include <array>
#include <stdint.h>
#include <iostream>
#include <vector>


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

	std::vector<Process> processes;
	GetProcesses(&processes);

	unsigned int proccount = processes.size();
	for(unsigned int i=0; i<proccount; ++i){
		Process& proc = processes[i];
		for(unsigned int j=0; j<Flags::num_attribs; ++j){
			if(enabled_flags[j]){
				proc.AppendAttrib(j);
			}
		}
	}

	/*
	for(unsigned int i=0; i<proccount; ++i){
		std::cout<<processes[i].GetDisplay()<<"\n";
	}
	*/

	/*
	std::string info = AssembleForDisplay(enabled_flags, processes);
	Display(info);
	*/

	return 0;
}
