#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void win() {
    FILE *f = fopen("flag.txt", "r");
    if (f){
        char flag[32];
        fgets(flag, 32, f);
        fclose(f);
        printf("\n\033[1;32m[!] ACCESS GRANTED [!]\033[0m\n");
        printf("Flag: %s\n", flag);
    }
    else {
        printf("\n[X] CRITICAL ERROR: flag.txt not found. Contact Admin. [X]\n");
        exit(1);
    }
}

int main() {
    int authenticated = 0;
    char buffer[64];

    setbuf(stdout, NULL); 
    printf("\033[38;5;93m╔═══════════════════════════════════════╗\033[0m\n");
    printf("\033[38;5;93m║\033[1;38;5;93m    Welcome to the Gates of Gryphon    \033[38;5;93m║\033[0m\n");
    printf("\033[38;5;93m╚═══════════════════════════════════════╝\033[0m\n");
    printf("Enter passcode: ");
    gets(buffer);

    if (authenticated != 0) {
        win();
    } else {
        printf("\n\033[1;31m[X] ACCESS DENIED [X]\033[0m\n");
    }

    return 0;
}
