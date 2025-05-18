#include "TerrainElement.h"
#include "LiberationArmy.h"

double calculateDistance(const Position& pos1, const Position& pos2) {
    int rowDiff = pos1.getRow() - pos2.getRow();
    int colDiff = pos1.getCol() - pos2.getCol();
    return (sqrt(double(rowDiff * rowDiff + colDiff * colDiff)));
}
//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------

// Constructor và Destructor của TerrainElement
TerrainElement::TerrainElement(Position pos) : pos(pos)
{}

TerrainElement::~TerrainElement() {
    // Giải phóng tài nguyên nếu có
}

// Road: không có hiệu ứng
void Road::getEffect(Army *army) {
    // Không gây ảnh hưởng cho quân đội.
}

// Mountain: stub – áp dụng hiệu ứng cho các đơn vị trong bán kính ảnh hưởng (theo đề bài, hiệu ứng có thể là:
// tăng EXP của bộ binh và giảm LF của phương tiện, tùy thuộc vào khoảng cách)
void Mountain::getEffect(Army *army) {
    if (!army) return;
    int n = army->unitList->getSize();
    LiberationArmy* Army = dynamic_cast<LiberationArmy*>(army);
    if (Army) {
        for (int i = 0; i < n; i++) {
        if (calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos) <= 2 ) {
            Infantry* infantry = dynamic_cast<Infantry*>((army->unitList->getUnits())[i]);
            if (infantry) {
                int new_Escore = ceil(infantry->getAttackScoreinFight() * 1.3);
                Army->setEXP(Army->getEXP() - (infantry->getAttackScoreinFight() - new_Escore));
                infantry->setAttackScore(infantry->getAttackScoreinFight() * 1.3);
            }
            Vehicle* vehicle = dynamic_cast<Vehicle*>((army->unitList->getUnits())[i]);
            if (vehicle) {
                int new_Lscore = ceil(vehicle->getAttackScoreinFight() * 0.9);
                Army->setLF(Army->getLF() - (vehicle->getAttackScoreinFight() - new_Lscore));
                vehicle->setAttackScore(vehicle->getAttackScoreinFight() * 0.9);
            }
        }
    }
    }
    else {
        for (int i = 0; i < n; i++) {
        if (calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos) <= 2 ) {
            Infantry* infantry = dynamic_cast<Infantry*>((army->unitList->getUnits())[i]);
            if (infantry) {
                int new_Escore = ceil(infantry->getAttackScoreinFight() * 1.2);
                army->setEXP(army->getEXP() - (infantry->getAttackScoreinFight() - new_Escore));
                infantry->setAttackScore(infantry->getAttackScoreinFight() * 1.2);
            }
            Vehicle* vehicle = dynamic_cast<Vehicle*>((army->unitList->getUnits())[i]);
            if (vehicle) {
                int new_Lscore = ceil(vehicle->getAttackScoreinFight() * 0.95);
                army->setLF(army->getLF() - (vehicle->getAttackScoreinFight() - new_Lscore));
                vehicle->setAttackScore(vehicle->getAttackScoreinFight() * 0.95);
            }
        }
    }
    }
}
    
    

// River: stub – giảm EXP của lực lượng bộ binh 10% nếu nằm trong bán kính 2 đơn vị
void River::getEffect(Army *army) {
    if (!army) return;
    int n = army->unitList->getSize();
    for (int i = 0; i < n; i++) {
        if (calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos) <= 2 ) {
            Infantry* infantry = dynamic_cast<Infantry*>((army->unitList->getUnits())[i]);
            if (infantry) {
                infantry->setAttackScore(infantry->getAttackScoreinFight() * 0.9);
            }
        }
    }
}

// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
    if (!army) return;
    int n = army->unitList->getSize();
    LiberationArmy* Army = dynamic_cast<LiberationArmy*>(army);
    if (Army) {
        for (int i = 0; i < n; i++) {
            double D = calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos);
            Infantry* infantry = dynamic_cast<Infantry*>((army->unitList->getUnits())[i]);
            Vehicle *vehicle = dynamic_cast<Vehicle*>((army->unitList->getUnits())[i]);
            if (infantry && infantry->getInfantryType() == (InfantryType::SPECIALFORCES || InfantryType::REGULARINFANTRY) && 0 < D <= 5 ) {
                infantry->setAttackScore(infantry->getAttackScoreinFight() + (infantry->getAttackScoreinFight() * 2) / D);
            } else if (vehicle && vehicle->getVehicleType() == VehicleType::ARTILLERY && D <= 2 ) {
                vehicle->setAttackScore(vehicle->getAttackScoreinFight() + (vehicle->getAttackScoreinFight() * 2) / D);
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            double D = calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos);
            Infantry* infantry = dynamic_cast<Infantry*>((army->unitList->getUnits())[i]);
            if (infantry && infantry->getInfantryType() == InfantryType::REGULARINFANTRY && 0 < D <= 3 ) {
                infantry->setAttackScore(infantry->getAttackScoreinFight() + (infantry->getAttackScoreinFight() * 3) / (D * 2));
            }
        }
    }
}

// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {
    if (!army) return;
    int n = army->unitList->getSize();
    LiberationArmy* Army = dynamic_cast<LiberationArmy*>(army);
    if (Army) {
        for (int i = 0; i < n; i++) {
            double D = calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos);
            if (D <= 2) {
                army->unitList->getUnits()[i]->setAttackScore(army->unitList->getUnits()[i]->getAttackScoreinFight() * 0.8);
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            double D = calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos);
            if (D <= 2) {
                army->unitList->getUnits()[i]->setAttackScore(army->unitList->getUnits()[i]->getAttackScoreinFight() * 0.9);
            }
        }
    }
}

// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {
    if (!army) return;
    int n = army->unitList->getSize();
    for (int i = 0; i < n; i++) {
        double D = calculateDistance(((army->unitList->getUnits())[i])->getCurrentPosition(), this->pos);
        if (D <= 1) {
            army->unitList->getUnits()[i]->setAttackScore(0);
        }
    }
}