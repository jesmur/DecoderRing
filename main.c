#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include "decoder.h"

// define macros
#define ENCRYPT(number, cypher) (number ^ cypher);
#define DECRYPT(number, cypher) (number ^ cypher);

int main() {

    // define arrays, enum and variables
    char START[51]={"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&():;?.,/"};
    char SUB[51]={":;?.,/0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&()"};

    enum type{ENCRYPT = 1, DECRYPT = 2};

    struct decoder cipher;

    cipher.evenmask = 0xa5;
    cipher.oddmask = 0x5a;

    int response;

    //loop to repeatedly prompt for encrypt/decrypt
    do {

        unsigned char stringSeq[80];
        unsigned int numericSeq[80];

        //prompt for user input
        printf("Enter 1 to encrypt or 2 to decrypt (any other key to quit): ");
        scanf("%i", &response);
        flushInput();

        // encrypt text
        if (response == ENCRYPT) {

            printf("Enter a string to encrypt: ");
            scanf("%[^\n]s", &stringSeq);

            // convert string to uppercase and substitute original characters
            for (int i = 0; i <= 80; i++) {
                if (stringSeq[i] != NULL) {
                    stringSeq[i] = toupper(stringSeq[i]);

                    for (int j = 0; j <= 50; j++) {
                        if (stringSeq[i] == START[j]) {
                            stringSeq[i] = SUB[j];
                            break;
                        }
                    }
                    numericSeq[i] = (int) stringSeq[i];

                    // determine odd and even masks
                    if (i % 2 == 0) {
                        numericSeq[i] = ENCRYPT(numericSeq[i], cipher.evenmask);
                    } else {
                        numericSeq[i] = ENCRYPT(numericSeq[i], cipher.oddmask);
                    }
                } else {
                    numericSeq[i] = NULL;
                    break;
                }
            }

            // print numeric cipher groups
            for (int i = 0; i < 80; i++) {
                if (numericSeq[i] == NULL) {
                    break;
                } else {
                    printf("%d ", numericSeq[i]);
                }
            }

            printf("\n\n");
        }

            // decrypt cipher groups
        else if (response == DECRYPT) {

            int counter = 0;
            char temp;

            printf("Enter cypher groups to be decrypted: ");

            // take in user input with space delimiting
            do {
                scanf("%d%c", &numericSeq[counter], &temp);
                counter++;
                numericSeq[counter] = NULL;
            } while (temp != '\n');

            // exclusive or operation on cypher groups
            for (int i = 0; numericSeq[i] != 0; i++) {

                if (i % 2 == 0) {
                    numericSeq[i] = DECRYPT(numericSeq[i], cipher.evenmask);
                }
                else {
                    numericSeq[i] = DECRYPT(numericSeq[i], cipher.oddmask);
                }

                // convert ASCII dec value to char
                stringSeq[i] = (char) numericSeq[i];

                for (int j = 0; j <= 50; j++) {

                    if (stringSeq[i] == SUB[j]) {
                        stringSeq[i] = START[j];
                        break;
                    }
                }

                // convert to uppercase
                stringSeq[i] = toupper(stringSeq[i]);
            }

            // print decrypted message
            printf("%s", stringSeq);
            printf("\n\n");

        }

        else {
            printf("Goodbye.\n\n");
            break;
        }

        memset(&stringSeq[0], 0, sizeof(stringSeq));

    }while(response != 1 || response != 2);
}