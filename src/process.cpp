#include <process.h>
#include <flags.h>

#include <string>
#include <stdio.h>


#define OK 0x0
#define OPEN_PROC_FAILURE 0x1
#define QUERY_MEMORY_FAILURE 0x2
#define QUERY_PNAME_FAILURE 0x4
#define QUERY_TCPTABLE_FAILURE 0x8



Process::Process(const Process& rhs){
	this->process_ID = rhs.process_ID;
	this->process_name = rhs.process_name;
	this->status = rhs.status;
  this->cpup = rhs.cpup;
  this->memp = rhs.memp;
  this->portp = rhs.portp;
  this->filep = rhs.filep;
}

Process::~Process(){

}


std::string Process::GetDisplay() const{
	char ID[32];
	snprintf(ID, 32, "%d", (int)process_ID);
	return std::string(ID)+=" : "+process_name+" "+memp.ToString()+"\n"+portp.ToString(); //placeholder
}

