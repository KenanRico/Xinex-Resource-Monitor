#ifndef CPU_PROFILE_H
#define CPU_PROFILE_H

struct CPUProfile{
	long long user_mode_time;
	long long kernel_mode_time;
	long long priority;
	long long thread_count;
	long long processor_number;
	void SetProfile(long long umt, long long kmt, long long p, long long tc, long long pn){
		user_mode_time = umt;
		kernel_mode_time = kmt;
		priority = p;
		thread_count = tc;
		processor_number = pn;
	}
	std::string ToString() const{
		std::stringstream ss;
		ss << "\n" <<
			"user mode time: "<<user_mode_time<<" "<<
			"kernel mode time: "<<kernel_mode_time<<" "<<
			"priority: "<<priority<<" "<<
			"threads: "<<thread_count<<" "<<
			"processor ID: "<<processor_number;
		return ss.str();
	}
};

#endif
