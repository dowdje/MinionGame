#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

const int inventory_array_size = 3; // Initializes the constant for maximum inventory size.
string inventory_array[inventory_array_size] = {"empty", "empty", "empty"}; // Initializes an inventory array.

void buff(); //Displays buff spell to the screen

string item_drop1 (); // A function that generates drops from low level enemies.
string item_drop2 ();// A function that determines items to be dropped for high level enemies.

int main()
{
//********************************************
//DEFINE VARIABLES
//********************************************
    string monster_name;

    int monster, // The value of the roll for an enemy
        exp, // the amount of experience an enemy gives
        exp_total = 0, //Total experience earned
        level = 1, //Player level
        max_life = 50,// The highest life a player can have
        life,// the current life a player has
        monster_attack_counter = 0,// A counter that determines when an enemy will attack
        monster_damage,// How much life is removed when a monster attacks
        heal,//An action the user can take to gain life points
        spell_counter = 2,// The well from which a player can use spells
        intelligence = 1,//Determines the strength of spells
        attack,// The amount of health a monster loses when a player attacks
        monster_atk_mod = 0,// A modifier that helps determine the damage an enemy will do
        hero_atk_mod = 0,// A modifier that gets added to the damage a player does
        attack_roll,// A roll that determines the base attack of a player action
        drop_roll,//A roll that determines the drop after an enemy dies
        flame,// flame spell
        frost,// frost spell
        monster_health,// current monster health
        frost_dmg;// damage done by frost spell

    string action,
           drop,
           target;

    srand(time(NULL));

    life = max_life;

    do
    {
        do
        {
           monster = rand() % 30 + ((21 + (5 * level))/2);
//*********************************
//                GENERATE MONSTER
//*********************************
       if (monster >= 60)
       {
           monster_name = "Tyrannosaurus Devil";
           monster_health = (40 * level);
           monster_atk_mod += 20;
       }
       else if (monster >= 50)
           {
             monster_name = "Undead Minotaur";
             monster_health = monster + ( 10 * level );
             monster_atk_mod = 10;
           }
       else if (monster >= 40)
           {
             monster_name = "Hulking Behemoth";
             monster_atk_mod = 5;
             monster_health = monster + (5*level);
           }
        else if (monster > 30)
            {
                monster_name = "Fissure Wolf";
                monster_atk_mod = 3;
                monster_health = monster;
            }
        else if (monster > 20)
            {
                monster_name = "Venomous Ooze";
                monster_atk_mod = 0;
                ++monster_attack_counter;
                monster_health = monster;
            }
        else if (monster > 0)
           {
               monster_name = "Peenbot";
               monster_atk_mod = 5;
               monster_health = monster + 5;
           }

        exp = monster_health * 10;
        cout << "A " << monster_name << " appears!\n";


//*********************************************************
//                      MONSTER FIGHT
//*********************************************************

        monster_atk_mod += (1 + level * level)/2;// determines monst attak modifier for current encounter

        while (monster_health > 0)
        {
            if (monster_attack_counter == 2)
            {
              monster_damage = rand () % 10 + monster_atk_mod;
              cout << monster_name << " lashes out in fury swinging for " << monster_damage << " damage!\n\n";
              life -= monster_damage;

              if (life <= 0 )//Displays player death before terminating program
              { 
                  cout << "You grab your chest in pain and fall to the ground. You are DEAD.........................\n\n";

                  system("PAUSE>NUL");

                  return 0;
              }

              monster_attack_counter -= 2;
            }
            cin >> action;
            cout << endl;

           if (action == "help")// displays a list of possible command inputs 
           {
               cout << "\n" << "COMMAND LIST: " << endl
                    << "\n" << "ENTER 'attack' to strike the monster.\n"
                    << "ENTER 'heal' to restore health, provided your spell well has enough energy.\n"
                    << "ENTER 'buff' to increase your stats, provided your spell well has enough energy.\n"
                    << "ENTER 'stats' to view your current condition and stats.\n"
                    << "ENTER 'frost' to cast frost spell that slows your enemies.\n"
                    << "ENTER 'flame' to cast a fire spell that blasts your enemies.\n"
                    << "ENTER 'inv' to check the contents of your inventory.\n\n";
           }
           else if (action == "inv")// displays player inventory
           {
               cout << "Weapon: " << inventory_array [0] << endl
                    << "Armor: " << inventory_array [1] << endl
                    << "Miscellaneous: " << inventory_array [2] << endl << endl;
           }
           else if ( action == "stats")// displays player's current stats
           {
               cout << "You are level " << level << "." << endl
                    << "You currently have " << life << " health and " << intelligence << " intelligence." << endl
                    << "Your attack deals between " << 3 + hero_atk_mod << " and " << 20 + hero_atk_mod << " damage." << endl
                    << "Your spell well contains " << spell_counter << " spell orbs." << endl
                    << "You have " << exp_total << " experience and need " << (1000 * level * level) - exp_total << " to level up.\n\n";

           }
            else if (action == "a" || action == "A" || action == "atk" || action == "attack")//performs a player attack
           {
               attack_roll = rand() % 20 + 1;// base attack roll
               attack = attack_roll + hero_atk_mod;// adds player's attack mod to attack roll
               if ( attack_roll <= 2 )// performs a missed attack and displays it
                    {
                        // YOU MISSED!
                        cout << "Your attack misses.\n";
                        ++monster_attack_counter;
                    }
                    else if ( attack_roll == 20)// checks attack roll for an aut-kill
                    {
                        cout << "You crush the " << monster_name << " with SPLENDID FORCE!\n\n";// displays auto-kill
                        monster_health = 0;// performs auto-kill
                    }
                    else//performs a regular attack
                    {
                        // HIT THE monster
                        monster_health -= attack;// damages minion for damage equalt to player's current attack

                        cout << "You hit the monster for " << attack//displays damage
                         << " damage!\n";
                         ++monster_attack_counter;// increments monster attack readiness
                    }
           }
//*********************************************************
//                      SPELLS
//*********************************************************
           else if (action == "h" || action == "H" || action == "heal")// performs a heal spell
           {
                     if (spell_counter > 0)//checks spell well for sufficient spell orbs
                     {
                        heal = intelligence * 10;// determines value of heal spell
                        cout << "You heal for " << heal << " health.";//displays heal spell
                        life += heal;//performs heal
                        if (life > max_life)// checks if heal exceeds maximum life
                            life = max_life;// if heal exceeds max life, sets life to max value
                        spell_counter--;
                        ++monster_attack_counter;
                     }
                     else
                         cout << "Your spell well is depleted. Level up to replenish it.";
            }

            else if ( action == "buff" || action == "B" || action == "b")
            {
                if (spell_counter > 2)
                {
                         buff();
                        hero_atk_mod += 10;
                        spell_counter -= 3;
                        ++monster_attack_counter;
                }
                      else
                          cout << "Your spell well is depleted. Level up to replenish it.";
            }
            else if ( action == "frost")
            {
                if (spell_counter > 0)
                {
                    frost_dmg = intelligence * 20;
                    cout << "A shiver runs through you as frost pours out of your hands freezing the " << monster_name << "." << endl
                         << "You deal " << frost_dmg << " damage. " << monster_name << "is frozen." << endl;
                    monster_health -= frost_dmg;
                    spell_counter -= 1;

                }
                else
                    cout << "Your spell well is depleted. Level up to replenish it.";
            }
            else if ( action == "flame" )
            {
                flame = 40 * intelligence;
                cout << "Sparks emanate between you and " << monster_name << " before it is consumed by flames.\n"
                     << "You deal " << flame << " damage.\n\n";
                monster_health -= flame;
                spell_counter--;
                monster_attack_counter++;
            }
            else
            {
                cout << "Invalid Command\n"
                     << "ENTER an action or ENTER 'help' for a list of commands.\n\n";
            }

        }
 //********************************
 // monster DEATH
 //**********************************
        cout << "You killed the monster! You gain " << exp << " experience points.\n\n";
        if ( monster_name == "Tyrannosaurus Devil")
        {
            cout << "Thousands of screaming spirits pour out of the Tyrannosaurus Devil." << endl
                 << "A magnificent pulse shakes the earth beneath you as the freed spirits surround" << endl
                 << " you. You feel your spirit bursting from your body as transform into a version" << endl
                 << " of yourself.\n\n";
            exp += 1000;
            intelligence += 1;
            hero_atk_mod += 10;
            life += 50;
            drop = "Nothing";
        }
        else if ( monster_name == "Undead Minotaur")
        {
            item_drop2();
            drop = item_drop2();
        }
        else
        {
          item_drop1();
          drop = item_drop1 ();
        }
        if (drop != "Nothing")
        cout << "The " << monster_name << " drops " << drop << ".\n\n";

        if (drop == "Gilded Behemoth Spine")
        {
            hero_atk_mod += 10;
            life += 30;
            cout << "You wield the Gilded Behemoth Spine.\n\n";
            inventory_array [0] = drop;
        }
        else if (drop == "Glittering Emerald Ring")
        {
            intelligence += 1;
            spell_counter += 1;
            cout << "You dawn the Glittering Emerald Ring. Ancient powers course through your body.\n\n";
        }
        else if (drop == "Knuckle Spikes" )
        {
            hero_atk_mod += 3;
            cout << "Your fists harden.\n\n";
            inventory_array [1] = drop;
        }
        else if (drop == "Lifeblood")
        {
            life += 10;
            cout << "You drink the Lifeblood. Your wounds begin to close.\n\n";
            inventory_array[2] = drop;
        }
        else if (drop == "Corrupted Soul")
        {
            ++spell_counter;
            cout << "You consume the soul and feel powerful.\n\n";
            inventory_array[2] = drop;
        }
        else;

        monster_attack_counter = 0;
        exp_total += exp;



   }
   while ( exp_total < 1000 * level * level);

   ++level;
   life += (((level + 1)/2) * 10);
   max_life += (((level + 1)/2) * 10);
   ++intelligence;
   ++spell_counter;
   hero_atk_mod += 2 * level;

   cout << "**************************************" << endl
        << "You leveled up! You are now level " << level << "!" << endl
        << "**************************************\n\n";
    }
    while (life > 0);

    system("PAUSE>NUL");

    return 0;
}
void buff()
{
cout << "******************************************\n"
     << "You are endowed with the POWER OF THE GODS!"
     << "\n****************************************\n";
     return;
}

