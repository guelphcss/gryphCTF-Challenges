#include "gauntlet.h"

Weapon starter_weapon = {"Wooden Stick", 1, 1};
Armor starter_armor = {"Flimsy Cloth", 1, 1};

Item shop_items[5] = {
    {"Mushroom", 10},
    {"Purple Amulet", 30},
    {"Gold Ring", 100},
    {"Iron Bracelet", 40},
    {"Mysterious Flag", 10000000}
};

Weapon shop_weapons[4] = {

    {"Rusty Dagger",    5,       10},       
    {"Iron Longsword",  15,      50},       
    {"Cobalt Glaive",   30,      200},      
    {"Obsidian Blade",   60,      500}     
};

Armor shop_armor[4] = {

    {"Torn Tunic",      1,       10},    
    {"Chainmail",       10,      50},    
    {"Carbon Plate",    25,      150},   
    {"Aegis Shield",    50,     500}     

};

Monster monsters[5] = {
    {"Slime", 10, 1, 1, 1},
    {"Goblin", 40, 5, 5, 5},
    {"Orc", 75, 25, 20, 20},
    {"Minotaur", 125, 35, 30, 50},
    {"Dragon", 180, 30, 50, 250}
};

Shop shop;

#define UI_RESET   "\033[0m"
#define UI_BOLD    "\033[1m"
#define UI_CYAN    "\033[36m"
#define UI_BLUE    "\033[34m"
#define UI_GREEN   "\033[32m"
#define UI_YELLOW  "\033[33m"
#define UI_RED     "\033[31m"
#define UI_MAGENTA "\033[35m"
#define UI_WHITE   "\033[37m"

static void print_divider(void)
{
    printf(UI_BLUE "===========================================================" UI_RESET "\n");
}

static void print_header(const char *title)
{
    print_divider();
    printf(UI_BOLD UI_CYAN " %s " UI_RESET "\n", title);
    print_divider();
}

static void print_subheader(const char *title)
{
    printf(UI_BOLD UI_MAGENTA "\n[%s]\n" UI_RESET, title);
}

static void print_player_status(const Player *player)
{
    printf(UI_YELLOW "Gold: %d" UI_RESET " | " UI_GREEN "HP: %d" UI_RESET
           " | Weapon: " UI_WHITE "%s" UI_RESET " | Armor: " UI_WHITE "%s" UI_RESET "\n",
           player->gold, player->health, player->weapon.name, player->armor.name);
}

static int roll_damage(int attack, int defense)
{
    int base = (attack * 100) / (100 + defense);
    int damage = base * (rand() % 16 + 85) / 100;
    if (damage < 1) {
        damage = 1;
    }
    return damage;
}

