#pragma once

#include "threads/base_thread.h"
#include "sockets/lidar_socket/lidar_socket.h"
#include "common/notation.h"
#include "common/types/lidar_msg.h"


namespace simulator{
	class LidarThread : public BaseThread
	{
	public:
		LidarThread(const std::string& lcm_channel);
		~LidarThread() override = default;
	protected:
		void CallBackFunction() override;

	private:
		LidarMsg lidar_msg_;
		std::unique_ptr<LidarSocket> lidar_socket_;

	};




}
