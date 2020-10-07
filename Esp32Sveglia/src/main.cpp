#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Orologio.h>
#include <NTPClient.h>
#include <WiFi.h> // for WiFi shield
#include "pitches.h"
#define pinBottoneOre 35
#define pinBottoneMinuti 36
#define pinBuzzerAttivo 4
#define pinBuzzerPassivo 2
RF24 radio(12, 14, 26, 25, 27);
char msg[10];

const char *ssid = "TP-LINK_BF32";
const char *password = "08631862";

WiFiUDP ntpUDP;

//Orologio Clock(22, 17, 13, 4, 34, 21, 15, 5, 23, 19, 18, 16);
Orologio Clock = Orologio();

// You can specify the time server pool and the offset ( in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

int OraSveglia = 6;
int MinutiSveglia = 30;

unsigned long wait = 0;

int melody[] = {
    NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_D5, NOTE_D5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_C5, NOTE_C5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_B4, NOTE_B4, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_AS4, NOTE_AS4, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_D5, NOTE_D5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_C5, NOTE_C5, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_B4, NOTE_B4, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5,
    NOTE_AS4, NOTE_AS4, NOTE_D6, NOTE_A5, 0, NOTE_GS5, 0, NOTE_G5, 0, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5};

int noteDurations[] = {
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 8, 8, 16, 16, 16, 16, 16, 8, 16, 16, 32};

int playing = 0;

void tone(byte pin, int freq, int dur)
{
  ledcSetup(0, 2000, 8);  // setup beeper
  ledcAttachPin(pin, 0);  // attach beeper
  ledcWriteTone(0, freq); // play tone
  playing = pin;
}

void noTone()
{
  tone(playing, 0, 1);
}

unsigned long Inizio = millis();

