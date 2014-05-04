/* Project Climate Control Vent System - Wireless Thermometer
 * CSUS - CPE 187 Spring 2014
 *
 * The Climate Control Vent System consists of wireless temperature sensors 
 * and servo motors. Each room will have a temperature sensor and servo motor.
 * The base unit receives sensor reading from the wireless sensor and makes
 * decisons to turn on the servos and control the HVAC.
 *
 * Authors: Logan Odell, Gerardo Ramirez
 */

/* ***************************************************
 * INCLUDES
 * Add any includes to this section
 * ***************************************************/
#include "VirtualWire.h"



/* ***************************************************
 * CONSTANTS
 * Add any constants, defines or macros to this section
 * ***************************************************/
 
/* ***************************************************
 * GLOBALS
 * Add any global variables to this section
 * ***************************************************/
 
float temp;
int tempPin=0;

 /* Setup function is run once on startup. Use this function to initialize 
 * any variables, pin modes, libraries or make other one-time calls */
void setup()
{
  pinMode(13,OUTPUT);
  vw_set_ptt_inverted(true); //
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
}

/* Loop function is repeated indefinitely. Any code that should continuously
 * be executed, should be place in this function. Avoid using delay calls by
 * using the concepts demonstrated in the BlinkWithoutDelay() example */
void loop()
{
  temp = analogRead(tempPin);
  temp = temp * 0.48828125;//formula to obtain temp in *C
  
  int tempC1 = (int)temp;
  int tempC2 = (int)(temp - tempC1) * 100; // For two decimal points
  char controller[24];
  sprintf(controller, "Temp in *C = %i.%i", tempC1,tempC2);
 
  //dtostrf(temp,1,2,&controller[15]);

  vw_send((uint8_t *)controller, strlen(controller));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1);
  delay(2000);
  digitalWrite(13,0);
  delay(2000);  
}
