#ifndef PORT_PROFILE_H
#define PORT_PROFILE_H

#include <vector>

struct PortProfile{

	struct Connection{
		unsigned int local_host;
		unsigned int local_port;
		unsigned int remote_host;
		unsigned int remote_port;
	};

	std::vector<Connection> connections;

	void Add(unsigned int lh, unsigned int lp, unsigned int rh, unsigned int rp){
		connections.push_back((struct Connection){lh, lp, rh, rp});
	}

};

#endif
