#include <process.h>
#include <flags.h>

#include <windows.h>
#include <string>
#include <psapi.h>
#include <stdio.h>


#define OK 0
#define OPEN_PROC_FAILURE 1
#define QUERY_MEMORY_FAILURE 2
#define QUERY_PNAME_FAILURE 3


std::vector<ProcFuncPtr> Process::proc_func;
int Process::attrib_count = 0;

Process::Process(DWORD pid): process_ID(pid), status(OK){
	/*get hanle and name*/
	process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_ID);
	if(process_handle==nullptr){
		status = OPEN_PROC_FAILURE;
		return;
	}
	GetName();
}

Process::Process(const Process& rhs){
	this->process_ID = rhs.process_ID;
	this->process_name = rhs.process_name;
}

Process::~Process(){

}

#define BUFF_SIZE 1024
void Process::GetName(){
	CHAR buffer[BUFF_SIZE];
	DWORD size = BUFF_SIZE;
	//if(QueryFullProcessImageName(process_handle, 0, buffer, &size)){
	if(GetModuleFileNameEx(process_handle, 0, buffer, size)){
		process_name = std::string(buffer);
	}else{
		status = QUERY_PNAME_FAILURE;
	}
}

void Process::AppendAttrib(unsigned int attrib){
	(this->*proc_func[attrib])();
}


/*
 *require Psapi.lib
 *require -DPSAPI_VERSION=1 compile flag
 */
#define MEGABYTE 2062336.0f
void Process::GenerateMemoryProfile(){
	PROCESS_MEMORY_COUNTERS pmc;
	if(GetProcessMemoryInfo(process_handle, &pmc, sizeof(pmc))){
		//std::stringstream str_builder;
		//str_builder<<"Memory: "<<"|page-fault-count="<<(float)pmc.PageFaultCount/MEGABYTE<<"|working-set="<<(float)pmc.WorkingSetSize/MEGABYTE<<"|peak-working-set="<<(float)pmc.PeakWorkingSetSize/MEGABYTE<<"|commited-memory-size="<<(float)pmc.PagefileUsage/MEGABYTE<<"|\n";
		memp.SetProfile(
			(float)pmc.PageFaultCount/MEGABYTE,
			(float)pmc.WorkingSetSize/MEGABYTE,
			(float)pmc.PeakWorkingSetSize/MEGABYTE,
			(float)pmc.PagefileUsage/MEGABYTE
		);
	}else{
		status = QUERY_MEMORY_FAILURE;
	}
}

void Process::GenerateCPUProfile(){

}

void Process::GenerateOpenFileProfile(){

}

void Process::GenerateOpenPortProfile(){

}

std::string Process::GetDisplay() const{
	char ID[32];
	snprintf(ID, 32, "%d", (int)process_ID);
	return std::string(ID)+" : "+process_name; //placeholder
}

void Process::LoadFunctions(const std::array<bool, Flags::X>& enabled){
	for(int i=0; i<Flags::X; ++i){
		if(enabled[i]){
			switch(i){
				case Flags::CPU:
					proc_func.push_back(&Process::GenerateCPUProfile);
					++attrib_count;
					break;
				case Flags::MEMORY:
					proc_func.push_back(&Process::GenerateMemoryProfile);
					++attrib_count;
					break;
				case Flags::FILES:
					proc_func.push_back(&Process::GenerateOpenFileProfile);
					++attrib_count;
					break;
				case Flags::PORTS:
					proc_func.push_back(&Process::GenerateOpenPortProfile);
					++attrib_count;
					break;
				default:
					break;
			}
		}
	}
}

#define MAX_P_COUNT 1024
void GetProcesses(std::vector<Process>* processes){
	DWORD process_pool[MAX_P_COUNT];
	DWORD process_count_bytes;
	EnumProcesses(process_pool, MAX_P_COUNT*sizeof(DWORD), &process_count_bytes);
	unsigned int process_count = process_count_bytes/sizeof(DWORD);
	for(DWORD i=0; i<process_count; ++i){
		processes->push_back(Process(process_pool[i]));
	}
}
