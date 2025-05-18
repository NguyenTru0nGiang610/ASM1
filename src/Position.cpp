#include "Position.h"

//!----------------------------------------------
//! Lớp Position
//!----------------------------------------------
Position::Position(int r, int c) : r(r), c(c) {}
Position::Position(const std::string &str_pos)
{
    sscanf(str_pos.c_str(), "(%d,%d)", &r, &c);
}
int Position::getRow() const { return r; }
int Position::getCol() const { return c; }
void Position::setRow(int r) { 
    this->r = std::max(0, r);
}
void Position::setCol(int c) { 
    this->c = std::max(0, c);
}
string Position::str() const {
    stringstream ss;
    ss << "(" << r << "," << c << ")";
    return ss.str();
}