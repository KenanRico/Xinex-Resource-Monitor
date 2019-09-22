#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <string>
#include <array>

class Flags{
	private:
		enum {CPU=0, MEMORY=1, PORT=2};
		static constexpr uint8_t flag_count = 3;
		const std::string registered_flags[flag_count];
	private:
		bool flags[flag_count];
		uint8_t status;
		std::string error_msg;

	public:
		Flags();
		~Flags();
	private:
		Flags(const Flags&) = delete;
		Flags& operator=(const Flags&) = delete;

	public:
		void ParseFlags(int, char**);
		inline bool Invalid() const { return status!=0; }
		inline bool Flag(int f) const { return flags[f]; }
		inline const std::string& ErrorMsg() const { return error_msg; }
	private:
		void HandleError(uint8_t, char const *);
};

#endif
