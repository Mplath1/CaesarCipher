#include "CaesarCipher.h"

CaesarCipher::CaesarCipher() {
	setKey(4);
}

CaesarCipher::CaesarCipher(std::string stringToEncrypt) {
	setKey(4);
	encrypt(stringToEncrypt);
}

CaesarCipher::~CaesarCipher() {
}


const int CaesarCipher::getKey() {
	return key;
}

void CaesarCipher::setKey(int keyValue) {
	if (keyValue <= getAcceptedCharsLength() && keyValue > 0) {
		key = keyValue;
	}
	else if (keyValue > getAcceptedCharsLength()) {
		key = (keyValue - getAcceptedCharsLength());
	}
	else if (keyValue == 0) {
		key = ((getAcceptedCharsLength() - keyValue));
	}
	else if (keyValue < 0) {
		key = (getAcceptedCharsLength() - std::abs(keyValue));
	}
}

const std::string CaesarCipher::getEncryptedText() {
	return encryptedText;
}

void CaesarCipher::setEncryptedText(std::string message) {
	encryptedText = message;
}

char* CaesarCipher::getAcceptedChars() {
	return acceptedChars;
}

const int CaesarCipher::getAcceptedCharsLength() {
	return acceptedCharsLength;
}

//returns encrpyted plaintext message
std::string CaesarCipher::encrypt() { 
	return encryptedText;
}

//encrpyts plaintext, sets encrpyted text, returns encrypted text
std::string CaesarCipher::encrypt(std::string stringToEncrypt) {
	convertToUpperCase(stringToEncrypt);
	bool valid = validateInput(stringToEncrypt);

	if (valid) {
		std::string newlyEncrypted{};
		for (std::string::iterator it = stringToEncrypt.begin(); it != stringToEncrypt.end();it++) {
			for (int i = 0;i < getAcceptedCharsLength();i++) {//arrayLength
				if (*it == (getAcceptedChars()[i]) && i <= (getAcceptedCharsLength() - getKey())) {//edge cases are arrayLength - key
				//std::cout<<"was "<<*it<<" and is now encrypted to ";
					//*it = getAcceptedChars()[i+(getKey())];
					newlyEncrypted += (getAcceptedChars()[i + (getKey())]);
					//std::cout<<*it<<std::endl;
					break;
				}
				else if (*it == (getAcceptedChars()[i]) && i > (getAcceptedCharsLength() - getKey())) {
					//std::cout<<"was "<<*it<<" and is now encrypted to ";
					//*it = getAcceptedChars()[i-((getAcceptedCharsLength()+1)-getKey())]; 
					newlyEncrypted += (getAcceptedChars()[i - ((getAcceptedCharsLength() + 1) - getKey())]); //  i-((arraylength+1)-key)
					//std::cout<<*it<<std::endl;
				}
			}
		}
		setEncryptedText(newlyEncrypted);
		return newlyEncrypted;
	}
	else {
		std::cout << "Unable to encrypt! Unrecognized characters!" << std::endl;
	}
}

//returns plaintext version of encrypted text
std::string CaesarCipher::decrypt() {
	std::string newlyDecrypted{};
	for (std::string::iterator it = encryptedText.begin(); it != encryptedText.end();it++) {
		for (int i = 0;i < getAcceptedCharsLength();i++) {
			if (*it == (getAcceptedChars()[i]) && i > (getKey() - 1)) { //key -1 
				//std::cout<<"Encrypted as "<<*it<<" and is now decrypted to ";//
				//*it = getAcceptedChars()[i-(getKey())];//
				newlyDecrypted += (getAcceptedChars()[i - getKey()]);
				//std::cout<<*it<<std::endl;//
				break;
			}
			else if (*it == (getAcceptedChars()[i]) && i <= (getKey() - 1)) {
				//std::cout<<"Encrypted as "<<*it<<" and is now decrypted to ";//
				//*it = getAcceptedChars()[i+((getAcceptedCharsLength()+1)-getKey())];// 
				//std::cout<<*it<<std::endl;//
				newlyDecrypted += (getAcceptedChars()[i + ((getAcceptedCharsLength() + 1) - getKey())]); //  i+ ((arraylength+1)-key)
				break;
			}
		}
	}
	return newlyDecrypted;
}


bool CaesarCipher::validateInput(std::string input) {
	bool valid{ true };
	for (std::string::iterator it = input.begin(); it != input.end(); it++) {
		bool found{ false };
		for (int i = 0;i < getAcceptedCharsLength();i++) {
			if (*it == getAcceptedChars()[i]) {
				found = true;
				break;
			}
		}
		if (!found) {
			valid = false;
			std::cout << "Can't Encrypt:" << *it << std::endl;
			break;
		}
	}
	return valid;
}

void CaesarCipher::convertToUpperCase(std::string &input) {
	for (int i = 0; i < input.size();i++) {
		if (input.at(i) != ' ') {
			input.at(i) = std::toupper(input.at(i));
		}
	}
}

//displays prompt and allows used to enter in char which must be within acceptedChar array
void CaesarCipher::queryForMessage(std::string prompt) {
	std::cout << prompt << std::endl;
	std::string input;
	std::getline(std::cin, input);
	encrypt(input);
}
