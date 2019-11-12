#include "threads/base_thread.h"

#include "common/mlog/mlog.h"

namespace simulator {
	BaseThread::BaseThread(const std::string& lcm_channel)
		: lcm_channel_(lcm_channel){}

	BaseThread::~BaseThread()
	{
	}

	bool BaseThread::Start() {
		if (!is_inited_)
		{
			AERROR << "This Thread has not been initiated." << std::endl;
			return false;
		}
		thread_.reset(new std::thread(&BaseThread::CallBackFunction, this));
		return true;
	}

	void BaseThread::Join() {
		if (thread_ && thread_->joinable()) {
			thread_->join();
		}
	}

	void BaseThread::Stop() {
		is_stoped_ = true;
		if (thread_ && thread_->joinable()) {
			thread_->join();
		}
	}

}