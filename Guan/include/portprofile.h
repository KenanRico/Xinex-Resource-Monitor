#ifndef PORT_PROFILE_H
#define PORT_PROFILE_H

#include <winpack.h>
#include <sstream>

#include <vector>

struct PortProfile{

	struct Connection{
		DWORD local_host;
		DWORD local_port;
		DWORD remote_host;
		DWORD remote_port;
		Connection(unsigned int lh, unsigned int lp, unsigned int rh, unsigned int rp) {
			local_host = lh;
			local_port = lp;
			remote_host = rh;
			remote_port = rp;
		}
	};

	std::vector<Connection> connections;

	void Add(unsigned int lh, unsigned int lp, unsigned int rh, unsigned int rp){
		connections.push_back(Connection(lh, lp, rh, rp));
	}
	
	private:
	std::string PrintableIP(DWORD host) const {
		std::stringstream ss;
		ss
			<< ((host >> 0) & 0xff) << '.'
			<< ((host >> 8) & 0xff) << '.'
			<< ((host >> 16) & 0xff) << '.'
			<< ((host >> 24) & 0xff);
		return ss.str();
	}

	public:
	std::string ToString() const {
		std::stringstream ss;
		for (int i = 0; i < connections.size(); ++i) {
			ss<<
				PrintableIP(connections[i].local_host)<<" "<<
				connections[i].local_port<<" "<<
				PrintableIP(connections[i].remote_host)<<" "<<
				connections[i].remote_port<<"\n";
		}
		return ss.str();
	}

};

#endif
