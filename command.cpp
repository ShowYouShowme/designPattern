#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*
    回调函数机制的一个替代品---有点类似策略模式
    回调函数有两种:1--全局函数
                   2--类的成员函数  需要绑定实例指针
*/
namespace CommandPattern
{
    struct ICommand;
    class CLight;
    class CLightOnCommand;
    class CSimpleRemoteControl;
    using Ptr_CLight = std::shared_ptr<CLight>;
    using Ptr_ICommand = std::shared_ptr<ICommand>;
    using Ptr_CLightOnCommand = std::shared_ptr<CLightOnCommand>;
    using Ptr_CSimpleRemoteControl = std::shared_ptr<CSimpleRemoteControl>;
    struct ICommand
    {
        virtual void execute() = 0;
    };

    class CLight
    {
    public:
        void on()
        {
            std::cout << "light is on" << std::endl;
        }

        void off()
        {
            std::cout << "light is off" << std::endl;
        }
    };

    class CLightOnCommand : public ICommand
    {
    private:
        Ptr_CLight m_light;
    public:
        CLightOnCommand(Ptr_CLight light) : m_light(light){}

        void execute()
        {
            this->m_light->on();
        }
    };

    //Invoker对象,存储Command对象,并在适当的时候调用,类似存回调函数
    class CSimpleRemoteControl
    {
    private:
        Ptr_ICommand m_slot;
    public:
        CSimpleRemoteControl(){}
        /*注册回调函数*/
        void setCommand(Ptr_ICommand command)
        {
            this->m_slot = command;
        }

        void buttonWasPressed()
        {
            //一系列操作
            //执行传入的回调
            this->m_slot->execute();
        }
    };

    class Client
    {
    public:
        static void main()
        {
            Ptr_CLight light = std::make_shared<CLight>();
            Ptr_ICommand lightOn = std::make_shared<CLightOnCommand>(light);//类似std::bind
            Ptr_CSimpleRemoteControl remoteControl = std::make_shared<CSimpleRemoteControl>();
            remoteControl->setCommand(lightOn);

            remoteControl->buttonWasPressed();
        }
    };
}

int main()
{
    CommandPattern::Client::main();
    return 1;
}