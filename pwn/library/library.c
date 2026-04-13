#include <stdio.h>
#include <stdlib.h>
#include <seccomp.h>
#include <unistd.h>

void cast_silence_spell() {
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);   
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execveat), 0); 
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(fork), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(vfork), 0);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clone), 0);

    seccomp_load(ctx);
}

void ask_librarian() {
    char scroll_name[64];
    printf("\n\033[38;5;220m[Librarian]\033[0m What forbidden text dost thou seek?\n> ");
    gets(scroll_name);
    printf("\033[38;5;220m[Librarian]\033[0m Searching the archives for: \033[1;36m%s\033[0m\n", scroll_name);
}

int main() {
    setbuf(stdout, NULL);
    
    printf("                \033[38;5;93m╔══════════════════════════════╗\033[0m\n");
    printf("                \033[38;5;93m║\033[1;38;5;93m     THE FORBIDDEN LIBRARY    \033[38;5;93m║\033[0m\n");
    printf("                \033[38;5;93m╚══════════════════════════════╝\033[0m\n");
    printf("\033[38;5;220m[Librarian]\033[0m WARNING: A Silence Spell is active. Destructive and unauthorized magic will be \033[1;31mpunished.\033[0m\n");

    cast_silence_spell();
    ask_librarian();

    return 0;
}