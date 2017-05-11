#include <Wire.h>
#include <Ciao.h>
#include <Lucky.h>

//set the sea level pressure for Lucky shield calibration
#define SEALEVELPRESSURE_HPA 1008

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "insecure-groker.initialstate.com"

#define ACCESSKEY  "Your_IS_Access_Key"
#define BUCKETKEY  "tianweatherhub"

void setup() {
  Ciao.begin(); // CIAO INIT
  lucky.begin();
}

void loop() {
    
    // read temperature, pressure, altitude, humidity
    int temp = lucky.environment().temperature();
    int pressure = (lucky.environment().pressure() / 100.0F);
    int alt = (lucky.environment().altitude(SEALEVELPRESSURE_HPA));
    int hum = lucky.environment().humidity();
    
    String uri = "/api/events?accessKey=";
    uri += ACCESSKEY;
    uri += "&bucketKey=";
    uri += BUCKETKEY;
    uri += "&temp=";
    uri += String(temp);
    uri += "&pressure=";
    uri += String(pressure);
    uri += "&alt=";
    uri += String(alt);
    uri += "&hum=";
    uri += String(hum);

    
    Ciao.println("Send data to Initial State"); 
      
    CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri);

    if (!data.isEmpty()){
      Ciao.println( "State: " + String (data.get(1)) );
      Ciao.println( "Response: " + String (data.get(2)) );
    }
    else{ 
      Ciao.println("Write Error");
    }    
 
  delay(300000); // wait 5 minutes between reads

}  
