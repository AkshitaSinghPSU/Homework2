#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// SensorType enum
enum class SensorType {
    Airspeed,
    Attitude,
    Altimeter
};

// Sensor base class
class Sensor {
public:
    virtual void sampleData() const = 0;
    virtual void analyzeData() const = 0;
    virtual ~Sensor() {} // Virtual destructor for proper cleanup of derived types
};

// Derived classes from Sensor
class AirspeedSensor : public Sensor {
public:
    void sampleData() const override {
        cout << "Sampling data from Airspeed Sensor" << endl;
    }
    void analyzeData() const override {
        cout << "Analyzing data from Airspeed Sensor" << endl;
    }
};

class AttitudeSensor : public Sensor {
public:
    void sampleData() const override {
        cout << "Sampling data from Attitude Sensor" << endl;
    }
    void analyzeData() const override {
        cout << "Analyzing data from Attitude Sensor" << endl;
    }
};

class AltimeterSensor : public Sensor {
public:
    void sampleData() const override {
        cout << "Sampling data from Altimeter Sensor" << endl;
    }
    void analyzeData() const override {
        cout << "Analyzing data from Altimeter Sensor" << endl;
    }
};

// SensorFactory for creating Sensor objects
class SensorFactory {
public:
    static unique_ptr<Sensor> makeSensor(SensorType sensorType) {
        switch (sensorType) {
        case SensorType::Airspeed:
            return make_unique<AirspeedSensor>();
        case SensorType::Attitude:
            return make_unique<AttitudeSensor>();
        case SensorType::Altimeter:
            return make_unique<AltimeterSensor>();
        }
        cout << "Unknown sensor type" << endl;
        return nullptr;
    }
};

// AerospaceControlSystem class to manage and use sensors
class ControlSystem {
private:
    vector<unique_ptr<Sensor>> sensors;

public:
    void addSensor(SensorType sensorType) {
        sensors.emplace_back(SensorFactory::makeSensor(sensorType));
    }

    void operateSystem() {
        for (auto& sensor : sensors) {
            sensor->sampleData();
            sensor->analyzeData();
            cout << "Adjusting controls based on sensor data." << endl;
        }
    }
};

// Main function
int main() {
    ControlSystem controlSystem;

    controlSystem.addSensor(SensorType::Airspeed);
    controlSystem.addSensor(SensorType::Attitude);
    controlSystem.addSensor(SensorType::Altimeter);

    controlSystem.operateSystem();

    return 0;
}
