#include "sockets/cmd_socket/cmd_socket.h"

#include "common/mlog/mlog.h"
#include "common/basicfunction.h"


namespace simulator{
	CmdSocket::CmdSocket(const std::string local_ip, const int& local_port,
		const std::string& remote_ip, const int& remote_port) :
		BaseSendSocket(local_ip, local_port, remote_ip, remote_port){}

	CmdSocket::CmdSocket(const int& local_port, const int& remote_port) :
		BaseSendSocket(local_port, remote_port){}

	void CmdSocket::Send(const CmdMsg& cmd_msg) {
		Convert2CharArray(cmd_msg);
		BaseSendSocket::Send(send_buff_);
	}

	void CmdSocket::Convert2CharArray(const CmdMsg& cmd_msg) {
		_uintbyte uibtemp;
		_intbyte ibtemp;

		unsigned char ucTXData[13];
		memset(ucTXData, 0, 13);					
		ucTXData[0] = 0xFF;						
		ucTXData[1] = 0xFF;						
		ucTXData[2] = 0xFF;	

		if (cmd_msg.gear() == 2) // R
		{
			ucTXData[3] = 2;
		} 
		else if(cmd_msg.gear() == 1) // D
		{
			ucTXData[3] = 1;
		}
		else                         // N
		{
			ucTXData[3] = 0;
		}

		// steering direction
		if (cmd_msg.front_wheel_angle() > 0)
		{
			ucTXData[3] |= 0x04;
		} 
		else
		{
			ucTXData[3] &= 0xFB;
		}
		
		// lat control enable
		if (cmd_msg.lateralctrl_enabled())
		{
			ucTXData[3] |= 0x08;
		} 
		else
		{
			ucTXData[3] &= 0xF7;
		}

		// long control enable
		if (cmd_msg.longitutdectrl_enabled())
		{
			ucTXData[3] |= 0x10;
		} 
		else
		{
			ucTXData[3] &= 0xEF;
		}

		// left turn lamp on
		if (cmd_msg.leftlamp_turnedon())
		{
			ucTXData[3] |= 0x40;
		} 
		else
		{
			ucTXData[3] &= 0xBF;
		}

		// right turn lamp on
		if (cmd_msg.rightlamp_turnedon())
		{
			ucTXData[3] |= 0x20;
		} 
		else
		{
			ucTXData[3] &= 0xDF;
		}

		// steering angel value
		uibtemp._uint = RoundNum(std::fabs(cmd_msg.front_wheel_angle()) * 100);
		ucTXData[4] = uibtemp._uchar[1];
		ucTXData[5] = uibtemp._uchar[0];

		// velocity control value
		ibtemp._int = RoundNum(std::fabs(cmd_msg.linear_velocity()) * 100);
		if (cmd_msg.gear() == 2)
		{
			ibtemp._int = -ibtemp._int;
		}
		ucTXData[6] = ibtemp._char[1];
		ucTXData[7] = ibtemp._char[0];

		// break control value
		uibtemp._uint = cmd_msg.brake();
		ucTXData[8] = uibtemp._uchar[1];
		ucTXData[9] = uibtemp._uchar[0];

		// e stop limit
		uibtemp._uint = cmd_msg.e_stop_limit();
		ucTXData[10] = uibtemp._uchar[1];
		ucTXData[11] = uibtemp._uchar[0];

		// check sum
		for (int i = 1; i < 12; i++)
		{
			ucTXData[12] ^= ucTXData[i];
		}
		ucTXData[12] &= 0x7F;

		send_buff_ = (char*)ucTXData;
		return;
	}

}