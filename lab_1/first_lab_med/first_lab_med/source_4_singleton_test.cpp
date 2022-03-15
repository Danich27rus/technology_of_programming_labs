#include <iostream>

class System {
public:
    System(int n_value) : value(n_value) {};
    System() : {};
protected:
    int value = 35, muteVolume = false;
};

class Volume {
public:
    static Volume* GetInstance() {
        static Volume* singleton = new Volume();
        return singleton;
    }

    void increaseVolume(sys, int val) {
        sys->value += val;
        if (sys->value > 100) {
            sys->value = 100;
            std::cout << "Volume is maxed out\n";
        }
        else if (sys->muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else {
            std::cout << "Current volume is " << sys->value << ", volume is increased by " << val << "\n";
        }
    }

    void decreaseVolume(sys, int val) {
        sys->value -= val;
        if (sys->value < 0 && sys->muteVolume == false) {
            sys->value = 0;
            std::cout << "Volume is below zero\n";
        }
        else if (sys->muteVolume == true) {
            std::cout << "Current volume is 0 because volume is muted\n";
        }
        else {
            std::cout << "Current volume is " << sys->value << ", volume is decreased by " << val << "\n";
        }
    }

private:
    System* sys;

    Volume() = default;

    Volume(const Volume&) = delete;
    Volume& operator=(const Volume&) = delete;
    Volume(Volume&&) = delete;
    Volume& operator=(Volume&&) = delete;
};

class Mute : public Volume {
public:
    void mute() {
        muteVolume = true;
    }
};

class Unmute : public Volume {
public:
    void unmute() {
        muteVolume = false;
    }
};


void main() {
    Volume* system = Volume::GetInstance();

    Unmute* unmute = new Unmute();
    Mute* mute = new Mute();
    system->increaseVolume(40);
    mute->mute(system);
    system->decreaseVolume(10);

    delete unmute;
    delete mute;
}