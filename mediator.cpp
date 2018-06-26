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
    class Widget;
    using Ptr_Widget = std::shared_ptr<Widget>;
    class DialogDirector;
    using Ptr_DialogDirector = std::shared_ptr<DialogDirector>;
    class ListBox;
    using Ptr_ListBox = std::shared_ptr<ListBox>;
    class EntryField;
    using Ptr_EntryField = std::shared_ptr<EntryField>;
    class Button;
    using Ptr_Button = std::shared_ptr<Button>;
    class MouseEvent;
    using Ptr_MouseEvent = std::shared_ptr<MouseEvent>;
    //仅仅做示范,不用实现
    class MouseEvent
    {

    };
    class DialogDirector : public std::enable_shared_from_this<DialogDirector>
    {
    public:
        virtual ~DialogDirector(){}
        virtual  void showDialog(bool visible)
        {
            if (visible)
            {
                std::cout << "the dialog is show in front of you!" << std::endl;
            }
            else
            {
                std::cout << "the dialog is dismissed!" << std::endl;
            }
        }
        virtual  void widgetChanged(Ptr_Widget) = 0;
        virtual void createWidgets() = 0;
    };

    class Widget : public std::enable_shared_from_this<Widget>
    {
    public:
        Widget(Ptr_DialogDirector director)
        {
            this->m_director = director;
        }
        virtual void changed()
        {
            this->m_director->widgetChanged(this->shared_from_this());
        }
        virtual void handleMouse(Ptr_MouseEvent event){
            std::cout << "this widget do not response the click event!" << std::endl;
        }
    private:
        Ptr_DialogDirector m_director;
    };

    //点击ListBox时会将内容设置到EntryField
    class ListBox : public Widget
    {
    public:
        ListBox(Ptr_DialogDirector director) :Widget(director){}

        std::string getSelection()
        {
            return this->m_fontNameList[this->selectIdx];
        }

        void setList(std::vector<std::string>& listItems)
        {
            this->m_fontNameList = listItems;
        }

        virtual void handleMouse(Ptr_MouseEvent event) override
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            this->selectIdx = rand() % m_fontNameList.size();
            std::cout << std::string("当前选择的是:") + this->m_fontNameList[this->selectIdx] << std::endl;
            this->changed();
        }
    private:
        std::vector<std::string> m_fontNameList;
        std::vector<std::string>::size_type  selectIdx;
    };

    class EntryField : public Widget
    {
    public:
        EntryField(Ptr_DialogDirector director) :Widget(director){}

        virtual void setText(const std::string& text)
        { 
            this->m_text = text; 
            std::cout << std::string("EntryField txt :") + text + "\n";
        }

        virtual std::string getText()
        {
            return this->m_text;
        }

    private:
        std::string m_text;
    };

    class Button : public Widget
    {
    public:
        Button(Ptr_DialogDirector director) :Widget(director){}

        void setText(const std::string& text)
        {
            this->m_name = text;
        }

        virtual void handleMouse(Ptr_MouseEvent event)
        {
            std::cout << std::string("button ") + this->m_name + "is clcked" + "\n";
            this->changed();
        }
    private:
        std::string m_name;
    };

    class FontDialogDirector : public DialogDirector
    {
    public:
        FontDialogDirector()
        {
        }
        virtual ~FontDialogDirector(){}
        virtual void widgetChanged(Ptr_Widget theChangedWidget)
        {
            if (theChangedWidget == this->m_fontList)
            {
                this->m_fontName->setText(this->m_fontList->getSelection());
            }
            else if (theChangedWidget == this->m_ok)
            {
                if (this->m_fontName->getText() == "")
                {
                    std::cout << "当前未选中任何字体" << std::endl;
                    return;
                }
                //apply font change and dismiss dialog
                //...
                std::cout << std::string("the font set to ") + this->m_fontName->getText() + "\n";
                this->showDialog(false);
            }
            else if (theChangedWidget == this->m_cancel)
            {
                std::cout << "dialog will be hide" << std::endl;
                //dismiss dialog
                this->showDialog(false);
            }
        }

        void userInput()
        {
            //选择字体列表

            this->m_ok->handleMouse(nullptr);

            std::cout << "====================================" << std::endl;
            this->m_fontList->handleMouse(nullptr);

            this->m_ok->handleMouse(nullptr);
        }
        virtual void createWidgets() override
        {
            auto it = this->shared_from_this();
            this->m_ok = std::make_shared<Button>(this->shared_from_this());
            this->m_cancel = std::make_shared<Button>(this->shared_from_this());
            this->m_fontList = std::make_shared<ListBox>(this->shared_from_this());
            this->m_fontName = std::make_shared<EntryField>(this->shared_from_this());

            //fill the listBox with the available font name
            std::vector<std::string> fontName = {"宋体", "微软雅黑", "Consolas", "黑体"};
            this->m_fontList->setList(fontName);
            //assemble the widgets in the dialog
        }
    private:
        Ptr_Button m_ok;
        Ptr_Button m_cancel;
        Ptr_ListBox m_fontList;
        Ptr_EntryField m_fontName;
    };

    class Client
    {
    public:
        static void main()
        {
            std::shared_ptr<FontDialogDirector> fontDialogDirector = std::make_shared<FontDialogDirector>();
            fontDialogDirector->createWidgets();
            fontDialogDirector->userInput();
        }
    };
}


int main()
{
    MediatorPattern::Client::main();
    return 1;
}
