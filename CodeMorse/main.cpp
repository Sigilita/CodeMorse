#include <cstdio>
#include <wiringPi.h>
#include <string.h>
#include <iostream>
#include <map>
#include "main.h"
#include <stdio.h>
using namespace std;

map <char, const char*> morseMap;

/* Declaration of times.*/
const static int basetime = 128000;
// Time to iluminate as a dot.
const static int sleepTime = basetime;
// Time between codes
const static int btwCodes = basetime * 2;
// Time between letters
const static int btwLetters = basetime * 4;
// Time between words.
const static int btwWords = basetime * 8;
void settingWiringPi() {
	cout << "Setting wiringPi" << endl;
	wiringPiSetupGpio();
	pinMode(17, OUTPUT);
}
void turnOn() {
	digitalWrite(17,HIGH);
}
void turnOff() {
	digitalWrite(17,LOW);
}
void initialiseMorse() {
	morseMap = {
		{ 'a',"._" },
		{ 'b',"_..." },
		{ 'c',"_._." },
		{ 'd',"_.." },
		{ 'e',"." },
		{ 'f',".._." },
		{ 'g',"__." },
		{ 'h',"...." },
		{ 'i',".." },
		{ 'j',".___" },
		{ 'k',"_._" },
		{ 'l',"._.." },
		{ 'm',"__" },
		{ 'n',"_." },
		{ 'o',"___" },
		{ 'p',".__." },
		{ 'q',"__._" },
		{ 'r',"._." },
		{ 's',"..." },
		{ 't',"_" },
		{ 'u',".._" },
		{ 'v',"..._" },
		{ 'w',".__" },
		{ 'x',"_.._" },
		{ 'y',"_.__" },
		{ 'z',"__.." },
		{ '1',".____" },
		{ '2',"..___" },
		{ '3',"...__" },
		{ '4',"...._" },
		{ '5',"....." },
		{ '6',"_...." },
		{ '7',"__..." },
		{ '8',"___.." },
		{ '9',"____." },
		{ '0',"_____" } };
}
const char * FindMorseCharacter(char character) {
	return morseMap.find(character)->second;
}
int main()
{
	settingWiringPi();
	initialiseMorse();
	std::cout << "Please, introduce a sentence to convert into morse code" << std::endl;
	std::string sentence;
	// If we are going to read a sentece that could have comas and dots, and whitespaces, i could 
	// just declare const char * and iterate the pointer.
	getline(cin, sentence);
	cout << "Testing lights" << endl;
	turnOn();
	delay(2);
	turnOff();
	for (unsigned int i = 0; i < sentence.length(); i++) {
		turnOff();
		if (sentence[i] == ' ') {

			delayMicroseconds(btwWords);
		}
		else
		{
			const char * morseCode = FindMorseCharacter(tolower(sentence[i]));


			for (unsigned int j = 0; j < strlen(morseCode); j++) {
				turnOn();
				if (morseCode[j] == '.') {
					delayMicroseconds(sleepTime);
					turnOff();
					delayMicroseconds(btwCodes);
				}
				else
				{
					delayMicroseconds(sleepTime * 3);
					turnOff();
					delayMicroseconds(btwCodes);
				}
			}
		}
	}
	return 0;
}