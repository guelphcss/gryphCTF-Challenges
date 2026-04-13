#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


struct DispatchRecord {
    char courier_name[32];
    int destination_fd;
};

int main() {

    setbuf(stdout, NULL);

    int flag_fd = open("flag.txt", O_RDONLY);
    if (flag_fd < 0) {
        printf("[!] flag.txt is missing from the vault!\n");
        exit(1);
    }
    char secret_message[64] = {0};
    read(flag_fd, secret_message, 63);
    close(flag_fd);

    int ledger_fd = open("/dev/null", O_WRONLY);

    struct DispatchRecord record;
    record.destination_fd = ledger_fd;

    printf("                \033[38;5;93m╔════════════════════════════════╗\033[0m\n");
    printf("                \033[38;5;93m║\033[1;38;5;93m     ROYAL COURIER DISPATCH     \033[38;5;93m║\033[0m\n");
    printf("                \033[38;5;93m╚════════════════════════════════╝\033[0m\n\n");
    
    printf("\033[38;5;220m[Guild Master]\033[0m We must send the King's secret message to the secure ledger.\n");
    printf("Sign the dispatch log with thy name: ");
    
    read(0, record.courier_name, 64); 

    printf("\n\033[38;5;220m[Guild Master]\033[0m Thank you. Routing the secret message to the \033[1;36mFated Destination\033[0m %d...\n", record.destination_fd);

    write(record.destination_fd, secret_message, strlen(secret_message));

    printf("\n\033[38;5;203m[Log]\033[0m Dispatch complete. Have a safe journey.\n");

    return 0;
}