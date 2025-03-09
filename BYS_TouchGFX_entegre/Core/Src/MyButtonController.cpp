/*
 * MybuttonController.cpp
 *
 *  Created on: Nov 28, 2024
 *      Author: bu
 */

#include <MyButtonController.hpp>
#include <main.h>
#include <touchgfx/hal/HAL.hpp>

extern "C" {
	extern uint8_t User_ButtonState1;
	extern uint8_t User_ButtonState2;
}

void MyButtonController::init()
{
//	previousState = 0xFF;
}

bool MyButtonController::sample(uint8_t& key)
{


    	if(User_ButtonState2)
	{
    		User_ButtonState2 = 0x00;
	        key = 0;
	        return true;

    }
    	if(User_ButtonState1)
       {
       		User_ButtonState1 = 0x00;
   	        key = 1;
   	        return true;
       }
 	return false;
}