/**这个pattern和代理模式类图是完全一样的 */
namespace Decorator 
{
    abstract class IBeverage
    {
        public abstract getDesc() : string;
        public abstract cost() : number;
    }

    class HouseBlend implements IBeverage
    {
        public getDesc() : string
        {
            return "HouseBlend";
        }
        public cost() : number
        {
            return 1.2;
        }
    }

    class Milk implements IBeverage
    {
        private _beverage : IBeverage;
        constructor(beverage : IBeverage)
        {
            this._beverage = beverage;
        }

        public getDesc() : string
        {
            return "Milk " + this._beverage.getDesc();
        }
        public cost() : number
        {
            return 0.5 + this._beverage.cost();
        }
    }

    class Soy implements IBeverage
    {
        private _beverage : IBeverage;
        constructor(beverage : IBeverage)
        {
            this._beverage = beverage;
        }

        public getDesc() : string
        {
            return "Soy " + this._beverage.getDesc();
        }
        public cost() : number
        {
            return 0.9 + this._beverage.cost();
        }
    }

    export class Client
    {
        public static main()
        {
            let houseBlend : IBeverage = new HouseBlend();
            houseBlend = new Milk(houseBlend);
            houseBlend = new Soy(houseBlend);
            console.log("desc: " + houseBlend.getDesc());
            console.log("price: " + houseBlend.cost());
        }
    }
}

Decorator.Client.main();