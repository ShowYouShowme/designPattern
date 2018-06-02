/** 抽象工厂模式用来创建一组相关的对象*/
namespace abstractFactory
{
    abstract class IButton
    {

    }

    class WindowsButton implements IButton
    {
        constructor()
        {
            console.log("制造Windows 按钮")
        }
    }

    class UnixButton implements IButton
    {
        constructor()
        {
            console.log("制造Unix 按钮")
        }
    }

    abstract class IText
    {

    }
    class WindowsText implements IText
    {
        constructor()
        {
            console.log("制造Windows Text");
        }
    }

    class UnixText implements IText
    {
        constructor()
        {
            console.log("制造Unix Text");
        }
    }

    abstract class IFactory
    {
        public abstract createBtn() : IButton;
        public abstract createTxt() : IText;
    }

    class WindowsFactory implements IFactory
    {
        public createBtn() : IButton
        {
            return new WindowsButton();
        }
        public createTxt() : IText
        {
            return new WindowsText();
        }
    }

    class UnixFactory implements IFactory
    {
        public createBtn() : IButton
        {
            return new UnixButton();
        }
        public createTxt() : IText
        {
            return new UnixText();
        }
    }

    export class Client
    {
        public static main()
        {
            let windowsUI : WindowsFactory = new WindowsFactory();
            windowsUI.createBtn();
            windowsUI.createTxt();

            let unixUI : UnixFactory = new UnixFactory();
            unixUI.createBtn();
            unixUI.createTxt();
            console.log("finished!!");
        }
    }
}

/**工厂方法 */
namespace factoryMethod
{
    abstract class IMouse
    {

    }

    class DellMouse
    {
        constructor()
        {
            console.log("Hi, I am DellMouse"!);
        }
    }

    class HpMouse
    {
        constructor()
        {
            console.log("Hi, i am HpMouse!");
        }
    }

    abstract class IMouseFactory
    {
        public abstract createMouse() : IMouse;
    }

    class HpMouseFactory implements IMouseFactory
    {
        public createMouse() : IMouse
        {
            return new HpMouse();
        }
    }

    class DellMouseFactory implements IMouseFactory
    {
        public createMouse() : IMouse
        {
            return new DellMouse();
        }
    }

    export class Client
    {
        public static main()
        {
            let hpFactory : IMouseFactory = new HpMouseFactory();
            let dellFactory : IMouseFactory = new DellMouseFactory();
            hpFactory.createMouse();
            dellFactory.createMouse();
        }
    }
}

factoryMethod.Client.main();