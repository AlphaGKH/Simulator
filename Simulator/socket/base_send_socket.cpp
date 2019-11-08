#include "base_send_socket.h"
#include "common/mlog/mlog.h"

namespace simulator{
	BaseSendSocket::BaseSendSocket(const std::string& local_ip, const int& local_port,
		const std::string& remote_ip, const int& remote_port) :
		BaseSocket(local_ip, local_port, remote_ip, remote_port){}

	BaseSendSocket::BaseSendSocket(const int& local_port, const int& remote_port) :
		BaseSocket(local_port, remote_port){}

	BaseSendSocket::~BaseSendSocket(){
		closesocket(send_socket_);
		WSACleanup();
	}

	bool BaseSendSocket::Init(){
		// startup  windows socket
		if (WSAStartup(MAKEWORD(2, 2), &wsd_) != 0)
		{
			AERROR << "WSAStartup Windows Socket ERROR = " << WSAGetLastError() << std::endl;
			return false;
		}

		// creat send socket
		send_socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (send_socket_ == INVALID_SOCKET)
		{
			AERROR << "Create Receive Socket ERROR = " << WSAGetLastError() << std::endl;
			return false;
		}

		local_addr_.sin_family = AF_INET;
		local_addr_.sin_port = htons(local_port_);
		local_addr_.sin_addr.s_addr = inet_addr(local_ip_.c_str());

		return true;
	}

	void BaseSendSocket::Send(const char* send_data) {
		sendto(send_socket_, send_data, strlen(send_data), 0, (SOCKADDR*)&local_addr_, sizeof(local_addr_));
	}



}