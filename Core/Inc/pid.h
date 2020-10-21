/*
 * pid.h
 *
 *  Created on: Feb 28, 2020
 *      Author: Kacper
 */

#include "stm32f3xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
	// Jeśli 1, regulator działa, jeśli 0, nie
	uint8_t run;

	// Nastawy regulatora
	float Kp; 	// Wzmocnienie członu P
	float Ti; 	// Wzmocnienie członu I
	float Ts; 	// Czas próbkowania
	float Kb; 	// Wzmocnienie w torze antywindup

	float P; 	// Wartość wyjściowa członu P
	float I; 	// Wartość wyjściowa członu I

	float reference; 	// Wartość zadana regulatora
	float input;		// Wejście regulatora z dodanym offsetem
	float input_raw;	// Wejście regulator bez offsetu
	float error;		// Uchyb sterowania z uwzględnieniem martwej strefy
	float error_dz;		// Uchyb sterowania bez uwzględnienia martwej strefy
	float last_error;	// Poprzedni uchyb
	float output_sat;	// Wyjście regulatora przed saturacją
	float output;		// Wyjście regulatora po saturacji

	float input_offset;				// Przesunięcie zera wejścia regulatora
	float output_min;				// Minimalna wartość wyjścia regulatora
	float output_max;				// Maksymalna wartość wyjścia regulatora
	float error_deadzone;			// Martwa strefa uchybu
	float antiwindup_correction;	// Korekcja antywindup
	float output_offset;			// Przesunięcie zera wyjścia regulatora
} PID_Data;

void PID_Init (PID_Data *pid, float P, float I, float Kb, float Ts, float deadzone, float min, float max, float output_offset, float input_offset);

void PID_Controller (PID_Data *pid);

void PID_TurnOn (PID_Data *pid);

void PID_TurnOff (PID_Data *pid);

uint8_t PID_Running (PID_Data *pid);
