/* Library for RFID */
#include <MFRC522.h>
#include <SPI.h>
/* Library for REST API (Get/ Post) */
#include <ArduinoJson.h>  // To convert received data to JSON format
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
/* Library for 1.3 OLED */
#include <Wire.h>
#include<SH1106.h>
#include <SoftwareSerial.h>

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;

/* RFID Pins */
constexpr uint8_t RST_PIN = D0;
constexpr uint8_t SS_PIN = D3;     

SoftwareSerial SIM900A(15, 2);

/* Instance of the class for the RFID */
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

/* Instance of 1.3 OLED Library */
SH1106 display(0x3C,D1,D2);

/* WIFI Credentials */
const char *ssid = "Trojan 24g";
const char *password = "hyper!Terminal2.4g";
WiFiClient wifiClient;

/* API Route */
const char *host = "http://snnhs-attendance-system.herokuapp.com/api";  // NODEJS REST API Host

String tag; // Init var for RFID tag

void setup() {
  Serial.begin(9600);
  SIM900A.begin(9600); 
  Serial.println("SIM900A started at 9600");
  delay(1000);
  Serial.println("Setup Complete! SIM900A is Ready!");
  
  /* Start of RFID config */
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  /* End of RFID config */

  /* Start of WIFI config */
  WiFi.mode(WIFI_OFF);  // Prevents reconnection during reuploading of code
  delay(1000);
  WiFi.mode(WIFI_STA);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.begin(ssid,password);
  Serial.println("");

  Serial.println("Connecting");
  // Wait for connection
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // If connection is successful
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  /* End of WIFI config */

  /* Initialize 1.3 OLED */
  display.init();
  display.setContrast(255);
  display.setLogBuffer(5, 30); // allocate memory to store 8 lines of text and 30 chars per line
  display.println("");
  display.println("");
  display.println("Scan your tag:");
  display.println("");
  display.println("");
  display.drawLogBuffer(0, 0);
  display.display();
}

void loop() {
  HTTPClient http;
  display.clear();
  if ( ! rfid.PICC_IsNewCardPresent())  // If no RFID detected, don't proceed and just return to loop
    return;
    
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }

    display.println("Scanning RFID tag...");
    display.println("Tag: " + tag);
    
    http.begin(wifiClient, host + String("/user/") + tag);  // Example: http://192.168.43.246:8888/api/user/2132323 (GET REQ)
    int httpCode = http.GET();
    String payload = "{}";

    if(httpCode == 404){  // If 404 then RFID tag does not exist in the DB. 
      display.println("RFID not recognized.");
      display.println("Register it to the admin.");
      display.println("");
      display.drawLogBuffer(0, 0);
      display.display();
      http.end();
    }else{
      // IF RFID is FOUND, return its data
      payload = http.getString();
      http.end();
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      // Save name and phone number of the RFID owner      
      String student_name = doc["name"];
      String guardian_number = doc["phone"];

      display.println("Welcome " + student_name);
      display.println("Please wait...");
      display.println("");
      display.drawLogBuffer(0, 0);
      display.display();
      delay(1500);

      // Create attendance in the db
      http.begin(wifiClient, host + String("/attendance"));
      String attendanceData = "rfid=" + tag;
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpCode = http.POST(attendanceData); // attendanceData is the RFID tag
      payload = http.getString();

      display.clear();
      display.println("");
      display.println("Attendance Recorded!");
      display.println("Sending text...");
      display.println("");
      display.println("");
      display.drawLogBuffer(0, 0);
      display.display();

      delay(2000);

      SendMessage(guardian_number);

      delay(1500);
      
      display.clear();
      display.println("");
      display.println("Text sent to your Guardian.");
      display.println("Have fun in school :)");
      display.println("Have a good day!");
      display.println("");
      display.drawLogBuffer(0, 0);
      display.display();
    }
    
    delay(1500);
    display.clear();
    display.println("");
    display.println("");
    display.println("Scan your tag:");
    display.println("");
    display.println("");
    display.drawLogBuffer(0, 0);
    display.display();
    display.clear();
    
    // Reinitialize RFID tag
    SPI.begin(); // Init SPI bus
    rfid.PCD_Init(); // Init MFRC522
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void SendMessage(String number)
{
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  SIM900A.println("AT+CMGS=\"+63"+String(number)+"\"\r"); // Replace x with mobile number
  delay(1000);
  SIM900A.print("Your son/daughter scanned his/her RFID. He is now inside the campus.");// The SMS text you want to send
  delay(100);
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
