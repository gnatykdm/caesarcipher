#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100 // Macros for Maximum Length of the Text
#define MAX_FILE_NAME_LENGTH 100 // Macros for Maimum Length of the FILE_NAME


/* @author gnatykdm */
/* @param Realization of the Caesar-Cipher */


// Encoder Function 
char* encoder(const char* input_text, int key) {
    int text_length = strlen(input_text);
    char* encoded = (char*)malloc(text_length + 1);

    for (int i = 0; i < text_length; i++) {
        if (input_text[i] >= 'A' && input_text[i] <= 'Z') {
            encoded[i] = (input_text[i] - 'A' + key) % 26 + 'A'; // For UpperCase
        } else if (input_text[i] >= 'a' && input_text[i] <= 'z') {
            encoded[i] = (input_text[i] - 'a' + key) % 26 + 'a'; // For LowerCase
        } else {
            encoded[i] = input_text[i];
        }
    }

    encoded[text_length] = '\0';
    return encoded; 
}


// Decoder Function
char* decoder(const char* output_text, int key) {
    int text_length = strlen(output_text);
    char* decoded = (char*)malloc(text_length + 1);

    for (int i = 0; i < text_length; i++) {
        if (output_text[i] >= 'A' && output_text[i] <= 'Z') {
            decoded[i] = (output_text[i] - 'A' - key + 26) % 26 + 'A';  // For UpperCase
        } else if (output_text[i] >= 'a' && output_text[i] <= 'z') {
            decoded[i] = (output_text[i] - 'a' - key + 26) % 26 + 'a'; // For LowerCase
        } else {
            decoded[i] = output_text[i];
        }
    }

    decoded[text_length] = '\0';
    return decoded;
}


// Reading Content from the FILE
char* read_file(const char* file_name) {
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File '%s' does not exist. Please try again.\n", file_name);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char* context = (char*)malloc(file_size + 1);
    if (context == NULL) {
        perror("Memory Allocation was Failed");
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(context, 1, file_size, fp);
    if (bytes_read != file_size) {
        perror("Reading File Error");
        fclose(fp);
        free(context);
        return NULL;
    }

    context[file_size] = '\0';
    fclose(fp);

    return context;
}



// Writeing to FILE
void write_file(const char* file_name, const char* content) {
    FILE* fp = fopen(file_name, "w");
    if (fp == NULL) {
        perror("File Opening Error");
        return;
    }

    fputs(content, fp);
    fclose(fp);
}


// Function for Encoding MetaData in File
void encode_file(const char* file_name, int key) {
    char* f_content = read_file(file_name);
    if (f_content == NULL) {
        return;
    }

    char* e_content = encoder(f_content, key);
    write_file(file_name, e_content);

    free(f_content);
    free(e_content);
}

// Function for Decoding MetaData in File
void decode_file(const char* file_name, int key) {
    char* f_content = read_file(file_name);
    if (f_content == NULL) {
        return;
    }

    char* d_content = decoder(f_content, key);
    write_file(file_name, d_content);

    free(f_content);
    free(d_content);
}


// Show Menu BAR
void show_info() {
    printf("\n-----------------------\n");
    printf("      OPTIONS MENU\n");
    printf("-----------------------\n");
    printf("1. Encode Text\n");
    printf("2. Decode Text\n");
    printf("3. Encode Text from File\n");
    printf("4. Decode Text from File\n");
    printf("5. Exit\n");
    printf("-----------------------\n");
}


// Main Function
int main() {
    printf("\n--- Welcome to Encoder-Decoder on Caesar-Cipher ---\n\n");

    bool step = true;
    int user_choose;
    int key;
    while(step) {
        show_info();

        printf("\n#Choose an option: ");
        if (scanf("%d", &user_choose) != 1) {
            printf("!!Invalid input! Please enter a number.!!\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (user_choose) {
            case 1: {
                char in_text[MAX_TEXT_LENGTH];

                printf("\n#Enter the text to encode: ");
                scanf(" %[^\n]", in_text); 

                printf("#Enter the key: ");
                if (scanf("%d", &key) != 1) {
                    printf("!!Invalid input! Please enter a number.!!\n");
                    while (getchar() != '\n'); 
                    continue;
                }
                char* en_text = encoder(in_text, key);
                printf("\n**Encoded Text: %s\n", en_text);
                free(en_text);
            }
            break;
            case 2: {
                char in_text[MAX_TEXT_LENGTH];

                printf("\n#Enter the text to decode: ");
                scanf(" %[^\n]", in_text); 

                printf("#Enter the key: ");
                if (scanf("%d", &key) != 1) {
                    printf("!!Invalid input! Please enter a number.!!\n");
                    while (getchar() != '\n');
                    continue;
                }
                char* de_text = decoder(in_text, key);
                printf("\n**Decoded Text: %s\n", de_text);
                free(de_text);
            }
            break;
            case 3: {
                char file_name_e[MAX_FILE_NAME_LENGTH];

                printf("\n#Enter the name of File to Encode: ");
                scanf(" %[^\n]", file_name_e);
                while (getchar() != '\n'); 

                printf("#Enter the key: ");
                if (scanf("%d", &key) != 1) {
                    printf("!!Invalid input! Please enter a number.!!\n");
                    while (getchar() != '\n');
                    continue;
                }
                encode_file(file_name_e, key);
                printf("\n**Your content in File: %s was Encoded**\n", file_name_e);
            }
            break;
            case 4: {
                char file_name_d[MAX_FILE_NAME_LENGTH];

                printf("\n#Enter the name of File to Decode:  ");
                scanf(" %[^\n]", file_name_d);  // Notice the space before %[^\n]

                printf("#Enter the key: ");
                if (scanf("%d", &key) != 1) {
                    printf("!!Invalid input! Please enter a number.!!\n");
                    while (getchar() != '\n');
                    continue;
                }
                decode_file(file_name_d, key);
                printf("\n**Your content in File: %s was Decoded**\n", file_name_d);
            }
            break;
            case 5:
                printf("\n**Exiting the program. Goodbye!\n");
                step = false;  
                break;
            default:
                printf("\n!!INVALID Option!!\n");
                break;
        }
    }
    return 1;
}