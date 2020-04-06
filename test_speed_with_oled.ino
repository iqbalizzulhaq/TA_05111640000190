
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>


const char* ssid     = "Fiki Fahrizal";
const char* password = "16091996";

const char* remote_host = "www.google.com";

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

String avg_time_ms;
int i;

void setup() {
  Serial.begin(115200);
  delay(10);
  lcd.begin (20,4); 
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  lcd.setCursor ( 0, 0 );
  lcd.print("Connecting to Wifi"); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");  // Just for troubleshot purpose.
  lcd.setCursor (0,1);
  lcd.print(WiFi.SSID());
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,2);
  lcd.print(WiFi.localIP());
  Serial.print("Pinging host ");
  Serial.println(remote_host);
  
}

void loop() {
    long rssi = WiFi.RSSI();
    lcd.noDisplay();
    delay(200);
    lcd.display();
    delay(200);
    lcd.clear();
    
    if(Ping.ping(remote_host)) 
    {
    Ping.ping(remote_host, 10);  //10 time ping to google, You can change value to higher or lower
    i= Ping.averageTime();
    avg_time_ms = Ping.averageTime(); // reading string and Int for easy display integration.
    Serial.println(i);

  if (i < 99)  // It is in general term, Please change as per your requirement
 {
  Serial.println("GOOD"); 
  lcd.setCursor(0,0);
  lcd.print("pingtime");
  lcd.setCursor(10,0);
  lcd.print(rssi);
  lcd.setCursor(0,1);
  lcd.print(avg_time_ms+"ms");
  lcd.setCursor(0,2);
  lcd.print("Internet condition");
  lcd.setCursor(0,3);
  lcd.print("Good");
 }
  if (i > 100 && i < 199)  // It is in general term, Please change as per your requirement
 {
  Serial.println("bad"); 
  lcd.setCursor(0,0);
  lcd.print("pingtime");
  lcd.setCursor(0,1);
  lcd.print(avg_time_ms+"ms");
  lcd.setCursor(0,2);
  lcd.print("Internet condition");
  lcd.setCursor(0,3);
  lcd.print("Bad");
 }
    } 
    
    else 
    {
    Serial.println("Error :(");
    lcd.setCursor(0,1);
    lcd.print("Internet condition");
    lcd.setCursor(0,2);
    lcd.print("Offline");
    }
  
  delay(60000);  // Every minutes
  lcd.clear();
}
