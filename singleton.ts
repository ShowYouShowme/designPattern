namespace SingletonPattern
{
    /**单例模式的经典实现 */
    class Singleton
    {
        private static _instance : Singleton = null;
        public static getInstance() : Singleton
        {
            if(Singleton._instance == null)
            {
                console.log("Creating unique instance!")
                Singleton._instance = new Singleton();
            }
            console.log("return unique instance!!");
            return Singleton._instance;
        }
        /**必须要将构造函数置为私有 */
        private constructor(){}
    }

    /**确保线程安全的单例模式 */
    class SingletonThreadSafe
    {
        private static _instance : SingletonThreadSafe = new SingletonThreadSafe();
        private constructor(){
            console.log("产生了一个SingletonThreadSafe实例!");
        }
        public static getInstance() : SingletonThreadSafe
        {
            return SingletonThreadSafe._instance;
        }
    }

    export class Client
    {
        public static main() : void
        {
            let v : SingletonThreadSafe = SingletonThreadSafe.getInstance();
            let v2 = SingletonThreadSafe.getInstance();
            let v3 = SingletonThreadSafe.getInstance();
        }
    }
}

SingletonPattern.Client.main();