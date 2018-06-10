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
    /*
        1:��ͨ�ص������İ�װ
        2:���undo�Ĺ���
        3:��Ӻ�����
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
    struct ICommand//ʹ������ָ��,���಻��Ҫд����������,��Ϊ����ָ�뱣���������ָ��,����ֱ�ӵ���������������
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

    //������
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

    //Invoker����,�洢Command����,�����ʵ���ʱ�����,���ƴ�ص�����
    class CSimpleRemoteControl
    {
    private:
        Ptr_ICommand m_slot;
        Ptr_ICommand m_prevCmd;//��¼��һ������,Ҳ������Vector������
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
            Ptr_ICommand lightOn = std::make_shared<CLightOnCommand>(light);//����std::bind
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