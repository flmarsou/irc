#pragma once

# include "types.hpp"
# include "debug.hpp"

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <vector>
# include <map>
# include <set>
# include <algorithm>

# include <sys/stat.h>		// fstat
# include <sys/socket.h>	// socket, setsockopt, getsockname, bind, connect, listen, accept, recv, send
# include <fcntl.h>			// fcntl
# include <poll.h>			// poll
# include <netinet/in.h>	// htons, htonl, ntohs, ntohl, sockaddr_in
# include <arpa/inet.h>		// inet_addr, inet_ntoa
# include <netdb.h>			// getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
# include <unistd.h>		// close, lseek
# include <csignal>			// signal, sigaction
# include <errno.h>			// error in poll handler
