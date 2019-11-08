#ifndef PROCESSES_H
#define PROCESSES_H

#include <process.h>
#include <flags.h>

#include <vector>
#include <array>
#include <string>


class Processes;
using ProcFuncPtr = void(Processes::*)();

class Processes{
	private:
		std::vector<Process> processes;
		std::vector<ProcFuncPtr> proc_func;
		unsigned int attrib_count;
	public:
		Processes();
		~Processes();
		void GetProcesses();
		void ConfigureByFlags(const std::array<bool, Flags::X>&);
		inline unsigned int CountAttribs() { return attrib_count; }
		void GenProfiles();
		void CleanUp();
		std::string Display() const;
	private:
		Processes(const Processes&) = delete;
		Processes& operator=(const Processes&) = delete;
		void LoadFunctions(const std::array<bool, Flags::X>&);
		void PrefetchCommonResource(const std::array<bool, Flags::X>&);
};

#endif
