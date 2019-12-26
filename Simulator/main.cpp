#include <iostream>

#include "threads/lidar_thread/lidar_thread.h"
#include "threads/chassis_thread/chassis_thread.h"
#include "threads/cmd_thread/cmd_thread.h"

int main(){

	// reveive lidar msg from vrep by socket and send them by lcm
	simulator::LidarThread lidar_thread(LIDAR_LCM_CHANNEL);
	lidar_thread.Start();

	// reveive chassis msg from vrep by socket and send them by lcm
	simulator::ChassisThread chassis_thread(CHASSIS_LCM_CHANNEL);
	chassis_thread.Start();

	// subscribe command msg by lcm and send them to vrep by socket
	simulator::CmdThread cmd_thread(CMD_LCM_CHANNEL);
	cmd_thread.Start();
}