#include <memory>
#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
/*自己写了类的声明,vs可以一键生成方法的实现*/
/*组合模式--主要用来表示树形结构*/
namespace CompositePattern
{
    struct MenuComponent
    {
        virtual void add(std::shared_ptr<MenuComponent> menuComponent);
        virtual void remove(std::shared_ptr<MenuComponent> menuComponent);
        virtual std::shared_ptr<MenuComponent> getChild(int i);
        virtual std::string getName();
        virtual std::string getDescription();
        virtual double getPrice();
        virtual bool isVegetarian();
        virtual void print();
    };

    class CMenuItem : public MenuComponent
    {
    private:
        std::string m_name;
        std::string m_description;
        bool        m_vegetarian;
        double      m_price;
    public:
        CMenuItem(const std::string& name, const std::string& description, bool vegetarian, double price);
        std::string getName() override;
        std::string getDescription() override;
        double getPrice() override;
        bool isVegetarian() override;
        void print() override;
    };

    class CMenu : public MenuComponent
    {
    private:
        /*该成员用来存孩子节点*/
        std::vector<std::shared_ptr<MenuComponent>> m_menuComponents;
        std::string m_name;
        std::string m_description;
    public:
        CMenu(std::string name, std::string description);
        void add(std::shared_ptr<MenuComponent> menuComponent) override;
        void remove(std::shared_ptr<MenuComponent> menuComponent) override;
        std::shared_ptr<MenuComponent> getChild(int i) override;
        std::string getName() override;
        std::string getDescription() override;
        void print() override;
    };

    class CWaitress
    {
    private:
        std::shared_ptr<MenuComponent> m_allMenus;
    public:
        CWaitress(std::shared_ptr<MenuComponent> allMenus);
        void printMenu();
    };

    CWaitress::CWaitress(std::shared_ptr<MenuComponent> allMenus)
    {
        this->m_allMenus = allMenus;
    }

    void CWaitress::printMenu()
    {
        this->m_allMenus->print();
    }

    CMenu::CMenu(std::string name, std::string description)
    {
        this->m_name = name;
        this->m_description = description;
    }

    void CMenu::add(std::shared_ptr<MenuComponent> menuComponent)
    {
        this->m_menuComponents.push_back(menuComponent);
    }

    void CMenu::remove(std::shared_ptr<MenuComponent> menuComponent)
    {
        auto pred = [menuComponent](std::shared_ptr<MenuComponent> param)->bool
        {
            return menuComponent->getName() == param->getName();
        };
        auto it = std::find_if(this->m_menuComponents.begin(), this->m_menuComponents.end(), pred);
        this->m_menuComponents.erase(it);
    }

    std::shared_ptr<MenuComponent> CMenu::getChild(int i)
    {
        return this->m_menuComponents[i];
    }

    std::string CMenu::getName()
    {
        return this->m_name;
    }

    std::string CMenu::getDescription()
    {
        return this->m_description;
    }

    /*主要是这个函数来遍历*/
    void CMenu::print()
    {
        std::cout << "\n" + this->getName() + ", " + this->getDescription() + "---------------------" + "\n";
        for (auto it = this->m_menuComponents.begin(); it != this->m_menuComponents.end(); ++it)
        {
            std::shared_ptr<MenuComponent> menuComponent = *it;
            (*it)->print();
        }
    }

    CMenuItem::CMenuItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        this->m_name = name;
        this->m_description = description;
        this->m_vegetarian = vegetarian;
        this->m_price = price;
    }

    std::string CMenuItem::getName()
    {
        return this->m_name;
    }

    std::string CMenuItem::getDescription()
    {
        return this->m_description;
    }

    double CMenuItem::getPrice()
    {
        return this->m_price;
    }

    bool CMenuItem::isVegetarian()
    {
        return this->m_vegetarian;
    }

    void CMenuItem::print()
    {
        std::cout << " " + this->getName() + ", " + std::to_string(this->getPrice()) + "     ---- " + this->getDescription() + "\n";
    }

    void MenuComponent::add(std::shared_ptr<MenuComponent> menuComponent)
    {
        throw std::bad_exception();
    }

    void MenuComponent::remove(std::shared_ptr<MenuComponent> menuComponent)
    {
        throw std::bad_exception();
    }

    std::shared_ptr<MenuComponent> MenuComponent::getChild(int i)
    {
        throw std::bad_exception();
    }

    std::string MenuComponent::getName()
    {
        throw std::bad_exception();
    }

    std::string MenuComponent::getDescription()
    {
        throw std::bad_exception();
    }

    double MenuComponent::getPrice()
    {
        throw std::bad_exception();
    }

    bool MenuComponent::isVegetarian()
    {
        throw std::bad_exception();
    }

    void MenuComponent::print()
    {
        throw std::bad_exception();
    }


    /************************************************************************/
    /* test                                                                */
    /************************************************************************/
    class MenuTestDrive
    {
    public:
        static void main()
        {
            std::shared_ptr<MenuComponent> pancakeHouseMenu(new CMenu("PANCAKE HOUSE MENU", "Breakfast"));
            std::shared_ptr<MenuComponent> dinerMenu(new CMenu("DINER MENU", "Lunch"));
            std::shared_ptr<MenuComponent> cafeMenu(new CMenu("CAFE MENU", "Dinner"));
            std::shared_ptr<MenuComponent> coffeeMenu(new CMenu("COFFEE MENU", "Stuff to go with your afternoon coffee"));

            std::shared_ptr<MenuComponent> allMenus(new CMenu("ALL MENUS", "All menus combined"));

            allMenus->add(pancakeHouseMenu);
            allMenus->add(dinerMenu);
            allMenus->add(cafeMenu);

            pancakeHouseMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "K&B's Pancake Breakfast",
                "Pancakes with scrambled eggs, and toast",
                true,
                2.99)));
            pancakeHouseMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Regular Pancake Breakfast",
                "Pancakes with fried eggs, sausage",
                false,
                2.99)));
            pancakeHouseMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Blueberry Pancakes",
                "Pancakes made with fresh blueberries, and blueberry syrup",
                true,
                3.49)));

            dinerMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Vegetarian BLT",
                "(Fakin') Bacon with lettuce & tomato on whole wheat",
                true,
                2.99)));
            dinerMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "BLT",
                "Bacon with lettuce & tomato on whole wheat",
                false,
                2.99)));
            dinerMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Soup of the day",
                "A bowl of the soup of the day, with a side of potato salad",
                false,
                3.29)));

            cafeMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Veggie Burger and Air Fries",
                "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
                true,
                3.99)));
            cafeMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Soup of the day",
                "A cup of the soup of the day, with a side salad",
                false,
                3.69)));
            cafeMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Burrito",
                "A large burrito, with whole pinto beans, salsa, guacamole",
                true,
                4.29)));
            cafeMenu->add(coffeeMenu);

            coffeeMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Coffee Cake",
                "Crumbly cake topped with cinnamon and walnuts",
                true,
                1.59)));
            coffeeMenu->add(std::shared_ptr<MenuComponent>(new CMenuItem(
                "Bagel",
                "Flavors include sesame, poppyseed, cinnamon raisin, pumpkin",
                false,
                0.69)));

            std::shared_ptr<CWaitress> waitress(new CWaitress(allMenus));
            waitress->printMenu();
        }
    };
}

int main()
{
    CompositePattern::MenuTestDrive::main();
    return 1;
}