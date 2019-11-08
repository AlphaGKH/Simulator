#pragma once

#include "base_socket.h"

namespace simulator{

	class BaseSendSocket :public BaseSocket
	{
	public:
		BaseSendSocket(const std::string& local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		BaseSendSocket(const int& local_port, const int& remote_port);
		~BaseSendSocket();

		bool Init() override;

	protected:

		void Send(const char* send_data);

	protected:
		SOCKET send_socket_;
	};

}