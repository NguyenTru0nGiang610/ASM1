#include "Army.h"

Army::Army(Unit **unitArray, int size, string name, BattleField *battleField) : name(name), battleField(battleField)
{
    // TODO: Implement
    this->EXP = this->LF = 0;
    for (int i = 0; i < size; i++) {
        if (dynamic_cast<Vehicle*>(unitArray[i])) {
            this->LF += unitArray[i]->getAttackScore();
        } else {
            this->EXP += unitArray[i]->getAttackScore();
    }
    }
    this->LF = min(this->LF, 1000);
    this->EXP = min(this->EXP, 500);
    this->unitList = new UnitList(this->LF + this->EXP);
    for (int i = 0; i < size; i++) {
        this->unitList->insert(unitArray[i]->cloneUnit());
    }
}

Army::~Army() {
    if (unitList) {
        delete unitList;
    }
}


int Army::safeCeil(double value) {
    // TODO: Implement
    return ceil(value);
}

void Army::updateScore(bool update) {
    if (update) {
        this->LF = 0;
        this->EXP = 0;
        for (int i = 0; i < (this->unitList->getSize()); i++) {
            Vehicle* veh = dynamic_cast<Vehicle*>((this->unitList->getUnit(i)));
            if (veh) LF += ((this->unitList->getUnit(i))->getAttackScoreinFight());
            else EXP += ((this->unitList->getUnit(i))->getAttackScoreinFight());
        }
        this->LF = min(this->LF, 1000);
        this->EXP = min(this->EXP, 500);
        this->unitList->setCapacity(this->LF + this->EXP);
    }

}

//Bổ sung
int Army::getLF() const {
    return LF;
}
int Army::getEXP() const {
    return EXP;
}
string Army::getName() const {
    return name;
}
void Army::decreaseWeight(float a) {
    for(int i =0; i<this->unitList->getSize(); i++){
        this->unitList->getUnit(i)->setWeight(((this->unitList)->getUnit(i))->getWeight() * a);
    }
}
void Army::decreaseQuantity(float a) {
    for(int i =0;i<this->unitList->getSize();i++){
        this->unitList->getUnit(i)->setQuantity(((this->unitList)->getUnit(i))->getQuantity() * a);
    }
}
UnitList* Army::clone(UnitList* units){
    UnitList* units_copy(units->getSize());
    units_copy->setCapacity(units->getCapacity());
    for (int i = 0; i < units->getSize(); i++) {
        Unit *temp = units->getUnit(i);
        units_copy->insert(temp->cloneUnit());
    }
    return units_copy;
}
UnitList* Army::knapsack(UnitList* inputList, int minScore) {
    int n = inputList->getSize();
    int minSum = INT_MAX;
    UnitList* bestSubset = nullptr;

    for (int mask = 1; mask < (1 << n); ++mask) {
        int sum = 0;
        UnitList* currentSubset = new UnitList(10);
        currentSubset->setCapacity(inputList->getCapacity());

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                Unit* unit = inputList->getUnit(i);
                sum += unit->getAttackScoreinFight();
                currentSubset->insert(unit->cloneUnit()); // Deep copy từng đơn vị
            }
        }

        if (sum > minScore && sum < minSum) {
            minSum = sum;

            // Xóa tập con cũ nếu có
            if (bestSubset != nullptr) {
                delete bestSubset;
            }

            bestSubset = currentSubset;
        } else {
            delete currentSubset;
        }
    }

    return bestSubset;
}
UnitList* Army::getUnitType(string type) {
    if (type == "Infantry") {
        UnitList * result = new UnitList(unitList->getCountInfantry());
        result->setCapacity(unitList->getCountInfantry());
        for (int i = unitList->getCountInfantry() - 1; i >= 0; i--) {
            Infantry *v = dynamic_cast<Infantry*>(unitList->getUnit(i));
            if (v) result->insert(v->cloneUnit());
        }
            return result;
    }
    else {
        UnitList * result = new UnitList(unitList->getCountVehicle());
        result->setCapacity(unitList->getCountVehicle());
        for (int i = unitList->getCountInfantry(); i > unitList->getSize(); i++) {
            Vehicle *v = dynamic_cast<Vehicle*>(unitList->getUnit(i));
            if (v) result->insert(v->cloneUnit());
        }
            return result;
    }
}