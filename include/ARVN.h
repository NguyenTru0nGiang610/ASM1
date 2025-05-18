#ifndef _H_ARVN_H_
#define _H_ARVN_H_

#include "Army.h"

class ARVN : public Army
{
private:
    // * Hin. You can remove it for your own implementation.
    int nearestFibonacci(int value);
    Unit* cloneUnit(Unit* unit);
    void resetARVN();
    int size_v = 0;
    int size_i = 0;
public:
    ARVN(Unit** unitArray, int size, string name, BattleField *battleField);
    void fight(Army* enemy, bool defense=false) override;
    string str() const;
    int getsize_v() {return size_v;}
    int getsize_i() {return size_i;}
    void updateScore(bool update);
};
#endif