int fight_monster(Player *player){
    int monster_choice, fighting = 1;

    print_header("Battle Selection");
    print_player_status(player);
    printf("Which monster do you want to fight?\n");
    printf(UI_GREEN "1." UI_RESET " %s\n", monsters[0].name);
    printf(UI_GREEN "2." UI_RESET " %s\n", monsters[1].name);
    printf(UI_GREEN "3." UI_RESET " %s\n", monsters[2].name);
    printf(UI_GREEN "4." UI_RESET " %s\n", monsters[3].name);
    printf(UI_GREEN "5." UI_RESET " %s\n", monsters[4].name);
    if (!read_int(&monster_choice)) {
        printf(UI_RED "End of input. Leaving fight.\n" UI_RESET);
        return 0;
    }
    if (monster_choice < 1 || monster_choice > 5) {
        printf(UI_RED "That monster does not exist.\n" UI_RESET);
        return 0;
    }

    Monster monster = monsters[monster_choice - 1];
    player->health = 100;
    printf(UI_GREEN "You feel fully restored before the fight.\n" UI_RESET);
    print_header("Combat");
    printf(UI_BOLD "You are fighting a %s!\n" UI_RESET, monster.name);
    while (fighting) {
        print_divider();
        printf(UI_GREEN "%s HP: %d" UI_RESET " | " UI_RED "%s HP: %d" UI_RESET "\n",
               player->name, player->health, monster.name, monster.health);
        printf("Enter a choice:\n");
        printf(UI_GREEN "1." UI_RESET " Attack\n");
        printf(UI_GREEN "2." UI_RESET " Run away\n");
        int fight_choice;

        if (!read_int(&fight_choice)) {
            printf(UI_RED "End of input. Leaving fight.\n" UI_RESET);
            return 0;
        }
        if (fight_choice == 1) {
            printf(UI_CYAN "You attacked the monster!\n" UI_RESET);
            int damage = roll_damage(player->weapon.attack, monster.defense);
            monster.health -= damage;
            printf(UI_CYAN "You did %d damage to the monster!\n" UI_RESET, damage);
            if (monster.health <= 0) {
                printf(UI_GREEN "You defeated the monster!\n" UI_RESET);
                player->gold += monster.gold_reward;
                printf(UI_YELLOW "You earned %d gold and now have %d gold.\n" UI_RESET,
                       monster.gold_reward, player->gold);
                return 1;
            }
        }
        else if (fight_choice == 2) {
            printf(UI_YELLOW "You ran away!\n" UI_RESET);
            fighting = 0;
            return 0;
        }
        else {
            printf(UI_RED "Invalid choice\n" UI_RESET);
            continue;
        }

        int damage = roll_damage(monster.attack, player->armor.defense);
        player->health -= damage;
        printf(UI_RED "The %s hit you for %d damage!\n" UI_RESET, monster.name, damage);
        if (player->health <= 0) {
            printf(UI_RED "You died and lost half your gold!\n" UI_RESET);
            fighting = 0;
            player->gold /= 2;
            return 0;
        }
        printf(UI_GREEN "You are still alive! You have %d health left.\n" UI_RESET, player->health);
    }
    return 0;
}

