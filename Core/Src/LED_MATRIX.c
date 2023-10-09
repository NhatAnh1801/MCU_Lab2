/*
 * LED_MATRIX.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "LED_MATRIX.h"
#include "main.h"

GPIO_TypeDef* LED_MATRIX_GPIO_Port = GPIOB;
GPIO_TypeDef* LED_MATRIX_A_GPIO_Port = GPIOA;
uint16_t COL_Pin[] = {GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
uint16_t ROW_Pin[] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {0x18,0x24,0x24,0x42,0x7e,0x42,0x42,0x42}; // character A

void displayLEDMATRIX (int index){
    uint8_t pattern = matrix_buffer[index];
    for (int i = 0; i < MAX_LED_MATRIX; i++) {
        uint8_t mask = 1 << i; // Create a mask with a 1 at the ith bit

        if (pattern & mask) {
            // If the ith bit is 1, turn on the corresponding column
            HAL_GPIO_WritePin(LED_MATRIX_A_GPIO_Port, COL_Pin[i], GPIO_PIN_RESET);
        } else {
            // If the ith bit is 0, turn off the corresponding column
            HAL_GPIO_WritePin(LED_MATRIX_A_GPIO_Port, COL_Pin[i], GPIO_PIN_SET);
        }
    }
}
void updateLEDMatrix(int index){
	for(int i = 0;i < MAX_LED_MATRIX;i++){
		if(i == index){
			HAL_GPIO_WritePin(LED_MATRIX_GPIO_Port,ROW_Pin[i],0);
		}
		else{
			HAL_GPIO_WritePin(LED_MATRIX_GPIO_Port,ROW_Pin[i],1);
		}
	}
	displayLEDMATRIX(index);
}
void LEDMatrix_Run(){
	updateLEDMatrix(index_led_matrix++);
	if(index_led_matrix >= MAX_LED_MATRIX) index_led_matrix = 0;
}
void shiftLeftMatrix() {
      for (int i = 0; i < MAX_LED_MATRIX; i++) {
		if (matrix_buffer[i] & 1) {
			matrix_buffer[i] >>=1;
			matrix_buffer[i] |= 0x80;
		}
		else matrix_buffer[i] >>= 1 ;
      }
}
//          00001100
