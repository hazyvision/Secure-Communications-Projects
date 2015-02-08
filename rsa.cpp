
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "cryptopp/osrng.h"
#include "cryptopp/rsa.h"
#include "cryptopp/modes.h"
#include "cryptopp/sha.h"
#include "cryptopp/hmac.h"

using namespace CryptoPP;
using namespace std;

void print_string_hex(byte* in, int len){
	for (int i=0; i<len; i++){
		cout << setfill('0') << setw(2) << hex << (short)in[i];
	}
}
int main( ) {
	int keyLength;
	cout<<"Enter input key length: ";
	cin >> keyLength;

	AutoSeededRandomPool rng;
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, keyLength);
	
	//ask user for plaintext
	string m = "";
	cout<< "Enter plaintext: ";
	cin >> m;

	RSA::PublicKey public_key(params);
	RSA::PrivateKey private_key(params);
	string c; // ciphertext
	string restored;

	//Encrypt plain text. 
	clock_t  encryptStart = clock(); //Start Timer
	RSAES_OAEP_SHA_Encryptor e(public_key);
	StringSource ss1(m, true, new PK_EncryptorFilter(rng, e, new StringSink(c)));
	clock_t  encryptEnd = clock(); //End Timer
	double encryptTime = double(encryptEnd - encryptStart) / CLOCKS_PER_SEC;
	//divide encryptionTime by 100 to get time per encryption
	//encryptTime = double(encryptTime / 100.00); 

	//Decrypt cipher text
	clock_t  decryptStart = clock(); //Start Timer
	RSAES_OAEP_SHA_Decryptor d(private_key);
	StringSource ss2(c, true, new PK_DecryptorFilter(rng, d, new StringSink(restored)));
	clock_t  decryptEnd = clock(); //End Timer
	double decryptTime = double(decryptEnd - decryptStart) / CLOCKS_PER_SEC;

	//Save publicKey to file.
	ofstream publicKey;
	publicKey.open("pubKey.txt");
	publicKey << params.GetPublicExponent();
	publicKey.close();

	//Save publicKey to file.
	ofstream privateKey;
	privateKey.open("priKey.txt");
	privateKey << params.GetPrivateExponent();
	privateKey.close();
	
	//print results
	cout << "Plain Text: "<<m<<endl;
	cout << "Ciphered Text: ";
	print_string_hex((byte*)m.data(),m.length());
	cout<<endl;
	cout << "Decrypted Text: " << restored << endl;
	cout << "Encryption Time = " << encryptTime <<" secs" << endl;
	cout << "Decryption Time = " << decryptTime <<" secs" << endl;
	return 0;
}
