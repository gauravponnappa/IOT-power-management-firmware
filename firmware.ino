
#include "Arduino.h" 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseESP8266.h>   
                     
#define FIREBASE_HOST "esp8266-3c928-default-rtdb.firebaseio.com"//The link                   
#define FIREBASE_AUTH "kFNJD5Vp7rPkCrbfyIubIxqhZCyFxmJ1d6CFk14G" //The secret key

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


FirebaseData firebaseData,fbdo,fbdohrs;
const unsigned long eventInterval = 5000;
unsigned long previousTime = 0;
const int input = 5;// input.
int val=0;
int pulse = 0; // pulse count.
int var = 0;
int days=0;
double hour = 0;
double tf = 24.00;
double zero = 0.00;
int currentMonth;
String currentMonthName;
String monthpath;
int jan,feb,mar,apr,may,jun,jul,aug,sept,oct,nov,dec;
int prevday,prevdayy;
 
//Variables
int i = 0;
int statusCode;
const char* ssid = "text";
const char* passphrase = "text";
String st;
String content;


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);

void setup()
{

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);

  Serial.println("Reading EEPROM pass");

  String fireuser = "";
  for (int i = 96; i < 160; ++i)
  {
    fireuser += char(EEPROM.read(i));
  }
  Serial.print("User: ");
  Serial.println(fireuser);


  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                             // connect to firebase
  Firebase.reconnectWiFi(true);       

  if (Firebase.getInt(fbdo, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/pulse")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      pulse=fbdo.intData();
    }

  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.getInt(fbdohrs, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/hours")) {

      if (fbdohrs.dataTypeEnum() == fb_esp_rtdb_data_type_double) {
      Serial.println(fbdohrs.to<double>());
      hour=fbdohrs.doubleData();
    }

  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.getInt(fbdo, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/prevday")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      prevdayy=fbdo.intData();
    }
   }else {
    Serial.println(fbdo.errorReason());
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
     monthpath="/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/";

     if (Firebase.getInt(fbdo,monthpath+"January")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      jan=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"February")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      feb=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"March")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      mar=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"April")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      apr=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"May")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      may=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"June")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      jun=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"July")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      jul=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"August")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      aug=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"September")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      sept=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"October")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      oct=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"November")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      nov=fbdo.intData();
    }}else {}

    if (Firebase.getInt(fbdo,monthpath+"December")) {

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.println(fbdo.to<int>());
      dec=fbdo.intData();
    }}else {}


          

      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/January",jan);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/February",feb);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/March",mar);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/April",apr);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/May",may);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/June",jun);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/July",jul);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/August",aug);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/September",sept);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/October",oct);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/November",nov);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/December",dec);
  
  
  timeClient.begin();
  timeClient.setTimeOffset(19800);
  timeClient.update();
 
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);
  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

    Serial.println("Succesfully Connected!!!");
    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }

  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }

}
void loop() {
 {
   if ((WiFi.status() == WL_CONNECTED))
  {

  unsigned long currentTime = millis();
 
  //read pulse//
  if(digitalRead(input) > var)
  {
      var = 1;
      pulse++;
      
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/pulse", pulse);
      Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/hours");
      
      Serial.println(hour);
      Serial.print(F(" hours"));
            
      Serial.print(F(" pulse"));
      Serial.println(pulse);
      
      
  
  }

  

  int daycheck=hour;
  int daycheckk=daycheck%24;
  if(daycheckk<0.2)
  {
     
    prevday=pulse-prevdayy;
    Firebase.setInt(firebaseData, "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/prevday", prevday);
  }
  
  if(digitalRead(input) == 0) 
  {
  var = 0;
  }



if(currentMonth!=currentMonth)
  {
    String logbook= "/users/RPQ57PCuiGWetgtlZpt4OVGOOPC3/data/logs/"+currentMonthName;
    Firebase.setInt(firebaseData,logbook,pulse);
    
    }

  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int currentMonth = ptm->tm_mon-0;
  String currentMonthName = months[currentMonth-1];
  
 /* This is the delay event */
  if (currentTime - previousTime >= eventInterval)
  { 
      hour=hour+0.00138909;  
   /* Update the timing for the next time around */
    previousTime = currentTime;
  }
}
}
}

//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("Schneider_setup", "");
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += st;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input name='user' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      String quser = server.arg("user");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 160; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
        Serial.println(quser);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        Serial.println("writing eeprom user:");
        for (int i = 0; i < quser.length(); ++i)
        {
          EEPROM.write(92 + i, quser[i]);
          Serial.print("Wrote: ");
          Serial.println(quser[i]);
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new credentials\"}";
        statusCode = 200;
        ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  } 
}
