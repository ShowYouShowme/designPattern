#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <list>
#include <memory>
namespace IteratorPattern
{
    template<typename T>
    struct Iterator
    {
        virtual bool hasNext() = 0;
        virtual T    next() = 0;
    };

    template<typename T>
    class PancakeHouseMenuIterator : public Iterator<T>
    {
    private :
        std::vector<T>& m_items;
        std::size_t m_position;
    public:
        PancakeHouseMenuIterator(std::vector<T>& items) : m_items(items), m_position(0){}
        T next()
        {
            T obj = this->m_items[this->m_position];
            this->m_position += 1;
            return obj;
        }

        bool hasNext()
        {
            return this->m_position < this->m_items.size();
        }
    };

    template<typename T>
    class DinerMenuIterator : public Iterator<T>
    {
    private:
        std::list<T>& m_items;
        typename std::list<T>::iterator it;
    public:
        DinerMenuIterator(std::list<T>& items) : m_items(items), it(this->m_items.begin()){}
        T next()
        {
            T obj = *it;
            ++it;
            return obj;
        }
        bool hasNext()
        {
            return this->it != this->m_items.end();
        }
    };
    template<typename T>
    void print(Iterator<T>& it)
    {
        //一个循环就可以遍历全部的集合
        while (it.hasNext())
        {
            std::cout << it.next() << " ";
        }
        std::cout << std::endl;
    }

    class Client
    {
    public:
        static void main()
        {
            std::vector<int> V1{ 1, 2, 5, 6, 7, 9 };
            Iterator<int>& it = PancakeHouseMenuIterator<int>(V1);
            print(it);

            std::list<double> V2{ 9.8, 9.1, 3.14, 7.29 };
            Iterator<double>& it2 = DinerMenuIterator<double>(V2);
            print(it2);
        }
    };
}
int main()
{
    IteratorPattern::Client::main();
    return 1;
}