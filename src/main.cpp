#include <flags.h>
#include <strfunc.h>

#include <array>
#include <stdint.h>
#include <iostream>


int main(int argc, char** argv){
	/*parse attribs*/
	std::array<bool, Attrib::num_attribs> attribs;
	uint8_t status = Input::Attribs::ParseFlags(argc, argv, &attribs);
	if(status!=0){
		std::cout<<"attrib flag error!\n";
		exit(1);
	}
	/*parse orientation*/
	unsigned int ori = 0;
	status = Input::Orientation::ParseOrientation(argc, argv, &ori);
	if(status!=0){
		std::cout<<"orientation flag error!\n";
		exit(1);
	}
	/*parse order*/
	unsigned int ord = 0;
	status = Input::Order::ParseOrder(argc, argv, &ord);
	if(status!=0){
		std::cout<<"order flag error!\n";
		exit(1);
	}

	/*
	Processes processes;
	processes.SetSortOrder(ori, ord);
	GetProcesses(&processes);
	processes.GetProcesses();

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
