#ifndef PROCESS_H
#define PROCESS_H

#include "flags.h"
#include "memoryprofile.h"
#include "cpuprofile.h"
#include "fileprofile.h"
#include "portprofile.h"
#include "winpack.h"

#include <string>
#include <vector>
#include <stdint.h>
#include <array>


class Process;
using ProcFuncPtr = void(Process::*)();

class Process{
	private:
		/*process properties*/
		DWORD process_ID;
		std::string process_name;
		HANDLE process_handle;
		/*attribute resources*/
		MemoryProfile memp;
		CPUProfile cpup;
		FileProfile filep;
		PortProfile portp;
		uint8_t status;

		static std::vector<ProcFuncPtr> proc_func;
		static int attrib_count;

		
	public:
		Process(DWORD);
		Process(const Process&);
		~Process();
		Process& operator=(const Process&);

		void AppendAttrib(unsigned int);
		std::string GetDisplay() const;
		static void LoadFunctions(const std::array<bool, Flags::X>&);
		void CleanUp();
		inline static int CountAttribs() { return attrib_count; }
		inline uint8_t Status() const { return status; }
	private:
		Process() = delete;
		void GetName();
		void GenerateMemoryProfile();
		void GenerateCPUProfile();
		void GenerateOpenFileProfile();
		void GenerateOpenPortProfile();
};

void GetProcesses(std::vector<Process>*);

#endif