int view_shop(Player *player){
    int shop_choice, running = 1;
    print_header("The Merchant's Shop");
    printf("Welcome to the shop! Here you can buy some better gear to aid you in your journey.\n");
    
    while (running) {
        print_player_status(player);
        print_divider();
        printf(UI_GREEN "1." UI_RESET " Buy weapon\n");
        printf(UI_GREEN "2." UI_RESET " Buy armor\n");
        printf(UI_GREEN "3." UI_RESET " Buy items\n");
        printf(UI_GREEN "4." UI_RESET " Go back\n");
        print_divider();
        if (!read_int(&shop_choice)) {
            printf(UI_RED "End of input. Leaving shop.\n" UI_RESET);
            break;
        }
        if (shop_choice == 1) {
            print_subheader("Weapons");
            for (int i = 0; i < 4; i++) {
                printf(UI_GREEN "%d." UI_RESET " %s - " UI_YELLOW "%d gold\n" UI_RESET,
                       i + 1, shop.weapons[i].name, shop.weapons[i].price);
            }

            int weapon_buying = 1;

            while (weapon_buying){
                printf("Enter the number of the weapon you want to buy or 0 to go back: ");
                int weapon_choice;
                if (!read_int(&weapon_choice)) {
                    printf(UI_RED "End of input. Returning.\n" UI_RESET);
                    weapon_buying = 0;
                    break;
                }

                if (weapon_choice == 0){
                    weapon_buying = 0;
                    break;
                }
                if (weapon_choice < 1 || weapon_choice > 4) {
                    printf(UI_RED "Invalid selection. Choose 0-4.\n" UI_RESET);
                    continue;
                }
                int weapon_price = shop.weapons[weapon_choice - 1].price;

                if (weapon_price > player->gold){
                    printf(UI_RED "Not enough gold to buy this weapon.\n" UI_RESET);
                }
                else {
                    player->gold -= weapon_price;
                    player->weapon = shop.weapons[weapon_choice - 1];
                    printf(UI_GREEN "Purchased %s! Take good care of it!\n" UI_RESET,
                           shop.weapons[weapon_choice - 1].name);
                }
            }

        } else if (shop_choice == 2){
            print_subheader("Armor");
            for (int i = 0; i < 4; i++){
                printf(UI_GREEN "%d." UI_RESET " %s - " UI_YELLOW "%d gold\n" UI_RESET,
                       i + 1, shop.armor[i].name, shop.armor[i].price);
            }
            int armor_buying = 1;

            while (armor_buying == 1){
                printf("Enter the number of the armor you would like to buy or 0 to go back: ");
                int armor_choice;
                if (!read_int(&armor_choice)) {
                    printf(UI_RED "End of input. Returning.\n" UI_RESET);
                    armor_buying = 0;
                    break;
                }

                if (armor_choice == 0){
                    armor_buying = 0;
                    break;
                }
                if (armor_choice < 1 || armor_choice > 4) {
                    printf(UI_RED "Invalid selection. Choose 0-4.\n" UI_RESET);
                    continue;
                }
                int armor_price = shop.armor[armor_choice - 1].price;
                if (armor_price > player->gold){
                    printf(UI_RED "Not enough gold to buy this armor.\n" UI_RESET);
                }
                else {
                    player->gold -= armor_price;
                    player->armor = shop.armor[armor_choice - 1];
                    printf(UI_GREEN "Purchased %s! Take good care of it!\n" UI_RESET,
                           shop.armor[armor_choice - 1].name);
                }
            }
        } else if (shop_choice == 3) {
            print_subheader("Items");
            for (int i = 0; i < 5; i++) {
                printf(UI_GREEN "%d." UI_RESET " %s - " UI_YELLOW "%d gold\n" UI_RESET,
                       i + 1, shop.items[i].name, shop.items[i].price);
            }
            int item_buying = 1;
            while (item_buying) {
                printf("Enter the number of the item you want to buy or 0 to go back: ");
                int item_choice;
                if (!read_int(&item_choice)) {
                    printf(UI_RED "End of input. Returning.\n" UI_RESET);
                    item_buying = 0;
                    break;
                }
                if (item_choice == 0) {
                    item_buying = 0;
                    break;
                }
                if (item_choice < 1 || item_choice > 5) {
                    printf(UI_RED "Invalid selection. Choose 0-5.\n" UI_RESET);
                    continue;
                }
                if (item_choice == 5) { 
                    if (player->gold >= 10000000) {
                        printf(UI_GREEN "\nThe Merchant's eyes widen. He reaches under the counter...\n" UI_RESET);
                        
                        FILE *fp = fopen("flag.txt", "r");
                        if (fp == NULL) {
                            printf("Error: flag.txt is missing. Contact an admin!\n");
                            break;
                        }
                        unsigned char gold_state = (player->gold >> 16) & 0xFF; 
                        unsigned char modifier = gold_state ^ 0x98;
                        
                        printf("FLAG: ");
                        int c;
                        while ((c = fgetc(fp)) != EOF) {
                            putchar(c ^ modifier); 
                        }
                        printf("\n\n");
                        fclose(fp);
                        player->gold = 0;
                        running = 0; 
                        break;
                    } else {
                        printf(UI_RED "[Merchant] Ah, the Mysterious Flag... I only sell this to those with *exactly* the right coin. No more, no less.\n\n" UI_RESET);
                    }
                }
                int item_price = shop.items[item_choice - 1].price;
                if (item_price > player->gold){
                    printf(UI_RED "Not enough gold to buy this item.\n" UI_RESET);
                }
                else {
                    player->gold -= item_price;
                    player->items[item_choice - 1] = shop.items[item_choice - 1];
                    printf(UI_GREEN "Purchased %s.\n" UI_RESET, shop.items[item_choice - 1].name);
                }
            }
        }
        else if (shop_choice == 4) {
            printf(UI_YELLOW "Goodbye Warrior!\n" UI_RESET);
            running = 0;
        }
        else {
            printf(UI_RED "Invalid Choice\n" UI_RESET);
        }
    }
    return 0;
}