string item_drop1 () // A function that generates drops from low level enemies.
{
    int drop_roll,
        drop;
    const int ARRAY_ITEM_SIZE = 6;
    string array_item [ARRAY_ITEM_SIZE] = {"Nothing", "Lifeblood", "Corrupted Soul", // Populates an array of possible items
     "Knuckle Spikes", "Glittering Emerald Ring", "Gilded Behemoth Spine"};

    srand(time(NULL));
    drop_roll = (rand() % 105 + 1); // assigns proabilities for each potential item to be dropped and rolls for that item.

    if (drop_roll <= 70)
        {
            array_item [0];
            drop = 0;
        }
    else if (drop_roll <= 85)
        {
            array_item [1];
            drop = 1;
        }
    else if (drop_roll <= 94)
        {
            array_item [2];
            drop = 2;
        }
    else if (drop_roll <= 100)
        {
            array_item [3];
            drop = 3;
        }
    else if (drop_roll <= 103)
        {
            array_item [4];
            drop = 4;
        }
    else if (drop_roll <= 105)
        {
            array_item [5];
            drop = 5;
        }

    return array_item [drop];
}

string item_drop2 ()// A function that determines items to be dropped for high level enemies.
{
    int drop_roll, //Variable of the integer value rolled.
        drop; // variable of which item gets called from the array
    const int ARRAY_ITEM_SIZE = 6;
    string array_item [ARRAY_ITEM_SIZE] = {"Nothing", "Lifeblood", "Corrupted Soul",// Populates an array of potential items
     "Knuckle Spikes", "Glittering Emerald Ring", "Gilded Behemoth Spine"};

    srand(time(NULL));
    drop_roll = (rand() % 105 + 1);

    if (drop_roll <= 25)
        {
            array_item [0];
            drop = 0;
        }
    else if (drop_roll <= 50)
        {
            array_item [1];
            drop = 1;
        }
    else if (drop_roll <= 75)
        {
            array_item [2];
            drop = 2;
        }
    else if (drop_roll <= 90)
        {
            array_item [3];
            drop = 3;
        }
    else if (drop_roll <= 100)
        {
            array_item [4];
            drop = 4;
        }
    else if (drop_roll <= 105)
        {
            array_item [5];
            drop = 5;
        }

    return array_item [drop];
}
