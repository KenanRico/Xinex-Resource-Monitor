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


class Process{
	public:
		/*process properties*/
		DWORD process_ID;
		std::string process_name;
		HANDLE process_handle;
	private:
		/*attribute resources*/
		MemoryProfile memp;
		CPUProfile cpup;
		FileProfile filep;
		PortProfile portp;
		uint8_t status;

	public:
		Process(DWORD);
		Process(const Process&);
		~Process();
		Process& operator=(const Process&);
		std::string GetDisplay() const;
		void CleanUp();
		void AddToMemoryProfile(DWORD, float, float, float);
		void AddToPortProfile(unsigned int, unsigned int, unsigned int, unsigned int);
		inline uint8_t Status() const { return status; }
	private:
		Process() = delete;
		void GetName();

	friend class Processes;
};

#endif
