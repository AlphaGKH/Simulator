#include "common/basicfunction.h"

namespace simulator {
	float unifytheta(float theta)
	{
		while (theta < 0)
			theta = theta + 2 * M_PI;
		while (theta >= 2 * M_PI)
			theta = theta - 2 * M_PI;

		return theta;
	}

	int RoundNum(const double x) {
		double ceil_number = ceil(x);
		double floor_number = floor(x);
		double mid_number = (ceil_number + floor_number) / 2;
		return int(x >= mid_number ? ceil_number : floor_number);
	}
}