/* Copyright (c) 2017 STMicroelectronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/****************************************************
*             RAPID PROTOTYPING WITH NUCLEO         *
* Example Code 30: Thermistor NTC B3950             *
* Author: Mauro D'Angelo                            *
* Organization: Perlatecnica APS ETS                *
*****************************************************/

#include "mbed.h"
#include "NTC_B3950.h"


// It creates an instance of the class Serial. 'pc' is the name of the variable and assign the TX and RX pin to it
UnbufferedSerial pc(USBTX, USBRX);


// It create an instance
NTC_B3950 *termistor = new NTC_B3950(A1, 10000);

// Entry point
int main() {
  // Print to the serial console a string
  printf("Hello World thermistor!\r\n");

  while(true){
	  printf("The temperature is %f !\r\n", termistor->getTemperature());
	  // Wait for 1s before reading temperature
	  ThisThread::sleep_for(1000ms);
  }
}

