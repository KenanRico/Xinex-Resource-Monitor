#ifndef PROCESS_H
#define PROCESS_H

#include "flags.h"
#include "memoryprofile.h"
#include "cpuprofile.h"
#include "fileprofile.h"
#include "portprofile.h"

#include <string>
#include <windows.h>
#include <vector>
#include <stdint.h>


class Process;
using ProcFuncPtr = void(Process::*)();

class Process{
	private:
    /*process properties*/
		DWORD process_ID;
		std::string process_name;
    HANDLE process_handle;
    /*attribute resources*/
		std::vector<ProcFuncPtr> proc_func;
    int attrib_count;
		MemoryProfile memp;
		CPUProfile cpup;
		FileProfile filep;
		PortProfile portp;

		uint8_t status;

		
	public:
		Process(DWORD, const std::array<bool, Flags::num_attribi>&);
		Process(const Process&);
		~Process();
		void AppendAttrib(unsigned int);
		std::string GetDisplay() const;
	private:
		Process() = delete;
		Process& operator=(const Process&) = delete;
    void GetName();
    inline int CountAttribs() const { return attrib_count; }
		void GenerateMemoryProfile();
		void GenerateCPUProfile();
		void GenerateOpenFileProfile();
		void GenerateOpenPortProfile();
};

void GetProcesses(std::vector<Process>*);

#endif
