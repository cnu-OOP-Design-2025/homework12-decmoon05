#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept> // 예외 처리를 위해 추가
#include "character.h"
#include "logger.h"  // Logger 사용을 위해 추가

using namespace std;

void equip_test1(shared_ptr<Character> c1) {
    try {
        c1 = make_shared<Armor>(c1);
        c1 = make_shared<Boots>(c1);
        c1 = make_shared<Sword>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Invalid equip: " << e.what() << endl;
        Logger::getInstance()->log("[Fail to Equip]");
    }
}

void equip_test2(shared_ptr<Character> c1) {
    try {
        c1 = make_shared<Armor>(c1);
        c1 = make_shared<Bow>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Invalid equip: " << e.what() << endl;
        Logger::getInstance()->log("[Fail to Equip]");
    }
}

void equip_test3(shared_ptr<Character> c1) {
    try {
        c1 = make_shared<Boots>(c1);
        c1 = make_shared<Staff>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Invalid equip: " << e.what() << endl;
        Logger::getInstance()->log("[Fail to Equip]");
    }
}

void doTest() {
    // Logger 인스턴스를 미리 생성하여 [Init] 로그가 먼저 찍히도록 함 (선택 사항이나 흐름상 자연스러움)
    Logger::getInstance();

    vector<shared_ptr<Character>> players;
    players.push_back(make_shared<Knight>());
    players.push_back(make_shared<Wizard>());
    players.push_back(make_shared<Archer>());

    for(auto player: players){
        cout << "-------------------------------------------------------------" << endl;
        equip_test1(player);
        equip_test2(player);
        equip_test3(player);
    }
    cout << "-------------------------------------------------------------" << endl;

}

struct Student{
    string name;
    Student(string name): name(name) {};
    Student() = delete;
    ~Student() { cout << "Delete Student " << name << endl; }
};

int main(int argc, const char *argv[]) {
    doTest();
    return 0;
}