#include "sockets/base_recv_socket.h"
#include "common/mlog/mlog.h"

namespace simulator{
	BaseRecvSocket::BaseRecvSocket(const std::string& local_ip, const int& local_port,
		const std::string& remote_ip, const int& remote_port) :
		BaseSocket(local_ip, local_port, remote_ip, remote_port){}

	BaseRecvSocket::BaseRecvSocket(const int& local_port, const int& remote_port) :
		BaseSocket(local_port, remote_port){}

	BaseRecvSocket::~BaseRecvSocket(){
		if (ptr_recv_buff_ != nullptr)
		{
			delete[] ptr_recv_buff_;
		}
		closesocket(recv_socket_);
		WSACleanup();
	}

	bool BaseRecvSocket::Init(){
		// startup  windows socket
		if (WSAStartup(MAKEWORD(2, 2), &wsd_) != 0)
		{
			AERROR << "WSAStartup Windows Socket ERROR = " << WSAGetLastError() << std::endl;
			return false;
		}

		// creat receive socket
		recv_socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (recv_socket_ == INVALID_SOCKET)
		{
			AERROR << "Create Receive Socket ERROR = " << WSAGetLastError() << std::endl;
			return false;
		}

		local_addr_.sin_family = AF_INET;
		local_addr_.sin_port = htons(local_port_);
		local_addr_.sin_addr.s_addr = inet_addr(local_ip_.c_str());

		if (bind(recv_socket_, (SOCKADDR*)&local_addr_, sizeof(local_addr_)) == SOCKET_ERROR)
		{
			AERROR << "Bind Receive Socket To Local Address ERROR = " << WSAGetLastError() << std::endl;
			return false;
		}

		return true;
	}

	bool BaseRecvSocket::IsReceived(const size_t& data_size){
		ptr_recv_buff_ = new char[data_size];
		if (ptr_recv_buff_ == nullptr)
		{
			AERROR << "Receive Buffer New Char Error!" << std::endl;
			return false;
		}

		int remote_addr_size = sizeof(remote_addr_);

		result_ = recvfrom(recv_socket_, ptr_recv_buff_, data_size, 0, (SOCKADDR*)&remote_addr_, &remote_addr_size);

		SOCKADDR_IN* r_addr = (SOCKADDR_IN*)&remote_addr_;
		int r_port = ntohs(r_addr->sin_port);
		std::string r_ip = inet_ntoa(r_addr->sin_addr);

		if (r_port != remote_port_ || r_ip != remote_ip_)
		{
			return false;
		}

		if (result_ == 0)
		{
			return false;
		}
		else if (result_ == SOCKET_ERROR)
		{
			AERROR << "RecvFrom Error" << WSAGetLastError() << std::endl;
			return false;
		}
		else
		{
			return true;

		}


	}



}