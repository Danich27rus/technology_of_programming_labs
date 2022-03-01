#include <iostream>
#include <memory>

class System {
public:
    System() {};
    ~System() {};
    virtual void getVolume() {
        std::cout << "Volume is " << value << std::endl;
    };
    friend class Mute;
    friend class Unmute;

protected:
    int value = 0, muteVolume = false;
};

class Mute {
public:
    Mute() {};
    ~Mute() {};

    void mute(std::shared_ptr<System> sys) {
        sys->muteVolume = true;
        std::cout << "Volume is muted\n";
    }

};

class Unmute {
public:
    Unmute() {};
    ~Unmute() {};

    void unmute(std::shared_ptr<System> sys) {
        sys->muteVolume = false;
        std::cout << "Volume is unmuted\n";
    }
};

class Volume : public System {
public:
    Volume() {};
    ~Volume() {};


    void increaseVolume(int val) {
        if (muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else if (value < 100) {
            value += val;
            if (value > 100) {
                value = 100;
                std::cout << "Volume is maxed out, making it equal to one hundred\n";
            }
            else {
                std::cout << "Current volume is " << value << ", volume is increased by " << val << "\n";
            }
        }
    }

    void decreaseVolume(int val) {
        if (muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else if (value > 0) {
            value -= val;
            if (value < 0) {
                value = 0;
                std::cout << "Volume is below zero, making it equal to zero\n";
            }
            else {
                std::cout << "Current volume is " << value << ", volume is decreased by " << val << "\n";
            }
        }
    }
};

void main() {
    auto system = std::make_shared<Volume>();
    auto muteVol = std::make_unique<Mute>();
    auto unmuteVol = std::make_unique<Unmute>();
    system->getVolume();
    system->decreaseVolume(10);
    muteVol->mute(system);
    system->increaseVolume(30);
    system->decreaseVolume(20);
    unmuteVol->unmute(system);
    system->increaseVolume(30);
}