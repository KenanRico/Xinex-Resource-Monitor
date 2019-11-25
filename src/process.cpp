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
}

Process& Process::operator=(const Process& rhs){
	this->process_ID = rhs.process_ID;
	this->process_name = rhs.process_name;
	this->status = rhs.status;
	return *this;
}

Process::~Process(){

}


std::string Process::GetDisplay() const{
	char ID[32];
	snprintf(ID, 32, "%d", (int)process_ID);
	return std::string(ID)+=" : "+process_name+" "+memp.ToString()+"\n"+portp.ToString(); //placeholder
}





void Process::AddToMemoryProfile(unsigned int pfc, float ws, float pws, float pfu){
	memp.SetProfile(pfc, ws, pws, pfu);
}

void Process::AddToPortProfile(unsigned int lh, unsigned int lp, unsigned int rh, unsigned int rp){
	portp.Add(lh, lp, rh, rp);
}
