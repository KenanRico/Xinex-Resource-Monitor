#ifndef PROCESS_H
#define PROCESS_H


class Process;
using ProcFuncPtr = void(Process::*)();

template <std::size_t N>
class Process{
	private:
		ProcFuncPtr proc_func[N];
		std::string msg;
};
