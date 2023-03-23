#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    bool valid_key;
    int key, length;

    // Checks whether key is the correct amount of command line arguments
    if (argc == 2)
    {
        // Converts key to an integer
        key = atoi(argv[1]);

        // Intialised as false until the key is valid
        valid_key = false;

        length = strlen(argv[1]);

        // Iterates through the key and checks whether it is a numerical value. If not, the program will remind the user of the correct format and exit
        for (int i = 0; i < length; i++)
        {
            if (isdigit(argv[1][i]))
            {
                valid_key = true;
            }
            else
            {
                printf("Usage ./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

    // If the key is valid, it will ask the user to enter the plain text
    if (valid_key == true)
    {
        string str_input = get_string("plaintext: ");
        int length_text = strlen(str_input);

        // Once prompted, the loop counts the length of the string entered
        for (int i = 0; i < length_text; i++)
        {
            // Checks whether the input is uppercase or lowercase
            if (isupper(str_input[i]))
            {
                // The plaintext (uppercase) entered will be shifted by however many letters the key specifies
                str_input[i] = ((str_input[i] - 65 + key) % 26) + 65;
            }
            else if (islower(str_input[i]))
            {
                // The plaintext (lowercase) entered will be shifted by however many letters the key specifies
                str_input[i] = ((str_input[i] - 97 + key) % 26) + 97;
            }
        }
        // Outputs the ciphertext
        printf("ciphertext: %s\n", str_input);

    }
}
