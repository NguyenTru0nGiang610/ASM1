#include "ARVN.h"

// TODO: Implement
ARVN::ARVN(Unit** unitArray, int size, string name, BattleField *battleField) 
        : Army(unitArray, size, name, battleField) {
    size_i = this->unitList->getCountInfantry();
    size_v = this->unitList->getCountVehicle();
}

void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
    if (!enemy) return;
    if (!defense) {
        this->decreaseQuantity(0.8);
        for (int i = 0; i < this->unitList->getSize(); i++) {
            if (this->unitList->getUnits()[i]->getQuantity() == 1) {
                delete this->unitList->getUnits()[i];
                this->unitList->remove(this->unitList->getUnits()[i]);
                i--;
            }
        }
        this->updateScore(true);
    } else {
        auto infantryList = enemy->unitList->getUnitstype("Infantry");
        auto vehicleList = enemy->unitList->getUnitstype("Vehicle");
        auto comboA = knapsack(infantryList, EXP);
        auto comboB = knapsack(vehicleList, LF);
        bool hasA = !comboA.empty();
        bool hasB = !comboB.empty();
        if (hasA && hasB) {
            enemy->unitList->remove_string_ofUnits(comboA);
            enemy->unitList->remove_string_ofUnits(comboB);
            this->decreaseWeight(0.8);
            enemy->unitList->insert_string_ofUnits(this->clone(this->unitList->getUnits()));
            this->updateScore(true);
            enemy->updateScore(true);
        }else if (hasA || hasB) {
            if (hasA && ceil(enemy->getLF() * 1.5) > LF) {
                    this->decreaseWeight(0.8);
                    enemy->unitList->remove_string_ofUnits(comboA);
                    enemy->unitList->remove_string_ofUnits(vehicleList);
                    enemy->unitList->insert_string_ofUnits(this->clone(this->unitList->getUnits()));
                    this->updateScore(true);
                    enemy->updateScore(true);
            }else if (hasB && ceil(enemy->getEXP() * 1.5) > EXP){
                    this->decreaseWeight(0.8);
                    enemy->unitList->remove_string_ofUnits(comboB);
                    enemy->unitList->remove_string_ofUnits(infantryList);
                    enemy->unitList->insert_string_ofUnits(this->clone(this->unitList->getUnits()));
                    this->updateScore(true);
                    enemy->updateScore(true);
            }else {
                enemy->decreaseWeight(0.9);
                enemy->updateScore(true);
            }   
        }else {
            enemy->decreaseWeight(0.9);
            enemy->updateScore(true);
        } 
    }
}

string ARVN::str() const {
    // TODO: Implement
    ostringstream oss;
    oss<<"ARVN[LF="<<LF<<",EXP="<<EXP<<",unitList=UnitList[count_vehicle="<<unitList->getCountVehicle()<<";count_infantry="<<unitList->getCountInfantry();
    for (size_t i = 0; i < unitList->getSize(); ++i) {
        if (i == 0) {oss <<";" ;}
        oss << (this->unitList->getUnits())[i]->str();  // Gọi hàm str() từ từng Unit
        if (i != unitList->getSize() - 1) oss << ",";
    }
    oss << "],battleField=";
    if (this->battleField != nullptr) {
        oss << this->battleField->str();
    }
    oss << "]"; 
    return oss.str();
}
void ARVN::updateScore(bool update) {
   Army::updateScore(update);
   size_i = this->unitList->getCountInfantry();
   size_v = this->unitList->getCountVehicle();
}

