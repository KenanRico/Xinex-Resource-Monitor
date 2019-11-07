
//#include <pch.h>
#include <flags.h>
#include <strfunc.h>
#include <process.h>
#include <debugfunc.h>

#include <array>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <algorithm>


int main(int argc, char** argv){
	DEBUG::check_procname_calls();
	DEBUG::check_tcptable_calls();
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

	Process::LoadFunctions(enabled_flags);
	std::vector<Process> processes;
	GetProcesses(&processes);


	/*Neglect all kernel processes and other processes with access restriction*/
	processes.erase(
		std::remove_if(processes.begin(), processes.end(), [](const Process& proc){return proc.Status()!=0x0;}),
		processes.end()
	);

	/*iterate processes to populate their performance profile*/
	size_t proccount = processes.size();
	int attrib_count = Process::CountAttribs();
	for(unsigned int i=0; i<proccount; ++i){
		Process& proc = processes[i];
		for(int j=0; j<attrib_count; ++j){
			proc.AppendAttrib(j);
			if(proc.Status()!=0){
				std::cout<<"status: "<<(int)proc.Status()<<"\n";
				exit(0);
			}
		}
	}

	for(unsigned int i=0; i<proccount; ++i){
		std::cout<<processes[i].GetDisplay()<<"\n";
		processes[i].CleanUp();
	}

	/*
	std::string info = AssembleForDisplay(enabled_flags, processes);
	Display(info);
	*/

	return 0;
}
