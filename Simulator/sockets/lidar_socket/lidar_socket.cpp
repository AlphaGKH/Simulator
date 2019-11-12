#include "sockets/lidar_socket/lidar_socket.h"

#include "common/mlog/mlog.h"
#include "common/notation.h"

namespace simulator{
	LidarSocket::LidarSocket(const std::string local_ip, const int& local_port,
		const std::string& remote_ip, const int& remote_port) :
		BaseRecvSocket(local_ip, local_port, remote_ip, remote_port){}

	LidarSocket::LidarSocket(const int& local_port, const int& remote_port) :
		BaseRecvSocket(local_port, remote_port){}

	bool LidarSocket::OnReceive(const size_t& lidar_pack_size, LidarMsg* lidar_msg){
		if (!IsReceived(lidar_pack_size))
		{
			AERROR << "Do not Receive Any Lidar Message!" << std::endl;
			return false;
		}

		std::vector<float> distance;
		distance.clear();
		int max_lidar_point = SCAN_ANGLE / SCAN_ANGLE_RESOLUTION + 1;
		distance.reserve(max_lidar_point);

		float number = max_lidar_point * sizeof(float);
		if (result_ == number)
		{
			for (unsigned int i = 0; i < result_ / sizeof(float); i++)
			{
				float value = *(float*)(ptr_recv_buff_ + i * sizeof(float));
				distance.emplace_back(value);
			}
			lidar_msg->set_distance_points(distance);
			return true;
		}
		return false;

	}
}