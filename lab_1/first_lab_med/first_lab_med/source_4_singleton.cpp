#include <iostream>

class Volume;

class System {
public:
    System() {};
    friend class Volume;
protected:
    int value = 0;
};

class Windows : public System {};


class Volume {
public:
    static Volume* GetInstance() {
        static Volume* singleton = new Volume();
        return singleton;
    }

    void setUniqueSystem(System* n_sys) {
        sys = n_sys;
    }

    void increaseVolume(int val) {
        sys->value += val;
        if (sys->value > 100) {
            sys->value = 100;
            std::cout << "Volume is maxed out\n";
        }
        else {
            std::cout << "Current volume is " << sys->value << ", volume is increased by " << val << "\n";
        }
    }

    void decreaseVolume(int val) {
        sys->value -= val;
        if (sys->value < 0) {
            sys->value = 0;
            std::cout << "Volume is below zero\n";
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


void main() {
    Volume* system = Volume::GetInstance();
    system->setUniqueSystem(new Windows());
    system->increaseVolume(40);
    system->decreaseVolume(10);

}