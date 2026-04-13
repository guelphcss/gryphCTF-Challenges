#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Monster {
    char name[16];
    int health;
    int attack;
    int defense;
    int gold_reward;
} Monster;

typedef struct Item {
    char name[32];
    int price;
} Item;

typedef struct Weapon {
    char name[16];
    int attack;
    int price;
} Weapon;

typedef struct Armor {
    char name[16];
    int defense;
    int price;
} Armor;

typedef struct Player {
    char name[128];
    int health;
    int gold;
    Weapon weapon;
    Armor armor;
    Item items[5];
} Player;

typedef struct Shop {
    Weapon weapons[5];
    Armor armor[5];
    Item items[5];
    char flag[32];
} Shop;

static void stdin_flush_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_int(int *out)
{
    for (;;) {
        if (scanf("%d", out) == 1) {
            stdin_flush_line();
            return 1;
        }
        if (feof(stdin)) {
            return 0;
        }
        stdin_flush_line();
        printf("Invalid input — please enter a whole number.\n");
    }
}

static int read_line(char *buf, size_t cap)
{
    if (cap == 0) {
        return 0;
    }
    if (!fgets(buf, (int)cap, stdin)) {
        return 0;
    }
    char *nl = strchr(buf, '\n');
    if (nl) {
        *nl = '\0';
    } else {
        stdin_flush_line();
    }
    return 1;
}

