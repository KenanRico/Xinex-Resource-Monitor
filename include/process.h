#ifndef PROCESS_H
#define PROCESS_H

#include <flags.h>

#include <string>
#include <windows.h>
#include <vector>


class Process;
using ProcFuncPtr = void(Process::*)();

template <std::size_t N>
class Process{
	private:
		DWORD process_ID;
		ProcFuncPtr proc_func[N];
		std::string msg;

		
	public:
		Process(DWORD);
		Process(const Process&);
		~Process();
		void AppendAttrib(unsigned int);
		inline const std::string& GetMsg() const { return msg; }
	private:
		Process() = delete;
		Process& operator=(const Process&) = delete;
		void GenerateMemoryProfile();
		void GenerateCPUProfile();
		void GenerateOpenFileProfile();
		void GenerateOpenPortProfile();
};

void GetProcesses(std::vector<Process<Flags::num_attribs>>*);

#endif
