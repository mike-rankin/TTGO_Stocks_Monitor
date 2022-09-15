// Original code that I used found at: https://github.com/aniketdhole07/Stock-Price-ESP8266-Display/blob/main/main.ino
// Full instructions here: https://www.electromaker.io/project/view/live-stock-price-display
// Hardware used is the TTGO
// Sign up for a free stocks tracking api at finnhub.io

#include <WiFi.h>
#include <TFT_eSPI.h> 
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 
#include "orb.h"

TFT_eSPI tft = TFT_eSPI(); 

#ifdef PLATFORMIO
const char* ssid     = WIFI_SSID;  // Please configure in platformio.ini   
const char* password = WIFI_PASS;
const char* finhub_api = FINHUB_API;
#else
const char* ssid     = "SSID";      
const char* password = "PASSWORD";
const char* finhub_api = "YOUR API TOKEN FROM FINNHUB.IO";
#endif


//#define gray 0x39C7
//#define dblue 0x01A9
//#define purple 0xF14F
#define green 0x2D51

String payload="";
double current=0;
double chng=0;
double last=0;

StaticJsonDocument<6000> doc;




void connect_to_wifi()
{
 WiFi.begin(ssid, password);
 tft.setTextColor(TFT_GREEN,TFT_BLACK); 
 tft.setTextSize(2); 
 tft.print("Connecting");
 tft.setCursor (0,20); 
 while (WiFi.status() != WL_CONNECTED)
 {
  delay(1000);
  tft.print(".");
 }
 tft.fillScreen(TFT_BLACK);
 tft.setCursor (0,0);  
 tft.print("CONNECTED!!!");
 delay(2000);
 tft.fillScreen(TFT_BLACK);
}


 void main_page()
 {
  tft.setTextSize(1);
  tft.setFreeFont(&Orbitron_Medium_16);  
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Stock Prices",0,0);  
  tft.setTextColor(green,TFT_BLACK);

}
  
void reset_screen()
{
 tft.fillScreen(TFT_BLACK);
} 

void stock_page(String s1,String s2,String s3,String s4,String s5,String s6,String s7)
{
 read_price(0,20,s1);  //20
 read_price(0,35,s2);
 read_price(0,50,s3);
 read_price(0,65,s4);
 read_price(0,80,s5);
 read_price(0,95,s6);
 read_price(0,110,s7);
} 


void read_price(int x_i,int y_i,String stock_name)
{ 
 float currentPrice;
 float differenceInPrice; 
 float percentchange; 
 
 HTTPClient http; 
 http.begin("https://finnhub.io/api/v1/quote?symbol="+stock_name+"&token="+String(finhub_api)); 
    
 int httpCode = http.GET();  
 if (httpCode > 0)
 { 
  payload = http.getString();
  char inp[payload.length()];
  payload.toCharArray(inp,payload.length());
  deserializeJson(doc,inp);
  //c = Current price, d = Change, dp = Percent change, pc = Previous close price
  String v=doc["c"];   
  String c=doc["dp"]; 
  current=v.toDouble(); 
  percentchange=c.toDouble();  

  tft.setTextSize(1);
  tft.setTextColor(TFT_ORANGE,TFT_BLACK);
  tft.drawString(stock_name,x_i,y_i,2); 
  tft.setTextColor(TFT_WHITE,TFT_BLACK);                       
  tft.drawString("PRICE: ",40+x_i,y_i,2);
  tft.drawString(String(current),85+x_i,y_i,2);
  
  if(percentchange<0.0)
  {
   tft.setTextColor(TFT_RED);
   tft.drawString("CHG:",150+x_i,y_i,2);
   tft.drawString(String(percentchange),185+x_i,y_i,2);
   tft.drawString("  %",215+x_i,y_i,2);
  } 
  
  else
  {
   tft.setTextColor(TFT_GREEN);
   tft.drawString("CHG:",150+x_i,y_i,2);
   tft.drawString(String(percentchange),185+x_i,y_i,2);
   tft.drawString(" %",215+x_i,y_i,2);
  }
  
 }
}

void setup() 
{
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  connect_to_wifi(); 
}


void loop() 
{
 main_page();
 stock_page("AAPL","AMZN","TSLA","MSFT","LAC","SNAP","SPOT");
 //delay(10000);  //10 seconds delay
 //delay(30000);  //30 seconds delay
 //delay(60000);  //1 minute delay
 delay(300000);  //5 minute delay

 reset_screen();

}
  
