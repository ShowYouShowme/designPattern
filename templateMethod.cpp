#include <string>
#include <iostream>
#include <memory>
#include <map>
/*在基类中定义算法的骨架,而将一些步骤延迟到子类来实现
作用:可以把公共行为提取到父类,避免代码重复,可变部分留到子类实现*/
namespace TemplateMethod
{
    struct CaffeineBeverage
    {
        /*把水煮沸*/
        void boilWater();
        /*泡茶或者咖啡*/
        virtual void brew() = 0;
        /*把饮料倒入杯子*/
        void pourInCup();
        /*添加调料*/
        virtual void addCondiments() = 0;
        void prepareRecipe();
    };

    class Coffee : public CaffeineBeverage
    {
    public:
        virtual void brew() override;
        virtual void addCondiments() override;
    };

    class Tea : public CaffeineBeverage
    {
    public:
        virtual void brew() override;
        virtual void addCondiments() override;
    };

    void Tea::brew()
    {
        std::cout << "Steeping the tea" << std::endl;
    }

    void Tea::addCondiments()
    {
        std::cout << "Adding Lemon" << std::endl;
    }

    void Coffee::brew()
    {
        std::cout << "Dripping Coffee through filter" << std::endl;
    }

    void Coffee::addCondiments()
    {
        std::cout << "Adding Sugar and Milk" << std::endl;
    }

    void CaffeineBeverage::boilWater()
    {
        std::cout << "Boiling water" << std::endl;
    }

    void CaffeineBeverage::pourInCup()
    {
        std::cout << "Pouring into cup" << std::endl;
    }

    void CaffeineBeverage::prepareRecipe()
    {
        this->boilWater();
        this->brew();
        this->pourInCup();
        this->addCondiments();
    }

    class Client
    {
    public:
        static void main()
        {
            std::shared_ptr<CaffeineBeverage> tea = std::make_shared<Tea>();
            std::shared_ptr<CaffeineBeverage> coffee = std::make_shared<Coffee>();

            std::cout << "Making tea..." << std::endl;
            tea->prepareRecipe();

            std::cout << "Making coffee..." << std::endl;
            coffee->prepareRecipe();
        }
    };

}

int main()
{
    TemplateMethod::Client::main();
    return 1;
}