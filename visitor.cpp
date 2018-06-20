#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

/*
    ˼��:1--Ϊһϵ��������²���,���ǲ��ı���Ĵ���
         2--���Ը���Ԫ�ص�һ�����������һ���������൱�ж����Ƿֲ��ڸ�������
         3--double-dispatch

    ʹ�ó���:1--����ṹ�Ƚ��ȶ�����������Ҫ�ڴ˶���ṹ�϶����µĲ���
             2--��Ҫ��һ������ṹ[�����ļ���]�еĶ�����кܶ಻ͬ���Ҳ���صĲ���������Ҫ������Щ��������Ⱦ����Щ������࣬
             Ҳ��ϣ���������²���ʱ�޸���Щ��

             3--�����¹���,����ô�ͳ��ʽ��ʵ��,��Ҫ��Node����������½ӿ�,������ÿ����������ʵ��,����������ģʽ
             ֻ��Ҫ��дһ��Visitor��,֮ǰ�Ĵ��벻��Ҫ���±���
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

    //ע��:1--��Node�����������²���ʱ,ֻ��Ҫдһ��Visitor��
    //     2--visitor������Է���Node�����������,������ʡ����

    //�����ӵĲ���
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