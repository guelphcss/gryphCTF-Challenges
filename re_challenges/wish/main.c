// Simple password checker for a flag, basically guaranteeing that an SMT solver (e.g. Z3) is needed to satisfy constraints of the program.
// The solver script is solve.py and uses the Z3 SMT solver python bindings to satisfy checks/constraints of the checker.
// This can also be solved with angr but that will take quite some time over just a deterministic approach of z3 over the exploration/trial and error of angr (which proves VERY costly and SLOW)
// This is compiled with Debug info though it CAN be solved without it by looking at the comparison logic in a debugger. Even with debug info, under decompilation, it still appears a bit wonky, which should hopefully make this a bit fun to look into.
#include <stdio.h>
#include <string.h>
int main() {
    char buf[1024];
    printf("10 eyes, a mouth of blight, and arms that glow bright.\nWho might this be? ");
    scanf("%s", buf);
    // R1v3n_1000_VOICES
    if (strlen(buf) != 17) {
        printf("I see the shadows recede.\n");
        return 0;
    } else if (buf[0] == 'R' 
            && strlen(buf) == 17
            && buf[5] == '_'
            && buf[1] == (buf[7] +1)
            && buf[1] == buf[6]
            && buf[7] == ((1 << 5) + 16)
            && buf[8] == buf[7]
            && buf[9] == buf[8]
            && buf[10] == buf[5]
            && buf[2] == (buf[1] + 69)
            && buf[3] == (buf[1] + 2)
            && buf[4] == 'n'
            && ((buf[11] ^ 10) == 92) 
            && buf[11] == 86
            && buf[12] == 79
            && ((buf[12] - buf[13]) == 6)
            && buf[14] == 67
            && buf[15] == 69
            && ((buf[16] * buf[15]) == 5727)) {
        printf("An identity is found out of darkness.\ngrypthCTF{%s}", buf);
    } else {
        printf("I see the shadows recede.\n");
    }
    return 0;
}
