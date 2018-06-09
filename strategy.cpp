#include <string>
#include <iostream>
#include <memory>
namespace StrategyPattern
{
    struct ITravelStrategy
    {
        virtual void travel() = 0;
    };

    class AirplaneStrategy : public ITravelStrategy
    {
    public:
        virtual void travel();
    };

    class TrainStrategy : public ITravelStrategy
    {
    public:
        virtual void travel();
    };

    class BicycleStrategy : public ITravelStrategy
    {
    public:
        virtual void travel();
    };

    class Person
    {
    private:
        std::shared_ptr<ITravelStrategy> m_strategy;
    public:
        void setStrategy(std::shared_ptr<ITravelStrategy> strategy);
        void travel();
    };

    void AirplaneStrategy::travel()
    {
        std::cout << "travel by airplane" + std::string("\n");
    }

    void TrainStrategy::travel()
    {
        std::cout << "travel by train" + std::string("\n");
    }

    void BicycleStrategy::travel()
    {
        std::cout << "travel by bicycle" + std::string("\n");
    }

    void Person::setStrategy(std::shared_ptr<ITravelStrategy> strategy)
    {
        this->m_strategy = strategy;
    }

    void Person::travel()
    {
        this->m_strategy->travel();
    }


    class Client
    {
    public:
        static void main()
        {
            std::shared_ptr<ITravelStrategy> t1 = std::make_shared<AirplaneStrategy>();
            std::shared_ptr<ITravelStrategy> t2 = std::make_shared<TrainStrategy>();
            std::shared_ptr<ITravelStrategy> t3 = std::make_shared<BicycleStrategy>();
            std::shared_ptr<Person> p = std::make_shared<Person>();
            p->setStrategy(t1);
            p->travel();

            std::cout << "--------------------" << std::endl;
            p->setStrategy(t2);
            p->travel();
            std::cout << "--------------------" << std::endl;
            p->setStrategy(t3);
            p->travel();
            std::cout << "--------------------" << std::endl;
        }
    };

}

//不使用策略模式的写法
namespace NoStrategy
{
    class Person
    {
    public:
        //将算法硬编码进去
        void travel(std::string vehicle)
        {
            if (vehicle == "Airplane")
            {
                this->airplaneTravel();
            }
            else if (vehicle == "Train")
            {
                this->trainTravel();
            }
            else if (vehicle == "bicycle")
            {
                this->bicycleTravel();
            }
        }
    private:

        void airplaneTravel()
        {
            std::cout << "travel by airplane" << std::endl;
        }

        void trainTravel()
        {
            std::cout << "travel by train" << std::endl;
        }

        void bicycleTravel()
        {
            std::cout << "travel by bicycle" << std::endl;
        }
    };
}
int main()
{
    //StrategyPattern::Client::main();
    std::shared_ptr<NoStrategy::Person> p = std::make_shared<NoStrategy::Person>();
    p->travel("Airplane");
    p->travel("Train");
    p->travel("bicycle");
    return 1;
}