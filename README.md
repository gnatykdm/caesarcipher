# Caesar Cipher in C

This is a simple implementation of the Caesar Cipher in C. The Caesar Cipher is a substitution cipher where each letter in the plaintext is shifted a certain number of places down or up the alphabet.

## Usage

1. **Encrypt**: To encrypt a message using the Caesar Cipher, run the program and choose the "Encrypt" option. Enter the text you want to encrypt and the shift value (the number of positions each letter should be shifted). The encrypted text will be displayed.

2. **Decrypt**: To decrypt an encrypted message, run the program and choose the "Decrypt" option. Enter the encrypted text and the shift value used during encryption. The decrypted text will be displayed.

3. **Exit**: To exit the program, choose the "Exit" option.

## How to Compile and Run

1. **Compile**: Open a terminal and navigate to the directory containing the source code (`caesar_cipher.c`). Compile the code using a C compiler such as GCC:
   
   ```bash
   gcc -o caesar_cipher caesar_cipher.c
