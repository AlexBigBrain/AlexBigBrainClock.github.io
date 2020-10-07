#ifndef Orologio_h
#define Orologio_h

#include "Arduino.h"

class Orologio
{
public:
	Orologio();
	Orologio(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int dot, int D1, int D2, int D3, int D4);
	void setOrologio(int pinE, int pinD, int dot, int pinC, int pinG, int D4, int pinB, int D3, int D2, int pinF, int pinA, int D1);
	void ControlloOrologio(int dOra, int uOra, int dMinuti, int uMinuti);
	void MostraNumero(int n);
	void PrimoDisplay();
	void SecondoDisplay();
	void TerzoDisplay();
	void QuartoDisplay();
	void NumberZero();
	void NumberOne();
	void NumberTwo();
	void NumberThree();
	void NumberFour();
	void NumberFive();
	void NumberSix();
	void NumberSeven();
	void NumberEight();
	void NumberNine();

private:
	int _pinA;
	int _pinB;
	int _pinC;
	int _pinD;
	int _pinE;
	int _pinF;
	int _pinG;
	int _dot;
	int _D1;
	int _D2;
	int _D3;
	int _D4;
	unsigned long _start;
};

#endif