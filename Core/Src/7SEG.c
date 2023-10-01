/*
 * 7SEG.c
 *
 *  Created on: Sep 20, 2023
 *      Author: ADMIN
 */
#include "7SEG.h"
#include "main.h"
GPIO_TypeDef* SEG_GPIO_Port = GPIOB; // GPIO port for the 7-segment display
uint16_t SEG_Pin[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6};
// Define patterns for displaying digits (common athode 7-segment display)
uint8_t SEG_Patterns[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // 0 to 9 patterns
void display7SEG(int num){
    if (num >= 0 && num <= 9) {
        // Turn off all segments (set them LOW for common anode)
        HAL_GPIO_WritePin(SEG_GPIO_Port, GPIO_PIN_All, GPIO_PIN_RESET);

        // Set the pattern for the selected digit (set corresponding segments HIGH)
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[0], !(SEG_Patterns[num] & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[1], !((SEG_Patterns[num] >> 1) & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[2], !((SEG_Patterns[num] >> 2) & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[3], !((SEG_Patterns[num] >> 3) & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[4], !((SEG_Patterns[num] >> 4) & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[5], !((SEG_Patterns[num] >> 5) & 0x01));
        HAL_GPIO_WritePin(SEG_GPIO_Port, SEG_Pin[6], !((SEG_Patterns[num] >> 6) & 0x01));
    }

}
