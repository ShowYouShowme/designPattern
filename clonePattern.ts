/**原型模式一般是指深拷贝吧 */
abstract class ICloneable
{
    public abstract clone() : ICloneable;
}

/**浅拷贝 */
class People implements ICloneable
{
    clone() : ICloneable
    {
        return this;
    }
    public showClothes() : void
    {
        console.log("your clothes:");
        this._clothes.forEach((elem)=>
        {
            console.log(elem);
        })
    }

    public buyClothes(name : string) : void
    {
        this._clothes.push(name);
    }

    private _clothes : string[] = [];
}

/**深拷贝 注意:数组的底层实现是指针*/
class Martian implements ICloneable
{
    clone() : ICloneable
    {
        let result : Martian = new Martian();
        result._clothes.push(...this._clothes);
        return result;
    }
    public showClothes() : void
    {
        console.log("your clothes:");
        this._clothes.forEach((elem)=>
        {
            console.log(elem);
        })
    }

    public buyClothes(name : string) : void
    {
        this._clothes.push(name);
    }

    private _clothes : string[] = [];
}

// let p : People = new People();
// p.buyClothes("adidas");
// p.buyClothes("nike");
// let p2 : People = p.clone() as People;
// p2.buyClothes("anta");
// p2.showClothes();


let v : Martian = new Martian();
v.buyClothes("adidas");
v.buyClothes("lv");
let v2 : Martian = v.clone() as Martian;
v2.buyClothes("Metersbonwe");
console.log(v);
console.log(v2);
console.log("finished!!!");