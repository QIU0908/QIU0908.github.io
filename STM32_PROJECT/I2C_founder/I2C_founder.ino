#include<Wire.h>

void setup(){
  Serial.begin(115200);

  Wire.setSCL(PB8);
  Wire.setSDA(PB9);
	
  Wire.begin();
	delay(1000);
	Serial.println("I2C ready");
  
}

void loop(){

  Serial.println("start loop");
for(byte address=1;address<128;address++){
	Wire.beginTransmission(address);
	int error=Wire.endTransmission();

	if(error==0){
		Serial.print("Found I2C device at 0x");
		Serial.println(address,HEX);
	}
}
delay(3000);
}