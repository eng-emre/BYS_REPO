/*
 * MyButtonController.hpp
 *
 *  Created on: Nov 28, 2024
 *      Author: bu
 */

#ifndef INC_MYBUTTONCONTROLLER_HPP_
#define INC_MYBUTTONCONTROLLER_HPP_

#include <platform/driver/button/ButtonController.hpp>

class MyButtonController : public touchgfx::ButtonController
{
    virtual void init();
    virtual bool sample(uint8_t& key);

private:
    uint8_t previousState;

};

#endif /* INC_MYBUTTONCONTROLLER_HPP_ */
