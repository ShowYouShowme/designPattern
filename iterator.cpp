#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
//你知道为什么C++的*.h和*.cpp要分开写吗
//你知道为什么类的成员变量如果是自定义类型,要用指针吗
//为什么要提前声明
namespace IteratorPattern
{
    //声明
    template<typename T>
    struct IIterator;
    template<typename T>
    struct IAggregate;
    template<typename T>
    class ConcreteAggregate;
    template<typename T>
    class ConcreteIterator;


    //typedef 已经过时,不能处理模板和嵌套类型
    template<typename T>
    using PtrIterator = std::shared_ptr<IIterator<T>>;

    template<typename T>
    using PtrAggregate = std::shared_ptr<IAggregate<T>>;

    template<typename T>
    using PtrConcreteAggregate = std::shared_ptr<ConcreteAggregate<T>>;

    template<typename T>
    using PtrConcreteIterator = std::shared_ptr<ConcreteIterator<T>>;
    /*T是集合中的数据类型*/
    template<typename T>
    struct IIterator
    {
        virtual bool hasNext() = 0;
        virtual T    next() = 0;
    };

    template<typename T>
    struct IAggregate
    {
        virtual PtrIterator<T> createIterator() = 0;
    };

    template<typename T>
    class ConcreteAggregate : public IAggregate<T>
    {
    private:
        //根据std::vector<T>实现,用组合非继承
        std::vector<T> m_vec;
        PtrConcreteAggregate<T> m_self;
        void saveSmartPtr(PtrConcreteAggregate<T> ptr)
        {
            this->m_self = ptr;
        }
    public:
        std::size_t size()
        {
            return this->m_vec.size();
        }
        bool empty()
        {
            return this->m_vec.empty();
        }
        void push_back(const T& val)
        {
            this->m_vec.push_back(val);
        }
        T& operator[] (std::size_t n)
        {
            return this->m_vec[n];
        }
        ~ConcreteAggregate()
        {
            std::cout << "delete Vec" << std::endl;
        }

        static PtrConcreteAggregate<T> create()
        {
            PtrConcreteAggregate<T> result = std::make_shared<ConcreteAggregate<T>>();
            result->saveSmartPtr(result);
            return result;
        }
        virtual PtrIterator<T> createIterator() override
        {
            PtrConcreteIterator<T> result = std::make_shared<ConcreteIterator<T>>(this->m_self);
            this->m_self.reset();
            return result;
        }
    };

    /*T是集合中元素类型*/
    template<typename T>
    class ConcreteIterator : public IIterator<T>
    {
    private:
        PtrConcreteAggregate<T> m_Vec;
        std::size_t position;
    public:
        ConcreteIterator(PtrConcreteAggregate<T> Vec)
        {
            this->m_Vec = Vec;
            this->position = 0;
        }

        virtual bool hasNext() override
        {
            return this->position < this->m_Vec->size();
        }
        virtual T    next() override
        {
            T result = (*this->m_Vec)[this->position];
            this->position += 1;
            return result;
        }
        ~ConcreteIterator()
        {
            std::cout << "delete ConcreteIterator" << std::endl;
        }
    };

    class Client
    {
    public:
        static void main()
        {
            PtrConcreteAggregate<int> vInt = ConcreteAggregate<int>::create();
            vInt->push_back(12);
            vInt->push_back(13);
            vInt->push_back(14);
            vInt->push_back(15);
            vInt->push_back(16);
            auto it = vInt->createIterator();
            while (it->hasNext())
            {
                std::cout << it->next() << " ";
            }
            std::cout << std::endl;
        }
    };
}

int main()
{
    IteratorPattern::Client::main();
    return 1;
}