#include "UnitList.h"

bool isSpecialInBase(int S, int base) { //Hàm kiểm tra số đặc biệt cơ số base
    // Danh sách các lũy thừa của base (theo thứ tự giảm dần)
    std::vector<int> powers;
    int power = 1;
    while (power <= S) {
        powers.push_back(power);
        power *= base;
    }

    // Duyệt từ lũy thừa cao nhất đến thấp nhất
    for (int i = powers.size() - 1; i >= 0; --i) {
        if (powers[i] <= S) {
            S -= powers[i]; // Trừ một lũy thừa duy nhất
        }
    }

    return S == 0;
}
int Special(int S) { //Hàm kiểm tra S có phải số đặc biệt có cơ số nguyên tố lẻ nhỏ hơn 10
    int oddPrimes[] = {3, 5, 7};
    for (int base : oddPrimes) {
        if (isSpecialInBase(S, base)) {
            return 12;
        }
    }
    return 8;
}
void UnitList::setCapacity(int capacity) {
    this->capacity = Special(capacity);
}
UnitList::UnitList(int S) : countInfantry(0), countVehicle(0), head(nullptr), tail(nullptr), currentSize(0)
{
    // TODO: Implement
    setCapacity(S);


}

bool UnitList::insert(Unit *unit)
{
        Node* node = new Node(unit);
        Vehicle *m = dynamic_cast<Vehicle*>(unit);
        Infantry *n = dynamic_cast<Infantry*>(unit);
        if (currentSize >= capacity && ((m && !UnitList::isContain(m->getVehicleType())) || (n && !UnitList::isContain(n->getInfantryType())))) return false;
        if (m) {
            if (UnitList::isContain(m->getVehicleType())) {
                increaseVquantity(m);
                delete node;
                // delete unit;
                return false;//có thể return false chưa biết
            }
            else {// Add to tail
                if (!tail) head = tail = node;
                else {
                    tail->next = node;
                    tail = node;
                }
                currentSize++;
                countVehicle++;
                return true;
            }
                
            
        } else if (n) {
            if (UnitList::isContain(n->getInfantryType())) {
                increaseIquantity(n);
                // delete unit;
                delete node;
                return false;//có thể return false chưa biết
            }
            else {// Add to head
                if (!head) head = tail = node;
                else {
                    node->next = head;
                    head = node;
                }
                countInfantry++;
                currentSize++;
                return true;
            }            

        }
        return false;
}

bool UnitList::isContain(VehicleType vehicleType)
{
    // TODO: Implement
    for(int i=0;i<getSize();i++){
        Vehicle* v = dynamic_cast<Vehicle*>(getUnit(i));
        if (v && v->getVehicleType() == vehicleType) {
            return true;
        }
    }
    return false;
}

bool UnitList::isContain(InfantryType infantryType)
{
    // TODO: Implement
    for(int i=0;i<getSize();i++){
        Infantry* in = dynamic_cast<Infantry*>(getUnit(i));
        if (in && in->getInfantryType() == infantryType) {
            return true;
        }
    }
    return false;
}

string UnitList::str() const {
    string result = "UnitList[count_vehicle=" + to_string(countVehicle)
                  + ";count_infantry=" + to_string(countInfantry) ;

    Node* curr = head;
    while (curr != nullptr) {
        if (curr == head) result +=  ";";
        result += curr->unit->str(); // gọi str() của từng Unit
        if (curr->next != nullptr)
            result += ",";
        curr = curr->next;
    }

    result += "]";
    return result;
}

void UnitList::remove(Unit *unit) {
    if (unit == nullptr || head == nullptr)
        return;

    Node* prev = nullptr;
    Node* curr = head;

    // Tìm node chứa unit
    while (curr != nullptr && curr->unit != unit) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr)
        return; // Không tìm thấy

    // Gỡ khỏi danh sách liên kết
    if (curr == head) {
        head = head->next;
        if (curr == tail) tail = nullptr; // danh sách chỉ có 1 phần tử
    } else {
        prev->next = curr->next;
        if (curr == tail) tail = prev;
    }

    delete curr; // Giải phóng node
    currentSize--;


    // Cập nhật đếm loại
    if (dynamic_cast<Vehicle*>(unit)) {
        countVehicle--;
    } else if (dynamic_cast<Infantry*>(unit)) {
        countInfantry--;
    }
}
//Bổ sung
UnitList::~UnitList() {
    // Xóa các Node trong danh sách liên kết
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;  // Xóa node (không delete Unit* vì bạn chưa new chúng)
        current = next;
    }

    // Giải phóng bộ nhớ cho các phần tử trong vector nếu bạn new chúng
    // Cẩn thận: chỉ delete nếu bạn đã dùng new khi tạo Unit*
    // for (Unit* u : units) {
    //     delete u;  // Chỉ delete nếu Unit* là do new
    // }
}


void UnitList::increaseVAfterContain(Vehicle* m) {
    for (int i=0;i<getSize();i++){
        Unit* u = getUnit(i);
        Vehicle* v = dynamic_cast<Vehicle*>(u);
        if (v && v->getVehicleType() == m->getVehicleType()) {
            int temp =v->getQuantity() + m->getQuantity();
            v->setQuantity( temp);
            v->setWeight(max(v->getWeight(), m->getWeight()));
            v->getAttackScore();
            return;
        }
    }
}
void UnitList::increaseIquantity(Infantry* n) {
    for (int i=0;i<getSize();i++){
        Unit* u = getUnit(i);{
        Infantry* i = dynamic_cast<Infantry*>(u);
        if (i && i->getInfantryType() == n->getInfantryType()) {
            int temp =i->getQuantity() + n->getQuantity();
            i->setQuantity( temp);
            i->setWeight(max(i->getWeight(), n->getWeight()));
            i->getAttackScore();
            return;
        }
        
    }    
}

void UnitList::remove_string_ofUnits(vector<Unit *> unitsToRemove) {
    for (Unit *u : unitsToRemove) {
        remove(u);
    }
}
void UnitList::insert_string_ofUnits(vector<Unit *> unitsToInsert) {
    
    for (int i = unitsToInsert.size() - 1; i >= 0; --i) {
        Unit* u = unitsToInsert[i];
        insert(u);
        u->getAttackScore();
    }
}
// vector<Unit *> UnitList::getUnits() const {
//     return units;
// }
Unit* UnitList::getUnit(int index) const {
    if (index < 0 || index >= getSize()) {
        return nullptr; // hoặc throw std::out_of_range nếu bạn muốn chặt chẽ hơn
    }

    Node* current = head;
    int count = 0;
    while (current != nullptr && count < index) {
        current = current->next;
        count++;
    }

    if (current)
        return current->unit;
    else
        return nullptr;
}


