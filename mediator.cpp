#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
/*
    �н���ģʽ
    ʹ�ó���:һ��ͼ���û������жԻ����ʵ��.�а�ť,�˵�������������.���֮��ͨ����������ϵ,���統������Ϊ��ʱ
    ,��ť����ʹ��.Ŀ��:��ͬ�ĶԻ���Ĵ�������в�ͬ��������ϵ,ϣ������������Щ�������

    ����Ϸ�ͻ��˾����ͬѧ���������ģʽ
*/

/*
    ��������:��EntryFieldΪ��ʱ,okBtn������
             ��ListBox����ѡ��һ��Item��ı�EntryField
             ���okBtn�ǻ�����ѡ�е�����
*/

/*
    ����shared_ptr:

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

        virtual void change()//�ú���������ָ��New�������ܵ���
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

    //ÿ����дһ��UIʱ��дһ��DialogDirector����Ϳ���,���������Button,ListBox֮���������
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
                    std::cout << "����ѡ��һ������" << std::endl;
                    return;
                }
                std::cout << "��ǰ��������Ϊ:" << this->m_fontName->getText() << std::endl;
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
            std::vector<std::string> fontList = { "consolas", "����", "����", "����", "΢���ź�" };
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
