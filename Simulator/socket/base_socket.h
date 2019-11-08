#pragma once

#include <WinSock2.h>
#include <winsock.h>
#include <string>

#include <thread>

#pragma comment(lib,"ws2_32.lib")
namespace simulator{

	class BaseSocket
	{
	public:
		BaseSocket(const std::string& local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port) :
			local_ip_(local_ip),
			local_port_(local_port),
			remote_ip_(remote_ip),
			remote_port_(remote_port){}

		BaseSocket(const int& local_port, const int& remote_port) :
			local_ip_("127.0.0.1"),
			local_port_(local_port),
			remote_ip_("127.0.0.1"),
			remote_port_(remote_port){}
		~BaseSocket() = default;

		virtual bool Init() = 0;

	protected:
		WSADATA wsd_;

		SOCKADDR_IN local_addr_;

		std::string local_ip_;

		int local_port_ = 9000;

		std::string remote_ip_;
		int remote_port_ = 9500;

		SOCKADDR_IN remote_addr_;



	};
}