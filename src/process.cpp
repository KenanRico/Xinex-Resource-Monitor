#include <process.h>
#include <flags.h>

#include <windows.h>


Process::Process(DWORD pid): process_ID(pid){
	proc_func[Flags::MEMORY] = &Process::GenerateMemoryProfile();
	proc_func[Flags::CPU] = &Process::GenerateCPUProfile();
	proc_func[Flags::FILES] = &Process::GenerateOpenFileProfile();
	proc_func[Flags::PORTS] = &Process::GenerateOpenPortProfile();
}

Process::~Process(){

}

void Process::AppendAttrib(unsigned int attrib){
	(this->*proc_func[attrib])();
}

void Process::GenerateMemoryProfile(){

}

void Process::GenerateCPUProfile(){

}

void Process::GenerateOpenFileProfile(){

}

void Process::GenerateOpenPortProfile(){

}
