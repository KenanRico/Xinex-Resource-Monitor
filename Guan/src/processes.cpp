#include <processes.h>
#include <process.h>
#include <flags.h>

#include <array>
#include <winpack.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <stdlib.h>
#include <algorithm>


#define OK 0x00000000
#define INSUF_TCP_BUFFER 0x00000001
#define QUERY_MEMORY_FAILURE 0x00000002


Processes::Processes(): tcp_table(nullptr), attrib_count(0), status(OK){
}


Processes::~Processes(){
}


#define MAX_P_COUNT 1024
void Processes::GetProcesses(){
	DWORD pids[MAX_P_COUNT];
	DWORD process_count_in_bytes = 0;
	EnumProcesses(pids, sizeof(pids), &process_count_in_bytes);
	unsigned int process_count = process_count_in_bytes/sizeof(DWORD);
	processes.reserve(process_count);
	for(unsigned int p = 0; p<process_count; ++p){
		processes.push_back(Process(pids[p]));
	}
	processes.erase(
		std::remove_if(processes.begin(), processes.end(), [](const Process& proc){return proc.Status()!=0x0;}),
		processes.end()
	);
}


void Processes::ConfigureByFlags(const std::array<bool, Flags::X>& flags){
	LoadFunctions(flags);
	PrefetchCommonResources(flags);
}


void Processes::GenProfiles(){
	for(unsigned int p=0; p<processes.size(); ++p){
		for(unsigned int i=0; i<attrib_count; ++i){
			(this->*proc_func[i])(&(processes[p]));
		}
	}

}


void Processes::CleanUp(){
	free(tcp_table);
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


void Processes::PrefetchCommonResources(const std::array<bool, Flags::X>& enabled){
	if(enabled[Flags::PORTS]){
		ULONG req_table_size = sizeof(MIB_TCPTABLE2);
		tcp_table = (PMIB_TCPTABLE2)malloc(req_table_size);
		GetTcpTable2(tcp_table, &req_table_size, FALSE);
		free(tcp_table);
		tcp_table = (PMIB_TCPTABLE2)malloc(req_table_size);
		if(GetTcpTable2(tcp_table, &req_table_size, FALSE)==ERROR_INSUFFICIENT_BUFFER){
			status |= INSUF_TCP_BUFFER;
			return;
		}
	}
}

/*
 *require Psapi.lib
 *require -DPSAPI_VERSION=1 compile flag
 */
#define BYTES_PER_MEGABYTE 2062336.0f
void Processes::GenerateMemoryProfile(Process* process){
	PROCESS_MEMORY_COUNTERS pmc;
	if(GetProcessMemoryInfo(process->process_handle, &pmc, sizeof(pmc))){
		process->AddToMemoryProfile(
			pmc.PageFaultCount,
			(float)pmc.WorkingSetSize/BYTES_PER_MEGABYTE,
			(float)pmc.PeakWorkingSetSize/BYTES_PER_MEGABYTE,
			(float)pmc.PagefileUsage/BYTES_PER_MEGABYTE
		);
	}else{
		status |= QUERY_MEMORY_FAILURE;
	}

}


void Processes::GenerateCPUProfile(Process* process){
	/*get number of threads*/
	int thread_count = 0;
	{
		HANDLE thread_walk_handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, process->process_ID);
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


void Processes::GenerateOpenFileProfile(Process*){

}


void Processes::GenerateOpenPortProfile(Process* process){
	unsigned int table_size = (unsigned int)tcp_table->dwNumEntries;
	for(unsigned int i=0; i<table_size; ++i){
		MIB_TCPROW2& row = tcp_table->table[i];
		if(row.dwOwningPid==process->process_ID){
			process->AddToPortProfile(
				(unsigned int)row.dwLocalAddr,
				(unsigned int)row.dwLocalPort,
				(unsigned int)row.dwRemoteAddr,
				(unsigned int)row.dwRemotePort
			);
		}
	}
}


