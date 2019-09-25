#include <process.h>
#include <flags.h>

#include <windows.h>
#include <string.h>
#include <psapi.h>


#define OK 0
#define OPEN_PROC_FAILURE 1
#define QUERY_MEMORY_FAILURE 2


Process::Process(DWORD pid): process_ID(pid), status(OK){
	proc_func[Flags::MEMORY] = &Process::GenerateMemoryProfile();
	proc_func[Flags::CPU] = &Process::GenerateCPUProfile();
	proc_func[Flags::FILES] = &Process::GenerateOpenFileProfile();
	proc_func[Flags::PORTS] = &Process::GenerateOpenPortProfile();
}

Process::Process(const Process& rhs){
	this->process_ID = rhs.process_ID;
	memcpy(this->proc_func, rhs.proc_func, sizeof(ProcFuncPtr)*N);
	this->msg = rhs.msg;
}

Process::~Process(){

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
	/*open process by pid*/
	HANDLE proc_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, this->process_ID);
	if(proc_handle==nullptr){
		status = OPEN_PROC_FAILURE;
		return;
	}
	/*get memory profile from process*/
	PROCESS_MEMORY_COUNTERS pmc;
	if(GetProcessMemoryInfo(proc_handle, &pmc, sizeof(pmc))){
		//std::stringstream str_builder;
		//str_builder<<"Memory: "<<"|page-fault-count="<<(float)pmc.PageFaultCount/MEGABYTE<<"|working-set="<<(float)pmc.WorkingSetSize/MEGABYTE<<"|peak-working-set="<<(float)pmc.PeakWorkingSetSize/MEGABYTE<<"|commited-memory-size="<<(float)pmc.PagefileUsage/MEGABYTE<<"|\n";
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

#define MAX_P_COUNT 1024
void GetProcesses(std::vector<Process<Flags::num_attribs>>* processes){
	DWORD process_pool[MAX_P_COUNT];
	DWORD process_count_bytes;
	EnumProcesses(process_pool, MAX_P_COUNT*sizeof(DWORD), &process_count);
	unsigned int process_count = process_count_bytes/sizeof(DWORD);
	for(DWORD i=0; i<process_count; ++i){
		processes->push_back(Process(process_pool[i]));
	}
}