void setup()
{
  Clock.setOrologio(13, 5, 16, 15, 18, 17, 32, 33, 19, 23, 22, 21);
  Serial.begin(115200);
  pinMode(pinBuzzerAttivo, OUTPUT);
  pinMode(pinBottoneOre, INPUT);
  pinMode(pinBottoneMinuti, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.setTimeOffset(7200);

  Serial.print(OraSveglia);
  Serial.print(":");
  Serial.println(MinutiSveglia);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(102);
  radio.setPayloadSize(10);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(0xABCDABCD71LL);
  radio.openReadingPipe(1, 0x544d52687CLL);
  radio.startListening();
  delay(10);
}

void DisplaySveglia(int Ore, int Minuti);

int ControlloMessaggi();

void Megalovania();

void BuzzerAttivoANDRecezione();

void CambioOrarioSveglia();


void loop()
{

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  if ((timeClient.getHours() == OraSveglia) && (timeClient.getMinutes() == MinutiSveglia) && (Inizio <= millis()))
  {
    Serial.println("sono entrato");

    Inizio = millis() + 3600000;

    radio.stopListening();
    delay(20);
    if (!radio.write("AvviaMEGA\0", 10))
    {
      delay(100);
      Serial.println("Non riesco ad avviare Arduino MEGA");
    }
    radio.startListening();
    delay(10000);

    while (true)
    {
      radio.stopListening();
      delay(20);
      if (!radio.write("AvviaMEGA\0", 10))
      {
        delay(100);
        Serial.println("Non riesco ad avviare Arduino MEGA");
      }
      radio.startListening();
      delay(20);
      BuzzerAttivoANDRecezione();

      if (strcmp(msg, "OffSveglia\0") == 0)
      {
        Serial.println("Messaggio 'OffSveglia' Controllato appena uscito da 'BuzzerAttivoANDRecezione'.");
        return;
      }

      Megalovania();

      if (strcmp(msg, "NOSuono\0") == 0)
      {
        Serial.println("Messaggio 'NOSuono' Ricevuto. NoFun");
        digitalWrite(pinBuzzerAttivo, LOW);

        wait = millis() + 25000;
        while (wait >= millis())
        {
          if ((ControlloMessaggi() == 2) || (strcmp(msg, "OffSveglia\0") == 0))
          {
            Serial.println("Messaggio 'OffSveglia' Ricevuto. Fun");
            return;
          }
        }
      }
    }
  }

  /*
  while ((timeClient.getHours() == OraSveglia) && (timeClient.getMinutes() > OraSveglia) && ( Inizio >= millis() ))
  {
    
    int dOra = timeClient.getHours() / 10;
    int uOra = timeClient.getHours() % 10;

    int dMinuti = timeClient.getMinutes() / 10;
    int uMinuti = timeClient.getMinutes() % 10;

    Clock.ControlloOrologio(dOra, uOra, dMinuti, uMinuti);
  }
  */
  unsigned long OrologioTime = millis();
  while (OrologioTime + 2500 >= millis())
  {
    DisplaySveglia( timeClient.getHours(), timeClient.getMinutes() );

    CambioOrarioSveglia();
  }
}

int ControlloMessaggi()
{
  int i = 0;
  if (radio.available())
  {
    radio.read(&msg, 10);
    delay(20);
    if (strcmp(msg, "NOSuono\0") == 0)
    {
      i = 1;
    }
    else if (strcmp(msg, "OffSveglia\0") == 0)
    {
      i = 2;
    }
  }
  return i;
}

void Megalovania()
{
  for (int thisNote = 0; thisNote < 208; thisNote++)
  {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pinBuzzerPassivo, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.80;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone();

    if (ControlloMessaggi() == 1)
    {
      return;
    }
  }
}

void BuzzerAttivoANDRecezione()
{
  digitalWrite(pinBuzzerAttivo, HIGH);

  unsigned long DurataSuono = millis() + 10000;
  while (DurataSuono >= millis())
  {
    if ((ControlloMessaggi() == 1) || (strcmp(msg, "NOSuono\0") == 0))
    {
      Serial.println("Messaggio 'NOSuono' Ricevuto. Fun");
      digitalWrite(pinBuzzerAttivo, LOW);

      wait = millis() + 25000;
      while (wait >= millis())
      {
        if ((ControlloMessaggi() == 2) || (strcmp(msg, "OffSveglia\0") == 0))
        {
          Serial.println("Messaggio 'OffSveglia' Ricevuto. Fun");
          DurataSuono = 0;
          return;
        }
      }
    }
  }

  digitalWrite(pinBuzzerAttivo, LOW);
}

void CambioOrarioSveglia(){
  unsigned long Start = millis();
  while(digitalRead(pinBottoneOre) == HIGH){}
  if(millis() - Start >= 250){
    while(true){
      DisplaySveglia(OraSveglia, MinutiSveglia);

      if(digitalRead(pinBottoneOre) == HIGH){
        Start = millis();
        while(digitalRead(pinBottoneOre) != LOW){}
        if(millis() - Start < 1000){
          OraSveglia++;
          delay(20);
          if(OraSveglia == 24)
            OraSveglia = 0;
        }
        else{
          while(true){
            DisplaySveglia(OraSveglia, MinutiSveglia);

            if(digitalRead(pinBottoneOre) == HIGH){
              Start = millis();
              while(digitalRead(pinBottoneOre) != LOW){}
              if(millis() - Start < 1000){
                MinutiSveglia++;
                delay(20);
                if(MinutiSveglia == 60)
                  MinutiSveglia = 0;

              }
              else{
                Start = millis() + 3000;
                unsigned long ciclo = 0;
                while( Start >= millis() ){
                  ciclo = millis() + 400;
                  while( ciclo >= millis() )
                  DisplaySveglia(OraSveglia, MinutiSveglia);

                  ciclo = millis() + 200;
                  while( ciclo >= millis() )
                  DisplaySveglia(69, 69);
                }
                Serial.print(OraSveglia);
                Serial.print(":");
                Serial.println(MinutiSveglia);
                return;
              }
            }
          }
        }
        
        
      }

      
    }
  }
}

void DisplaySveglia(int Ore, int Minuti){
  int dOra = Ore / 10;
  int uOra = Ore % 10;

  int dMinuti = Minuti / 10;
  int uMinuti = Minuti % 10;

  Clock.ControlloOrologio(dOra, uOra, dMinuti, uMinuti);
}


