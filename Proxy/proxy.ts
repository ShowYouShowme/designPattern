namespace ProxyPattern
{
    abstract class IGamePlayer
    {
        public abstract login(user : string, password : string) : void;
        public abstract killBoss() : void;
        public abstract upgrade() : void;
    }

    /**客户端不可以访问这个类 */
    class GamePlayer implements IGamePlayer
    {
        private _name : string;
        constructor(name : string)
        {
            this._name = name;
        }
        public login(user : string, password : string) : void
        {
            console.log("登录名为:" + user + "的用户 " + this._name + "登录成功!!")
        }
        public killBoss() : void
        {
            console.log(this._name + "在打怪");
        }
        public upgrade() : void
        {
            console.log(this._name + " 又升级了");
        }
    }

    class GamePlayerProxy implements IGamePlayer
    {
        private _gamePlayer : IGamePlayer;
        constructor(name : string)
        {
            this._gamePlayer = new GamePlayer(name);
        }

        public login(user : string, password : string) : void
        {
            this._gamePlayer.login(user, password);
        }
        public killBoss() : void
        {
            this._gamePlayer.killBoss();
        }
        public upgrade() : void
        {
            this._gamePlayer.upgrade();
        }
    }

    export class Client
    {
        public static main()
        {
            let player : IGamePlayer = new GamePlayerProxy("郭敬明");
            console.log("开始时间是:" + new Date().toDateString());
            player.login("xiaosi", "123456");

            player.killBoss();

            player.upgrade();
            console.log("游戏结束！")
        }
    }
}

ProxyPattern.Client.main();