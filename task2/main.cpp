#include <iostream>

using namespace std;

class Nameable {
public:
    virtual const char* name() = 0;
    virtual ~Nameable(){cout << "I'm destNameable" << endl;}
};

class Car : public Nameable {
private:
    static constexpr const char* def = "AA1234BB";
public:
    const string& licensePlate;
    char    *str_ret = new char[256];
    Car(const string& aLicensePlate = Car::def)
            : licensePlate(aLicensePlate)
    {
    }
    const char* name() override
    {
        string  src = "Car " + licensePlate;

        for (int i = 0; i < src.length(); i++)
            str_ret[i] = src[i];
        str_ret[src.length()] = 0;

        return (str_ret);
    }
    ~Car(){cout << "I'm destCar" << endl;
        delete[] str_ret;}
};


int main()
{
    Nameable* car = new Car;
    cout << car->name() << endl;

    delete car;
}