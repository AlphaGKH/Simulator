#include "common/mlog/mlog.h"
#include "common/mtime/mtime.h"
#include "threads/chassis_thread/chassis_thread.h"
#include "msgs/simulator/ChassisLcmType.hpp"



namespace simulator {
	ChassisThread::ChassisThread(const std::string& lcm_channel)
		: BaseThread(lcm_channel)
	{
		chassis_socket_ = std::make_unique<ChassisSocket>(CHASSIS_LOCAL_PORT, CHASSIS_REMOTE_PORT);
		lcm_ = std::make_unique<lcm::LCM>();
		is_inited_ = true;
		if ((!chassis_socket_->Init()) || (!lcm_->good()))
		{
			is_inited_ = false;
		}
	}

	void ChassisThread::CallBackFunction() {
		kSleepTime_ = CHASSIS_THREAD_CYCLE;
		while (!is_stoped_)
		{
			std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(kSleepTime_));
			std::lock_guard<std::mutex> lock(base_mutex_);
			if (!chassis_socket_->OnReceive(CHASSIS_BUFF_MAX_SIZE, &chassis_msg_)) {
				continue;
			}

			ChassisLcmType chassis_lcm_data;
			chassis_lcm_data.timestamp = common::mtime::GetCurrentTimeSec();
			chassis_lcm_data.x = chassis_msg_.x();
			chassis_lcm_data.y = chassis_msg_.y();
			chassis_lcm_data.theta = chassis_msg_.theta();
			chassis_lcm_data.linear_velocity = chassis_msg_.linear_velocity();
			chassis_lcm_data.linear_acceleration = chassis_msg_.linear_acceleration();
			chassis_lcm_data.kappa = chassis_msg_.kappa();
			lcm_->publish(lcm_channel_, &chassis_lcm_data);
		}
	}
}