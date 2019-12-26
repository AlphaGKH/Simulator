#include "threads/cmd_thread/cmd_thread.h"

#include "common/mlog/mlog.h"

namespace simulator {
	CmdThread::CmdThread(const std::string& lcm_channel)
		: BaseThread(lcm_channel)
	{
		cmd_socket_ = std::make_unique<CmdSocket>(CMD_LOCAL_PORT, CMD_REMOTE_PORT);
		lcm_ = std::make_unique<lcm::LCM>();
		is_inited_ = true;
		if ((!cmd_socket_->Init()) || (!lcm_->good()))
		{
			is_inited_ = false;
		}
		else
		{
			lcm_->subscribe(lcm_channel_, &CmdThread::HandleLcmMsg, this);
		}

	}

	void CmdThread::CallBackFunction() {
		kSleepTime_ = CMD_THREAD_CYCLE;
		while ((!is_stoped_) && (0 == lcm_->handle()))
		{
			std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(kSleepTime_));
			std::lock_guard<std::mutex> lock(base_mutex_);
			cmd_socket_->Send(cmd_msg_);
		}
	}

	void CmdThread::HandleLcmMsg(const lcm::ReceiveBuffer *rbuf,
		const std::string &chan,
		const CMDLcmType *cmd_data) {
		std::lock_guard<std::mutex> lock(base_mutex_);
		cmd_msg_.set_gear(cmd_data->gear);
		cmd_msg_.set_linear_velocity(cmd_data->linear_velocity);
		cmd_msg_.set_front_wheel_angle(cmd_data->front_wheel_angle);
		cmd_msg_.set_lateralctrl_enabled(cmd_data->lateralctrl_enabled);
		cmd_msg_.set_longitutdectrl_enabled(cmd_data->longitutdectrl_enabled);
		cmd_msg_.set_leftlamp_turnedon(cmd_data->leftlamp_turnedon);
		cmd_msg_.set_rightlamp_turnedon(cmd_data->rightlamp_turnedon);
		cmd_msg_.set_brake(cmd_data->brake);
		cmd_msg_.set_e_stop_limit(cmd_data->e_stop_limit);
	}


}