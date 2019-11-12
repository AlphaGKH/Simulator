#pragma once

#include "sockets/base_recv_socket.h"
#include "common/types/chassis_msg.h"

namespace simulator{
	class ChassisSocket : public BaseRecvSocket
	{
	public:
		ChassisSocket(const std::string local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		ChassisSocket(const int& local_port, const int& remote_port);

		~ChassisSocket() = default;

		bool OnReceive(const size_t& chassis_pack_size, ChassisMsg* chassis_msg);

	private:
		void ChassisDataAnlysis(ChassisMsg* chassis_msg);

	};

}