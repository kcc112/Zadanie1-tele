#include "header.h"

int main() {

    std::vector<int> messageIntCorrect;
    std::vector<int> messageIntDamaged;
    std::string messageString;
    int bitNumOne;
    int bitNumTwo;

    std::cout << "Podaj ośmiobitową wiadomość np: 01010101" << std::endl;
    std::cin >> messageString;

    if (messageString.size() != 8) {
        std::cout << "Wiadomość nie posiada ośmiu znaków" << std::endl;
        return 1;
    }

    for (int i = 0; i < messageString.size(); i++) {
        if((messageString[i] != '1') && (messageString[i] != '0')) {
            std::cout << "Bity mają wartość  1 albo 0" << std::endl;
            return 1;
        }
    }

    //zamiana char na int
    messageToInt(messageString, messageIntCorrect);

    //kodwoanie
    addParityBitsToMessage(messageIntCorrect);

    std::cout << "Wiadomość po dodaniu bitów parzystości:" << std::endl;
    writeMessage(messageIntCorrect);

    std::cout << "Podaj nr bitów które chcesz zmienić 1-17 lub 0 jeśli wiadomość "
                 "nie powinna zostać uszkodzona:" << std::endl;
    std::cout << "Pierwszy: " << std::endl;
    std::cin >> bitNumOne;
    std::cout << "Drugi: " << std::endl;
    std::cin >> bitNumTwo;

    if (bitNumOne > 17 || bitNumTwo > 17 || bitNumTwo < 0 || bitNumOne < 0){
        std::cout << "Niepoprawny numer bitu" << std::endl;
        return 1;
    }

    //wiadomość do uszkodzenia
    messageIntDamaged = messageIntCorrect;

    //wiadomość ulega uszkodzeniu
    changeBit(bitNumOne, messageIntDamaged);
    changeBit(bitNumTwo, messageIntDamaged);

    std::cout << "Uszkodzona wiadomość:" << std::endl;
    writeMessage(messageIntDamaged);

    //sprawdzenie czy wiadomość uległa uszkodzeniu jeśli tak to  zostanie naprawiona
    checkIfMessageIsCorrect(messageIntDamaged);

    std::cout << "Poprawiona wiadomość:" << std::endl;
    writeMessage(messageIntDamaged);

    return 0;
}