#include "Configuration.h"

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

Configuration::Configuration(const std::string &filepath) {
    num_rows = 0;
    num_cols = 0;
    eventCode = 0;

    ifstream file(filepath);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filepath);
    }

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        // Split line into key and value
        size_t eq_pos = line.find('=');
        if (eq_pos == string::npos) continue;
        string key = trim(line.substr(0, eq_pos));
        string value = trim(line.substr(eq_pos + 1));

        if (key == "NUM_ROWS") {
            num_rows = stoi(value);
        } else if (key == "NUM_COLS") {
            num_cols = stoi(value);
        } else if (key == "EVENT_CODE") {
            int ec = stoi(value);
            if (ec < 0) {
                eventCode = 00;
            } else {
                eventCode = ec % 100; // Take last two digits if > 99
            }
        } else if (key == "ARRAY_FOREST" || key == "ARRAY_RIVER" || 
                   key == "ARRAY_FORTIFICATION" || key == "ARRAY_URBAN" || 
                   key == "ARRAY_SPECIAL_ZONE") {
            vector<Position*>* targetArray = nullptr;
            if (key == "ARRAY_FOREST") targetArray = &arrayForest;
            else if (key == "ARRAY_RIVER") targetArray = &arrayRiver;
            else if (key == "ARRAY_FORTIFICATION") targetArray = &arrayFortification;
            else if (key == "ARRAY_URBAN") targetArray = &arrayUrban;
            else if (key == "ARRAY_SPECIAL_ZONE") targetArray = &arraySpecialZone;

            // Remove brackets and parse positions
            value = trim(value.substr(1, value.size() - 2));
            if (value.empty()) continue;

            stringstream ss(value);
            string pos;
            while (getline(ss, pos, ',')) {
                pos = trim(pos);
                if (pos.empty()) continue;
                // Remove parentheses
                pos = pos.substr(1, pos.size() - 2);
                stringstream pos_ss(pos);
                int x, y;
                char comma;
                pos_ss >> x >> comma >> y;
                targetArray->push_back(new Position(x, y));
            }
        } else if (key == "UNIT_LIST") {
            // Remove brackets
            value = trim(value.substr(1, value.size() - 2));
            if (value.empty()) continue;

            stringstream ss(value);
            string unit_str;
            while (getline(ss, unit_str, ',')) {
                unit_str = trim(unit_str);
                if (unit_str.empty()) continue;

                // Parse unit: UNIT_NAME(quantity,weight,position,armyBelong)
                size_t name_end = unit_str.find('(');
                string unit_name = unit_str.substr(0, name_end);
                string params = unit_str.substr(name_end + 1, unit_str.size() - name_end - 2);
                stringstream params_ss(params);
                int quantity, weight, x, y, armyBelong;
                char comma, open_paren, close_paren;
                params_ss >> quantity >> comma >> weight >> comma 
                         >> open_paren >> x >> comma >> y >> close_paren >> comma >> armyBelong;

                Position* pos = new Position(x, y);
                Unit* unit = nullptr;
                if (unit_name == "TRUCK" || unit_name == "MORTAR" || 
                    unit_name == "ANTIAIRCRAFT" || unit_name == "ARMOREDCAR" || 
                    unit_name == "APC" || unit_name == "ARTILLERY" || 
                    unit_name == "TANK") {
                    unit = new Vehicle(quantity, weight, *pos, Vehicle::stringToVehicleType(unit_name));
                } else if (unit_name == "SNIPER" || unit_name == "ANTIAIRCRAFTSQUAD" || 
                           unit_name == "MORTARSQUAD" || unit_name == "ENGINEER" || 
                           unit_name == "SPECIALFORCES" || unit_name == "REGULARINFANTRY") {
                    unit = new Infantry(quantity, weight, *pos, Infantry::stringToInfantryType(unit_name));
                } else {
                    delete pos;
                    continue; // Skip unknown unit types
                }

                if (armyBelong == 0) {
                    liberationUnits.push_back(unit);
                } else if (armyBelong == 1) {
                    ARVNUnits.push_back(unit);
                } else {
                    delete unit; // Invalid armyBelong
                }
            }
        }
    }
    file.close();
}

Configuration::~Configuration() {
    // Free Position objects in terrain arrays
    for (Position* pos : arrayForest) delete pos;
    for (Position* pos : arrayRiver) delete pos;
    for (Position* pos : arrayFortification) delete pos;
    for (Position* pos : arrayUrban) delete pos;
    for (Position* pos : arraySpecialZone) delete pos;

    // Free Unit objects (Position objects are deleted by Unit destructor)
    for (Unit* unit : liberationUnits) delete unit;
    for (Unit* unit : ARVNUnits) delete unit;
}

string Configuration::str() const {
    stringstream ss;
    ss << "[";
    ss << "num_rows=" << num_rows << ",";
    ss << "num_cols=" << num_cols << ",";
    ss << "arrayForest=[";
    for (size_t i = 0; i < arrayForest.size(); ++i) {
        ss << arrayForest[i]->str();
        if (i < arrayForest.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "arrayRiver=[";
    for (size_t i = 0; i < arrayRiver.size(); ++i) {
        ss << arrayRiver[i]->str();
        if (i < arrayRiver.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "arrayFortification=[";
    for (size_t i = 0; i < arrayFortification.size(); ++i) {
        ss << arrayFortification[i]->str();
        if (i < arrayFortification.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "arrayUrban=[";
    for (size_t i = 0; i < arrayUrban.size(); ++i) {
        ss << arrayUrban[i]->str();
        if (i < arrayUrban.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "arraySpecialZone=[";
    for (size_t i = 0; i < arraySpecialZone.size(); ++i) {
        ss << arraySpecialZone[i]->str();
        if (i < arraySpecialZone.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "liberationUnits=[";
    for (size_t i = 0; i < liberationUnits.size(); ++i) {
        ss << liberationUnits[i]->str();
        if (i < liberationUnits.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "ARVNUnits=[";
    for (size_t i = 0; i < ARVNUnits.size(); ++i) {
        ss << ARVNUnits[i]->str();
        if (i < ARVNUnits.size() - 1) ss << ",";
    }
    ss << "],";
    ss << "eventCode=" << eventCode;
    ss << "]";
    return ss.str();
}