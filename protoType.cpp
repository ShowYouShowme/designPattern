#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

/*
    原型模式
    场景:音符,休止符,五线谱继承自Graphics类.工具面板中有很多工具,Tool是抽象基类.Tool子类GraphicsTool创建乐谱图形对象并加入到文档,
    如何设计GraphicsTool类?
    方法1:为每一种音乐对象创建一个GraphicsTool子类
    方法2:原型模式---这里要介绍的

    棋牌游戏服务器会用到该模式:将每款麻将的游戏Logic都继承一个基类GameLogic并且写成DLL,有个原型管理器在GameLogic dll载入时注册该逻辑
    实例,然后程序主框架向原型管理器请求Logic实例
*/

namespace PrototypePattern
{
    struct IGraphic
    {
        virtual void draw(double x, double y) = 0;
        virtual IGraphic* clone() = 0;
    };

    /*
        五线谱
    */
    class Staff : public IGraphic
    {
    public:
        virtual void draw(double x, double y)
        {
            std::cout << std::string("在(") + std::to_string(x) + "," + std::to_string(y) + ")绘制了一个五线谱\n";
        }

        /*
            这里可以写成拷贝构造
        */
        virtual IGraphic* clone()
        {
            return new Staff();
        }
    };

    /*
        音符
    */
    class MusicalNote : public IGraphic
    {

    };

    /*
        全音符
    */
    class WholeNote : public MusicalNote
    {
        virtual void draw(double x, double y)
        {
            std::cout << std::string("在(") + std::to_string(x) + "," + std::to_string(y) + ")绘制了一个全音符\n";
        }
        virtual IGraphic* clone()
        {
            std::cout << "clone 了一个全音符\n";
            return new WholeNote();
        }
    };

    /*
        二分音符
    */
    class HalfNote : public MusicalNote
    {
        virtual void draw(double x, double y)
        {
            std::cout << std::string("在(") + std::to_string(x) + "," + std::to_string(y) + ")绘制了一个二分音符\n";
        }
        virtual IGraphic* clone()
        {
            std::cout << "clone 了一个二分音符\n";
            return new HalfNote();
        }
    };
    struct ITOOL
    {
        virtual void manipulate() = 0;
    };

    class RotateTool : public ITOOL
    {

    };

    class GraphicTool : public ITOOL
    {
    public:
        GraphicTool(IGraphic* graphic) : m_graphic(graphic){}
        virtual void manipulate() override
        {
            IGraphic* p = this->m_graphic->clone();
            srand(time(nullptr));
            p->draw(rand() % 500, rand() % 500);
        }
    private:
        IGraphic* m_graphic;
    };

    class Client
    {
    public:
        static void main()
        {
            ITOOL* staffTool = new GraphicTool(new Staff());
            ITOOL* wholeNoteTool = new GraphicTool(new WholeNote());
            ITOOL* halfNote = new GraphicTool(new HalfNote());

            staffTool->manipulate();
            wholeNoteTool->manipulate();
            halfNote->manipulate();
        }
    };
}

int main()
{
    PrototypePattern::Client::main();
    return 1;
}