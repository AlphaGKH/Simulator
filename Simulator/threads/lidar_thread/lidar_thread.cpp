#include "common/mlog/mlog.h"
#include "common/mtime/mtime.h"
#include "threads/lidar_thread/lidar_thread.h"
#include "msgs/simulator/LidarLcmType.hpp"

namespace simulator {
	LidarThread::LidarThread(const std::string& lcm_channel)
		: BaseThread(lcm_channel)
	{
		lidar_socket_ = std::make_unique<LidarSocket>(LIDAR_LOCAL_PORT, LIDAR_REMOTE_PORT);
		lcm_ = std::make_unique<lcm::LCM>();
		is_inited_ = true;
		if ((!lidar_socket_->Init()) || (!lcm_->good()))
		{
			is_inited_ = false;
		}
	}

	void LidarThread::CallBackFunction() {
		kSleepTime_ = LIDAR_THREAD_CYCLE;
		while (!is_stoped_)
		{
			std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(kSleepTime_));
			std::lock_guard<std::mutex> lock(base_mutex_);
			lidar_socket_->OnReceive(LIDAR_BUFF_MAX_SIZE, &lidar_msg_);

			LidarLcmType lidar_lcm_data;
			size_t number = lidar_msg_.distance_points().size();
			lidar_lcm_data.timestamp = common::mtime::GetCurrentTimeSec();
			lidar_lcm_data.point_number = number;
			for (const auto& point : lidar_msg_.distance_points())
			{
				lidar_lcm_data.distance_points.emplace_back(point);
			}
			lcm_->publish(lcm_channel_, &lidar_lcm_data);
		}
	}
}