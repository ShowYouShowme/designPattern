#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*
    1:״̬����û�г�Ա����,��˿����õ���
    2:GumballMachine����״̬�йص���Ϊί�и���Ա����m_state������
    3:��������state�����ı�GumballMachine��״̬
*/
namespace StatePattern
{
    struct State;
    using Ptr_State = std::shared_ptr<State>;
    class GumballMachine;
    using Ptr_GumballMachine = std::shared_ptr<GumballMachine>;

    class GumballMachine : public std::enable_shared_from_this<GumballMachine>
    {
    private:
        Ptr_State m_state;
        int       m_count;
    public:
        GumballMachine(int count);
        /*Ͷ��25��*/
        void insertQuarter();
        /*�˻�25��*/
        void ejectQuarter();
        /*ת������*/
        void turnCrank();
        /*�����ǹ�*/
        void dispense();
        void releaseBall();
        int getCount();
    private:
        //ע������Ŷ,��ɧ
        friend class State;
        void changeState(Ptr_State newState);
    };

    /*�ṩĬ����Ϊ,ͬʱ��ֹ�ͻ�����State����*/
    struct State
    {
        /*Ͷ��25��*/
        virtual void insertQuarter(Ptr_GumballMachine machine){ std::cout << "default behavior" << std::endl; }
        /*�˻�25��*/
        virtual void ejectQuarter(Ptr_GumballMachine machine){ std::cout << "default behavior" << std::endl; }
        /*ת������*/
        virtual void turnCrank(Ptr_GumballMachine machine){ std::cout << "default behavior" << std::endl; }
        /*�����ǹ�*/
        virtual void dispense(Ptr_GumballMachine machine){ std::cout << "default behavior" << std::endl; }
    protected:
        void changeState(Ptr_GumballMachine machie, Ptr_State state)
        {
            machie->changeState(state);
        }
        State(){}
    };

    /*û��25��״̬*/
    class NoQuarterState : public State
    {
    public:
        /*Ͷ��25��*/
        virtual void insertQuarter(Ptr_GumballMachine machine);
        /*�˻�25��*/
        virtual void ejectQuarter(Ptr_GumballMachine machine);
        /*ת������*/
        virtual void turnCrank(Ptr_GumballMachine machine);
        /*�����ǹ�*/
        virtual void dispense(Ptr_GumballMachine machine);
        static Ptr_State getInstance();
    private:
        NoQuarterState();
    };

    /*��25��״̬*/
    class HasQuarterState : public State
    {
    public:
        /*Ͷ��25��*/
        virtual void insertQuarter(Ptr_GumballMachine machine);
        /*�˻�25��*/
        virtual void ejectQuarter(Ptr_GumballMachine machine);
        /*ת������*/
        virtual void turnCrank(Ptr_GumballMachine machine);
        /*�����ǹ�*/
        virtual void dispense(Ptr_GumballMachine machine);
        static Ptr_State getInstance();
    private:
        HasQuarterState();
    };

    /*�۳��ǹ�״̬*/
    class SoldState : public State
    {
    public:
        /*Ͷ��25��*/
        virtual void insertQuarter(Ptr_GumballMachine machine);
        /*�˻�25��*/
        virtual void ejectQuarter(Ptr_GumballMachine machine);
        /*ת������*/
        virtual void turnCrank(Ptr_GumballMachine machine);
        /*�����ǹ�*/
        virtual void dispense(Ptr_GumballMachine machine);
        static Ptr_State getInstance();
    private:
        SoldState();
    };

    /*�ǹ���ܰ״̬*/
    class SoldOutState : public State
    {
    public:
        /*Ͷ��25��*/
        virtual void insertQuarter(Ptr_GumballMachine machine);
        /*�˻�25��*/
        virtual void ejectQuarter(Ptr_GumballMachine machine);
        /*ת������*/
        virtual void turnCrank(Ptr_GumballMachine machine);
        /*�����ǹ�*/
        virtual void dispense(Ptr_GumballMachine machine);
        static Ptr_State getInstance();
    private:
        SoldOutState();
    };

