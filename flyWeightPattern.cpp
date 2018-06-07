#include <string>
#include <iostream>
#include <memory>
#include <map>
//享元模式
//对象的属性分为内部状态(可共享)和外部状态(由客户端传入，执行函数)
//同一个class 产生出来的大量对象，有一部分属性相同,可以把这部分相同的属性保留在concreteFlyweight里,不相同的属性由客户端传入，
//concreteFlyweight不保存外部状态
namespace FlyWeightPattern
{
    struct IFlyWeight
    {
        virtual void draw(double x, double y) = 0;
    };


    class CShape : public IFlyWeight
    {
    private:
        //图像有形状,颜色,坐标三个属性,坐标是外部状态,由客户端传入
        std::string   m_shape;
        std::string   m_color;
    public:
        CShape(std::string shape, std::string color);
        virtual void draw(double x, double y) override;
        ~CShape();
    };

    CShape::~CShape()
    {
        std::cout << "CShape 对象delete了" + std::string("\n");
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
            std::cout << "直接从池子里面取得" + key + "\n";
            return it->second;
        }
        else
        {
            std::cout << "建立对象" + key + "\n";
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
        std::cout << "在(" + std::to_string(x) + "," + std::to_string(y) + ")绘制了一个" + this->m_color + this->m_shape + " 形的图像" + "\n";
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