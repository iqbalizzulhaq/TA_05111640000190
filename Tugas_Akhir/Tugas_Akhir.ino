#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include "FS.h"
#include <ESP8266HTTPClient.h>


const char* ssid      = "Fiki Fahrizal";
const char* password  = "16091996";
const char* host      = "192.168.100.8";// localhost 

const char* remote_host = "www.google.com";

int averagePingtime,maxPingtime,minPingtime;
float throughput;
String kategori="";

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin (20,4); 
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  connectWiFi();

}

void loop() {
  //put your main code here, to run repeatedly:
  getPingtime();
  downloadAndSaveFile("/test.txt","http://jsonplaceholder.typicode.com/users/1");
  logDatabase2();
  delay(5000);

}


void connectWiFi(){
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
    }
    Serial.print("connected to ");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP());
    Serial.println("-----------------------------");
  }

void getPingtime(){
  String avg_time_ms;
  String max_time_ms;
  String min_time_ms;
  

  if(Ping.ping(remote_host)) 
    {
    Ping.ping(remote_host, 10);  //10 time ping to google, You can change value to higher or lower
    averagePingtime= Ping.averageTime();
    avg_time_ms = Ping.averageTime(); // reading string and Int for easy display integration.
    maxPingtime=Ping.maxTime();
    max_time_ms= Ping.maxTime();
    minPingtime=Ping.minTime();
    min_time_ms=Ping.minTime();

    Serial.print("Averange Pingtime ");
    Serial.println(averagePingtime);
    Serial.print("Max Pingtime ");
    Serial.println(maxPingtime);
    Serial.print("Min Pingtime ");
    Serial.println(minPingtime);

    
    if (averagePingtime <99){
     kategori="Internet_Condition_Good";
     Serial.println(kategori); 
     Serial.println("------------------------");
    }
    if (averagePingtime > 100 && averagePingtime < 199){
      kategori="Internet_Condition_Bad";
      Serial.println(kategori);
      Serial.println("------------------------");
    }
    }
  else{
    Serial.println("Internet_offline");
  }  
  }

void downloadAndSaveFile(String fileName, String  url){
 
  HTTPClient http;

  
  Serial.println("[HTTP] begin...\n");
  Serial.println(fileName);
  Serial.println(url);
  int time  = millis();
  
//  Serial.print("time is ");
//  Serial.println(time);
  
  http.begin(url);
  Serial.printf("[HTTP] GET...\n", url.c_str());
  // start connection and send HTTP header
  int httpCode = http.GET();
  int time1 = millis()-time;
//  Serial.println(millis());
//  Serial.println(time1);
  
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      Serial.printf("[FILE] open file for writing %d\n", fileName.c_str());
     
      File file = SPIFFS.open(fileName, "w");
      
//      Serial.println(SPIFFS.exists("/test.txt"));
//      Serial.println(SPIFFS.exists(fileName));

      // file found at server
      if(httpCode == HTTP_CODE_OK) {

          // get lenght of document (is -1 when Server sends no Content-Length header)
          int len = http.getSize();
          Serial.print(len);
          Serial.println(" Bytes");
          Serial.print(time1);
          Serial.println(" ms");
          
          //get throughput 
          throughput = len/time1;
          Serial.print(throughput);
          Serial.println(" Bytes/ms");

          // create buffer for read
          uint8_t buff[128] = { 0 };

          // get tcp stream
          WiFiClient * stream = http.getStreamPtr();

          // read all data from server
          while(http.connected() && (len > 0 || len == -1)) {
              // get available data size
              size_t size = stream->available();
              if(size) {
                  // read up to 128 byte
                  int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
                  // write it to Serial
                  //Serial.write(buff, c);
                  file.write(buff, c);
                  if(len > 0) {
                      len -= c;
                  }
              }
              delay(1);
          }

          Serial.println();
          Serial.println("[HTTP] connection closed or file end.");
          Serial.println("[FILE] closing file");
          Serial.println("-----------------------");
          file.close();

          
         
      }
          
  }
  http.end();

 
}


//void logDatabase(){
//  HTTPClient http;
//
//  String link, getData;
//  getData = String("?averangePingtime= ") + averagePingtime + String("&maxPingtime=") + maxPingtime + String("&minPingtime=")+ minPingtime +
//  String("&throughput=") + throughput + String("&kategori")+ kategori ;
//
//  link ="http://192.168.100.8/Tugas_Akhir/addData.php" + getData;
//  http.begin(link);
//  Serial.println(getData);
//  int httpCode = http.GET();            //Send the request
//  String payload = http.getString();    //Get the response payload
// 
////  Serial.println(httpCode);   //Print HTTP return code
////  Serial.println(payload);    //Print request response payload
// 
//  http.end();  //Close connection  
//  }


 void logDatabase2(){
  
    WiFiClient client;
    String request_string;
    
    const int httpPort = 80;
    
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
    }

    if (client.connect(host, httpPort)) {
    Serial.println("Connected to local host ");
    request_string +=" /Tugas_Akhir/try.php?averagePingtime=";
    request_string +=averagePingtime;
    request_string +="&maxPingtime=";
    request_string += maxPingtime;
    request_string +="&minPingtime=";
    request_string += minPingtime;
    request_string +="&throughput=";
    request_string += throughput;
    request_string +="&kategori=";
    request_string += kategori;

    
    Serial.print("request URL :");
    Serial.println(request_string);
    Serial.println("--------------------------");
    
    client.print(String("GET") + request_string +
    "HTTP/1.1\r\n" + "Host: " 
    +host + "\r\n" + "Connection: close \r\n\r\n");
    
    }
    else
    {
    Serial.println("Connection to localhost unsuccesful");
    }

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      Serial.println("----------------------------------");
      client.stop();
      return;
    }
  }

  
  }

void lcdDisplay(){
  lcd.setCursor ( 0, 0 );
  lcd.print("Connecting to Wifi");
  lcd.setCursor (0,1);
  lcd.print(WiFi.SSID());
  lcd.setCursor(0,2);
  lcd.print(WiFi.localIP());
  lcd.clear();

  if (averagePingtime < 99){
    lcd.setCursor(0,0);
    lcd.print("pingtime");
    lcd.setCursor(10,0);
    lcd.print(rssi);
    lcd.setCursor(0,1);
    lcd.print(averagePingtime+"ms");
    lcd.setCursor(0,2);
    lcd.print("Internet condition");
    lcd.setCursor(0,3);
    lcd.print("Good");

    }
  if (averagePingtime > 100 && averagePingtime < 199)
 {
  Serial.println("bad"); 
  lcd.setCursor(0,0);
  lcd.print("pingtime");
  lcd.setCursor(0,1);
  lcd.print(averagePingtime+"ms");
  lcd.setCursor(0,2);
  lcd.print("Internet condition");
  lcd.setCursor(0,3);
  lcd.print("Bad");
 }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Internet condition");
    lcd.setCursor(0,2);
    lcd.print("Offline");
    }
  
  }

 
