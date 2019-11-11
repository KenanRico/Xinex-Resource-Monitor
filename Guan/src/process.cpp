#include <WinSock2.h>

#include <process.h>
#include <flags.h>

#include <string>
#include <psapi.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <winpack.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")


#define OK 0x0
#define OPEN_PROC_FAILURE 0x1
#define QUERY_MEMORY_FAILURE 0x2
#define QUERY_PNAME_FAILURE 0x4
#define QUERY_TCPTABLE_FAILURE 0x8



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
	int size = BUFF_SIZE;
	if(QueryFullProcessImageNameA(process_handle, 0, buffer, (PDWORD)&size)){
	//if(GetModuleFileNameEx(process_handle, 0, (LPWSTR)buffer, BUFF_SIZE)){
		process_name = std::string(buffer);
	}else{
		status |= QUERY_PNAME_FAILURE;
	}
}



std::string Process::GetDisplay() const{
	char ID[32];
	snprintf(ID, 32, "%d", (int)process_ID);
	return std::string(ID)+=" : "+process_name+" "+memp.ToString()+"\n"+portp.ToString(); //placeholder
}


void Process::CleanUp(){
	CloseHandle(process_handle);
}



void Process::AddToMemoryProfile(DWORD pfc, float ws, float pws, float pfu){
	memp.SetProfile((unsigned int)pfc, ws, pws, pfu);
}

void Process::AddToPortProfile(unsigned int lh, unsigned int lp, unsigned int rh, unsigned int rp){
	portp.Add(lh, lp, rh, rp);
}
