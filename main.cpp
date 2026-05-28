#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void showIntro() {
    cout << "======================================\n";
    cout << "        SPACE QUEST: DEFEND EARTH      \n";
    cout << "======================================\n";
    cout << "You are the captain of the starship Aurora.\n";
    cout << "Enemy aliens are approaching Earth, and only you can stop them!\n\n";
}

int getRandom(int minValue, int maxValue) {
    return rand() % (maxValue - minValue + 1) + minValue;
}

void showStatus(int health, int shields, int score, int round) {
    cout << "\n--- STATUS ---\n";
    cout << "Round: " << round << "\n";
    cout << "Health: " << health << "\n";
    cout << "Shields: " << shields << "\n";
    cout << "Score: " << score << "\n";
    cout << "--------------\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    showIntro();

    int health = 100;
    int shields = 50;
    int score = 0;
    int round = 1;
    bool won = false;

    while (health > 0 && round <= 5) {
        int enemyStrength = getRandom(15, 35);
        int enemyShield = getRandom(10, 30);

        cout << "Round " << round << ": An alien cruiser appears!\n";
        cout << "Enemy strength: " << enemyStrength << "\n";
        cout << "Enemy shield:   " << enemyShield << "\n\n";

        int choice = 0;
        while (choice < 1 || choice > 3) {
            cout << "Choose your action:\n";
            cout << "  1) Fire laser cannons\n";
            cout << "  2) Raise shield and evade\n";
            cout << "  3) Launch missile barrage\n";
            cout << "Enter 1, 2 or 3: ";
            cin >> choice;

            if (!cin || choice < 1 || choice > 3) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid choice. Try again.\n";
                choice = 0;
            }
        }

        int damageToEnemy = 0;
        int damageToPlayer = 0;

        if (choice == 1) {
            cout << "You fire laser cannons!\n";
            damageToEnemy = getRandom(20, 40);
            damageToPlayer = getRandom(5, 20);
        } else if (choice == 2) {
            cout << "You raise shields and attempt to evade.\n";
            damageToEnemy = getRandom(10, 25);
            damageToPlayer = getRandom(0, 15);
            shields += 5;
            cout << "Shield systems absorb energy and gain +5 shield points.\n";
        } else if (choice == 3) {
            cout << "You launch a missile barrage!\n";
            damageToEnemy = getRandom(30, 50);
            damageToPlayer = getRandom(10, 25);
            shields -= 10;
            if (shields < 0) shields = 0;
        }

        int enemyRemaining = enemyStrength - damageToEnemy;
        if (enemyRemaining <= 0) {
            cout << "Direct hit! The alien cruiser is destroyed.\n";
            score += 100;
        } else {
            cout << "The enemy cruiser survives and fires back.\n";
            score += 50;
            if (shields > 0) {
                int shieldDamage = min(shields, damageToPlayer);
                shields -= shieldDamage;
                damageToPlayer -= shieldDamage;
                cout << "Your shields absorb " << shieldDamage << " damage.\n";
            }
            health -= damageToPlayer;
            if (health < 0) health = 0;
            cout << "You take " << damageToPlayer << " damage.\n";
        }

        showStatus(health, shields, score, round);

        if (health <= 0) {
            cout << "\nYour ship has been destroyed. Earth is in danger...\n";
            break;
        }

        if (round == 5) {
            won = true;
            break;
        }

        cout << "Press Enter to continue to the next round...\n";
        cin.ignore(10000, '\n');
        cin.get();
        round++;
    }

    if (won && health > 0) {
        cout << "\nCongratulations, Captain! You defended Earth from the alien assault.\n";
        cout << "Final score: " << score << "\n";
    }

    cout << "Game over. Thanks for playing!\n";
    return 0;
}
