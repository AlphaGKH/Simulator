#pragma once

#include "common/notation.h"

#include <vector>

namespace simulator{

class ChassisMsg
{
public:
	ChassisMsg() = default;
	~ChassisMsg() = default;

	const float& x() const { return x_; }
	const float& y() const { return y_; }
	const float& theta() const { return theta_; }
	const float& linear_velocity() const { return linear_velocity_; }
	const float& linear_acceleration() const { return linear_acceleration_; }
	const float& kappa() const { return kappa_; }

	void set_x(const float& x) { x_ = x; }
	void set_y(const float& y) { y_ = y; }
	void set_theta(const float& theta) { theta_ = theta; }
	void set_linear_velocity(const float& linear_velocity) { linear_velocity_ = linear_velocity; }
	void set_linear_acceleration(const float& linear_acceleration) { linear_acceleration_ = linear_acceleration; }
	void set_kappa(const float& kappa) { kappa_ = kappa; }

	void copyFrom(const ChassisMsg& other) {
		x_ = other.x();
		y_ = other.y();
		theta_ = other.theta();
		linear_velocity_ = other.linear_velocity();
		linear_acceleration_ = other.linear_acceleration();
		kappa_ = other.kappa();
	}
	


private:
	float x_; // east_pos
	float y_; // north_pose
	float theta_; // angle from east(0), to north(90), to west(180/-180), to south(-90)
	float linear_velocity_;
	float linear_acceleration_;
	float kappa_;

};

}
