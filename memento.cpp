#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>
/*
    思想:把Original里面的部分状态移到Memento里面保存,并且只有Original才能访问Memento
*/
namespace MementoPattern
{
    template<typename T>
    class Memento;

    template<typename T>
    using Ptr_Memento = std::shared_ptr<Memento<T>>;

    template<typename T>
    class Original;

    //关键是这个类的设计,仅仅允许class Original<T>访问里面的状态,达到封装的目的
    template<typename T>
    class Memento
    {
    private:
        friend class Original<T>;
        Memento();;
        void setState(T s);
        T getState();
    private:
        T m_state;
    };

    template<typename T>
    class Original
    {
    private:
        T m_state;//状态
    public:
        Original(T param);
        void setMemento(Ptr_Memento<T> m);

        Ptr_Memento<T> createMemento();
        void action();
        void print();
    };

    template<typename T>
    Memento<T>::Memento()
    {

    }

    template<typename T>
    void Memento<T>::setState(T s)
    {
        this->m_state = s;
    }

    template<typename T>
    T Memento<T>::getState()
    {
        return this->m_state;
    }

    template<typename T>
    Original<T>::Original(T param) :m_state(param)
    {

    }

    template<typename T>
    void Original<T>::setMemento(Ptr_Memento<T> m)
    {
        this->m_state = m->getState();
    }

    template<typename T>
    Ptr_Memento<T> Original<T>::createMemento()
    {
        //这里用工厂函数创建会报错,因为只有Original<T>可以创建
        //Ptr_Memento<T> result = std::make_shared<Memento<T>>();
        Ptr_Memento<T> result(new Memento<T>());
        result->setState(this->m_state);
        return result;

    }

    template<typename T>
    void Original<T>::action()
    {
        std::string stateType(typeid(T).name());
        if (typeid(int).name() == stateType)
        {
            this->m_state += 1;
        }
        else if (typeid(std::string).name() == stateType)
        {
            this->m_state += "_litt" + std::to_string(this->m_state.size());
        }
    }

    template<typename T>
    void Original<T>::print()
    {
        std::cout << this->m_state << std::endl;
    }

    class Client
    {
    public:
        static void main()
        {
            Original<std::string> original("nash");
            original.action();
            original.print();
            Ptr_Memento<std::string> memento = original.createMemento();
            original.action();
            original.print();
            original.setMemento(memento);
            original.print();
        }
    };
}

int main()
{
    MementoPattern::Client::main();
    return 1;
}