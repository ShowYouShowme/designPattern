#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*责任链模式*/
/*
  应用场景:1--异常处理,可以自己处理,也可以重新抛出
           2--客户端UI点击事件,可以由Sprite自己处理,也可以Sprite的父容器处理
  */
namespace ResponsibilityPattern
{
    //声明
    class HelpHandler;
    using Ptr_HelpHandler = std::shared_ptr<HelpHandler>;
    class Request;
    using Prt_Request     = std::shared_ptr<Request>;
    class PrintHelpHandler;
    using Ptr_PrintHelpHandler = std::shared_ptr<PrintHelpHandler>;
    class PreviewHelpHandler;
    using Ptr_PreviewHelpHandler = std::shared_ptr<PreviewHelpHandler>;
    class RootHelpHandler;
    using Ptr_RootHelpHandler = std::shared_ptr<RootHelpHandler>;

    enum class RequestType
    {
        PRINT,
        HELP,
        PREVIEW
    };
    class Request
    {
    public:
        Request(RequestType type): m_kind(type){}
        RequestType getKind(){ return this->m_kind;}
    private:
        RequestType m_kind;
    };
    class HelpHandler
    {
    public:
        HelpHandler(Ptr_HelpHandler s) : m_successor(s){}
        virtual void  handlerRequest(Prt_Request theRequest)
        {
            this->m_successor->handlerRequest(theRequest);
        }
    private:
        Ptr_HelpHandler m_successor;
    };

    class PrintHelpHandler : public HelpHandler
    {
    public:
        PrintHelpHandler(Ptr_HelpHandler s) :HelpHandler(s){}
        virtual void  handlerRequest(Prt_Request theRequest) override
        {
            switch (theRequest->getKind())
            {
            case RequestType::PRINT:
            {
                std::cout << "request handled by PrintHelpHandler" << std::endl;
                return;
            }
            default:
                HelpHandler::handlerRequest(theRequest);
            }
        }
    };

    class PreviewHelpHandler : public HelpHandler
    {
    public:
        PreviewHelpHandler(Ptr_HelpHandler s) :HelpHandler(s){}
        virtual void handlerRequest(Prt_Request theRequest) override
        {
            switch (theRequest->getKind())
            {
            case RequestType::PREVIEW:
            {
               std::cout << "request handled by PreviewHelpHandler" << std::endl;
               return;
            }
            default:
                HelpHandler::handlerRequest(theRequest);
            }
        }
    };
    
    class RootHelpHandler : public HelpHandler
    {
    public:
        RootHelpHandler(Ptr_HelpHandler s = nullptr) :HelpHandler(s){}
        virtual void handlerRequest(Prt_Request theRequest) override
        {
            std::cout << "request handled by RootHelpHandler" << std::endl;
            return;
        }
    };

    class Client
    {
    public:
        static void main()
        {
            Ptr_RootHelpHandler root = std::make_shared<RootHelpHandler>();
            Ptr_PrintHelpHandler print = std::make_shared<PrintHelpHandler>(root);
            Ptr_PreviewHelpHandler preview = std::make_shared<PreviewHelpHandler>(print);

            Prt_Request printRequest = std::make_shared<Request>(RequestType::PRINT);
            Prt_Request previewRequest = std::make_shared<Request>(RequestType::PREVIEW);
            Prt_Request helpRequest = std::make_shared<Request>(RequestType::HELP);

            preview->handlerRequest(printRequest);
            preview->handlerRequest(previewRequest);
            preview->handlerRequest(helpRequest);
        }
    };
}

int main()
{
    ResponsibilityPattern::Client::main();
    return 1;
}