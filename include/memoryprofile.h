#ifndef MEMORY_PROFILE_H
#define MEMORY_PROFILE_H

#include <string>
#include <sstream>
#include <iostream>

struct MemoryProfile{

	long long minor_fault_count;
	long long major_fault_count;
  long long virtual_mem_size;
  long long page_frame_count;
  long long swapped_pages;

	void SetProfile(long long mifc, long long mafc, long long vms, long long pfc, long long sp){
		minor_fault_count = mifc;
		major_fault_count = mafc;
    virtual_mem_size = vms/1048576; //convert to MB
    page_frame_count = pfc;
    swapped_pages = sp;
	}

	std::string ToString() const{
		std::stringstream ss;
		ss<<
			minor_fault_count<<" "<<
			major_fault_count<<" "<<
			virtual_mem_size<<" "<<
			page_frame_count<<" "<<
      swapped_pages;
		return ss.str();
	}

};

#endif
