#include "Infantry.h"

// TODO: implement

// ? Kiểm tra n có phải là số chính phương không


// ? Tính tổng các chữ số của n


//!----------------------------------------------
//! Lớp Infantry
//!----------------------------------------------
bool isPerfectSquare(int num) { // Số chính phương
    int root = static_cast<int>(sqrt(num));
    return (root * root == num) ? true : false;
}
int getPersonalNumber(int value, int year) { //Hàm lấy số cá nhân
    int sum = value;
    // Cộng tất cả các chữ số của value và year
    while (year > 0) {
        sum += year % 10;
        year /= 10;
    }
    // Rút gọn còn 1 chữ số
    while (sum >= 10) {
        int temp = 0;
        while (sum > 0) {
            temp += sum % 10;
            sum /= 10;
        }
        sum = temp;
    }
    return sum;
}
Infantry::Infantry(int quantity, int weight, Position pos, InfantryType infantryType)
    : Unit(quantity, weight, pos), infantryType(infantryType)
{
}

int Infantry::getAttackScore() {
    int typeValue = static_cast<int>(infantryType);
    int score = typeValue * 56 + quantity * weight;

    // Nếu là đặc công
    if (infantryType == SPECIALFORCES && isPerfectSquare(weight)) {
        score += 75;
    }

    // Tính số cá nhân với năm 1975
    int personalNumber = getPersonalNumber(score, 1975);

    // Điều chỉnh quantity
    if (personalNumber > 7) {
        double q = quantity * 1.2;
        quantity = static_cast<int>(ceil(q));  // Chi viện 20%    
    } else if (personalNumber < 3) {
        double q = quantity * 0.9;
        quantity = static_cast<int>(ceil(q));  // Đào ngũ 10%
    }
    // Tính lại điểm tấn công
    score = typeValue * 56 + quantity * weight;
    AttackScore = score;

 

    return score;
}

string Infantry::str() const {
    string infantryName = infantryTypeToString(Infantry::infantryType) ;
    return "Infantry[infantryType="+infantryName+",quantity="+to_string(quantity)+",weight="+ to_string(weight) + ",position=" + pos.str() + "]";
}
//Bổ sung



