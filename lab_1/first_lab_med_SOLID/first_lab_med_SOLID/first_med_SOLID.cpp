#include <iostream>
#include <memory>

class System {
public:
    System() {};
    ~System() {}

protected:
    friend class Mute;
    friend class Unmute;
    friend class getVolume;
    friend class IncreaseVolume;
    friend class DecreaseVolume;
    int value = 0, muteVolume = false;
};

class getVolume {
public:
    void printVolume(std::shared_ptr<System> sys) {
        std::cout << "Volume is " << sys->value << std::endl;
    };
};

class Mute {
public:
    void mute(std::shared_ptr<System> sys) {
        sys->muteVolume = true;
        std::cout << "Volume is muted\n";
    }
};

class Unmute {
public:
    void unmute(std::shared_ptr<System> sys) {
        sys->muteVolume = false;
        std::cout << "Volume is unmuted\n";
    }
};

class DecreaseVolume {
public:
    void decreaseVolume(std::shared_ptr<System> sys, int val) {
        sys->value -= val;
        if (sys->muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else if (sys->value >= 0) {
            if (sys->value < 0) {
                sys->value = 0;
                std::cout << "Volume is below zero, making it equal to zero\n";
            }
            else {
                std::cout << "Current volume is " << sys->value << ", volume is decreased by " << val << "\n";
            }
        }
    }
};

class IncreaseVolume {
public:
    void increaseVolume(std::shared_ptr<System> sys, int val) {
        sys->value += val;
        if (sys->muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else if (sys->value <= 100) {
            if (sys->value > 100) {
                sys->value = 100;
                std::cout << "Volume is maxed out, making it equal to one hundred\n";
            }
            else {
                std::cout << "Current volume is " << sys->value << ", volume is increased by " << val << "\n";
            }
        }
    }
};

void main() {
    auto sys = std::make_shared<System>();
    auto decVol = std::make_shared<DecreaseVolume>();
    auto incVol = std::make_shared<IncreaseVolume>();
    auto getVol = std::make_shared<getVolume>();
    auto muteVol = std::make_unique<Mute>();
    auto unmuteVol = std::make_unique<Unmute>();
    getVol->printVolume(sys);
    decVol->decreaseVolume(sys, 10);
    muteVol->mute(sys);
    incVol->increaseVolume(sys, 30);
    decVol->decreaseVolume(sys, 40);
    unmuteVol->unmute(sys);
    incVol->increaseVolume(sys, 80);
    getVol->printVolume(sys);
}