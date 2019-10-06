#ifndef CPU_PROFILE_H
#define CPU_PROFILE_H

struct CPUProfile{
	int thread_count;
	int core_occupancy;
	float cpu_usage;
	void SetProfile(int tc, int co, float cu){
		thread_count = tc;
		core_occupancy = co;
		cpu_usage = cu;
	}
};

#endif
