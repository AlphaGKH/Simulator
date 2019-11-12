#pragma once

#include "sockets/base_socket.h"

namespace simulator{

	class BaseSendSocket :public BaseSocket
	{
	public:
		BaseSendSocket(const std::string& local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		BaseSendSocket(const int& local_port, const int& remote_port);
		virtual ~BaseSendSocket();

		bool Init() override;

		virtual void Send(const char* send_data);

	protected:
		SOCKET send_socket_;
	};

}