#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void print_sword() {
    printf("                 /()\n");
    printf("                / /\n");
    printf("               / /\n");
    printf("  /============| |------------------------------------------,\n");
    printf("{=| / / / / / /|()}     }     }     }                        >\n");
    printf("  \\============| |------------------------------------------'\n");
    printf("               \\ \\\n");
    printf("                \\ \\\n");
    printf("                 \\()\n\n");

}

void unlock_royal_vault() {
    char flag[64];
    FILE *f = fopen("flag.txt", "r");
    if (f == NULL) {
        printf("\n\033[1;31m[X] The vault is empty! flag.txt is missing. [X]\033[0m\n");
        exit(1);
    }
    fgets(flag, 64, f);
    printf("\n\033[1;33m[!] ANCIENT VAULT UNLOCKED [!]\033[0m\n");
    printf("You have claimed the legendary artifact: %s\n", flag);
}

void issue_training_sword() {
    printf("\n\033[38;5;220m[Blacksmith]\033[0m Here is your wooden training sword.\n");
    printf("\033[38;5;220m[Blacksmith]\033[0m Run along now, the real weapons are for the Cyber-Knights.\n");
}

int main() {
    void (*blacksmith_action)() = issue_training_sword;
    char knight_name[48];

    setbuf(stdout, NULL);

    printf("                \033[38;5;93m╔════════════════════════════════╗\033[0m\n");
    printf("                \033[38;5;93m║\033[1;38;5;93m   THE GRYPHON'S \033[38;5;93mCYBER-ARMORY   \033[0m\033[38;5;93m║\033[0m\n");
    printf("                \033[38;5;93m╚════════════════════════════════╝\033[0m\n\n");
    
    print_sword();
    
    printf("\033[38;5;220mWelcome, Squire. The forge is burning hot today.\033[0m\n");
    printf("\033[1;38;5;93m[Magical Aura]\033[0m The anvil is currently resonating at: \033[38;5;208m%p\033[0m\n", blacksmith_action);
    printf("\nState thy name to receive thy weapon: ");

    gets(knight_name);

    printf("\n\033[38;5;220m[Blacksmith]\033[0m Processing requisition for: \033[38;5;208m%s\033[0m\n", knight_name);
    
    blacksmith_action();

    return 0;
}