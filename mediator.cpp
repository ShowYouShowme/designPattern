#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
/*
    中介者模式
    使用场景:一个图形用户界面中对话框的实现.有按钮,菜单和输入域等组件.组件之间通常有依赖关系,比如当输入域为空时
    ,按钮不能使用.目标:不同的对话框的窗口组件有不同的依赖关系,希望可以重用这些窗口组件

    有游戏客户端经验的同学会深刻理解该模式
*/

/*
    交互过程:当EntryField为空时,okBtn不可用
             在ListBox里面选中一个Item会改变EntryField
             点击okBtn是会设置选中的字体
*/

/*
    关于shared_ptr:

*/
namespace MediatorPattern
{
    class DialogDirector;
    using Ptr_DialogDirector = std::shared_ptr<DialogDirector>;
    class Widget;
    using Ptr_Widget = std::shared_ptr<Widget>;
    class ListBox;
    using Ptr_ListBox = std::shared_ptr<ListBox>;
    class EntityField;
    using Ptr_EntityField = std::shared_ptr<EntityField>;
    class Button;
    using Ptr_Button = std::shared_ptr<Button>;
    class FontDialogDirector;
    using Ptr_FontDialogDirector = std::shared_ptr<FontDialogDirector>;
    class DialogDirector : public std::enable_shared_from_this<DialogDirector>
    {
    public:
        virtual ~DialogDirector(){};
        virtual void widgetChanged(Ptr_Widget) = 0;
        virtual void createWidget() = 0;
    };

    class Widget : public std::enable_shared_from_this<Widget>
    {
    public:
        Widget(Ptr_DialogDirector directory) : m_directory(directory){}

        virtual void change()//该函数用智能指针New对象后才能调用
        {
            this->m_directory->widgetChanged(this->shared_from_this());
        }
        //TODO
        virtual void handleMouse()
        {
            throw "you must rewrite this function!";
        }
    private:
        Ptr_DialogDirector m_directory;
    };

    class ListBox : public Widget
    {
    public:
        ListBox(Ptr_DialogDirector directory) :Widget(directory){}

        std::string getSelection()
        {
            return this->m_listItems[idx];
        }

        void setList(const std::vector<std::string>& listItems)
        {
            this->m_listItems = listItems;
        }

        virtual void handleMouse() override
        {
            srand(time(nullptr));
            this->idx = rand() % this->m_listItems.size();
            this->change();
        }
    private:
        std::vector<std::string> m_listItems;
        std::size_t   idx;
    };

    class EntityField : public Widget
    {
    public:
        EntityField(Ptr_DialogDirector directory) :Widget(directory){}

        void setText(const std::string& text){ this->m_text = text; }

        std::string getText(){ return this->m_text; }

        virtual void handleMouse() override
        {
            std::cout << "the EntityField can not click!" << std::endl;
        }
    private:
        std::string m_text;
    };

    class Button : public Widget
    {
    public:
        Button(Ptr_DialogDirector directory) :Widget(directory){}

        /*
            set button label
        */
        void setText(const std::string& text)
        {
            this->m_label = text;
        }

        virtual void handleMouse()
        {
            std::cout << this->m_label + " is clicked!" + "\n";
            this->change();
        }
    private:
        std::string m_label;
    };

    //每次新写一个UI时，写一个DialogDirector子类就可以,其它的组件Button,ListBox之类可以重用
    class FontDialogDirector : public DialogDirector
    {
    public:
        virtual ~FontDialogDirector(){}
        virtual void widgetChanged(Ptr_Widget theChangedWidget) override
        {
            if (theChangedWidget == this->m_fontList)
            {
                this->m_fontName->setText(this->m_fontList->getSelection());
            }
            else if (theChangedWidget == this->m_ok)
            {
                if (this->m_fontName->getText().empty())
                {
                    std::cout << "请先选中一种字体" << std::endl;
                    return;
                }
                std::cout << "当前字体设置为:" << this->m_fontName->getText() << std::endl;
                //dismiss dialog
            }
            else if (theChangedWidget == this->m_cancel)
            {
                //dismiss dialog
            }
        }
        virtual void createWidget() override
        {
            this->m_ok          = std::make_shared<Button>(this->shared_from_this());
            this->m_ok->setText("ok");
            this->m_cancel      = std::make_shared<Button>(this->shared_from_this());
            this->m_cancel->setText("cancel");
            this->m_fontList    = std::make_shared<ListBox>(this->shared_from_this());
            std::vector<std::string> fontList = { "consolas", "仿宋", "黑体", "宋体", "微软雅黑" };
            this->m_fontList->setList(fontList);
            this->m_fontName    = std::make_shared<EntityField>(this->shared_from_this());
        }

        void run()
        {
            this->createWidget();
            this->m_fontList->handleMouse();
            this->m_ok->handleMouse();
        }
    private:
        Ptr_Button          m_ok;
        Ptr_Button          m_cancel;
        Ptr_ListBox         m_fontList;
        Ptr_EntityField     m_fontName;
    };

    class Client
    {
    public:
        static void main()
        {
            Ptr_FontDialogDirector fontDialogDirector = std::make_shared<FontDialogDirector>();
            fontDialogDirector->run();
        }
    };
}


int main()
{
    MediatorPattern::Client::main();
    return 1;
}
