#include <string>
#include <iostream>
#include <memory>
#include <map>
//��Ԫģʽ
//��������Է�Ϊ�ڲ�״̬(�ɹ���)���ⲿ״̬(�ɿͻ��˴��룬ִ�к���)
//ͬһ��class ���������Ĵ���������һ����������ͬ,���԰��ⲿ����ͬ�����Ա�����concreteFlyweight��,����ͬ�������ɿͻ��˴��룬
//concreteFlyweight�������ⲿ״̬
namespace FlyWeightPattern
{
    struct IFlyWeight
    {
        virtual void draw(double x, double y) = 0;
    };


    class CShape : public IFlyWeight
    {
    private:
        //ͼ������״,��ɫ,������������,�������ⲿ״̬,�ɿͻ��˴���
        std::string   m_shape;
        std::string   m_color;
    public:
        CShape(std::string shape, std::string color);
        virtual void draw(double x, double y) override;
        ~CShape();
    };

    CShape::~CShape()
    {
        std::cout << "CShape ����delete��" + std::string("\n");
    }

    class CFlyWeightFactory
    {
    private:
        std::map<std::string, std::shared_ptr<CShape>> m_pool;
    public:
        std::shared_ptr<CShape> getFlyweight(std::string key);

    };


    std::shared_ptr<CShape> FlyWeightPattern::CFlyWeightFactory::getFlyweight(std::string key)
    {
        auto it = this->m_pool.find(key);
        if (it != this->m_pool.end())
        {
            std::cout << "ֱ�Ӵӳ�������ȡ��" + key + "\n";
            return it->second;
        }
        else
        {
            std::cout << "��������" + key + "\n";
            std::size_t idx = key.find_first_of('_');
            std::string shape = key.substr(0, idx);
            std::string color = key.substr(idx + 1);
            auto result = std::make_shared<CShape>(shape, color);
            this->m_pool[key] = result;
            return result;
        }
    }

    void FlyWeightPattern::CShape::draw(double x, double y)
    {
        std::cout << "��(" + std::to_string(x) + "," + std::to_string(y) + ")������һ��" + this->m_color + this->m_shape + " �ε�ͼ��" + "\n";
    }

    FlyWeightPattern::CShape::CShape(std::string shape, std::string color)
    {
        this->m_color = color;
        this->m_shape = shape;
    }

    struct Client
    {
    public:
        static void main()
        {
            auto factory = std::make_shared<CFlyWeightFactory>();
            auto s1 = factory->getFlyweight("circle_red");
            auto s2 = factory->getFlyweight("circle_green");
            auto s3 = factory->getFlyweight("circle_grey");
            auto s4 = factory->getFlyweight("circle_red");
            auto s5 = factory->getFlyweight("circle_green");

            s1->draw(1, 2);
            s2->draw(2, 3);
            s3->draw(3, 4);
            s4->draw(4, 5);
            s5->draw(5, 6);
        }
    };
}

int main()
{
    FlyWeightPattern::Client::main();
    return 1;
}