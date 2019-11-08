#pragma once

#include "base_socket.h"

namespace simulator{

	class BaseRecvSocket :public BaseSocket
	{
	public:
		BaseRecvSocket(const std::string& local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		BaseRecvSocket(const int& local_port, const int& remote_port);
		~BaseRecvSocket();

		bool Init() override;

	protected:
		bool IsReceived(const size_t& data_size);

	protected:
		SOCKET recv_socket_;

		char* ptr_recv_buff_ = nullptr;

		int result_;

	};

}