#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
 
#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4  
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

unsigned long msecLst;

char auth[] = "iVvp4rmllTb1M-Hj9DrsgxjUMCJP0asM";       // You should get Auth Token in the Blynk App.
const int BUTTON1 = 16;
const int BUTTON2 = 5; 
const int BUTTON3 = 15; // switch 1 of BlynkBoard Conneted with D9(GPIO 03) pin of NodeMCU
char ssid[] = "sumit";    // Your WiFi credentials.
char pass[] = "12345678";             // Set password to "" for open networks.
int buttonState1 = 0;         // variable for reading the pushbutton status
int count_value1 =0;
int prestate1 =0;
int buttonState2 = 0;         // variable for reading the pushbutton status
int count_value2 =0;
int prestate2 =0;
int buttonState3 = 0;         // variable for reading the pushbutton status
int count_value3 =0;
int prestate3 =0;
int n1=1;
int n2=1;
int nt=10;
int c1=0;
int c2=0;
int nb=3;

void setup()
  {
  Serial.begin(9600);                 // Debug console
  Blynk.begin(auth, ssid, pass);
  pinMode (BUTTON1, INPUT);
  pinMode (BUTTON2, INPUT);
  pinMode (BUTTON3, INPUT);

   tft.begin();
 
 
    tft.fillScreen(ILI9341_BLACK);
     tft.setCursor(20, 20);
    tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Delhi-Agra");


   tft.setCursor(20, 120);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Del-Manali");
  }



  
  void button1()
  {
     buttonState1 = digitalRead(BUTTON1);

  // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
  if (buttonState1 == HIGH && prestate1 == 0) {
    if(count_value1<nt){
      count_value1++;
      Serial.println(count_value1);
      Serial.println(n1);
      c1++;
    }
   else if(count_value1==nt){
     Serial.println("Supply one more bus in agra route");
     Blynk.notify("Supply one more bus in Delhi-agra route");
     count_value1=0;
     n1++;
     nb--;
     
    }
    
    
    // turn LED on
  //  digitalWrite(ledPin, HIGH);
    //delay(100);
    // turn LED off
    //digitalWrite(ledPin, LOW);
     Blynk.virtualWrite(V0, count_value1);
     Blynk.virtualWrite(V2, c1);
     Blynk.virtualWrite(V3, n1);
    tft.fillRect(10, 60, 220, 40, ILI9341_YELLOW);
      tft.setCursor(10, 70);
    tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(4);
  tft.print(count_value1);
  tft.setCursor(60, 70);
   tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(4);
  tft.println(n1);
     

    prestate1 = 1;
  } else if(buttonState1 == LOW) {
    prestate1 = 0;
  }
  }

  void button2()
  {
     buttonState2 = digitalRead(BUTTON2);

  // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
  if (buttonState2 == HIGH && prestate2 == 0) {
    
    if(count_value2<nt){
      count_value2++;
      Serial.println(count_value2);
      Serial.println(n2);
      c2++;
    }
   else if(count_value2==nt){
     Serial.println("Supply one more bus in Delhi-manali route");
     Blynk.notify("Supply one more bus in Delhi-manali route");
     count_value2=0;
     n2++;
     nb--;
   
    }
    // turn LED on
  //  digitalWrite(ledPin, HIGH);
    //delay(100);
    // turn LED off
    //digitalWrite(ledPin, LOW);
     Blynk.virtualWrite(V1, count_value2);
     Blynk.virtualWrite(V4, c2);
     Blynk.virtualWrite(V6, n2);
       tft.fillRect(10, 160, 220, 40, ILI9341_GREEN);
    
       tft.setCursor(10, 170);
    tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(4);
  tft.print(count_value2);
  tft.setCursor(60, 170);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(4);
  tft.println(n2);
    
    prestate2 = 1;
  } else if(buttonState2 == LOW) {
    prestate2 = 0;
  }
  }

 
void loop()
  {
  Blynk.run();
   button1();
    button2();
   buttonState3 = digitalRead(BUTTON3);

  // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
  if (buttonState3 == HIGH && prestate3 == 0)
  {
    if (c1>c2 && nb>0 ){
      Blynk.notify("Delhi to Agra route high and More buses required in Delhi-Agra route");
      Blynk.email("tkjha07022001@gmail.com","Bus route","More buses required in Delhi-Agra route");
      
       tft.fillRect(10, 220, 220, 60, ILI9341_WHITE);
       tft.setCursor(10, 240);
    tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(3);
  tft.println("del-agr high");
    }
    else if(c2>c1 && nb>0) {
      Blynk.notify(" Delhi to manali route high and More buses required in Delhi-Manali route ");
      Blynk.email("tkjha07022001@gmail.com","Bus route","More buses required in Delhi-Manali route");
  
      tft.fillRect(10, 220, 220, 60, ILI9341_WHITE);
       tft.setCursor(10, 240);
    tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(3);
  tft.println("del-mnl high");
    }
    else if(nb==0){
      Blynk.notify("We have no more buses left");
    }
     prestate3 = 1;
  } 
  else if(buttonState3 == LOW)
  {
    prestate3 = 0;
  }
  }
  

  
  
