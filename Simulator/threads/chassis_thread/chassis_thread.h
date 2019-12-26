#pragma once

#include "threads/base_thread.h"
#include "sockets/chassis_socket/chassis_socket.h"
#include "common/notation.h"
#include "common/types/chassis_msg.h"


namespace simulator {
	class ChassisThread : public BaseThread
	{
	public:
		ChassisThread(const std::string& lcm_channel);
		~ChassisThread() override = default;

	protected:
		void CallBackFunction() override;

	private:
		ChassisMsg chassis_msg_;
		std::unique_ptr<ChassisSocket> chassis_socket_;

	};




}
