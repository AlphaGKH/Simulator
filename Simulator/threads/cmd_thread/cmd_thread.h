#pragma once

#include "threads/base_thread.h"
#include "sockets/cmd_socket/cmd_socket.h"
#include "common/types/cmd_msg.h"
#include "msgs/simulator/CMDLcmType.hpp"

namespace simulator {

	class CmdThread : public BaseThread
	{
	public:
		CmdThread(const std::string& lcm_channel);
		~CmdThread() override = default;

	protected:
		void CallBackFunction() override;
		void HandleLcmMsg(const lcm::ReceiveBuffer *rbuf, const std::string &chan, const CMDLcmType *cmd_data);

	protected:
		CmdMsg cmd_msg_;
		std::unique_ptr<CmdSocket> cmd_socket_;

	};




}
