#include <iostream>
#include <string>

using namespace std;

class Car{
private:
    string car_brand_;
    int cylinders_num_;
    int power_;
    
    static int num_cars_;  // статическая переменная для хранения количества объектов
public:
    // Конструктор без параметров:
    Car() : car_brand_(""), cylinders_num_(0), power_(0) {
        ++num_cars_;    // увеличиваем счетчик объектов
    }

    // Конструктор с параметрами:
    Car(string car_brand, int cylinders_num, int power)
        : car_brand_(car_brand), cylinders_num_(cylinders_num), power_(power) {
            ++num_cars_;    // увеличиваем счетчик объектов
        }
    
    // Конструктор копирования:
    Car(const Car& copy) :
        car_brand_(copy.car_brand_), cylinders_num_(copy.cylinders_num_), power_(copy.power_) {
        ++num_cars_;    // увеличиваем счетчик объектов
    }

    // Перегрузка оператора присваивания:
    Car& operator = (const Car& car){
        // Копирование значений:
        car_brand_ = car.car_brand_;
        cylinders_num_ = car.cylinders_num_;
        power_ = car.power_;

        // Возвращаем текущий объект:
        return *this;
    }

    // Деструктор:
    ~Car(){
        --num_cars_;    // Уменьшаем счетчик объектов при удалении
    }
    
    // Геттеры:
    string getCarBrand(){return car_brand_;}
    int getCylindersNum(){return cylinders_num_;}
    int getPower(){return power_;}
    
    // Сеттеры: 
    void setCarBrand(string car_brand){car_brand_ = car_brand;}
    void setCylindersNum(int cylinders_num){cylinders_num_ = cylinders_num;}
    void setPower(int power){power_ = power;}

    // Перегрузка операторов вывода/ввода как дружественных функций классу Car:
    friend ostream& operator<<(ostream& out, const Car& car);
    friend istream& operator>>(istream& is, Car& car);

    // Дружественная функция count:
    friend int count();
};

// Определение статической переменной-члена:
int Car::num_cars_ = 0;

//  Перегрузка оператора вывода:
ostream& operator<<(ostream& out, const Car& car){
    out << car.car_brand_ << " has " << car.cylinders_num_ << " cylinders and " << car.power_ << " kW engine." << endl;
    return out;
}

// Перегрузка оператора ввода:
istream& operator>>(istream& in, Car& car){
    cout << "Enter brand:";
    in >> car.car_brand_;
    cout << "Enter number of cylinders:";
    in >> car.cylinders_num_;
    cout << "Enter engine power:";
    in >> car.power_;

    return in;
}

// Дружественная функция count, возвращающая количество объектов:
int count(){
    return Car::num_cars_;
}


class Lorry : public Car{
private:
    int load_capacity_;
public:
    // Конструктор без параметрв для грузовика:
    Lorry(int load_capacity = 0) : Car(), load_capacity_(load_capacity) {}
    // Конструктор с параметром для грузоподъемности:
    Lorry(string car_brand, int cylinders_num, int power, int load_capacity) 
        : Car(car_brand, cylinders_num, power), load_capacity_(load_capacity) {}

    ~Lorry(){
    }

    void setLoadCapacity(int load_capacity){load_capacity_ = load_capacity;}
    int getLoadCapacity(){return load_capacity_;}

    // Перегрузка оператора вывода для Lorry:
    friend ostream& operator<<(ostream& out, const Lorry& lorry){
        out << static_cast<const Car&>(lorry);  // Вызов оператора вывода для базового класса
        out << "Load capacity: " << lorry.load_capacity_ << " kg" << endl;
        return out;
    }

    // Дружественная функция count:
    friend int count();
};



int main(){
    // Вызов перегруженного оператора ввода:
    Car reno;
    cin >> reno;
    cout << reno;

    Car audi;       // Создание нового объекта класса Car
    audi = reno;    // Вызов перегруженного оператора присваивания
    audi.setCarBrand("Audi");
    cout << audi;

    Car bmw("BMW", 8, 360); // Создание нового объекта класса Car

    cout << bmw;      // Вывод параметров с перегрузкой оператора вывода

    Lorry volvo("Volvo FH", 6, 500, 18000);  // Создание нового объекта класса Lorry
    cout << volvo;  // Вывод параметров с перегрузкой оператора вывода

    // Вывод количества объектов:
    cout << "Total objects created: " << count() << endl;

    return 0;
}