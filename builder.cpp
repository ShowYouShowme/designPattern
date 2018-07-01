#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

/*
    Builderģʽ
    ��ͼ:1--ͬ���Ĺ������̴�����ͬ��ʾ(product) ***********
         2--ͬ����product��ͬ���������ڲ���ʾ��ͬ
         3--��Ʒ��������ֱ��new �õ�,��Ҫdirector����������ݲ�������

    Ӧ�ó���:RTF�Ķ����ܹ���RTF�ĵ�ת��Ϊ�������ĸ�ʽ(product),ϣ����������ת�����ǲ���Ҫ�ı�RTF�Ķ���

    ʵ������:1--Builder����ķ���ȱʡΪ��
            2--Productû�г�����
            3--ע�⹹���װ����̵�ģ��(��director��������ӵ�product����)
*/
namespace BuilderPattern
{
    class Maze;
    using Ptr_Maze = std::shared_ptr<Maze>;
    class MazeBuilder;
    using Ptr_MazeBuilder = std::shared_ptr<MazeBuilder>;
    class Room;
    using Ptr_Room = std::shared_ptr<Room>;
    class Wall;
    using Ptr_Wall = std::shared_ptr<Wall>;
    class IConnector;
    using Ptr_IConnector = std::shared_ptr<IConnector>;
    class Door;
    using Ptr_Door = std::shared_ptr<Door>;
    class MazeGame;
    using Ptr_MazeGame = std::shared_ptr<MazeGame>;
    class StandardMazeBuilder;
    using Ptr_StandardMazeBuilder = std::shared_ptr<StandardMazeBuilder>;
    enum class Direction
    {
        North = 0,
        South = 1,
        East  = 2,
        West  = 3
    };

    //����ͷ���������������,ǽ���Ŷ���������
    class IConnector
    {

    };
    class Wall : public IConnector
    {

    };
    class Room
    {
    public:
        Room(int num) : m_num(num){}
        void setSide(Direction d, Ptr_IConnector wall)
        {
            this->m_side[d] = wall;
        }
        int getRoomNum()
        {
            return this->m_num;
        }
    private:
        std::map<Direction, Ptr_IConnector> m_side;
        int     m_num;
    };

    class Door : public IConnector
    {
    public:
        Door(Ptr_Room r1, Ptr_Room r2) :m_r1(r1), m_r2(r2){}
    private:
        Ptr_Room m_r1;
        Ptr_Room m_r2;
    };
    class Maze
    {
    public:
        /*
            �Ƿ����ָ������
        */
        Ptr_Room RoomNo(int num)
        {
            auto it = std::find_if(this->m_roomVec.begin(), this->m_roomVec.end(), [num](Ptr_Room room){
                return room->getRoomNum() == num;
            });
            auto ret = (it != this->m_roomVec.end() ? *it : nullptr);
            return ret;
        }
        /*
            ��ӷ���
        */
        void addRoom(Ptr_Room room)
        {
            this->m_roomVec.push_back(room);
        }
    private:
        std::vector<Ptr_Room> m_roomVec;
    };
    class MazeBuilder
    {
    public:
        virtual void buildMaze(){}
        virtual void buildRoom(int room){}
        virtual void buildDoor(int roomFrom, int roomTo){}
        virtual Ptr_Maze getMaze() = 0;
    };

    class MazeGame
    {
    public:
        Ptr_Maze createMaze(Ptr_MazeBuilder builder)
        {
            builder->buildMaze();
            builder->buildRoom(1);
            builder->buildRoom(2);
            builder->buildDoor(1, 2);
            return builder->getMaze();
        }

        Ptr_Maze createComplexMaze(Ptr_MazeBuilder builder)
        {
            builder->buildRoom(1);
            //...
            builder->buildRoom(1001);
            return builder->getMaze();
        }
    };

    class StandardMazeBuilder : public MazeBuilder
    {
    public:
        StandardMazeBuilder()
        {
            this->m_currentMaze.reset();
        }
        virtual void buildMaze() override
        {
            this->m_currentMaze = std::make_shared<Maze>();
        }
        virtual void buildRoom(int roomNum) override
        {
            if (this->m_currentMaze->RoomNo(roomNum) == nullptr)
            {
                Ptr_Room room = std::make_shared<Room>(roomNum);
                room->setSide(Direction::North, std::make_shared<Wall>());
                room->setSide(Direction::South, std::make_shared<Wall>());
                room->setSide(Direction::East, std::make_shared<Wall>());
                room->setSide(Direction::West, std::make_shared<Wall>());
                this->m_currentMaze->addRoom(room);
            }
        }
        virtual void buildDoor(int roomFrom, int roomTo)
        {
            Ptr_Room r1 = this->m_currentMaze->RoomNo(roomFrom);
            Ptr_Room r2 = this->m_currentMaze->RoomNo(roomTo);
            Ptr_Door d = std::make_shared<Door>(r1, r2);
            r1->setSide(this->commonWall(r1, r2), d);
            r2->setSide(this->commonWall(r1, r2), d);
        }
        virtual Ptr_Maze getMaze() override
        {
            return this->m_currentMaze;
        }

        /*
            ��CPP11�ĺ��������������,������C���Ե�rand
        */
        Direction commonWall(Ptr_Room r1, Ptr_Room r2)
        {
            std::default_random_engine dre(static_cast<unsigned int>(time(nullptr)));
            std::uniform_int_distribution<int> di(0, 3);
            std::map<int, Direction> dieMap = { { 0, Direction::North }, { 1, Direction::South }, 
                                                { 2, Direction::East }, { 3, Direction::West } };
            Direction ret = dieMap[di(dre)];
            return ret;
        }
    private:
        Ptr_Maze m_currentMaze;
    };


    class Client
    {
    public:
        static void main()
        {
            Ptr_MazeGame game = std::make_shared<MazeGame>();
            Ptr_StandardMazeBuilder builder = std::make_shared<StandardMazeBuilder>();
            game->createMaze(builder);

            Ptr_Maze maze = builder->getMaze();
        }
    };
}

int main()
{
    BuilderPattern::Client::main();
    return 1;
}