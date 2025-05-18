#ifndef UNIT_H
#define UNIT_H

#include "Position.h"

class Unit
{
protected:
    int quantity, weight;
    Position pos;
    int AttackScore;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    int getAttackScoreinFight() {return AttackScore;};
    void setAttackScore(float score) { AttackScore = ceil(score); };
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    virtual Unit* cloneUnit() = 0;
    int getQuantity();
    int getWeight() ;
    void setQuantity(float quantity);
    void setWeight(float weight);
};

#endif // UNIT_H
