#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
int verde=11;
int rosu=12;
int albastru=13;


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value


void setup() {
// set up the LCD's number of columns and rows:
Serial.begin(9600);
lcd.begin(16, 2);
dht.begin();
lcd.print("DATE METEO:  ");
pinMode(verde,OUTPUT);
pinMode(rosu,OUTPUT);
pinMode(albastru,OUTPUT);
}

int x_curr, x_prev = 800;


void loop() {
  x_curr=analogRead(0); //butoane
  hum = dht.readHumidity();     //senzt temp-umidit
  temp= dht.readTemperature();  //senz temp-umidit
  int value = analogRead(A1);   //senz ploaie
  //Serial.println(value);
  Serial.println(x_curr);
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1);

if (x_curr < 800)
  x_prev = x_curr;

if(x_prev<100){    //RIGHT
  lcd.setCursor(0,0);
  lcd.print("DATE METEO:   ");
   lcd.setCursor(0, 1);
   lcd.print("Temperatura:"); 
   lcd.setCursor(12,1);
   lcd.print(temp);
   lcd.setCursor(14,0);
   lcd.print("*C");
   delay(500);
}

else if(x_prev<200)    //UP
{
  //while(x==1023){
      lcd.setCursor(0,0);
      lcd.print("STAREA VREMII:   ");
    lcd.setCursor(0,1);
    lcd.print("Senin            ");
     digitalWrite(rosu,LOW);
     digitalWrite(verde,LOW); 
     digitalWrite(albastru,HIGH);
  
  if (value > 1010) {
    lcd.setCursor(0,1);
    lcd.print("Senin        ");
     digitalWrite(rosu,LOW);
     digitalWrite(verde,LOW); 
    digitalWrite(albastru,HIGH); 
    }
  else if ((value > 400) && (value <= 900)) {
    lcd.setCursor(0,1);
    lcd.print("Ploaie usoara   ");
    digitalWrite(albastru,LOW); 
    digitalWrite(rosu,HIGH);
    digitalWrite(verde,HIGH); 
  }
  else if(value<400){
    lcd.setCursor(0,1);
    lcd.print("Ploua torential");
     digitalWrite(albastru,LOW); 
     digitalWrite(rosu,LOW);
     digitalWrite(verde,LOW); 
     digitalWrite(rosu,HIGH);
   }
  delay(1000);
}

 
   else if(x_prev<400)
       lcd.print("Down        "); //DOWN
       
    else if(x_prev<600){   //LEFT
     lcd.setCursor(0,0);
     lcd.print("DATE METEO:   ");
        lcd.setCursor(0,1);
        lcd.print("Umiditate:");
        lcd.setCursor(10,1);
        lcd.print(hum);
        lcd.setCursor(14,0);
        lcd.print("%  ");
        delay(500);
    }
    else if(x_prev<800){ //SELECT
      
    lcd.setCursor(0,0);
    lcd.print("LFT:temp,RHT:umid    ");
    lcd.setCursor(0,1);
    lcd.print("UP:ploaie            ");
    }

}

   