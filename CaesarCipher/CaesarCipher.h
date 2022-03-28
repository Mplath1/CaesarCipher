#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H
#include <iostream>
#include <string>
#include <cctype> 
#include <cmath>


class CaesarCipher
{
private:
	int key;
	std::string encryptedText;
	char acceptedChars[37] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ' };
	int acceptedCharsLength = sizeof(acceptedChars);//used by functions. as all functions use variables instead of constants this in theory allows for any charSet to be loaded
	bool validateInput(std::string input);
	void convertToUpperCase(std::string &input);
	char* getAcceptedChars();





public:
	CaesarCipher();
	CaesarCipher(std::string stringToEncrypt);
	~CaesarCipher();

	const int getKey();
	void setKey(int keyValue);
	std::string encrypt();
	std::string decrypt();
	void queryForMessage(std::string prompt);
	void setEncryptedText(std::string message);
	std::string encrypt(std::string stringToEncrypt);
	const std::string getEncryptedText();
	const int getAcceptedCharsLength();
};
#endif // CAESARCIPHER_H