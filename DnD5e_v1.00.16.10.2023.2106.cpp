#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <random>
using namespace std;

int statRolls(){
    const int D6_MIN = 1;
    const int D6_MAX = 6;
    const int ROLL_MAX = 4;
    
    random_device dieRoller;
    uniform_int_distribution<int> d6(D6_MIN, D6_MAX);
    
    int statRoll[ROLL_MAX];
    for(int count = 0; count < ROLL_MAX; count++){
        statRoll[count] = d6(dieRoller);
        while(statRoll[count] == 1 || statRoll[count] == 2){
            statRoll[count] = d6(dieRoller);
        }
        cout << statRoll[count];
    }
    
    int lowest = 0;
    for(int count = 0; count < ROLL_MAX; count++){
        if(statRoll[count] < statRoll[lowest]){
            lowest = count;
        }
    }
    int total;
    for(int count = 0; count < ROLL_MAX; count++){
        total += statRoll[count];
    }
    int roll = total - statRoll[lowest];
    cout << ", dropping " << statRoll[lowest] << ", making " << roll << endl;
    total = 0;
    return roll;
}

void charCreation(){
    const int RACE_MAX = 9;
    const int RACE_MIN = 1;
    const int CLASS_MAX = 12;
    const int CLASS_MIN = 1;
    const int STAT_NUM = 6;
    const int COLUMN = 10;
    
    ofstream charInit;
    charInit.open("charSheet.txt");
    cout << "Welcome to character creation." << endl
         << "Enter your name: ";
    string charName;
    getline(cin, charName);

    string race[RACE_MAX] = {"Dwarf", "Elf", "Halfling", "Human", "Dragonborn",
                             "Gnome", "Half-Elf", "Half-Orc", "Tiefling"};
    cout << "Choose a race:" << endl;
    for(int count = 0; count < RACE_MAX; count++){
        cout << (count + 1) << ". " << race[count] << endl;
    }

    int raceChoice;
    cin >> raceChoice;
    while(raceChoice < RACE_MIN || raceChoice > RACE_MAX){
        cout << "Invalid choice. Try again. ";
        cin >> raceChoice;
    }
    string charRace = race[raceChoice - 1];
    
    string classList[CLASS_MAX] = {"Barbarian", "Bard", "Cleric", "Druid",
                                   "Fighter", "Monk", "Paladin", "Ranger",
                                   "Rogue", "Sorcerer", "Warlock", "Wizard"};
    cout << "Pick a class:" << endl;
    for(int count = 0; count < CLASS_MAX; count++){
        cout << (count + 1) << ". " << classList[count] << endl;
    }

    int classChoice;
    cin >> classChoice;
    while(classChoice < CLASS_MIN || classChoice > CLASS_MAX){
        cout << "Invalid choice. Try again. ";
        cin >> classChoice;
    }
    string charClass1 = classList[classChoice - 1];
    
    
    string statName[STAT_NUM] = {"Strength", "Dexterity", "Constitution",
                                 "Intelligence", "Wisdom", "Charisma"};
    string statNameAbbr[STAT_NUM] = {"STR", "DEX", "CON",
                                     "INT", "WIS", "CHA"};
    int stats[STAT_NUM] = {0, 0, 0, 0, 0, 0};
    
    cout << "Now we'll roll for your stats." << endl
         << "Rolling 4d6 and rerolling 1's and 2's, your rolls are:" << endl;
    int roll[STAT_NUM];
    for(int count = 0; count < STAT_NUM; count++){
        roll[count] = statRolls();
    }
    
    cout << "Now that your stats have been rolled, you can choose how to allocate them."
         << endl << endl;
    for(int count = 0; count < STAT_NUM; count++){
        cout << (count + 1) << ". " << statName[count] << endl;
    }
    
    for(int count = 0; count < (STAT_NUM - 1); count++){
        cout << "Which stat would you like to assign " << roll[count] << " to? ";
        
        int statChoice;
        cin >> statChoice;
        while(statChoice < 1 || statChoice > STAT_NUM || stats[statChoice - 1] > 0){
            cout << "Error: ";
            cout << ((stats[statChoice] > 0)? "You have already assigned a value to this stat. " : "");
            cout << ((statChoice < 1 || statChoice > STAT_NUM)? "That choice was invalid. " : "");
            cin >> statChoice;
        }
        
        stats[statChoice - 1] = roll[count];
        cout << statName[statChoice - 1] << " will be " << roll[count] << "." << endl;
        if(count != (STAT_NUM - 1)){
            for(int count = 0; count < (STAT_NUM); count++){
                if(stats[count] == 0){
                    cout << (count + 1) << ". " << statName[count] << endl;
                }
            }
        }
    }
    for(int count = 0; count < STAT_NUM; count++){
        if(stats[count] == 0){
            cout << "And finally, " << statName[count] << " will be " << roll[5] << ".";
            stats[count] = roll[5];
        }
    }
    
    int modifier[STAT_NUM];
    for(int count = 0; count < STAT_NUM; count++){
        modifier[count] = (stats[count] / 2) - 5;
    }
    
    charInit << "Name: " << charName << endl
             << "Race: " << charRace << endl
             << "Class: " << charClass1 << " 1" << endl << endl;
    string lineItem = "STATS";
    charInit << "STATS" << setw(COLUMN - lineItem.length() + COLUMN + 2)
             << "Modifier" << endl;
    for(int count = 0; count < STAT_NUM; count++){
        lineItem = statNameAbbr[count];
        charInit << statNameAbbr[count] << setw(COLUMN - lineItem.length()) << stats[count]
                 << ((stats[count] < 10)? setw(COLUMN - 1) : setw(COLUMN));
        if(modifier[count] >= 0){
            charInit << "(+" << modifier[count] << ")" << endl;
        }else{
            charInit << "(" << modifier[count] << ")" << endl;
        }
    }
}

int main(){
    const double VERSION = 1.00;
    cout << "Welcome to the beta test of a D&D 5e program developed by supamusu." << endl
         << "Made to operate on C++. This is in no way endorsed by" << endl
         << "Wizards of the Coast, and it was not made for profit." << endl
         << "v" << fixed << showpoint << setprecision(2) << VERSION << ".16.10.2023.2106" 
         << endl << endl;
    charCreation();

    return 0;
}