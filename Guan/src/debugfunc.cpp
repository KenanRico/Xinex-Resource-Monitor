#include <debugfunc.h>

#include <iostream>
#include <winpack.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <psapi.h>



#define DEBUGGING


#ifdef DEBUGGING

void DEBUG::check_tcptable_calls() {
	PMIB_TCPTABLE2 tcp_table = nullptr;
	ULONG req_table_size = sizeof(MIB_TCPTABLE2);
	tcp_table = (PMIB_TCPTABLE2)malloc(req_table_size);
	GetTcpTable2(tcp_table, &req_table_size, FALSE);
	free(tcp_table);
	tcp_table = (PMIB_TCPTABLE2)malloc(req_table_size);
	if(GetTcpTable2(tcp_table, &req_table_size, FALSE)==ERROR_INSUFFICIENT_BUFFER){
		std::cout << "DEBUG: Insufficient buffer error\n";
		exit(0);

	}

	int table_size = (int)tcp_table->dwNumEntries;
	for(int i=0; i<table_size; ++i){
		MIB_TCPROW2& row = tcp_table->table[i];
		std::cout <<row.dwOwningPid<<"|"<< row.dwLocalAddr << ":" << row.dwLocalPort << " <-> " << row.dwRemoteAddr <<":"<< row.dwRemotePort << "\n";
	}
	
	exit(0);

}

void DEBUG::check_procname_calls() {

	DWORD process_pool[1024];
	DWORD process_count_bytes;
	EnumProcesses(process_pool, 1024*sizeof(DWORD), &process_count_bytes);
	unsigned int process_count = process_count_bytes/sizeof(DWORD);
	for(unsigned int i=0; i<process_count; ++i){
		HANDLE process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_pool[i]);
		if(process_handle==nullptr){
			std::cout << "DEBUG: null process handle\n";
			//exit(0);
			continue;
		}
		CHAR buffer[1024];
		int size = 1024;
		//if(QueryFullProcessImageName(process_handle, 0, (LPWSTR)buffer, (PDWORD)&size)){
		if(GetModuleFileNameEx(process_handle, 0, (LPWSTR)buffer, size)){
			std::string process_name = std::string(buffer);
		}else{
			std::cout << "DEBUG: failure to retrieve process name\n";
			exit(0);
		}
	}

	exit(0);

}

#else

void DEBUG::check_tcptable_calls() {
	std::cout << "Error: calling check_tcptable_calls in non-debug mode\n";
	exit(0);
}

void DEBUG::check_procname_calls() {
	std::cout << "Error: calling check_procname_calls in non-debug mode\n";
	exit(0);
}

#endif