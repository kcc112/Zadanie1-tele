//
// Created by kamil on 3/17/19.
//

#ifndef ZAD1A_TELE_INCLUDE_H
#define ZAD1A_TELE_INCLUDE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <bits/stdc++.h> //revere

//zamienia wiadomość zapisaną w stringu na vector<int>
void messageToInt(std::string messageString, std::vector<int> & messageIntCorrect);
//zamienia bit o podanym numerze w vector na przeciwny
void changeBit(int bitNum, std::vector<int> & messageInt);
//(h11 * a1 + h12 * a2)%2 = 0
int modTow(std::vector<int> messageInt, int row);
//poprawia zmieniony bit
void correctError(std::vector<int> & messageInt, std::vector<int> error);
//sprawdza czy bit został zmieniony
void checkIfMessageIsCorrect(std::vector<int> & messageInt);
//oblicza na podstawie macierzy H bity które trzeba dodać do wiadomości
void addParityBitsToMessage(std::vector<int> & messageInt);
//do wypisywania wiadomości
void writeMessage(std::vector<int> messageInt);
//zamienia char na binary string
std::vector<std::string> cheangeCharToBinString(std::vector<unsigned char> message);

//////////PLIKI/////////////////////////
//odczytuje wiadomość z pliku
std::vector<unsigned char> readMessageFromFile();
//zapisuje wiadomość do pliku jako string
void writeToFileTxt(std::vector<int> messageInt, std::string name);
//zapisuje do pliku odkodowanom wiadomość
void writeCharToFile(char input);
//odczytuje i naprawia wiadomość + zapis do pliku
void readWriteFromFileAndFix();

#endif //ZAD1A_TELE_INCLUDE_H
