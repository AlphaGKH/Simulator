#pragma once

#include <thread>
#include <memory>
#include <mutex>
#include <string>

#include <lcm/lcm-cpp.hpp>

namespace simulator{

	class BaseThread
	{
	public:
		BaseThread(const std::string& lcm_channel);
		virtual ~BaseThread();

	public:
		bool Start();
		void Stop();

	protected:
		virtual void CallBackFunction() = 0;

	protected:
		bool is_inited_ = false;
		bool is_stoped_ = false;
		int kSleepTime_ = 50;// ms
		std::unique_ptr<std::thread>  thread_;
		
		std::mutex base_mutex_;

		std::string lcm_channel_;
		std::unique_ptr<lcm::LCM> lcm_;

	};




}
