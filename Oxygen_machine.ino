//DS 18b20 start
#include <OneWire.h>
#include <DallasTemperature.h>
//DHT22 Start

#include <DHT.h>
#define DHTPIN 14 //what pin were connected
#define DHTTYPE DHT22 //Initialized DHT sensor for normal 16 mhz sensor
DHT dht(DHTPIN,DHTTYPE);

//DHT22 Stop

#define ONE_WIRE_BUS 4
const int oneWireBus = 4;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress; 

//DS 18b20 stop



//variables assign

int chk;
float humidity;
float temperature;

//DHT22 stop

void setup(){
  
  //start serial port
  //Serial.begin(115200);
Serial.begin(9600);
  //DS 18b20 start
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
  //DS 18b20 stop

  //DHT22 start
  Serial.begin(9600);
  dht.begin();
  //DHT22 stop
}
  

void loop(){ 

  //DS 18b20 start
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++){
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
      // Output the device ID
      Serial.print("Temperature for device: ");
      Serial.println(i,DEC);
      // Print the data
      float Motorheaderone = sensors.getTempC(tempDeviceAddress);
      Serial.print("Motorheaderone Temperature in C: ");
      Serial.print(Motorheaderone);
      
      float Motorheadertwo = sensors.getTempC(tempDeviceAddress);
      Serial.print("Motorheadertwo Temperature in C: ");
      Serial.print(Motorheadertwo);

      float Coolingcoil = sensors.getTempC(tempDeviceAddress);
      Serial.print("Coolingcoil Temperature in C: ");
      Serial.print(Coolingcoil);

      
      float regulator = sensors.getTempC(tempDeviceAddress);
      Serial.print("Regulator Temperature in C: ");
      Serial.print(regulator);
      
    }
  }
  delay(5000);
  //DS 18b20 stop

//DST22 start
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");
    delay(2000); //Delay 2 sec.
  
//DST22 stop
}

//DS 18b20 start
// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
//DS 18b20 stop
