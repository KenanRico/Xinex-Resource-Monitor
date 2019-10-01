#ifndef MEMORY_PROFILE
#define MEMORY_PROFILE

struct MemoryProfile{
	float page_fault_count;
	float working_set;
	float peak_working_set;
	float page_file_usage;
	SetProfile();
};

#endif
