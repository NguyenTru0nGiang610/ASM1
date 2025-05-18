#include "Vehicle.h"

//!----------------------------------------------
//! Lớp Vehicle
//!----------------------------------------------
string vehicleTypeToString(VehicleType type) { // enum to string
    switch (type) {
        case TRUCK: return "TRUCK";
        case MORTAR: return "MORTAR";
        case ANTIAIRCRAFT: return "ANTIAIRCRAFT";
        case ARMOREDCAR: return "ARMOREDCAR";
        case APC: return "APC";
        case ARTILLERY: return "ARTILLERY";
        case TANK: return "TANK";
        default: return "UNKNOWN";
    }
}
Vehicle::Vehicle(int quantity, int weight, Position pos, VehicleType vehicleType)
    : Unit(quantity, weight, pos), vehicleType(vehicleType)
{
}

int Vehicle::getAttackScore()
{
    int typeValue = static_cast<int>(vehicleType);
    float score = float((typeValue*304+(quantity*weight)))/30;
    AttackScore = ceil(score);
    return ceil(score);
}


/* 
@Fix
 */
string Vehicle::str() const{
    string vehicleName = vehicleTypeToString(vehicleType) ;
    return "Vehicle[vehicleType=" + vehicleName+",quantity="+to_string(quantity)+",weight="+ to_string(weight) + ",position=" + pos.str() + "]";
}
//Bổ sung
VehicleType Vehicle::getVehicleType() const { return vehicleType; }
