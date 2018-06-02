/**适配器模式 */
/**包含了普通的适配器模式和类适配器模式 */
namespace Adapter 
{
    abstract class IDuck
    {
        public abstract quack() : void;
        public abstract fly() : void;
    }

    class MallardDuck implements IDuck
    {
        public quack() : void
        {
            console.log("Quack");
        }

        public fly() : void
        {
            console.log("I am flying");
        }
    }

    abstract class ITurkey
    {
        public abstract gobble() : void;
        public abstract fly() : void;
    }

    class WildTurkey implements ITurkey
    {
        public gobble() : void
        {
            console.log("Gobble gobble");
        }
        public fly() : void
        {
            console.log("I am flying a short distance");
        }
    }

    class TurkeyAdapter implements IDuck
    {
        private _turkey : ITurkey;
        constructor(turkey : ITurkey)
        {
            this._turkey = turkey;
        }
        public quack() : void
        {
            this._turkey.gobble();
        }
        public fly() : void
        {
            for(let idx: number = 0; idx < 5; ++idx)
            {
                this._turkey.fly();
            }
        }
    }

    /**类适配器  */
    class ClsTurkeyAdapter extends WildTurkey implements IDuck
    {
        public quack() : void
        {
            super.gobble();
        }
        public fly() : void
        {
            for(let idx : number = 0; idx < 3; ++idx)
            {
                super.fly();
            }
        }
    }

    export class Client
    {
        public static main()
        {
            let duck : IDuck = new MallardDuck();
            let turkey : ITurkey = new WildTurkey();
            let adapter : IDuck = new TurkeyAdapter(turkey);

            Client.testDuck(duck);
            console.log("------------------------");
            Client.testDuck(adapter);
            console.log("------------------------");
            let clsAdapter : IDuck = new ClsTurkeyAdapter();
            Client.testDuck(clsAdapter);
        }

        /**该函数需要适配 */
        private static testDuck(duck : IDuck)
        {
            duck.quack();
            duck.fly();
        }
    }
}

/**接口适配器 不希望实现全部接口*/
namespace interfaceAdapter
{
    abstract class IPort
    {
        public abstract ssh() : void;
        public abstract net() : void;
        public abstract mysql() : void;
        public abstract ftp() : void;
    }

    class Wrapper implements IPort
    {
        public ssh() : void{}
        public net() : void{}
        public mysql() : void{}
        public ftp() : void{}
    }

    class Chat extends Wrapper
    {
        public net() : void
        {
            console.log("hello world!");
        }

        public ftp() : void
        {
            console.log("File upload succeddful!");
        }
    }

    class Server extends Wrapper
    {
        public ssh() : void
        {
            console.log("connect success!");
        }

        public net() : void
        {
            console.log("hello www!!!");
        }

        public mysql() : void
        {
            console.log("mysql is running!");
        }
    }

    export class Client
    {
        public static main()
        {
            let chartPort : IPort = new Chat();
            let serverPort : IPort = new Server();
            chartPort.net();
            chartPort.ftp();

            console.log("---------------");
            serverPort.mysql();
            serverPort.ssh();
        }
    }
}
interfaceAdapter.Client.main();
//Adapter.Client.main();