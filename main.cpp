#include <assert.h>
#include <iostream>
#include <string>

// Define the Enigma components
//char CHIFFRE[26]              = {'1', '2', '3', '4', '5', '6', '7', '8', '9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26'};
char ROMAN[26]                  = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char STATIC_ROTOR[26]           = {'T', 'L', 'B', 'V', 'R', 'W', 'X', 'Y', 'G', 'Z', 'A', 'S', 'J', 'K', 'F', 'E', 'P', 'O', 'U', 'N', 'H', 'M', 'Q', 'C', 'D', 'I'};
const char ROTOR_I_BASE[26]     = {'L', 'B', 'V', 'O', 'J', 'U', 'Z', 'C', 'G', 'P', 'S', 'Y', 'D', 'T', 'E', 'I', 'H', 'X', 'M', 'A', 'W', 'N', 'Q', 'F', 'R', 'K'};
const char ROTOR_II_BASE[26]    = {'G', 'L', 'R', 'P', 'K', 'W', 'E', 'F', 'S', 'O', 'J', 'Q', 'A', 'U', 'D', 'V', 'I', 'C', 'M', 'Y', 'N', 'X', 'T', 'Z', 'H', 'B'};
char REFLECTOR[26]              = {'Z', 'R', 'J', 'S', 'M', 'I', 'P', 'W', 'F', 'C', 'L', 'K', 'E', 'V', 'U', 'G', 'Y', 'B', 'D', 'X', 'O', 'N', 'H', 'T', 'Q', 'A'};

char getLetterFromRotor(int index, char* r) {
    return r[index];
}

int getIndexFromRotor(char letter, char* r) {
    for (int i = 0; i < 26; i++) {
        if (r[i] == letter) {
            return i;
        }
    }
    return -1;
}

void rotateRotor(char* r) {
    char temp = r[0];
    for (int i = 0; i < 25; i++) {
        r[i] = r[i + 1];
    }
    r[25] = temp;
}

typedef struct {
    char c;
    int index;
} Letter;

Letter processRotor(Letter l, char* r) {
    l.c = getLetterFromRotor(l.index, r);
    l.index = getIndexFromRotor(l.c, ROMAN);
    assert(l.index != -1);
    return l;
}
Letter processReverseRotor(Letter l, char* r) {
    l.index = getIndexFromRotor(l.c, r);
    assert(l.index != -1);
    l.c = getLetterFromRotor(l.index, ROMAN);
    return l;
}


// Function to perform Enigma encryption/decryption with given rotor settings
std::string enigma(const std::string& input) {
    char ROTOR_I[26];
    for(int i = 0; i < 26; i++) {
        ROTOR_I[i] = ROTOR_I_BASE[i];
    }
    char ROTOR_II[26];
    for(int i = 0; i < 26; i++) {
        ROTOR_II[i] = ROTOR_II_BASE[i];
    }

    for(int i = 0; i < 25; i++) {
    //rotateRotor(ROTOR_I);
    }
    std::string output;
    for (char c : input) {
        // Convert to uppercase if necessary
        c = toupper(c);

        int index = getIndexFromRotor(c, ROMAN);
        //std::cout << "Letter: " << c << " at index: " << index << std::endl;
        assert(index != -1);

        Letter l = {c, index};
        std::cout << l.c;

        // Rotate the rotors
        //rotateRotor(ROTOR_I);

        l = processRotor(l, STATIC_ROTOR);
        std::cout << " -> S:" << l.c;

        l = processRotor(l, ROTOR_I);
        std::cout << " -> R1:" << l.c;

        l = processRotor(l, ROTOR_II);
        std::cout << " -> R2:" << l.c;

        l = processRotor(l, REFLECTOR);
        std::cout << " -> ||:" << l.c;

        l = processReverseRotor(l, ROTOR_II);
        std::cout << " -> R2:" << l.c;

        l = processReverseRotor(l, ROTOR_I);
        std::cout << " -> R1:" << l.c;

        l = processReverseRotor(l, STATIC_ROTOR);
        std::cout << " -> S:" << l.c;

        output += l.c;
        std::cout << std::endl;
    }

    return output;

}

int main() {
    std::string originalMessage = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Example encrypted message

    // Decrypt the message using the simplified Enigma machine
    std::string encryptedMessage = enigma(originalMessage);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    std::cout << std::endl;

    std::string decryptedMessage = enigma(encryptedMessage);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}