#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*
    �ص��������Ƶ�һ�����Ʒ---�е����Ʋ���ģʽ
    �ص�����������:1--ȫ�ֺ���
                   2--��ĳ�Ա����  ��Ҫ��ʵ��ָ��
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

    //Invoker����,�洢Command����,�����ʵ���ʱ�����,���ƴ�ص�����
    class CSimpleRemoteControl
    {
    private:
        Ptr_ICommand m_slot;
    public:
        CSimpleRemoteControl(){}
        /*ע��ص�����*/
        void setCommand(Ptr_ICommand command)
        {
            this->m_slot = command;
        }

        void buttonWasPressed()
        {
            //һϵ�в���
            //ִ�д���Ļص�
            this->m_slot->execute();
        }
    };

    class Client
    {
    public:
        static void main()
        {
            Ptr_CLight light = std::make_shared<CLight>();
            Ptr_ICommand lightOn = std::make_shared<CLightOnCommand>(light);//����std::bind
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