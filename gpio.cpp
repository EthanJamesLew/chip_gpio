#include "gpio.h"

/*patch addresses a known issue in the g++ compiler.
to_string does not exist.
*/
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}


namespace gpio
{


	void enable(int pinNum)
	{
		_checkPinNum(pinNum);
		int pinAddr = 408 + pinNum;
		std::string command = "sudo sh -c 'echo " + patch::to_string(pinAddr) + " > /sys/class/gpio/export'";
		system(command.c_str());
	}

	void disable(int pinNum)
	{
		_checkPinNum(pinNum);
		int pinAddr = 408 + pinNum;
		std::string command = "sudo sh -c 'echo " + patch::to_string(pinAddr) + " > /sys/class/gpio/unexport";
		system(command.c_str());
	}

	void mode(int pinNum, std::string mode)
	{
		_checkPinNum(pinNum);
		std::string comMode = "";
		if (mode == "IN" || mode == "in")
		{
			comMode = "in";
		}
		else if (mode == "OUT" || mode == "out")
		{
			comMode = "out";
		}
		else
		{
			fprintf(stderr, "%s is not a valid mode. Use {0, IN, in} or {1, OUT, out}.", mode.c_str());
			exit(-1);
		}

		int pinAddr = 408 + pinNum;
		std::string command = "sudo sh -c 'echo " + patch::to_string(comMode) +" > /sys/class/gpio/gpio"+ patch::to_string(pinAddr)+"/direction'";
		std::cout << command << std::endl;
		system(command.c_str());
	}

	void mode(int pinNum, int modeNum)
	{
		if (modeNum == 0)
		{
			mode(pinNum, "in");
		}
		else if (modeNum == 1)
		{
			mode(pinNum, "out");
		}
		else
		{
			fprintf(stderr, "%d is not a valid mode. Use {0, IN, in} or {1, OUT, out}.", modeNum);
			exit(-1);
		}
	}

	void write(int pinNum, int out)
	{
		_checkPinNum(pinNum);

		int pinAddr = 408 + pinNum;
		std::string command = "sudo sh -c 'echo " + patch::to_string(out) + " > /sys/class/gpio/gpio" + patch::to_string(pinAddr) + "/value'";
		system(command.c_str());
	}

	void read()
	{

	}

	void _checkPinNum(int pinNum)
	{
		if (pinNum < 0 | pinNum > 8)
		{
			fprintf(stderr, "Pin %d is not a valid pin. [1...8]", pinNum);
			exit(-1);
		}
	}
}