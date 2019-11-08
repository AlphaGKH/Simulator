#pragma once

#include "common/notation.h"

#include <vector>

namespace simulator {

	class CmdMsg
	{
	public:
		CmdMsg() = default;
		~CmdMsg() = default;

		const unsigned char& gear() const { return gear_; };
		const float& linear_velocity() const { return linear_velocity_; };
		const float& front_wheel_angle() const { return front_wheel_angle_; };
		const bool& lateralctrl_enabled() const { return lateralctrl_enabled_; };
		const bool& longitutdectrl_enabled() const { return longitutdectrl_enabled_; };
		const bool& leftlamp_turnedon() const { return leftlamp_turnedon_; };
		const bool& rightlamp_turnedon() const { return rightlamp_turnedon_; };
		const unsigned short& brake() const { return brake_; }
		const unsigned short& e_stop_limit() const { return e_stop_limit_; }

		void set_gear(const unsigned char& gear) { gear_ = gear; }
		void set_linear_velocity(const float& linear_velocity) { linear_velocity_ = linear_velocity; }
		void set_front_wheel_angle(const float& front_wheel_angle) { front_wheel_angle_ = front_wheel_angle; }
		void set_lateralctrl_enabled(const bool& lateralctrl_enabled) {
			lateralctrl_enabled_ = lateralctrl_enabled;
		}
		void set_longitutdectrl_enabled(const bool& longitutdectrl_enabled) {
			longitutdectrl_enabled_ = longitutdectrl_enabled;
		}
		void set_leftlamp_turnedon(const bool& leftlamp_turnedon) {
			leftlamp_turnedon_ = leftlamp_turnedon;
		}
		void set_rightlamp_turnedon(const bool& rightlamp_turnedon) {
			rightlamp_turnedon_ = rightlamp_turnedon;
		}
		void set_brake(const unsigned short& brake) {
			brake_ = brake;
		}
		void set_e_stop_limit(const unsigned short& e_stop_limit) {
			e_stop_limit_ = e_stop_limit;
		}


	private:
		unsigned char gear_;
		float linear_velocity_;
		float front_wheel_angle_;
		bool lateralctrl_enabled_ = true;
		bool longitutdectrl_enabled_ = true;
		bool leftlamp_turnedon_ = true;
		bool rightlamp_turnedon_ = true;
		unsigned short brake_;
		unsigned short e_stop_limit_;


	};

}
