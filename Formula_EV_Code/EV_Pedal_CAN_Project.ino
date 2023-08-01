#include <CAN.h>

void setup() {

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Pedal voltage to CAN message program");

  if (!CAN.begin(500E3)) // We have 4 different bit rate: 1) 125 kbps, 250kbps, 500kbps, 1Mbps
  {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

//Start range voltage is 1.4/4.4 V
//End range voltage is 1/4.8 V
// Plotted in desmos: https://www.desmos.com/calculator/7ob8hfbr4l


// APPS_1 Working voltage range: 1.4 - 4.8
// APPS_2 Working voltage range: 4.4 - 1

int APPS_1_Pin = A0;
int APPS_2_pin = A1;
int status;

float tolerance = 0.1 //Voltage tolerance between pedal voltages
float ADC_conversion = 5/1023;


// Accounts for the jitter/error when switching channels on ADC multiplexer
void adc_read_compensation(int reading, int pin) 
{
  reading = analogRead(pin) //Switches ADC mux channels
  delay(10)
  reading = analogRead(pin) //Gets a more stable reading after switching
  delay(10)

  return reading 
}



void signal_pedal_verification(int pedal_1, int pedal_2) 
{
  adc_read_compensation(APPS_1, APPS_1_pin)
  adc_read_compensation(APPS_2, APPS_2_pin)

  APPS_1_Voltage = float(APPS_1 * ADC_conversion);
  APPS_2_Voltage = float(APPS_2 * ADC_conversion);

// Have to account for the 0.8V starting voltage for APPS1
 if(5 - (APPS_2_Voltage + tolerance) < APPS_1_Voltage - 0.8 < 5 - (APPS_2_Voltage - tolerance))
 {
   status = 1; 
  }
 else
 {
   status = 0;
 }
  return status
}

// Map out voltages to angles
void loop() {

  pinmode(brake_pedal_pin, INPUT);
  pinmode(accelerator_pedal_pin, INPUT);

  signal_pedal_verification(brake_pedal_pin, accelerator_pedal_pin);

////// Probably will turn these into functions depending on complexity of content in 'if' loops
  if (status == 0) // Pedals Fail
  {
    
  }
  if (status == 1) // Pedals verified
  {
    
  }
//////

// send packet: id is 11 bits, packet can contain up to 8 bytes of data 
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('x')
  CAN.endPacket();

  Serial.println("done");
  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('y');
  CAN.endPacket();

  Serial.println("done");
  delay(1000);
}

