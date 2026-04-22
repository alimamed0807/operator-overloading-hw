#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class Airplane {
    int _id;
    char* _model = nullptr;
    char* _color = nullptr;
    double _engine;
    int _capacity;

public:
    static int staticId;
    static int MAXCOUNT;

    Airplane() : _id(++staticId), _model(nullptr), _color(nullptr), _engine(0.0), _capacity(0) {}

    explicit Airplane(const char* model, const char* color, double engine, int capacity)
        : _id(++staticId) {
        setModel(model);
        setColor(color);
        setEngine(engine);
        setCapacity(capacity);
    }

    int getId() const { return _id; }
    const char* getModel() const { return _model; }
    const char* getColor() const { return _color; }
    double getEngine() const { return _engine; }
    int getCapacity() const { return _capacity; }

    void setModel(const char* model) {
        assert(model != nullptr);
        if (this->_model) delete[] this->_model;
        size_t len = strlen(model) + 1;
        this->_model = new char[len];
        strcpy_s(this->_model, len, model);
    }

    void setColor(const char* color) {
        assert(color != nullptr);
        if (this->_color) delete[] this->_color;
        size_t len = strlen(color) + 1;
        this->_color = new char[len];
        strcpy_s(this->_color, len, color);
    }

    void setEngine(double engine) {
        assert(engine > 0);
        this->_engine = engine;
    }

    void setCapacity(int capacity) {
        assert(capacity > 0);
        this->_capacity = capacity;
    }

    static int getMaxCount() { return MAXCOUNT; }

    void print() {
        cout << "ID: " << _id << " | Model: " << (_model ? _model : "N/A")
            << " | Color: " << (_color ? _color : "N/A")
            << " | Engine: " << _engine << " | Capacity: " << _capacity << endl;
    }

    ~Airplane() {
        delete[] _model;
        delete[] _color;
    }
};

int Airplane::staticId = 0;
int Airplane::MAXCOUNT = 100;

class Garage {
private:
    Airplane** airplanes = nullptr;
    size_t _count = 0;
    char* _name = nullptr;
    char* _address = nullptr;

public:
    Garage() = default;

    Garage(const char* name, const char* address) {
        setName(name);
        setAddress(address);
    }

    const char* getName() const { return _name; }
    const char* getAddress() const { return _address; }

    void setName(const char* name) {
        assert(name != nullptr);
        if (this->_name) delete[] this->_name;
        this->_name = new char[strlen(name) + 1];
        strcpy_s(this->_name, strlen(name) + 1, name);
    }

    void setAddress(const char* address) {
        assert(address != nullptr);
        if (this->_address) delete[] this->_address;
        this->_address = new char[strlen(address) + 1];
        strcpy_s(this->_address, strlen(address) + 1, address);
    }

    void addAirplane(Airplane* airplane) {
        assert(airplane != nullptr);
        Airplane** newAirplanes = new Airplane * [_count + 1];
        for (size_t i = 0; i < _count; i++) {
            newAirplanes[i] = airplanes[i];
        }
        newAirplanes[_count] = airplane;
        delete[] airplanes;
        airplanes = newAirplanes;
        _count++;
    }

    Airplane* getAirplaneById(int id) {
        for (size_t i = 0; i < _count; i++) {
            if (airplanes[i]->getId() == id) return airplanes[i];
        }
        return nullptr;
    }

    Airplane** getAirplanesCapacityGreaterThan(int minCapacity) {
        int tempCount = 0;
        for (size_t i = 0; i < _count; i++) {
            if (airplanes[i]->getCapacity() > minCapacity) tempCount++;
        }
        if (tempCount == 0) return nullptr;
        Airplane** result = new Airplane * [tempCount + 1];
        int j = 0;
        for (size_t i = 0; i < _count; i++) {
            if (airplanes[i]->getCapacity() > minCapacity) {
                result[j++] = airplanes[i];
            }
        }
        result[j] = nullptr;
        return result;
    }

    Airplane** getAirplanesByColor(const char* color) {
        assert(color != nullptr);
        int tempCount = 0;
        for (size_t i = 0; i < _count; i++) {
            if (strcmp(airplanes[i]->getColor(), color) == 0) tempCount++;
        }
        if (tempCount == 0) return nullptr;
        Airplane** result = new Airplane * [tempCount + 1];
        int j = 0;
        for (size_t i = 0; i < _count; i++) {
            if (strcmp(airplanes[i]->getColor(), color) == 0) {
                result[j++] = airplanes[i];
            }
        }
        result[j] = nullptr;
        return result;
    }

    void print() {
        cout << "\nGarage: " << (_name ? _name : "N/A") << endl;
        cout << "Address: " << (_address ? _address : "N/A") << endl;
        for (size_t i = 0; i < _count; i++) {
            airplanes[i]->print();
        }
    }

    ~Garage() {
        delete[] _name;
        delete[] _address;
        for (size_t i = 0; i < _count; i++) {
            delete airplanes[i];
        }
        delete[] airplanes;
    }
};

int main() {
    Garage g("Sky Hangar", "Baku");
    g.addAirplane(new Airplane("Boeing 747", "White", 4.2, 400));
    g.addAirplane(new Airplane("Airbus A320", "Blue", 3.0, 150));
    g.print();
    return 0;
}