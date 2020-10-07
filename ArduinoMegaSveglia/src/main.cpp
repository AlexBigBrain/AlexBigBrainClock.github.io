#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LedBlue 13
#define LedRed 11
#define LedYellow 9
#define LedGreen 5
#define LedWhite 3

#define ButtonBlue 12
#define ButtonRed 10
#define ButtonYellow 6
#define ButtonGreen 4
#define ButtonWhite 2

int Led[] = {LedBlue, LedRed, LedYellow, LedGreen, LedWhite};
int Button[] = {ButtonBlue, ButtonRed, ButtonYellow, ButtonGreen, ButtonWhite};

unsigned long wait;

char msg[10];
RF24 radio(7, 8, 52, 50, 51);

void ON(int pin)
{
  digitalWrite(pin, HIGH);
}
void OFF(int pin)
{
  digitalWrite(pin, LOW);
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(2, INPUT);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(102);
  radio.setPayloadSize(10);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(0x544d52687CLL);
  radio.openReadingPipe(1, 0xABCDABCD71LL);
  radio.startListening();

  for (int x = 0; x < 5; x++)
  {
    pinMode(Led[x], OUTPUT);
    pinMode(Button[x], INPUT_PULLUP);
  }
}

int Game()
{
  int numR = random(5);
  //digitalWrite(Led[random(numR)], HIGH);
  ON(Led[numR]);
  unsigned long GameDuration = 2500;
  unsigned long StartG = millis();
  while (StartG >= (millis() - GameDuration))
  {
    if (digitalRead(Button[numR]) == LOW)
    {
      OFF(Led[numR]);
      return 1;
    }
  }
  OFF(Led[numR]);
  return 0;
}

void GameStart()
{
  for (int x = 0; x < 5; x++)
  {
    ON(Led[x]);
    delay(250);
    while (digitalRead(Button[x]) != LOW)
    {
    };
  }
  for (int x = 0; x < 5; x++)
  {
    OFF(Led[x]);
  }
  delay(1000);
}

void loop(void)
{
  delay(20000);

  if (radio.available())
  {
    radio.read(&msg, 10);
    Serial.println(msg);
    delay(10);
  }

  if (strcmp(msg, "AvviaMEGA\0") == 0)
  {
    radio.stopListening();
    Serial.println("Gioco Iniziato");
    GameStart();
    Serial.println("Setup Completato");
    wait = millis() + 1000;
    while (wait >= millis())
    {
      if (!radio.write("NOSuono\0", 10))
      {
        Serial.println("Messaggio 'NOSuono' non inviato");
      }
      delay(10);
    }
    Serial.println("Messaggio 'NOSuono' Inviato.");
    delay(50);
    int GamePoint = 0, Games = 7;
    for (int Tentativi = 0; Tentativi < Games; Tentativi++)
    {
      Serial.println("Inizio Tentativo");
      GamePoint += Game();
      Serial.print("I punti sono ");
      Serial.println(GamePoint);
      delay(1000);
      Serial.println("Fine Tentativo");
    }
    if (GamePoint >= 5)
    {
      Serial.println("YOU WON");
      wait = millis() + 15000;
      while (wait >= millis())
      {
        radio.write("NOSuono\0", 10);
        delay(100);
        radio.write("OffSveglia\0", 10);
        delay(100);
      }
      strcpy(msg, "Vinto\0");
      delay(10);
    }
    else
    {
      Serial.println("YOU LOST");
    }
  }
}
