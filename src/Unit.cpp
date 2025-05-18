#include "Unit.h"

//!----------------------------------------------
//! Lớp Unit
//!----------------------------------------------
Unit::Unit(int quantity, int weight, Position pos)
    : quantity(quantity), weight(weight), pos(pos)
{}
Unit::~Unit()
{
    // Virtual destructor – nếu có bộ nhớ động thì giải phóng ở đây.
}
Position Unit::getCurrentPosition() const
{
    // TODO: Implement
    return pos;
}

void Unit::setWeight(float weight) {
    // TODO: Implement
    this->weight = ceil(weight);
    this->weight = max (this->weight, 1);
}

void Unit::setQuantity(float quantity) {
    // TODO: Implement
    this->quantity = ceil(quantity);
    this->quantity = max (this->quantity, 1);
}
//Hàm bổ sung
int Unit::getQuantity() {
    return quantity;
}
int Unit::getWeight() {
    return weight;
}