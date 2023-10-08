#include <iostream>
#include <memory>
#include <string>

class Tea {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Tea() = default;
};

class BasicTea : public Tea {
public:
    std::string getDescription() const override {
        return "Basic Tea";
    }

    double cost() const override {
        return 1.0;
    }
};

class TeaDecorator : public Tea {
protected:
    Tea* _tea;

public:
    TeaDecorator(Tea* tea) : _tea(tea) {}

    std::string getDescription() const override {
        return _tea->getDescription();
    }

    double cost() const override {
        return _tea->cost();
    }
};

class HoneyDecorator : public TeaDecorator {
public:
    HoneyDecorator(Tea* tea) : TeaDecorator(tea) {}

    std::string getDescription() const override {
        return _tea->getDescription() + " with Honey";
    }

    double cost() const override {
        return _tea->cost() + 0.5;
    }
};

class LemonDecorator : public TeaDecorator {
public:
    LemonDecorator(Tea* tea) : TeaDecorator(tea) {}

    std::string getDescription() const override {
        return _tea->getDescription() + " with Lemon";
    }

    double cost() const override {
        return _tea->cost() + 0.3;
    }
};

int main() {
    auto basicTea = std::make_unique<BasicTea>();
    auto teaWithMilk = std::make_unique<HoneyDecorator>(basicTea.get());
    auto teaWithMilkAndSugar = std::make_unique<LemonDecorator>(teaWithMilk.get());


    std::cout << basicTea->getDescription() << ": $" << basicTea->cost() << std::endl;
    std::cout << teaWithMilk->getDescription() << ": $" << teaWithMilk->cost() << std::endl;
    std::cout << teaWithMilkAndSugar->getDescription() << ": $" << teaWithMilkAndSugar->cost() << std::endl;

}
