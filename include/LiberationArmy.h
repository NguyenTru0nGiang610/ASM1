#ifndef _H_LIBERATIONARMY_H_
#define _H_LIBERATIONARMY_H_

#include "Army.h"

class LiberationArmy : public Army
{
private:
    Unit **unitArray;       // For temporary
    // * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.
    int size_V = 0;
    int size_I = 0;
    int nearestFibonacci(int value);
    Unit* cloneUnit(Unit* unit);
    void QuantitytonearestFibonacci();

public:
    LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField);
    void fight(Army *enemy, bool defense) override;
    string str() const override;

    // * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.
    int getLF() {
        return this->LF;
    }
    int getEXP() {
        return this->EXP;
    }
    int getsize_V() {return size_V;}
    int getsize_I() {return size_I;}
    void checkRange(int& num, int MAX){
        num = std::max(0, std::min(num, MAX));
    }
    void defenseFightRecursive(int enemyEXP, int enemyLF);
    ~LiberationArmy() {
    delete[] unitArray;  // chỉ delete mảng con trỏ, không delete từng Unit*
}
    void updateScore(bool update);
};

#endif