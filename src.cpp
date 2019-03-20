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
void messageToInt(std::string messageString, std::vector<int> & messageInt) {
    for (int i = 0; i < messageString.size(); i++) {
        // 1 dec = 49
        // 0 dec = 48
        messageInt.push_back((int) messageString[i] - 48);
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
        sum += H[row][j] * messageInt[j]; //wiersz H * wiersz wiadomości
    }
    sum %= 2; // jeśli 0 to dopisujemy 0 jeśli 1 to 1
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
            if (j == H_ROWS - 1) {
                messageInt[i] ^= 1; //(XOR)
                return;
            }
        }
    }

    //Jeśli wystąpiły 2 błędy
    for (int i = 0; i < H_COL; i++) {
        for (int j = i; j < H_COL; j++) {
            for (int k = 0; k < H_ROWS; k++) { // porówna 1 do 1
                //jeśli suma kolumn będzie równa wektorowi error to numery tych kolumn
                //oznaczają numery uszkodzonych bitów
                if ((H[k][i] ^ H[k][j]) != error[k]) {
                    break;
                }
                if(k == H_ROWS - 1) {
                    messageInt[i] ^= 1; //XOR błędne
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
        messageInt.push_back(sum); // dopisywanie bitu kontrolnego do wiadomości
    }
}

//wypisuje podany vector
void writeMessage(std::vector<int> messageInt) {
    for (int i = 0; i < messageInt.size(); i++) {
        std::cout << messageInt[i];
    }
    std::cout << std::endl;
}


std::vector<std::string> cheangeCharToBinString(std::vector<unsigned char> message) {

    std::vector<std::string> messageReady;

    for (int i = 0; i <= message.size(); i++) {

        int val = message[i];
        std::string messageString;

        while ( val > 0) {
            if(val % 2 == 1) {
                messageString.push_back('1');
            } else {
                messageString.push_back('0');
            }
            val /= 2;
        }
        while (messageString.size() % 8 != 0) {
            messageString.push_back('0');
        }

        reverse(messageString.begin(), messageString.end()); //odwrócenie wiadomości bo w złą stronę
        messageReady.push_back(messageString); //vector stringów
        messageString.clear(); //czyszczenie przed kolejnym
    }
    return messageReady;
}

//zamienia wektor kintów 01010101 na char
void changeToChar(std::vector<int> input) {
    int sum = 0;
    int j = 0;
    for (int i = 8; i > 0; --i) {
        sum += pow(2, i - 1) * input[j];
        j++;
    }
    writeCharToFile((char)sum);
}



///////////////////////ODCZYT ZAPIS DO PLIKU/////////////////////////////////

//odczyt z pliku binarnie
std::vector<unsigned char> readMessageFromFile() {

    std::ifstream file("plikDoZakodowania.txt", std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
    return buffer;
}

//zapis do pliku normalnie
void writeToFileTxt(std::vector<int> messageInt, std::string name) {

    std::string line;
    std::fstream file;
    file.open(name, std::ios::out | std::ios::app);
    if(file.good())
    {
        for (int i = 0; i < messageInt.size(); i++) {
            file << messageInt[i];
        }
        file.close();
    }
}

//odczytuje wiadomość poprawia i zapisuje w pliku

void readWriteFromFileAndFix() {

    std::string line;
    std::fstream file;
    std::string messageToModify;
    std::string messageModified;


    //odczytujemy wiadomośc z pliku
    file.open("plikZakodowany.txt", std::ios::in);
    if(file.good() == true)
    {
        while(!file.eof())
        {
            getline(file, line);
            messageToModify += line;
        }
        file.close();
    }

    std::vector<int> messageInt;
    std::vector<int> messageFinal;

    //bierzemy po 12 bitów/znaków zamieniamy na int,
    //sprawdzamy, poprawiamy, usuwamy dodatkowe bity, zapisujemy popraione
    for ( int i = 0; i < messageToModify.size(); i += 17) {
        for (int j = 0; j < 17; j++) {
            messageModified += messageToModify[j + i];
        }

        messageToInt(messageModified, messageInt);
        checkIfMessageIsCorrect(messageInt);

        writeToFileTxt(messageInt, "poprawionyBin.txt");

        for (int i = 0; i < 8; i++) {
            messageFinal.push_back(messageInt[i]);
        }
        messageInt.clear();
        messageModified.clear();
        //zamienia na char i zapisuje do pliku
        changeToChar(messageFinal);
        messageFinal.clear();
    }
}

//zapisuje do pliku odkodowanom wiadomość
void writeCharToFile(char input) {

    std::string line;
    std::fstream file;

    file.open("odkodowanyPoprawiony.txt", std::ios::out | std::ios::app);
    if(file.good())
    {
        file << input;
        file.close();
    }
}