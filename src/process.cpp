#include <process.h>
#include <flags.h>

#include <windows.h>
#include <string>
#include <psapi.h>
#include <stdio.h>
#include <tlhelp32.h>


#define OK 0x0
#define OPEN_PROC_FAILURE 0x1
#define QUERY_MEMORY_FAILURE 0x2
#define QUERY_PNAME_FAILURE 0x4


std::vector<ProcFuncPtr> Process::proc_func;
int Process::attrib_count = 0;

#include <iostream>
Process::Process(DWORD pid): process_ID(pid), status(OK){
	/*get hanle and name*/
	process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_ID);
	if(process_handle==nullptr){
		status |= OPEN_PROC_FAILURE;
		return;
	}
	GetName();
}

Process::Process(const Process& rhs){
	this->process_ID = rhs.process_ID;
	this->process_name = rhs.process_name;
	this->process_handle = rhs.process_handle;
	this->status = rhs.status;
}

Process& Process::operator=(const Process& rhs){
	this->process_ID = rhs.process_ID;
	this->process_name = rhs.process_name;
	this->process_handle = rhs.process_handle;
	this->status = rhs.status;
	return *this;
}

Process::~Process(){

}

#define BUFF_SIZE 1024
void Process::GetName(){
	CHAR buffer[BUFF_SIZE];
	//if(QueryFullProcessImageName(process_handle, 0, buffer, &size)){
	if(GetModuleFileNameEx(process_handle, 0, buffer, BUFF_SIZE)){
		process_name = std::string(buffer);
	}else{
		status |= QUERY_PNAME_FAILURE;
	}
}

void Process::AppendAttrib(unsigned int attrib){
	(this->*proc_func[attrib])();
}


/*
 *require Psapi.lib
 *require -DPSAPI_VERSION=1 compile flag
 */
#include <iostream>
#define MEGABYTE 2062336.0f
void Process::GenerateMemoryProfile(){
	PROCESS_MEMORY_COUNTERS pmc;
	if(GetProcessMemoryInfo(process_handle, &pmc, sizeof(pmc))){
		//std::stringstream str_builder;
		//str_builder<<"Memory: "<<"|page-fault-count="<<(float)pmc.PageFaultCount/MEGABYTE<<"|working-set="<<(float)pmc.WorkingSetSize/MEGABYTE<<"|peak-working-set="<<(float)pmc.PeakWorkingSetSize/MEGABYTE<<"|commited-memory-size="<<(float)pmc.PagefileUsage/MEGABYTE<<"|\n";
		memp.SetProfile(
			pmc.PageFaultCount,
			(float)pmc.WorkingSetSize/MEGABYTE,
			(float)pmc.PeakWorkingSetSize/MEGABYTE,
			(float)pmc.PagefileUsage/MEGABYTE
		);
	}else{
		if(GetLastError()==ERROR_INVALID_HANDLE){
		}
		status |= QUERY_MEMORY_FAILURE;
	}
}

void Process::GenerateCPUProfile(){
	/*get number of threads*/
	int thread_count = 0;
	{
		HANDLE thread_walk_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, this->process_ID);
		if(thread_walk_handle!=INVALID_HANDLE_VALUE){
			THREADENTRY32 te;
			te.dwSize = sizeof(te);
			if(Thread32First(thread_walk_handle, &te)){
				thread_count = 1;
				while(Thread32Next(thread_walk_handle, &te)){
					++thread_count;
				}
			}
		}
		CloseHandle(thread_walk_handle);
	}

	/*get percentage cpu usage*/
	float cpu_usage = 0.0f;

}

void Process::GenerateOpenFileProfile(){

}

void Process::GenerateOpenPortProfile(){

}

std::string Process::GetDisplay() const{
	char ID[32];
	snprintf(ID, 32, "%d", (int)process_ID);
	return std::string(ID)+" : "+process_name+" "+memp.ToString(); //placeholder
}

void Process::LoadFunctions(const std::array<bool, Flags::X>& enabled){
	for(unsigned int i=0; i<Flags::X; ++i){
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

void Process::CleanUp(){
	CloseHandle(process_handle);
}



#define MAX_P_COUNT 1024
void GetProcesses(std::vector<Process>* processes){
	DWORD process_pool[MAX_P_COUNT];
	DWORD process_count_bytes;
	EnumProcesses(process_pool, MAX_P_COUNT*sizeof(DWORD), &process_count_bytes);
	unsigned int process_count = process_count_bytes/sizeof(DWORD);
	processes->reserve(process_count);
	for(unsigned int i=0; i<process_count; ++i){
		processes->push_back(Process(process_pool[i]));
	}
}
