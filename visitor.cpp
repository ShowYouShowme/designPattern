#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*
    思想:1--为一系列类添加新操作,但是不改变类的代码
         2--将对各个元素的一组操作集中在一个访问者类当中而不是分布于各个子类
         3--double-dispatch

    使用场景:1--对象结构比较稳定，但经常需要在此对象结构上定义新的操作
             2--需要对一个对象结构[存对象的集合]中的对象进行很多不同的且不相关的操作，而需要避免这些操作“污染”这些对象的类，
             也不希望在增加新操作时修改这些类

             3--增加新功能,如果用传统方式来实现,需要在Node类里面添加新接口,并且在每个子类里面实现,但是用这种模式
             只需要新写一个Visitor类,之前的代码不需要重新编译
*/
namespace VisitorPattern
{
    struct INode;
    using Ptr_INode = std::shared_ptr<INode>;
    struct INodeVisitor;
    using Ptr_INodeVisitor = std::shared_ptr<INodeVisitor>;
    class  VariableRefNode;
    using Ptr_VariableRefNode = std::shared_ptr<VariableRefNode>;
    class  AssignmentNode;
    using Ptr_AssignmentNode = std::shared_ptr<AssignmentNode>;
    struct INode
    {
        virtual void accept(Ptr_INodeVisitor v) = 0;
    };
    struct INodeVisitor
    {
        virtual void visit(Ptr_VariableRefNode) = 0;
        virtual void visit(Ptr_AssignmentNode) = 0;
    };

    class VariableRefNode : public INode , public std::enable_shared_from_this<VariableRefNode>
    {
    public :
        virtual void accept(Ptr_INodeVisitor v)
        {
            v->visit(this->shared_from_this());
        }
    };

    class AssignmentNode : public INode, public std::enable_shared_from_this<AssignmentNode>
    {
    public:
        virtual void accept(Ptr_INodeVisitor v)
        {
            v->visit(this->shared_from_this());
        }
    };

    class TypeCheckingVisitor : public INodeVisitor
    {
    public:
        virtual void visit(Ptr_VariableRefNode)
        {
            std::cout << "typeCheck for VariableRefNode" << std::endl;
        }
        virtual void visit(Ptr_AssignmentNode)
        {
            std::cout << "typeCheck for AssignmentNode" << std::endl;
        }
    };

    class PrettyPrint : public INodeVisitor
    {
    public:
        virtual void visit(Ptr_VariableRefNode)
        {
            std::cout << "PrettyPrint for VariableRefNode" << std::endl;
        }
        virtual void visit(Ptr_AssignmentNode)
        {
            std::cout << "PrettyPrint for AssignmentNode" << std::endl;
        }
    };

    //注意:1--对Node的子类增加新操作时,只需要写一个Visitor类
    //     2--visitor里面可以访问Node的子类的属性,我这里省略了

    //新增加的操作
    class GenerateCode : public INodeVisitor
    {
    public:
        virtual void visit(Ptr_VariableRefNode)
        {
            std::cout << "GenerateCode in VariableRefNode" << std::endl;
        }
        virtual void visit(Ptr_AssignmentNode)
        {
            std::cout << "GenerateCode in AssignmentNode" << std::endl;
        }
    };
    class Client
    {
    public:
        static void main()
        {
            std::vector<Ptr_INode> nodeVec;
            nodeVec.push_back(std::make_shared<VariableRefNode>());
            nodeVec.push_back(std::make_shared<AssignmentNode>());
            Ptr_INodeVisitor visitor = std::make_shared<TypeCheckingVisitor>();
            std::for_each(nodeVec.begin(), nodeVec.end(), [&visitor](Ptr_INode elem){
                elem->accept(visitor);
            });

            visitor = std::make_shared<PrettyPrint>();
            std::for_each(nodeVec.begin(), nodeVec.end(), [&visitor](Ptr_INode elem){
                elem->accept(visitor);
            });


            visitor = std::make_shared<GenerateCode>();
            std::for_each(nodeVec.begin(), nodeVec.end(), [&visitor](Ptr_INode elem){
                elem->accept(visitor);
            });
        }
    };
}

int main()
{
    VisitorPattern::Client::main();
    return 1;
}