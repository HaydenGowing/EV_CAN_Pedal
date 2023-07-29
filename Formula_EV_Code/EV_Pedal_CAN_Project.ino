#include <CAN.h>

void setup() {

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Pedal voltage to CAN message program");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

int brake_pedal_pin = A0;
int accelerator_pedal_pin = A1;
int status;
float ADC_conversion = 5/1023;

void signal_pedal_verification(int pedal_1, int pedal_2) 
{
  brake_reading = analogRead(pedal_1);
  accelerator_reading = analogRead(pedal_2);

  brake_voltage = float(brake_pedal_pin * ADC_conversion);
  accelerator_voltage = float(accelerator_pedal_pin * ADC_conversion);

  

 voltage_conditions = [brake_voltage > 2.5 && accelerator < 2.5, brake_voltage < 2.5 && accelerator > 2.5, brake_voltage && accelerator == 2.5];

  //Assuming brake_voltage = 5 V at rest so accelerator_voltage = 0 V at rest
 if( 1 // Maybe we cycle through the conditions, or we could store previous couple pedal outputs and make sure multiple signals are correct vs just one) 
 {
   status = 1; 
 }
 else
 {
   status = 0;
 }
  return status
}

void loop() {

  pinmode(brake_pedal_pin, INPUT);
  pinmode(accelerator_pedal_pin, INPUT);

  // send packet: id is 11 bits, packet can contain up to 8 bytes of data 
  signal_pedal_verification(brake_pedal_pin, accelerator_pedal_pin);

////// Probably will turn these into functions depending on complexity of content in 'if' loops
  if (status == 0) // Pedals Fail
  {

  }

  if (status == 1) // Pedals verified
  {
    
  }
//////
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

