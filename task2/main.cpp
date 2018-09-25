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
    char    *strRet = new char[256];
  explicit Car(const string& aLicensePlate = Car::def)
            : licensePlate(aLicensePlate)
    {
    }
    const char* name() override
    {
        string  src = "Car " + licensePlate;

        for (int i = 0; i < src.length(); i++)
            strRet[i] = src[i];
        strRet[src.length()] = 0;

        return (strRet);
    }
    ~Car(){cout << "I'm destCar" << endl;
        delete[] strRet;}
};


int main()
{
    Nameable* car = new Car;
    cout << car->name() << endl;

    delete car;
}
