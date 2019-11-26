#ifndef PROCESS_H
#define PROCESS_H

#include "flags.h"
#include "memoryprofile.h"
#include "cpuprofile.h"
#include "fileprofile.h"
#include "portprofile.h"

#include <string>
#include <vector>
#include <stdint.h>
#include <array>


class Processes;

class Process{
	public:
		/*process properties*/
		uint32_t process_ID;
		std::string process_name;
	private:
		/*attribute resources*/
		MemoryProfile memp;
		CPUProfile cpup;
		FileProfile filep;
		PortProfile portp;
		uint8_t status;

	public:
		Process(const std::string&);
		Process(const Process&);
		~Process();
		std::string GetDisplay() const;
		void CleanUp();
		void AddToMemoryProfile(unsigned int, float, float, float);
		void AddToPortProfile(unsigned int, unsigned int, unsigned int, unsigned int);
		inline uint8_t Status() const { return status; }
	private:
		Process() = delete;
		Process& operator=(const Process&) = delete;

	friend class Processes;
};

#endif
