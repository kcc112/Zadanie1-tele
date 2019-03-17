//
// Created by kamil on 3/17/19.
//

#include "header.h"
#define H_ROWS 9 //ilość wierszy macierzy H
#define H_COL 17 //ilość kolumn macierzy H


//minimalna jest chyba 7x15 ale jest zdecydowanie ciężej znaleźć odpowiednie kolumny
int H[H_ROWS][H_COL]{{1, 1, 0, 1, 1, 1, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0, 0},
                     {1, 0, 1, 0, 0, 1, 0, 1,  0, 1, 0, 0, 0, 0, 0, 0, 0},
                     {1, 0, 0, 1, 1, 0, 1, 0,  0, 0, 1, 0, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 1, 1, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0, 0},
                     {0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 0, 0, 0, 1, 0, 0, 0},
                     {1, 1, 1, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 1, 0, 0},
                     {0, 1, 0, 0, 1, 0, 1, 0,  0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 0, 0, 0, 1, 0, 1, 1,  0, 0, 0, 0, 0, 0, 0, 0, 1}};

//zamiana wiadomość na wartości int
void messageToInt(std::string messageString, std::vector<int> & messageIntCorrect) {
    for (int i = 0; i < messageString.size(); i++) {
        // 1 dec = 49
        // 0 dec = 48
        messageIntCorrect.push_back((int) messageString[i] - 48);
    }

}

//zmienia bit w vector na podanym  miejscu jeśli zero to nic nie zminia
void changeBit(int bitNum, std::vector<int> & messageInt) {
    if (bitNum != 0) {
        if (messageInt[bitNum - 1] == 0) {
            messageInt[bitNum - 1] = 1;
        } else {
            messageInt[bitNum - 1] = 0;
        }
    }

}

//aby nie powtarzać kodu
int modTow(std::vector<int> messageInt, int row) {
    int  sum = 0;
    for ( int j = 0; j < messageInt.size(); j++) {
        sum += H[row][j] * messageInt[j];
    }
    sum %= 2;
    return sum;
}

//poprawia błąd jeżeli taki zaistniał HR = H(T + R) = HT + HE = HE gdzie R = T + E
//H - macierz wcześniej ustalona
//T - wiadomość
//E - błąd
//HT = 0
//Numer kolumny macierzy H która jest identyczna co HE oznacza nr bitu który należy zkorygować
void correctError(std::vector<int> & messageInt, std::vector<int> error) {

    //sprawdzenie gdyby wystąpił tylko 1 błąd
    for (int i = 0; i < H_COL; i++) {
        for (int j = 0; j < H_ROWS; j++) {
            if (error[j] != H[j][i]) {
                break;
            }
            if (j == 8) {
                messageInt[i] ^= 1; //(XOR)
                return;
            }
        }
    }

    //Jeśli wystąpiły 2 błędy
    for (int i = 0; i <H_COL; i++) {
        for (int j = i; j < H_COL; j++) {
            for (int k = 0; k < H_ROWS; k++) {
                //jeśli suma kolumn będzie równa wektorowi error to numery tych kolumn
                //oznaczają numery uszkodzonych bitów
                if ((H[k][i] ^ H[k][j]) != error[k]) {
                    break;
                }
                if(k == H_ROWS - 1) {
                    messageInt[i] ^= 1;
                    messageInt[j] ^= 1;
                    return;
                }
            }
        }
    }

}

//sprawda czy jakiś bit uległ uszkodzeniu
void checkIfMessageIsCorrect(std::vector<int> & messageInt) {
    bool flag = true;
    std::vector<int> error;
    int sum = 0;

    for (int i = 0; i < H_ROWS; i++) {
        sum = modTow(messageInt, i);
        error.push_back(sum);
        if (sum == 1) flag = false;
    }

    if (!flag) correctError(messageInt, error);
}

//Wyliczanie bitów parzystości na podstawie macierzy H
//oraz dopisywanie ich do wiadomości
void addParityBitsToMessage(std::vector<int> & messageInt) {
    int sum = 0;
    for (int i = 0; i < H_ROWS; i++) {
        sum = modTow(messageInt, i);
        messageInt.push_back(sum);
    }
}

//wypisuje podany vector
void writeMessage(std::vector<int> messageInt) {
    for (int i = 0; i < messageInt.size(); i++) {
        std::cout << messageInt[i];
    }
    std::cout << std::endl;
}
