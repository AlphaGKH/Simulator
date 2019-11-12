#include <iostream>

#include "threads/lidar_thread/lidar_thread.h"
#include "threads/chassis_thread/chassis_thread.h"
#include "threads/cmd_thread/cmd_thread.h"

int main(){
	simulator::LidarThread lidar_thread(LIDAR_LCM_CHANNEL);
	lidar_thread.Start();

	simulator::ChassisThread chassis_thread(CHASSIS_LCM_CHANNEL);
	chassis_thread.Start();

	simulator::CmdThread cmd_thread(CMD_LCM_CHANNEL);
	cmd_thread.Start();


	chassis_thread.Join();
	lidar_thread.Join();
	cmd_thread.Join();
}