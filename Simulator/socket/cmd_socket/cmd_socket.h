#pragma once

#include "socket/base_send_socket.h"

#include "common/types/cmd_msg.h"

namespace simulator{

	class CmdSocket : public BaseSendSocket
	{
	public:
		CmdSocket(const std::string local_ip, const int& local_port,
			const std::string& remote_ip, const int& remote_port);
		CmdSocket(const int& local_port, const int& remote_port);

		~CmdSocket() = default;

	private:
		union _uintbyte
		{
			unsigned short _uint;
			unsigned char _uchar[2];
		};

		union _intbyte
		{
			short _int;
			char _char[2];
		};

	public:
		void Send(const CmdMsg& cmd_msg);

	private:
		void Convert2CharArray(const CmdMsg& cmd_msg);

	private:
		char* send_buff_ = nullptr;

	};
}