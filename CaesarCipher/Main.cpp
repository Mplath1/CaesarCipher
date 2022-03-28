#include <iostream>
#include <sstream>
#include "CaesarCipher.h"

bool runMainMenu(CaesarCipher &cipher);

int main(){
	CaesarCipher cipher("tHe QuIcK bRoWn FoX jUmPs OvEr ThE LaZy DoG");

	bool run{ true };

	do {
		run = runMainMenu(cipher);
	} while (run);
	return 0;
}


bool runMainMenu(CaesarCipher &cipher){
	std::cout << "\nPlease select an option from the menu below:\n1.Show encrypted message\n2.Decrypt message\n3.Redefine cipher shift\n4.Enter new message\n5.Quit" << std::endl;
	std::string input;
	std::cin >> input;
	std::stringstream streamInput(input);
	int selection;
	int currentKey;
	if (streamInput >> selection) {
		std::cin.clear();
		std::cin.sync();
		switch (selection) {
		case 1:
			std::cout << "Encrypted message:" << cipher.encrypt() << std::endl;
			break;
		case 2:
			std::cout << "Decrypted message:" << cipher.decrypt() << std::endl;
			break;
		case 3:
			std::cout << "Current key is:" << cipher.getKey() << " Enter new key value:" << std::endl;
			int keyValue;
			std::cin >> keyValue;
			currentKey = cipher.getKey();
			if (keyValue < cipher.getAcceptedCharsLength() && keyValue>0) {
				cipher.setKey(std::abs(currentKey - keyValue));
				cipher.encrypt(cipher.getEncryptedText());
				cipher.setKey(keyValue);
			}
			else if (keyValue == 0) {
				std::cout << "Key cannot be 0! This would not be encryption!" << std::endl;
				break;
			}
			else if (keyValue < 0) {//math is correct but problems persist. if -5 is entered then F(5th letter of alphabet) appears as a blank???complains about fancy latin f sometimes???
				cipher.setKey((-1 * currentKey) + 1);
				std::cout << "Key temp set to:" << cipher.getKey() << std::endl;
				cipher.encrypt(cipher.getEncryptedText());
				std::cout << "Shifted to " << cipher.getEncryptedText() << std::endl;
				cipher.setKey(keyValue);
				cipher.encrypt(cipher.getEncryptedText());
			}
			std::cout << "Message re-encrypted with new key" << std::endl;
			break;
		case 4:
			cipher.queryForMessage("Please enter a message:");
			break;
		case 5:
			std::cout << "Exiting Caesars Cipher..." << std::endl;
			return false;
			break;
		default:
			std::cout << "Invalid Selection!\nPlease try again" << std::endl;
			break;
		}
	}
	else {
		std::cout << "Invalid Selection!\nPlease try again" << std::endl;
	}
	return true;
}
