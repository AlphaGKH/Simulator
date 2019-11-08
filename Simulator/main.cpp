#include <iostream>

#include "socket/lidar_socket/lidar_socket.h"
#include "socket/chassis_socket/chassis_socket.h"
#include "common/notation.h"
#include "common/basicfunction.h"

#include <thread>

int main(){

	simulator::LidarMsg lidar_msg;
	simulator::LidarSocket lidarsocket(LIDAR_LOCAL_PORT, LIDAR_REMOTE_PORT);
	lidarsocket.Init();

	simulator::ChassisMsg chassis_msg;
	simulator::ChassisSocket chassissocket(CHASSIS_LOCAL_PORT, CHASSIS_REMOTE_PORT);
	chassissocket.Init();

	std::cout << std::this_thread::get_id() << std::endl;

	while (true)
	{
		lidarsocket.OnReceive(6010, &lidar_msg);
		chassissocket.OnReceive(6010, &chassis_msg);
	}

	std::cout << "hello, world!" << std::endl;
}