#ifndef PORT_PROFILE_H
#define PORT_PROFILE_H

#include <sstream>
#include <vector>

struct PortProfile{

	struct Connection{
		unsigned int local_host;
		unsigned int local_port;
		unsigned int remote_host;
		unsigned int remote_port;
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
	std::string PrintableIP(unsigned int host) const {
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
		for (unsigned int i = 0; i < connections.size(); ++i) {
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