    //implement  NoQuarterState
    void NoQuarterState::insertQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "You inserted a quarter" << std::endl;
        this->changeState(machine, HasQuarterState::getInstance());
    }

    void NoQuarterState::ejectQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "You haven't inserted a quarter" << std::endl;
    }

    void NoQuarterState::turnCrank(Ptr_GumballMachine machine)
    {
        std::cout << "You turned, but there's no quarter" << std::endl;
    }

    void NoQuarterState::dispense(Ptr_GumballMachine machine)
    {
        std::cout << "You need to pay first" << std::endl;
    }

    Ptr_State NoQuarterState::getInstance()
    {
        static Ptr_State pInstance(nullptr);
        if (pInstance == nullptr)
        {
            pInstance.reset(new NoQuarterState());
        }
        return pInstance;
    }

    NoQuarterState::NoQuarterState()
    {

    }

    //implements HasQuarterState
    void HasQuarterState::insertQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "You can't insert another quarter" << std::endl;
    }

    void HasQuarterState::ejectQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "Quarter returned" << std::endl;
        this->changeState(machine, NoQuarterState::getInstance());
    }

    void HasQuarterState::turnCrank(Ptr_GumballMachine machine)
    {
        std::cout << "You turned..." << std::endl;
        this->changeState(machine, SoldState::getInstance());
    }

    void HasQuarterState::dispense(Ptr_GumballMachine machine)
    {
        std::cout << "No gumball dispensed" << std::endl;
    }

    Ptr_State HasQuarterState::getInstance()
    {
        static Ptr_State pInstance(nullptr);
        if (pInstance == nullptr)
        {
            pInstance.reset(new HasQuarterState());
        }
        return pInstance;
    }

    HasQuarterState::HasQuarterState()
    {

    }

    //implement  SoldState
    void SoldState::insertQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "Please wait, we're already giving you a gumball" << std::endl;
    }

    void SoldState::ejectQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "Sorry, you already turned the crank" << std::endl;
    }

    void SoldState::turnCrank(Ptr_GumballMachine machine)
    {
        std::cout << "Turning twice doesn't get you another gumball!" << std::endl;
    }

    void SoldState::dispense(Ptr_GumballMachine machine)
    {
        machine->releaseBall();
        if (machine->getCount() > 0)
        {
            this->changeState(machine, NoQuarterState::getInstance());
        }
        else
        {
            std::cout << "Oops, out of gumballs!" << std::endl;
            this->changeState(machine, SoldOutState::getInstance());
        }
    }

    Ptr_State SoldState::getInstance()
    {
        static Ptr_State pInstance(nullptr);
        if (pInstance == nullptr)
        {
            pInstance.reset(new SoldState());
        }
        return pInstance;
    }

    SoldState::SoldState()
    {

    }

    //implement SoldOutState
    void SoldOutState::insertQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
    }

    void SoldOutState::ejectQuarter(Ptr_GumballMachine machine)
    {
        std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
    }

    void SoldOutState::turnCrank(Ptr_GumballMachine machine)
    {
        std::cout << "You turned, but there are no gumballs" << std::endl;
    }

    void SoldOutState::dispense(Ptr_GumballMachine machine)
    {
        std::cout << "No gumball dispensed" << std::endl;
    }

    Ptr_State SoldOutState::getInstance()
    {
        static Ptr_State pInstance(nullptr);
        if (pInstance == nullptr)
        {
            pInstance.reset(new SoldOutState());
        }
        return pInstance;
    }

    SoldOutState::SoldOutState()
    {

    }

    //implements
    GumballMachine::GumballMachine(int count)
    {
        this->m_count = count;
        this->m_state = NoQuarterState::getInstance();
    }

    void GumballMachine::insertQuarter()
    {
        this->m_state->insertQuarter(this->shared_from_this());
    }

    void GumballMachine::ejectQuarter()
    {
        this->m_state->ejectQuarter(this->shared_from_this());
    }

    void GumballMachine::turnCrank()
    {
        this->m_state->turnCrank(this->shared_from_this());
        this->m_state->dispense(this->shared_from_this());
    }

    void GumballMachine::dispense()
    {
        this->m_state->dispense(this->shared_from_this());
    }

    void GumballMachine::changeState(Ptr_State newState)
    {
        this->m_state = newState;
    }

    void GumballMachine::releaseBall()
    {
        std::cout << "A gumball comes rolling out the slot..." << std::endl;
        if (this->m_count != 0)
        {
            this->m_count -= 1;
        }
    }

    int GumballMachine::getCount()
    {
        return this->m_count;
    }

    //client

    class Client
    {
    public:
        static void main()
        {
            Ptr_GumballMachine gumballMachine = std::make_shared<GumballMachine>(5);

            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();
            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();

            std::cout << "------------------------------------" << std::endl;

            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();
            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();

            std::cout << "------------------------------------" << std::endl;

            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();
            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();

            std::cout << "------------------------------------" << std::endl;

            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();
            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();

            std::cout << "------------------------------------" << std::endl;

            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();
            gumballMachine->insertQuarter();
            gumballMachine->turnCrank();


        }
    };
}

int main()
{
    StatePattern::Client::main();
    return 1;
}