#include <iostream>

class Volume {
public:
    static Volume& GetInstance() {
        static Volume* singleton = new Volume();
        singleton->getVolume();
        return *singleton;
    }

    void increaseVolume(int val) {
        value += val;
        if (value > 100) {
            value = 100;
            std::cout << "Volume is maxed out\n";
        }
        else if (muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else {
            std::cout << "Current volume is " << value << ", volume is increased by " << val << "\n";
        }
    }

    void decreaseVolume(int val) {
        value -= val;
        if (value < 0 && muteVolume == false) {
            value = 0;
            std::cout << "Volume is below zero\n";
        }
        else if (muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else {
            std::cout << "Current volume is " << value << ", volume is decreased by " << val << "\n";
        }
    }

    void mute() {
        muteVolume = true;
        value = 0;
    }

    void unmute() {
        muteVolume = false;
        value = 0;
    }

private:
    int value = 35, muteVolume = false;

    Volume() = default;
    void getVolume() {
        std::cout << "Volume is " << value << std::endl;
    }
    Volume(const Volume&) = delete;
    Volume& operator=(const Volume&) = delete;
    Volume(Volume&&) = delete;
    Volume& operator=(Volume&&) = delete;
};

void main() {
    Volume& system = Volume::GetInstance();
    system.increaseVolume(40);

    system.decreaseVolume(10);
}