int main(void){
    setvbuf(stdout, NULL, _IONBF, 0);
    int running = 1;

    memcpy(shop.weapons, shop_weapons, sizeof shop.weapons);
    memcpy(shop.armor, shop_armor, sizeof shop.armor);
    memcpy(shop.items, shop_items, sizeof shop.items);
    strncpy(shop.flag, "flag", sizeof shop.flag - 1);
    shop.flag[sizeof shop.flag - 1] = '\0';

    print_header("The Iron Gauntlet");
    printf("Enter your name: ");
    char name[128];
    if (!read_line(name, sizeof name)) {
        printf(UI_YELLOW "Goodbye.\n" UI_RESET);
        return 0;
    }

    Player player = {0};
    memcpy(player.name, name, sizeof player.name - 1);
    player.name[sizeof player.name - 1] = '\0';    player.health = 100;
    player.gold = 0;
    player.weapon = starter_weapon;
    player.armor = starter_armor;

    unsigned long real_addr = (unsigned long)&player.gold;
    unsigned long secret_key = 0xDEADBEEF;
    unsigned long prophecy = real_addr ^ secret_key;
    
    printf(UI_CYAN "Best of luck on your journey through the gauntlet %s!\n" UI_RESET, player.name);
    printf(UI_CYAN "[Seer] The prophecy of your wealth reads: %lx\n" UI_RESET, prophecy);
    
    while (running) {
        print_header("Main Menu");
        print_player_status(&player);
        printf(UI_GREEN "1." UI_RESET " Enter the gauntlet\n");
        printf(UI_GREEN "2." UI_RESET " Edit your name\n");
        printf(UI_GREEN "3." UI_RESET " Exit\n");
        int gauntlet_choice;
        if (!read_int(&gauntlet_choice)) {
            printf(UI_YELLOW "Goodbye.\n" UI_RESET);
            break;
        }

        if (gauntlet_choice == 1) {
            int in_game_choice, in_gauntlet = 1;
            print_header("Inside the Gauntlet");
            printf(UI_CYAN "Entering the gauntlet...\n" UI_RESET);
            while (in_gauntlet){
                print_player_status(&player);
                print_divider();
                printf(UI_GREEN "1." UI_RESET " Fight a monster\n");
                printf(UI_GREEN "2." UI_RESET " View shop\n");
                printf(UI_GREEN "3." UI_RESET " Back to main menu\n");
                if (!read_int(&in_game_choice)) {
                    printf(UI_YELLOW "Goodbye.\n" UI_RESET);
                    running = 0;
                    break;
                }
                if (in_game_choice == 1) {
                    fight_monster(&player);
                }
                else if (in_game_choice == 2) {
                    view_shop(&player);
                }
                else if (in_game_choice == 3) {
                    printf(UI_YELLOW "Goodbye Warrior!\n" UI_RESET);
                    in_gauntlet = 0;
                    break;
                }
                else {
                    printf(UI_RED "Invalid choice\n" UI_RESET);
                }
            }

        } else if (gauntlet_choice == 2) {
            print_subheader("Edit Name");
            printf("Enter new name: ");
            if (!read_line(name, sizeof name)) {
                printf(UI_YELLOW "Goodbye.\n" UI_RESET);
                running = 0;
                break;
            }
            if (strchr(name, '$') != NULL) {
                printf(UI_RED "The gods forbid the use of that cursed symbol!\n" UI_RESET);
                continue;
            }
            strncpy(player.name, name, sizeof player.name - 1);
            player.name[sizeof player.name - 1] = '\0';
            printf(UI_GREEN "Name edited successfully! Your new name is " UI_RESET);
            printf(player.name);
            printf("\n");

        } else if (gauntlet_choice == 3) {
            printf(UI_YELLOW "Goodbye Warrior!\n" UI_RESET);
            running = 0;
        }

        else {
            printf(UI_RED "Invalid choice\n" UI_RESET);
        }
    }
    return 0;
}
