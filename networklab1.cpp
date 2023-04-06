#include <iostream>
#include <vector>
#include <string>

using namespace std;

class EndDevice {
private:
    string name;
public:
    EndDevice(string n) : name(n) {}

    string getName() const {
        return name;
    }

    void receiveData(string data) {
        cout << "End Device " << name << " received data: " << data << endl;
    }

    void sendData(string data, EndDevice* recipient) {
        cout << "End Device " << name << " sent data: " << data << " to End Device " << recipient->getName() << endl;
        recipient->receiveData(data);
    }
};

class Hub {
private:
    string name;
    vector<EndDevice*> devices;
public:
    Hub(string n) : name(n) {}

    string getName() const {
        return name;
    }

    void connectDevice(EndDevice* device) {
        devices.push_back(device);
        cout << "End Device " << device->getName() << " connected to Hub " << name << endl;
    }

    void sendData(string data, EndDevice* sender) {
        cout << "Hub " << name << " received data: " << data << " from End Device " << sender->getName() << endl;
        for (EndDevice* device : devices) {
            if (device != sender) {
                device->receiveData(data);
            }
        }
    }
};

int main() {
    // Create two end devices with a dedicated connection and enable data transmission between them.
    EndDevice device1("Device 1");
    EndDevice device2("Device 2");
    device1.sendData("Hello from device 1", &device2);

    cout << endl;

    // Create a star topology with five end devices connected to a hub and enable communication within end devices.
    Hub hub("Hub 1");
    EndDevice device3("Device 3");
    EndDevice device4("Device 4");
    EndDevice device5("Device 5");
    EndDevice device6("Device 6");

    hub.connectDevice(&device3);
    hub.connectDevice(&device4);
    hub.connectDevice(&device5);
    hub.connectDevice(&device6);

    device3.sendData("Hello from device 3", &device4);
    device5.sendData("Hello from device 5", &device6);
}
