#include <assert.h>
#include <iostream>
#include <string>

// Define the Enigma components
char ROMAN[26]      = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char REFLECTOR[26]  = {'Z', 'R', 'J', 'S', 'M', 'I', 'P', 'W', 'F', 'C', 'L', 'K', 'E', 'V', 'U', 'G', 'Y', 'B', 'D', 'X', 'O', 'N', 'H', 'T', 'Q', 'A'};
char ROTOR_I[26]    = {'K', 'J', 'H', 'G', 'F', 'D', 'S', 'A', 'L', 'E', 'W', 'Q', 'R', 'T', 'V', 'B', 'N', 'M', 'Z', 'U', 'I', 'O', 'P', 'Y', 'X', 'C'};
char ROTOR_II[26]   = {'P', 'Y', 'X', 'C', 'T', 'V', 'B', 'N', 'M', 'F', 'D', 'S', 'A', 'G', 'H', 'K', 'L', 'J', 'R', 'E', 'W', 'Q', 'O', 'I', 'U', 'Z'};

char LAMPE[26]      = {'P', 'Y', 'X', 'C', 'T', 'V', 'B', 'N', 'M', 'F', 'D', 'S', 'A', 'G', 'H', 'K', 'L', 'J', 'R', 'E', 'W', 'Q', 'O', 'I', 'U', 'Z'};
char PLUGBOARD[26]  = {'K', 'J', 'H', 'G', 'F', 'D', 'S', 'A', 'L', 'E', 'W', 'Q', 'R', 'T', 'V', 'B', 'N', 'M', 'Z', 'U', 'I', 'O', 'P', 'Y', 'X', 'C'};
char KEYBOARD[26]   = {'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'P', 'Y', 'X', 'C', 'V', 'B', 'N', 'M', 'L'};

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


// Function to perform Enigma encryption/decryption with given rotor settings
std::string enigma(const std::string& input) {

    std::string output;
    for (char c : input) {
        // Convert to uppercase if necessary
        c = toupper(c);

        int index = getIndexFromRotor(c, ROMAN);
        //std::cout << "Letter: " << c << " at index: " << index << std::endl;
        assert(index != -1);

        Letter l = {c, index};
        std::cout << "Original - Letter: " << l.c << " at index: " << l.index << std::endl;

        // Rotate the rotors
        //rotateRotor(ROTOR_I);

        l = processRotor(l, ROTOR_I);
        std::cout << "Rotor 1 - Letter: " << l.c << " at index: " << l.index << std::endl;

        l = processRotor(l, REFLECTOR);
        std::cout << "Reflector - Letter: " << l.c << " at index: " << l.index << std::endl;

        l = processRotor(l, ROTOR_I);
        std::cout << "Rotor 1 - Letter: " << l.c << " at index: " << l.index << std::endl;

        output += l.c;
        std::cout << std::endl;
    }

    return output;

}

int main() {
    std::string originalMessage = "HELLO"; // Example encrypted message

    // Decrypt the message using the simplified Enigma machine
    std::string encryptedMessage = enigma(originalMessage);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    std::cout << std::endl;

    std::string decryptedMessage = enigma(encryptedMessage);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}