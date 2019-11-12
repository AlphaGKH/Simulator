#include "sockets/chassis_socket/chassis_socket.h"

#include "common/mlog/mlog.h"
#include "common/notation.h"
#include "common/basicfunction.h"

namespace simulator{
	ChassisSocket::ChassisSocket(const std::string local_ip, const int& local_port,
		const std::string& remote_ip, const int& remote_port) :
		BaseRecvSocket(local_ip, local_port, remote_ip, remote_port){}

	ChassisSocket::ChassisSocket(const int& local_port, const int& remote_port) :
		BaseRecvSocket(local_port, remote_port){}

	bool ChassisSocket::OnReceive(const size_t& chassis_pack_size, ChassisMsg* chassis_msg){
		if (!IsReceived(chassis_pack_size))
		{
			AERROR << "Do not Receive Any Chassis Message!" << std::endl;
			return false;
		}
		ChassisDataAnlysis(chassis_msg);
		return true;




	}

	void ChassisSocket::ChassisDataAnlysis(ChassisMsg* chassis_msg){
		bool HeadFlag = false;
		bool TailFlag = false;
		unsigned char ucHeadNo = 0;
		unsigned char ucTailNo = 0;
		char cCheckSum = 0;

		int i = 0;

		for (i = 0; i < result_; ++i)
		{
			if ('$' == ptr_recv_buff_[i]) // find the message head '$', mark its index to ucHeadNo
			{
				HeadFlag = true;
				ucHeadNo = i;
				TailFlag = false;
				cCheckSum = ptr_recv_buff_[i];
			}

			if (HeadFlag)
			{
				if ('*' == ptr_recv_buff_[i]) // find the message tail '*', mark its index to ucTailNo
				{
					TailFlag = true;
					ucTailNo = i;
					HeadFlag = false;
				}

				if (TailFlag)
				{
					char cTemp1 = 0;
					char cTemp2 = 0;
					cTemp1 = ((cCheckSum >> 4) & 0x0F);
					cTemp2 = (cCheckSum & 0x0F);
					if (cTemp1 < 10)
					{
						cTemp1 += '0';
					}
					else
					{
						cTemp1 += 'A' - 10;
					}

					if (cTemp2 < 10)
					{
						cTemp2 += '0';
					}
					else
					{
						cTemp2 += 'A' - 10;
					}
					// check success
					if ((cTemp1 == ptr_recv_buff_[ucTailNo + 1]) & (cTemp2 == ptr_recv_buff_[ucTailNo + 2]))
					{
						int k = 0;
						char cDataTemp[30];
						int CommaNumber = 0;
						memset(cDataTemp, 0, 30);
						// Find header : NETVSTA
						if (('N' == ptr_recv_buff_[ucHeadNo + 1]) & ('E' == ptr_recv_buff_[ucHeadNo + 2]) &
							('T' == ptr_recv_buff_[ucHeadNo + 3]) & ('V' == ptr_recv_buff_[ucHeadNo + 4]) &
							('S' == ptr_recv_buff_[ucHeadNo + 5]) & ('T' == ptr_recv_buff_[ucHeadNo + 6]) &
							('A' == ptr_recv_buff_[ucHeadNo + 7]))
						{
							for (int j = ucHeadNo + 9; j < ucTailNo; j++)
							{
								if (',' == ptr_recv_buff_[j])
								{
									k = 0;
									CommaNumber++;

									switch (CommaNumber)
									{
									case 1:{}
										memset(cDataTemp, 0, 30);
										break;
									case 2:{
											   chassis_msg->set_x(atof(cDataTemp));
									}
										memset(cDataTemp, 0, 30);
										break;
									case 3:{
											   chassis_msg->set_y(atof(cDataTemp));
									}
										memset(cDataTemp, 0, 30);
										break;
									case 4:{
											   chassis_msg->set_linear_velocity(atof(cDataTemp));
									}
										memset(cDataTemp, 0, 30);
										break;
									case 5:{}
										memset(cDataTemp, 0, 30);
										break;
									case 6:{
											   float kappa;
											   float front_wheel_angle = atof(cDataTemp);//(degree)
											   if (front_wheel_angle < 0.03)
											   {
												   kappa = 0.0;
											   } 
											   else
											   {
												   kappa = atan(front_wheel_angle) / WHEEL_BASE;
											   }
											   chassis_msg->set_kappa(kappa);
									}
										memset(cDataTemp, 0, 30);
										break;
									case 7:{
											   float heading = atof(cDataTemp);
											   float theta = M_PI / 2 - heading;
											   theta = unifytheta(theta);
											   chassis_msg->set_theta(theta);
									}
										memset(cDataTemp, 0, 30);
										break;
										
									default:
										break;
									}
								}

								else
								{
									if (CommaNumber < 12)
									{
										if (k < 28)
											cDataTemp[k++] = ptr_recv_buff_[j];
										else
											k = 0;
									}
								}
							}
						}
					}
				}
				else
				{
					cCheckSum ^= ptr_recv_buff_[i];
				}
			}
		}
		return;
	}

}