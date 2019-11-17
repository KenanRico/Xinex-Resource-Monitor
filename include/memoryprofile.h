#ifndef MEMORY_PROFILE_H
#define MEMORY_PROFILE_H

#include <string>
#include <sstream>

struct MemoryProfile{
	unsigned int page_fault_count;
	float working_set;
	float peak_working_set;
	float page_file_usage;
	void SetProfile(unsigned int pfc, float ws, float pws, float pfu){
		page_fault_count = pfc;
		working_set = ws;
		peak_working_set = pws;
		page_file_usage = pfu;
	}
	std::string ToString() const{
		std::stringstream ss;
		ss<<
			page_fault_count<<" "<<
			working_set<<" "<<
			peak_working_set<<" "<<
			page_file_usage;
		return ss.str();
	}
};

#endif
