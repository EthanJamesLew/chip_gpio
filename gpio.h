/*
gpio.h

Author: Ethan Lew

This file contains a functional, bash-like interface to NextThing's CHIP GPIO pins. 
*/

#ifndef _GPIO_H
#define _GPIO_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string>
#include <sstream>
#include <iostream>

namespace gpio
{
	void enable(int);
	void disable(int);
	void mode(int, std::string);
	void mode(int, int);
	void write(int, int);
	void read();
	void _checkPinNum(int);
}
#endif
