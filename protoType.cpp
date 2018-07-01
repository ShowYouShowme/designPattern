#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

/*
    ԭ��ģʽ
    ����:����,��ֹ��,�����׼̳���Graphics��.����������кܶ๤��,Tool�ǳ������.Tool����GraphicsTool��������ͼ�ζ��󲢼��뵽�ĵ�,
    ������GraphicsTool��?
    ����1:Ϊÿһ�����ֶ��󴴽�һ��GraphicsTool����
    ����2:ԭ��ģʽ---����Ҫ���ܵ�

    ������Ϸ���������õ���ģʽ:��ÿ���齫����ϷLogic���̳�һ������GameLogic����д��DLL,�и�ԭ�͹�������GameLogic dll����ʱע����߼�
    ʵ��,Ȼ������������ԭ�͹���������Logicʵ��
*/

namespace PrototypePattern
{
    struct IGraphic
    {
        virtual void draw(double x, double y) = 0;
        virtual IGraphic* clone() = 0;
    };

    /*
        ������
    */
    class Staff : public IGraphic
    {
    public:
        virtual void draw(double x, double y)
        {
            std::cout << std::string("��(") + std::to_string(x) + "," + std::to_string(y) + ")������һ��������\n";
        }

        /*
            �������д�ɿ�������
        */
        virtual IGraphic* clone()
        {
            return new Staff();
        }
    };

    /*
        ����
    */
    class MusicalNote : public IGraphic
    {

    };

    /*
        ȫ����
    */
    class WholeNote : public MusicalNote
    {
        virtual void draw(double x, double y)
        {
            std::cout << std::string("��(") + std::to_string(x) + "," + std::to_string(y) + ")������һ��ȫ����\n";
        }
        virtual IGraphic* clone()
        {
            std::cout << "clone ��һ��ȫ����\n";
            return new WholeNote();
        }
    };

    /*
        ��������
    */
    class HalfNote : public MusicalNote
    {
        virtual void draw(double x, double y)
        {
            std::cout << std::string("��(") + std::to_string(x) + "," + std::to_string(y) + ")������һ����������\n";
        }
        virtual IGraphic* clone()
        {
            std::cout << "clone ��һ����������\n";
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