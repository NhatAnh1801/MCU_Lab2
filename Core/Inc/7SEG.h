/*
 * 7SEG.h
 *
 *  Created on: Oct 1, 2023
 *      Author: ADMIN
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_

int index_led;
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer(hour,minute);

#endif /* INC_7SEG_H_ */
