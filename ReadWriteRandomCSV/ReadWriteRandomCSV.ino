/*	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
 and pin #10 (SS) must be an output
 ** Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (CS pin can be changed)
 and pin #52 (SS) must be an output
 ** Leonardo: Connect to hardware SPI via the ICSP header
 */
#include <SPI.h>
#include <SD.h>

File myFile;

//     change this to match your SD shield or module;
//     Arduino Ethernet shield: pin 4
//     Adafruit SD shields and modules: pin 10
//     Sparkfun SD shield: pin 8

const int chipSelect = 10;
float recordTime = 20000;            //this is how long the data recording will last
int number=0;


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SS, OUTPUT);
  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("datafun.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("success!");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening datafun.csv");
  }
}


void loop()
{
  myFile = SD.open("datafun.csv", FILE_WRITE);
  number = random(0,30000);           //pick a random number
  // if the file opened okay, write to it:
  if ((myFile) && (millis()<recordTime)) {
    myFile.print(millis()/1000);       //record how long the program is running divided by 1000 to make seconds
    myFile.print(",");                 //separate with a comma
    myFile.println(number);            //record the random number
    
    Serial.print(millis()/1000);       //print the same data in the serial window.
    Serial.print(","); 
    Serial.println(number);
  } 

  else if ((myFile) && (millis()>recordTime)){
    // if the file didn't open, print an error:
    Serial.println("done recording");
    delay(10000);
  }

  else{
    // if the file didn't open, print an error:
    Serial.println("error opening data file");
  }
  myFile.close();         //close the data file
  delay(1000);            //one reading per second
}







