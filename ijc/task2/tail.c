// autor: Mikuláš Šťastný, FIT
// uloha: IJC DU2, příklad A)
// přeloženo: gcc 11.2
// datum: 20. 4. 2022

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define MAX_CHARS_ON_LINE 4095

void tail(FILE *file, int n){

    if(n <= 0){
        return; 
    }

    // Pole pro uchování posledních n řádků ze souboru.
    char circle_buffer[n][MAX_CHARS_ON_LINE];

    // Pole pro uchování znaků jednoho řádku.
    char one_line[MAX_CHARS_ON_LINE];
    int line_counter = 0;
    bool error_printed = false;

    while(fgets(one_line, MAX_CHARS_ON_LINE, file) != NULL){
        // Kontroluje úplnost řádku
        if(one_line[strlen(one_line)-1] != '\n'){
            if(!error_printed){
                fprintf(stderr, "Některý řádek v souboru překročil maximální délku řádku!\n");
                error_printed = true;
            }
            // Čte řádek pomocí fgets, dokud se v tmp poli neobjeví znak konce řádku
            if(one_line[MAX_CHARS_ON_LINE-1] != '\n'){
                char tmp[MAX_CHARS_ON_LINE];
                bool continue_reading = true;

                while(continue_reading){
                    fgets(tmp, MAX_CHARS_ON_LINE, file);
                    for(int i = 0; i < MAX_CHARS_ON_LINE; i++){
                        if(tmp[i] == '\n' || tmp == NULL){
                            continue_reading = false;
                        }
                    }
                }
            }
            // Zkrátí textový řetězec podle velikosti bufferu
            one_line[MAX_CHARS_ON_LINE-2] = '\n';
            one_line[MAX_CHARS_ON_LINE-1] = '\0';
        }

        if(line_counter < n){
            strcpy(circle_buffer[line_counter], one_line);
        }
        else{
            for(int i = 0; i < n-1; i++){
                strcpy(circle_buffer[i], circle_buffer[i+1]);
            }
            strcpy(circle_buffer[n-1], one_line);
        }
        line_counter++;
    }

    // Vytiskne obsah circle_buffer.
    for(int i = 0; i < n && i < line_counter; i++){
        printf("%s", circle_buffer[i]);
    }
}

int main(int argc, char **argv){

    int n = 10;

    FILE *file = stdin; 

    switch(argc){

        case 1: // Není zadán argument, čte se ze stdin
            break;

        case 2: // Je zadán pouze název souboru
            file = fopen(argv[1], "r");
            break;
        
        case 3: // Je zadán pouze -n argument, čte se ze stdin
            if(strcmp(argv[1], "-n") != 0){
                fprintf(stderr, "Neznámý argument %s", argv[1]);
                return 1;
            }
                
            n = (int) strtol(argv[2], NULL, 0);
            break;

        case 4: // Je zadán -n argument i soubor
            if(strcmp(argv[1], "-n") != 0){
                fprintf(stderr, "Neznámý argument %s", argv[1]);
                return 1;
            }
                  
            n = (int) strtol(argv[2], NULL, 0);
            file = fopen(argv[3], "r");
            break;

        default:
            fprintf(stderr, "Špatný počet argumentů.");
            return 1;
    }

    if((argc == 2 || argc == 4) && file == NULL){
        fprintf(stderr, "Chyba otevření souboru!\n");
        return 1;
    }

    tail(file, n);

    if(argc == 2 || argc == 4)
        fclose(file);

}
