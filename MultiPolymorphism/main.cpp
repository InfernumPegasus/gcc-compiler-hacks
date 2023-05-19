#include <iostream>
#include <vector>

struct ISwimable {
    virtual void Swim() const = 0;
};

struct IFlyable {
    virtual void Fly() const = 0;
};

struct IWalkable {
    virtual void Walk() const = 0;
};

struct Penguin : public virtual ISwimable,
                 public virtual IWalkable {
    void Swim() const override {
        std::cout << "Penguin can swim\n";
    }

    void Walk() const override {
        std::cout << "Penguin can walk\n";
    }
};

struct FlyingFish : public virtual ISwimable,
                    public virtual IFlyable {
    void Swim() const override {
        std::cout << "FlyingFish can swim\n";
    }

    void Fly() const override {
        std::cout << "FlyingFish can fly\n";
    }
};

struct Human : public virtual ISwimable,
               public virtual IWalkable {
    void Swim() const override {
        std::cout << "Human can swim\n";
    }

    void Walk() const override {
        std::cout << "Human can walk\n";
    }
};

struct JackOfAllTrades : public virtual ISwimable,
                         public virtual IWalkable,
                         public virtual IFlyable {
    void Swim() const override {
        std::cout << "JackOfAllTrades can swim\n";
    }

    void Fly() const override {
        std::cout << "JackOfAllTrades can fly\n";
    }

    void Walk() const override {
        std::cout << "JackOfAllTrades can walk\n";
    }
};

int main() {
    {
        std::vector<IFlyable *> flyingCreatures{
                {new FlyingFish, new JackOfAllTrades}
        };
        for (const auto &creature: flyingCreatures) {
            creature->Fly();
        }
    }
    std::cout << "\n";
    {
        std::vector<ISwimable *> swimmingCreatures{
                {new FlyingFish, new Penguin, new JackOfAllTrades}
        };
        for (const auto &creature: swimmingCreatures) {
            creature->Swim();
        }
    }
    std::cout << "\n";
    {
        std::vector<IWalkable *> walkingCreatures{
                {new Human, new JackOfAllTrades}
        };
        for (const auto &creature: walkingCreatures) {
            creature->Walk();
        }
    }

    return 0;
}
