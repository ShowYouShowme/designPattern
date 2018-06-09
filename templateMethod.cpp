#include <string>
#include <iostream>
#include <memory>
#include <map>
/*�ڻ����ж����㷨�ĹǼ�,����һЩ�����ӳٵ�������ʵ��
����:���԰ѹ�����Ϊ��ȡ������,��������ظ�,�ɱ䲿����������ʵ��*/
namespace TemplateMethod
{
    struct CaffeineBeverage
    {
        /*��ˮ���*/
        void boilWater();
        /*�ݲ���߿���*/
        virtual void brew() = 0;
        /*�����ϵ��뱭��*/
        void pourInCup();
        /*��ӵ���*/
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