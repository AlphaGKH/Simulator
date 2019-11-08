#pragma once

#include "common/notation.h"

#include <vector>

namespace simulator{

class LidarMsg
{
public:
	LidarMsg() = default;
	~LidarMsg() = default;

	void set_distance_points(const std::vector<float>& distance_points){
		distance_points_ = distance_points;
	}

	const std::vector<float>& distance_points() const { return distance_points_; }

private:
	std::vector<float> distance_points_;
	

};

}
