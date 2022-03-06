/* Copyright (c) 2022 Perlatecnica
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



#include "NTC_B3950.h"

/***
 * Constructor
 * pADCpin is the ADC pin name
 * pSerialResistance is the Serial Resistance value [ohm]
 **/

NTC_B3950::NTC_B3950(PinName pADCpin, uint16_t pSerialResistance):
	adcpin(pADCpin)
{
	serialResistance = pSerialResistance;
}

/**
 * Read temperature
 * @return temperature in 0.1 ºC
 */
float NTC_B3950::getTemperature(void)
{
  uint8_t i;
  float sample;
  float average = 0;
  float numerator, denominator;

  float m = 0;
  float q = 0;
  float x1,y1,x2,y2 = 0;

  // It takes some measurements and calculate the average
  for (i=0; i< NUMSAMPLES; i++)
  {
    sample = adcpin.read()*3.3; // 3V3 is the reference voltage
    average += sample;
    ThisThread::sleep_for(10ms);
  }
  average /= NUMSAMPLES; // It is the voltage average

  //printf("Voltage measured is %.2f\r\n", average); // DEBUG

  // convert the value to resistance
  numerator = average * serialResistance;
  denominator = 3.3 - average;

  average = numerator / denominator;

  //printf("Resistance measured is %.2f\r\n", average); // DEBUG

  i = 0;
  float temperature = 0;
  while( (i<LOOK_UP_TABLE_ELEMENTS) & (average<lookUpTable[i])){
	  i++;
  }

  if((i+1) < LOOK_UP_TABLE_ELEMENTS){
	  x1 = lookUpTable[i];
	  y1 = i-55;
	  x2 = lookUpTable[i+1];
	  y2 = i+1-55;
	  //printf("x1 = %.2f\r\ny1 = %.2f\r\nx2 = %.2f\r\ny2 = %.2f\r\n", x1,y1,x2,y2);

	  //Linear interpolation
	 m = (y1-y2)/(x1-x2);
	 q = (x1*y2 - x2*y1)/(x1-x2);
	 //printf("m = %f\r\nq = %f\r\n", m,q);

	 temperature = m * average + q;
  }
  else{
	  temperature = i;
  }

  return (float)(temperature); // °C
}
