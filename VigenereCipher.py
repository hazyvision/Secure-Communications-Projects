# Adriene Cuenco

# ****Compiled with Python 2.7.6****
#Encryption/Decryption software using Vigenere Cipher
#Note: Key = vig
 
#!/usr/bin/python
 
def encrypt(plainText,key):
    ciphertext = ""
    stretch = stretchKey(plainText,key)
    i = 0
    password = "vig"
    if str(key) == password:
        for c in plainText:
            # encrypt  = (c+k) mod 26 and build and save ciphertext
            # c is the ith char of text. k is ith char of key phrase
            ciphertext+= getAlphabet(( getNumeric(c) + getNumeric(stretch[i])) % 26)    
            i+=1
    else:
        print("Key not valid!") 
    return ciphertext;
def decrypt(ciphertext,key):
    plainText = ""
    stretch = stretchKey(ciphertext,key)
    i = 0
    password = "vig"
    if str(key) == password:
        for c in ciphertext:
            #decrypt = (26 +c - k) mod 26
            #c is the ith char of text. k is ith char of key phrase
            plainText+=getAlphabet( (26 + getNumeric(c) - (getNumeric(stretch[i]))) % 26 )
            i+=1
    else:
        print("key not valid!")
    return plainText;   
def getNumeric(char):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    return alphabet.index(char)
def getAlphabet(num):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    return alphabet[num];
#Stretches the key to the length of the cipher or plain text
def stretchKey(text,key):
    result = ""
    ctr = 0
    for i in text:
        #When ctr reaches the last character of the key; restart ctr
        if ctr >= len(key):
            ctr = 0
        #else build result from key
        result+=key[ctr]
        ctr+=1
    return result
 
     
#--------Main-------------------------------------------
print("******Vigenere Cipher******")
enOrDe = input("Press 1 to Decrypt. Press 2 to Encrypt: ")
 
if enOrDe is 1: # Start Decrypt
    message = raw_input("Enter Cipher Text: ")
    keyPhrase = raw_input("Enter key: ")
    #lowercase message
    message = message.lower()
    #remove spaces
    message = message.replace(" ", "")
    print("")
    print("Plain Text: " + decrypt(message,keyPhrase))
elif enOrDe is 2: # Start Encrypt
    message = raw_input("Enter Plain Text: ")
    keyPhrase = raw_input("Enter key: ")
    #lowercase message
    message = message.lower()
    #remove spaces
    message = message.replace(" ", "")
    print("")
    print("Cipher Text: " + encrypt(message,keyPhrase))
else: #Invalid Key
    print( "Input not valid")
    
