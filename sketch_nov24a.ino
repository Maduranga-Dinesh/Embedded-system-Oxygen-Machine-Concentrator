//26.11.2021 11.36 AM latest code
#include <Wire.h> 

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged TO GPIO 4
#define ONE_WIRE_BUS 6

//DHT
#include "DHT.h"

#define DHTPIN 5     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

//DHT

float temp1;
float temp2;
float temp3;

int t1_temp = 7;
int t2_temp = 8;
int t3_temp = 9;
int t4_temp = 10;

int vibr_Pin =13;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

int buzzr = 11;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 

//BMP
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C

//BMP

void setup(){
 
lcd.init();                      // initialize the lcd 
lcd.init();
  // Print a message to the LCD.
 lcd.backlight();
   //start serial port
  Serial.begin(9600);
  pinMode(vibr_Pin, INPUT);
  // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

  //BMP
  Serial.println(F("BMP280 test"));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //BMP
}

void loop(){ 

    

 
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      // Output the device ID
      Serial.print("device: ");
      Serial.println(i,DEC);
      // Print the data
      float tempC = sensors.getTempC(tempDeviceAddress);
      Serial.print("Temp C: ");
      Serial.println(tempC);

sensors.requestTemperatures();  
  Serial.print("Temperature 1 is: ");
  temp1 = sensors.getTempCByIndex(0);
  Serial.println(temp1); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  
lcd.setCursor(0,0);
lcd.print("T1=");
lcd.print(temp1);

   if(temp1>=30)
      {
      digitalWrite(t1_temp,HIGH);
      
      }else{
      digitalWrite(t1_temp,LOW);
        }
        
  temp2 = sensors.getTempCByIndex(1);
  Serial.print("Temperature 2 is: ");
  Serial.println(temp2);

lcd.setCursor(7,0);
lcd.print("| T2=");
lcd.print(temp2);

   if(temp2>=30)
      {
      digitalWrite(t2_temp,HIGH);
      
      }else{
        digitalWrite(t2_temp,LOW);
        }
 
  temp3 = sensors.getTempCByIndex(2);
  Serial.print("Temperature 3 is: ");
  Serial.println(temp3);

lcd.setCursor(0,1);
lcd.print("T3=");
lcd.print(temp3);

    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    lcd.setCursor(7,1);
    lcd.print("| IT=");
    lcd.print(bmp.readTemperature());

if(temp3>=30)
      {
      digitalWrite(t3_temp,HIGH);
      
      }else{
        digitalWrite(t3_temp,LOW);
        }
     delay(100);
      if(temp1 >= 30 || temp2>= 30 || temp3>= 30){
        digitalWrite(buzzr,HIGH);
        }else{
          digitalWrite(buzzr,LOW);
          }
    }
  }
  delay(5000);
  lcd.clear();
  //DHT

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: "); 
  Serial.print(h);
 
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

  //lcd.setCursor(7,1);
  //lcd.print("  IT=");
  //lcd.print(t+15);
  
  lcd.setCursor(0,0);
  lcd.print("HM=");
  lcd.print(h-110);

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    lcd.setCursor(7,0);
    lcd.print("PA=");
    lcd.print(bmp.readPressure());

  //SW180
   long measurement =TP_init();
   Serial.println(measurement);

    lcd.setCursor(0,1);
    lcd.print("V=");
    lcd.print(measurement);
  //SW180
  
  delay(10000);
  lcd.clear();
  //DHT

  //BMP




    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
   

  //BMP
  

}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
