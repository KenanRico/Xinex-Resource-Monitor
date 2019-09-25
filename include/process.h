#ifndef PROCESS_H
#define PROCESS_H


class Process;
using ProcFuncPtr = void(Process::*)();

template <std::size_t N>
class Process{
	private:
		DWORD process_ID;
		ProcFuncPtr proc_func[N];
		std::string msg;
	public:
		inline const std::string& GetMsg() const { return msg; }
		void GenerateMemoryProfile();
		void GenerateCPUProfile();
		void GenerateOpenFileProfile();
		void GenerateOpenPortProfile();
		
	public:
		Process(DWORD);
		~Process();
	private:
		Process() = delete;
		Process(const Process&) = delete;
		Process& operator=(const Process&) = delete;
};
