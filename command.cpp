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
    /*
        1:普通回调函数的包装
        2:添加undo的功能
        3:添加宏命令
    */
    struct ICommand;
    class CLight;
    class CLightOnCommand;
    class CSimpleRemoteControl;
    class CMacroCommand;
    using Ptr_CLight = std::shared_ptr<CLight>;
    using Ptr_ICommand = std::shared_ptr<ICommand>;
    using Ptr_CLightOnCommand = std::shared_ptr<CLightOnCommand>;
    using Ptr_CSimpleRemoteControl = std::shared_ptr<CSimpleRemoteControl>;
    using Ptr_CMacroCommand = std::shared_ptr<CMacroCommand>;
    template<typename T>
    using Ptr_Vec = std::shared_ptr<std::vector<T>>;
    struct ICommand//使用智能指针,基类不需要写虚析构函数,因为智能指针保存的是子类指针,可以直接调用子类析构函数
    {
        virtual void execute() = 0;
        virtual void undo() = 0;
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

        void undo()
        {
            this->m_light->off();
        }
        ~CLightOnCommand(){ std::cout << "CLightOnCommand delete" << std::endl; }
    };

    class CLightOffCommand : public ICommand
    {
    private:
        Ptr_CLight m_light;
    public:
        CLightOffCommand(Ptr_CLight light) : m_light(light){}

        void execute()
        {
            this->m_light->off();
        }

        void undo()
        {
            this->m_light->on();
        }
    };

    //宏命令
    class CMacroCommand : public ICommand
    {
    private:
        Ptr_Vec<Ptr_ICommand> m_commands;
    public:
        CMacroCommand(Ptr_Vec<Ptr_ICommand> commands)
        {
            this->m_commands = commands;
        }
        void execute()
        {
            for (auto it = this->m_commands->begin(); it != this->m_commands->end(); ++it)
            {
                (*it)->execute();
            }
        }
        void undo()
        {
            std::for_each(this->m_commands->begin(), this->m_commands->end(), [](Ptr_ICommand elem){
                elem->undo();
            });
        }
    };

    //Invoker对象,存储Command对象,并在适当的时候调用,类似存回调函数
    class CSimpleRemoteControl
    {
    private:
        Ptr_ICommand m_slot;
        Ptr_ICommand m_prevCmd;//记录上一个操作,也可以用Vector保存多个
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
            this->m_prevCmd = this->m_slot;
        }

        void undoButtonWasPressed()
        {
            this->m_prevCmd->undo();
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
            remoteControl->undoButtonWasPressed();

            Ptr_ICommand lightOff = std::make_shared<CLightOffCommand>(light);
            Ptr_Vec<Ptr_ICommand> cmdVec = std::make_shared<std::vector<Ptr_ICommand>>();
            cmdVec->push_back(lightOff);
            cmdVec->push_back(lightOn);
            Ptr_ICommand macroCmd = std::make_shared<CMacroCommand>(cmdVec);
            remoteControl->setCommand(macroCmd);
            remoteControl->buttonWasPressed();
        }
    };
}

int main()
{
    CommandPattern::Client::main();
    return 1;
}