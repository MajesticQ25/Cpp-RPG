#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Entity {

private:
    string name;

    int hp;
    int maxHp;
    int mp;
    int sp;
    int level;
    int exp;

    int atkPow;
    int defPow;

public:

    Entity() {
        hp = 0;
        maxHp = 0;
        mp = 0;
        sp = 0;
        level = 1;
        exp = 0;
        atkPow = 0;
        defPow = 0;
    }

    bool isAlive(){
        return hp > 0;
    }

    // SETTERS

    void setName(string n){
        name = n;
    }

    void setHp(int hp_count){
        hp = hp_count;
        maxHp = hp_count;
    }

    void setMp(int mp_count){
        mp = mp_count;
    }

    void setSp(int sp_count){
        sp = sp_count;
    }

    void setExp(int exp_count){
        exp = exp_count;
    }

    void setAtk(int atk){
        atkPow = atk;
    }

    void setDef(int def){
        defPow = def;
    }

    // GETTERS

    string getName(){
        return name;
    }

    int getHp(){
        return hp;
    }

    int getAtkPow(){
        return atkPow;
    }

    int getDefPow(){
        return defPow;
    }

    // COMBAT

    void attack(Entity &target) {

        int damage = atkPow - target.defPow;

        if(damage < 1)
            damage = 1;

        cout << name << " attacks "
             << target.name
             << " for "
             << damage << " damage.\n";

        target.takeDamage(damage);
    }

    void takeDamage(int dmg) {

        hp -= dmg;

        if(hp < 0)
            hp = 0;

        cout << name << " HP: "
             << hp << endl;
    }

};


int main()
{

    Entity player;
    Entity enemy;

    player.setName("Hero");
    player.setHp(100);
    player.setMp(50);
    player.setSp(80);
    player.setAtk(40);
    player.setDef(30);

    enemy.setName("Drake");
    enemy.setHp(100);
    enemy.setMp(80);
    enemy.setSp(60);
    enemy.setAtk(20);
    enemy.setDef(20);

    int choice;

    while(player.isAlive() && enemy.isAlive()){

        cout << "\n---- Player Turn ----\n";
        cout << "1. Attack\n";
        cout << "2. Quit\n";
        cin >> choice;

        if(choice == 1){
            player.attack(enemy);
        }
        else if(choice == 2){
            cout << "Exiting game.\n";
            break;
        }

        if(!enemy.isAlive())
            break;

        cout << "\n---- Enemy Turn ----\n";
        enemy.attack(player);
    }

    if(player.isAlive())
        cout << "\nVictory!\n";
    else
        cout << "\nYou were defeated.\n";

    return 0;
}