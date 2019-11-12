#pragma once

#include "sockets/base_recv_socket.h"
#include "common/types/lidar_msg.h"
#include <iostream>

namespace simulator{
	class LidarSocket : public BaseRecvSocket
	{
	public:
		LidarSocket(const std::string local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		LidarSocket(const int& local_port, const int& remote_port);

		~LidarSocket() { std::cout << "lidar socket xigou" << std::endl; };

		bool OnReceive(const size_t& lidar_pack_size , LidarMsg* lidar_msg);
	};

}