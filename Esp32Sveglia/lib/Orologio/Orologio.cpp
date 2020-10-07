#include "Orologio.h"
#include "Arduino.h"

Orologio::Orologio() {}

Orologio::Orologio(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int dot, int D1, int D2, int D3, int D4)
{
  pinMode(pinA, OUTPUT);
  _pinA = pinA;
  pinMode(pinB, OUTPUT);
  _pinB = pinB;
  pinMode(pinC, OUTPUT);
  _pinC = pinC;
  pinMode(pinD, OUTPUT);
  _pinD = pinD;
  pinMode(pinE, OUTPUT);
  _pinE = pinE;
  pinMode(pinF, OUTPUT);
  _pinF = pinF;
  pinMode(pinG, OUTPUT);
  _pinG = pinG;
  pinMode(dot, OUTPUT);
  _dot = dot;
  pinMode(D1, OUTPUT);
  _D1 = D1;
  pinMode(D2, OUTPUT);
  _D2 = D2;
  pinMode(D3, OUTPUT);
  _D3 = D3;
  pinMode(D4, OUTPUT);
  _D4 = D4;
}

void Orologio::setOrologio(int pinE, int pinD, int dot, int pinC, int pinG, int D4, int pinB, int D3, int D2, int pinF, int pinA, int D1)
{
  pinMode(pinA, OUTPUT);
  _pinA = pinA;
  pinMode(pinB, OUTPUT);
  _pinB = pinB;
  pinMode(pinC, OUTPUT);
  _pinC = pinC;
  pinMode(pinD, OUTPUT);
  _pinD = pinD;
  pinMode(pinE, OUTPUT);
  _pinE = pinE;
  pinMode(pinF, OUTPUT);
  _pinF = pinF;
  pinMode(pinG, OUTPUT);
  _pinG = pinG;
  pinMode(dot, OUTPUT);
  _dot = dot;
  pinMode(D1, OUTPUT);
  _D1 = D1;
  pinMode(D2, OUTPUT);
  _D2 = D2;
  pinMode(D3, OUTPUT);
  _D3 = D3;
  pinMode(D4, OUTPUT);
  _D4 = D4;
}

void Orologio::ControlloOrologio(int dOra, int uOra, int dMinuti, int uMinuti)
{
  unsigned long _start = millis();

  while (_start >= millis() - 900)
  {
    this->PrimoDisplay();
    this->MostraNumero(dOra);
    this->SecondoDisplay();
    digitalWrite(_dot, HIGH);
    this->MostraNumero(uOra);
    digitalWrite(_dot, LOW);
    this->TerzoDisplay();
    this->MostraNumero(dMinuti);
    this->QuartoDisplay();
    this->MostraNumero(uMinuti);
  }
}

void Orologio::MostraNumero(int n)
{
  switch (n)
  {
  case 0:
    this->NumberZero();
    break;
  case 1:
    this->NumberOne();
    break;
  case 2:
    this->NumberTwo();
    break;
  case 3:
    this->NumberThree();
    break;
  case 4:
    this->NumberFour();
    break;
  case 5:
    this->NumberFive();
    break;
  case 6:
    this->NumberSix();
    break;
  case 7:
    this->NumberSeven();
    break;
  case 8:
    this->NumberEight();
    break;
  case 9:
    this->NumberNine();
    break;
  default:
    break;
  }
}

void Orologio::PrimoDisplay()
{
  digitalWrite(_D1, LOW);
  digitalWrite(_D2, HIGH);
  digitalWrite(_D3, HIGH);
  digitalWrite(_D4, HIGH);
}

void Orologio::SecondoDisplay()
{
  digitalWrite(_D1, HIGH);
  digitalWrite(_D2, LOW);
  digitalWrite(_D3, HIGH);
  digitalWrite(_D4, HIGH);
}

void Orologio::TerzoDisplay()
{
  digitalWrite(_D1, HIGH);
  digitalWrite(_D2, HIGH);
  digitalWrite(_D3, LOW);
  digitalWrite(_D4, HIGH);
}

void Orologio::QuartoDisplay()
{
  digitalWrite(_D1, HIGH);
  digitalWrite(_D2, HIGH);
  digitalWrite(_D3, HIGH);
  digitalWrite(_D4, LOW);
}

void Orologio::NumberZero()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, LOW);
  delay(1);
}

void Orologio::NumberOne()
{
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
  delay(1);
}

void Orologio::NumberTwo()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberThree()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberFour()
{
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberFive()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberSix()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberSeven()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
  delay(1);
}

void Orologio::NumberEight()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
  delay(1);
}

void Orologio::NumberNine()
{
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
  delay(1);
}