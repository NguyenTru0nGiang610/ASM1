#include "BattleField.h"
//!-----------------------------------------------------
// CLASS BattleField
//!-----------------------------------------------------
BattleField::BattleField(int n_rows, int n_cols,
                         const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver,
                         const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban,
                         const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    // Cấp phát mảng 2 chiều
    terrain = new TerrainElement**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        terrain[i] = new TerrainElement*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            Position pos(i, j);
            terrain[i][j] = new Road(pos);  // Khởi tạo mặc định là đường mòn
        }
    }

    // Gán từng loại địa hình theo vị trí trong mảng
    for (Position* pos : arrayForest)
        terrain[pos->getRow()][pos->getCol()] = new Mountain(*pos);

    for (Position* pos : arrayRiver)
        terrain[pos->getRow()][pos->getCol()] = new River(*pos);

    for (Position* pos : arrayFortification)
        terrain[pos->getRow()][pos->getCol()] = new Fortification(*pos);

    for (Position* pos : arrayUrban)
        terrain[pos->getRow()][pos->getCol()] = new Urban(*pos);

    for (Position* pos : arraySpecialZone)
        terrain[pos->getRow()][pos->getCol()] = new SpecialZone(*pos);
}

BattleField::~BattleField() {
    for (int i = 0; i < n_rows; ++i) {
        delete[] terrain[i];
    }
    delete[] terrain;
}


TerrainElement* BattleField::getElement(int r, int c) const {
    if (r >= 0 && r < n_rows && c >= 0 && c < n_cols) {
        return terrain[r][c];
    }
    else {
        return nullptr;
    }
}
string BattleField::str() const {
    stringstream ss;
    ss << "BattleField[n_rows=" << n_rows << ",n_cols=" << n_cols << "]";
    return ss.str();
}