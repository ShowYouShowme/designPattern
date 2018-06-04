/**一个类可以从两个以上的角度来分类 */
namespace BridgePattern
{
    /**类有形状和颜色两个属性 */
    abstract class IShape
    {
        protected _color : IColor;
        public setColor(color : IColor)
        {
            this._color = color;
        }
        public draw() : void
        {
            console.log("绘制了一个" + this._color.getColorDesc() + " " + this.getShapeDesc());
        }
        public abstract getShapeDesc() : string;
    }

    class Circle extends IShape
    {
        public getShapeDesc() : string
        {
            return "圆形";
        }
    }

    class Rectangle extends IShape
    {
        public getShapeDesc() : string
        {
            return "长方形";
        }
    }

    class Squre extends IShape
    {
        public getShapeDesc() : string
        {
            return "正方形";
        }
    }

    abstract class IColor
    {
        public abstract getColorDesc() : string;
    }

    class Gray implements IColor
    {
        public getColorDesc() : string
        {
            return "灰色";
        }
    }

    class Black implements IColor
    {
        public getColorDesc() : string
        {
            return "黑色";
        }
    }

    export class Client
    {
        public static main() : void
        {
            let s1 : IShape = new Circle();
            let c1 : IColor = new Black();
            s1.setColor(c1);
            s1.draw();

            let s2 : IShape = new Rectangle();
            let c2 : IColor = new Gray();
            s2.setColor(c2);
            s2.draw();
        }
    }
}

BridgePattern.Client.main();