## Pedal Voltage to Can Bus Arduino Task

This project aims to monitor the output voltages of the brake and accelerator pedals of a Formula race car and convert them into a CAN message format to be sent to the car MCU. The potentiometers in both pedals output feed into two analog input pins on the Arduino microcontroller, and the Arduino CAN library is utilized to convert the analog signals from the pedals into a CAN message.


<img width="800" alt="MicrosoftTeams-image (1)" src="https://github.com/HaydenGowing/EV_CAN_Pedal/assets/97248426/0ae32032-1f4a-4d6a-b0ed-374abeb04d74">


### CAN Datasheet:

The CAN Protocol (V6_1).pdf provides detailed information on the CAN protocol and the necessary steps to convert the potentiometer values into a CAN message format. It is important to follow the specifications outlined in the datasheet to ensure that the converted message is accurate and can be successfully sent to the car MCU.

[CAN Protocol (V6_1).pdf](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1ff552d2-bffb-46c4-842d-9aecac4ec688/CAN_Protocol_(V6_1).pdf)

### Project Task Progress:

- [ ]  Write the code to read the potentiometer values from the analog input pins on the Arduino
- [ ]  Use the CAN library to convert the potentiometer values into a CAN message format

The first task involves writing the code to read the potentiometer values from the analog input pins on the Arduino. The potentiometers are inverse, which means that a voltage of [0-5]V corresponds to [5-0]V. Therefore, the code needs to account for this inverse relationship and accurately read the potentiometer values.

The second task involves utilizing the Arduino CAN library to convert the potentiometer values into a CAN message format. The CAN Datasheet provides guidance for this task and should be consulted during the implementation.
