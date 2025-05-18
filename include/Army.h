#ifndef _H_ARMY_H_
#define _H_ARMY_H_

class BattleField; // Forward declaration

#include "UnitList.h"
#include "BattleField.h"
using namespace std;

//!-----------------------------------------------------
//! CLASS Army 
//!-----------------------------------------------------
/* 
   * Army: 
   *  LF được tính bằng tổng điểm tấn công của các phương tiện.
   *  EXP được tính bằng tổng điểm tấn công của các lực lượng bộ binh.
   *  Capacity của UnitList được tính dựa vào S = LF + EXP.
   *(Các thao tác thêm vào danh sách đơn vị được thực hiện trong Army constructor.)
*/
class Army {
protected:
    int LF;        // * Tổng điểm từ các phương tiện (Vehicle)
    int EXP;       // * Tổng điểm từ các lực lượng bộ binh (Infantry)
    string name;
    UnitList* knapsack(UnitList* inputList, int minScore);
    BattleField *battleField;
public:
    UnitList *unitList;
    Army(Unit **unitArray, int size, string name, BattleField *battleField);
    virtual ~Army();
    virtual void fight(Army *enemy, bool defense = false) = 0;
    virtual string str() const = 0;
    UnitList * getUnitType(string type) ;
    // * Additional functions if possible
    //Bổ sung
    int getLF() const;
    int getEXP() const;
    void setLF(int LF) { this->LF = ceil(min(LF, 1000));};
    void setEXP(int EXP) { this->EXP = ceil(min(EXP, 500));};
    string getName() const;
    //Bổ sung
    int safeCeil(double value); 
    Unit getUnitByType(string type);
    void updateScore(bool update);
    void TEupdateScore();
    void decreaseWeight(float a);
    void decreaseQuantity(float a);
    UnitList* clone(UnitList* units);
    
};

#endif
