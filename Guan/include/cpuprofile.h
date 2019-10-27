#ifndef CPU_PROFILE_H
#define CPU_PROFILE_H

struct CPUProfile{
	int thread_count;
	float cpu_usage;
	void SetProfile(int tc, float cu){
		thread_count = tc;
		cpu_usage = cu;
	}
};

#endif
