#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  analogReference(5);
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }




  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
 int xAxis = analogRead(A1);
 int yAxis = analogRead(A3); 

  if (mySerial.available())
    Serial.println(" ");
    Serial.println(xAxis);
    Serial.println(" ");
    Serial.println(yAxis);
    delay(50);
}
