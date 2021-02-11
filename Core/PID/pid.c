/*
 * pic.c
 *
 *  Created on: Feb 28, 2020
 *      Author: Kacper
 */

#include "pid.h"

/**
  * @brief  Inicjalizacja parametrów regulatora.
  *
  * @note   Funckcja służy do inicjalizacji parametrów reguatroa
  *
  *
  *
  * @param  pid - wskaźnik na strukturę przechowującą wartości związane z regulatorem
  * @param  P - wzmocnienie członu P
  * @param  I - wzmocnienie członu I
  * @param 	D - wzmocnienie członu D
  * @param  Kb - wzmocnienie członu antiwindup
  * @param 	Ts - czas próbkowania
  * @param 	rate - maksymalny przyrost wyjścia
  * @param 	deadzone - martwa strefa uchybu
  * @param 	min - minimalna wartośc wyjścia
  * @param 	max - maksymalna wartość wyjścia
  * @param 	output_offset - offset wyjścia
  * @param 	input_offset - offset wejścia
  *
  * @retval None
  */
void PID_Init (PID_t *pid,
				float P, float I, float Kb, float Ts,
				float deadzone, float min, float max,
				float output_offset, float input_offset){
	pid -> Kp = P;
	pid -> Ti = I;
	pid -> Ts = Ts;
	pid -> output_min = min;
	pid -> output_max = max;
	pid -> Kb = Kb;
	pid -> output_offset = output_offset;
	pid -> input_offset = input_offset;
	pid -> error_deadzone = deadzone;
}

void PID_Controller (PID_t *pid){
	pid->input = pid->input_raw - pid->input_offset;
	if(pid->run){
		//Obliczenie uchybu sterowania
		pid->error_dz = pid->reference - (pid->input);
		if(pid->error_deadzone){
			if((pid->error_dz < pid->error_deadzone) && (pid->error_dz > -pid->error_deadzone)){
				pid->error = 0.0;
			}else pid->error = pid->error_dz;
		}
		pid->P = pid->Kp * pid->error;
		if(pid->Ti){
			pid->I += (pid->error + pid->antiwindup_correction)*pid->Ts*pid->Ti;
		}else{
			pid->I = 0;
		}
		//obliczenie wyjścia
		pid->output_sat = pid->P + pid->I;

	}else{
		pid->output_sat = 0;
	}
	//Dodanie przesunięcia do wyjścia
	pid -> output_sat += pid -> output_offset;
	//Saturacja wyjścia, jeśli istnieją ograniczenia
	if(pid->output_sat < pid->output_min) pid->output = pid->output_min;
	else if(pid->output_sat > pid->output_max) pid->output = pid->output_max;
	else pid->output = pid->output_sat;
	//Zapamiętanie poprzednich wartości
	pid->antiwindup_correction = pid->Kb * (pid->output - pid->output_sat);
	pid->last_error = pid->error_dz;
}

void PID_TurnOn (PID_t *pid){
	pid->run = 1;
}

void PID_TurnOff (PID_t *pid){
	pid->I = 0;
	pid->antiwindup_correction = 0;
	pid->error = 0;
	pid->error_dz = 0;
	pid->last_error = 0;
	pid->reference = 0;
	pid->output_sat = 0;
	pid->output = pid->output_offset;
	pid->run = 0;
}

uint8_t PID_Running (PID_t *pid){
	return pid->run;
}

void PID_Input(PID_t *pid, float in){
	pid -> input_raw = in;
}

float PID_Out(PID_t* pid){
	return pid -> output;
}
