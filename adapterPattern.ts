/**适配器模式 */
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
        }

        /**该函数需要适配 */
        private static testDuck(duck : IDuck)
        {
            duck.quack();
            duck.fly();
        }
    }
}

Adapter.Client.main();