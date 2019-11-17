#ifndef PROCESSES_H
#define PROCESSES_H

#include <process.h>
#include <flags.h>

#include <vector>
#include <array>
#include <string>
#include <stdint.h>
#include <iphlpapi.h>


class Processes;
using ProcFuncPtr = void(Processes::*)(Process*);

class Processes{
	private:
		std::vector<Process> processes;
		std::vector<ProcFuncPtr> proc_func;
		PMIB_TCPTABLE2 tcp_table;
		unsigned int attrib_count;
		uint32_t status; //32 flags
	public:
		Processes();
		~Processes();
		void GetProcesses();
		void ConfigureByFlags(const std::array<bool, Flags::X>&);
		void GenProfiles();
		void CleanUp();
		std::string Display() const;
		inline unsigned int CountAttribs() const { return attrib_count; }
		inline uint32_t Status() const { return status; }
	private:
		Processes(const Processes&) = delete;
		Processes& operator=(const Processes&) = delete;
		void LoadFunctions(const std::array<bool, Flags::X>&);
		void PrefetchCommonResources(const std::array<bool, Flags::X>&);
		void GenerateMemoryProfile(Process*);
		void GenerateCPUProfile(Process*);
		void GenerateOpenFileProfile(Process*);
		void GenerateOpenPortProfile(Process*);
};

#endif
