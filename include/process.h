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
#include <unordered_map>


class Processes;

class Process{
	public:
		/*process properties*/
		uint32_t process_ID;
		std::string process_name;
		std::string process_state;
	private:
		/*attribute resources*/
		MemoryProfile memp;
		CPUProfile cpup;
		FileProfile filep;
		PortProfile portp;
		uint8_t status;
		static std::unordered_map<char, std::string> state;

	public:
		Process(const std::string&);
		Process(const Process&);
		~Process();
		std::string GetDisplay() const;
		void CleanUp();
		inline uint8_t Status() const { return status; }
	private:
		Process() = delete;
		Process& operator=(const Process&) = delete;

	friend class Processes;
};

#endif
