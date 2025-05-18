#include "LiberationArmy.h"


// TODO: Implement
// class LiberationArmy
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name, BattleField *battleField)
                                                : Army(unitArray,size,name, battleField) {
this->unitArray = new Unit*[size];
    for (int i = 0; i < min(this->unitList->getCapacity(), size); ++i) {
        this->unitArray[i] = this->unitList->getUnits()[i]; // lưu lại con trỏ gốc (hoặc clone nếu cần)
    }
    size_I = this->unitList->getCountInfantry();
    size_V = this->unitList->getCountVehicle();
}

void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
    if (!enemy) return;
    int enemyLF = enemy->getLF();
    int enemyEXP = enemy->getEXP();
    if (!defense) {
        auto infantryList = getUnitType("Infantry");
        auto vehicleList = getUnitType("Vehicle");
        auto comboA = knapsack(infantryList, enemyEXP);
        auto comboB = knapsack(vehicleList, enemyLF);
        bool hasA = comboA->getSize() > 0;
        bool hasB = comboB->getSize() > 0;
        if (hasA && hasB) {
            // enemy->decreaseWeight(0.8);
            this->unitList->remove_string_ofUnits(comboA);
            this->unitList->remove_string_ofUnits(comboB);
            this->unitList->insert_string_ofUnits(this->clone(enemy->unitList->getUnits()));
            enemy->unitList->remove_string_ofUnits(enemy->unitList->getUnits());
            enemy->updateScore(true);
        }else if (hasA || hasB) {
            if (hasA && ceil(LF * 1.5) > enemyLF) {
                    // enemy->decreaseWeight(0.8);
                    this->unitList->remove_string_ofUnits(comboA);
                    this->unitList->remove_string_ofUnits(vehicleList);
                    this->unitList->insert_string_ofUnits(this->clone(enemy->unitList->getUnits()));
                    enemy->unitList->remove_string_ofUnits(enemy->unitList->getUnits());
                    enemy->updateScore(true);
            }else if (hasB && ceil(EXP * 1.5) > enemyEXP){
                    // enemy->decreaseWeight(0.8);
                    this->unitList->remove_string_ofUnits(comboB);
                    this->unitList->remove_string_ofUnits(infantryList);
                    this->unitList->insert_string_ofUnits(this->clone(enemy->unitList->getUnits()));
                    enemy->unitList->remove_string_ofUnits(enemy->unitList->getUnits());
                    enemy->updateScore(true);
            }else {
                this->decreaseWeight(0.9);
            }
        }else {
            this->decreaseWeight(0.9);
        }
        this->updateScore(true);   
    } else {
        defenseFightRecursive(enemyEXP, enemyLF);
    }
}

string LiberationArmy::str() const {
    // TODO: Implement
    ostringstream oss;
    oss<<"LiberationArmy[LF="<<LF<<",EXP="<<EXP<<",unitList=UnitList[count_vehicle="<<size_V<<";count_infantry="<<size_I;
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


// Sup function
int LiberationArmy::nearestFibonacci(int value) {
    // TODO: Implement
    int a = 0, b = 1;
    while (b <= value) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
void LiberationArmy::QuantitytonearestFibonacci() {
    // TODO: Implement
    vector<Unit *> OG_units = this->unitList->getUnits();
        for (int i = 0; i < OG_units.size(); i++) {
            OG_units[i]->setQuantity(nearestFibonacci(OG_units[i]->getQuantity()));
    }
    for (Unit *u : OG_units) {
        delete u;
    }
    OG_units.clear();
}


void LiberationArmy::defenseFightRecursive(int enemyEXP, int enemyLF) {
    this->setEXP (ceil(this->EXP * 1.3));
    this->setLF (ceil(this->LF * 1.3));

    if (EXP > enemyEXP && LF > enemyLF) {
        // Trường hợp thắng hoàn toàn: không làm gì thêm
        return;
    } 
    else if (EXP > enemyEXP || LF > enemyLF) {
        // Hòa hoãn: giảm 10% quantity tất cả đơn vị
        this->decreaseQuantity(0.9);
        this->updateScore(true);  // cập nhật lại EXP, LF
        return;
    } 
    else {
        // Cả 2 chỉ số đều nhỏ hơn => cần chi viện (đệ quy)

        this->QuantitytonearestFibonacci();

        this->updateScore(true);
        // Đệ quy xét lại tình huống sau chi viện
        this->defenseFightRecursive(enemyEXP, enemyLF);
    }
}
 void LiberationArmy::updateScore(bool update) {
    Army::updateScore(update);
    size_I = this->unitList->getCountInfantry();
    size_V = this->unitList->getCountVehicle();
 }
