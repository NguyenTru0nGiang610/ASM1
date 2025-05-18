#ifndef _H_UNITLIST_H_
#define _H_UNITLIST_H_

#include "Infantry.h"
#include "Vehicle.h"

class UnitList
{
private:
struct Node {
    Unit *unit; //con trỏ đến đối tượng Unit
    Node *next; //con trỏ đến node tiếp theo
    Node(Unit* u) : unit(u), next(nullptr) {}
};
    int capacity;
    // vector<Unit *> units;
    int countVehicle, countInfantry;
    //Bổ sung
    int currentSize;
    Node *head;
    Node *tail;

public:
    UnitList(int capacity);
    bool insert(Unit *unit);
    bool isContain(VehicleType vehicleType);
    bool isContain(InfantryType infantryType);
    
    string str() const;
    // * Additional functions if possible
    //Bổ sung
    void remove(Unit *unit);
    ~UnitList();
    void increaseVAfterContain(Vehicle* V);
    void increaseIquantity(Infantry* I);
    void remove_string_ofUnits(vector<Unit *> units);
    void insert_string_ofUnits(vector<Unit *> units);
    // vector<Unit *> getUnits() const;
    Unit *getUnit(int i) const;
    int getSize() const{ return currentSize; };
    void setSize(int size){ currentSize = size; };
    int getCapacity() const{ return capacity; };
    void setCapacity(int capacity);
    int getCountVehicle() const{ return countVehicle; };
    int getCountInfantry() const{ return countInfantry; };
    void reduceQuantity(int percent);
    void reduceWeight(int percent);
    void clear() {}
    // void setUnits(vector<Unit *> units);
};

#endif
