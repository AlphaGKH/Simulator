#pragma once

namespace simulator{

	// vehicle param
#define WHEEL_BASE 4.0
	// lidar
#define SCAN_ANGLE     190
#define SCAN_DISTANCE  40
#define SCAN_ANGLE_RESOLUTION 0.25
#define NUMBER_LIDAR_POINT SCAN_ANGLE / SCAN_ANGLE_RESOLUTION + 1

#define LIDAR_LOCAL_PORT 9000
#define LIDAR_LOCAL_IP "127.0.0.1"

#define LIDAR_REMOTE_PORT 9500
#define LIDAR_REMOTE_IP "127.0.0.1"

	// chassis

#define CHASSIS_LOCAL_PORT 5005
#define CHASSIS_LOCAL_IP "127.0.0.1"

#define CHASSIS_REMOTE_PORT 5012
#define CHASSIS_REMOTE_IP "127.0.0.1"

}
