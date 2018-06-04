/**一个接口访问子系统中的一群接口 */
namespace FacadePattern
{
    class Tuner 
    {
        private _description : String;
        private _amplifier : Amplifier;
        private _frequency : number;
        
        constructor(description : String , amplifier : Amplifier) {
            this._description = description;
        }
     
        public on() {
            console.log(this._description + " on");
        }
     
        public off() {
            console.log(this._description + " off");
        }
     
        public setFrequency(frequency : number) {
            console.log(this._description + " setting frequency to " + frequency);
            this._frequency = frequency;
        }   
    }

    class Amplifier
    {
        private _description : string;
        private _tuner : Tuner;
        
        constructor(description : string) {
            this._description = description;
        }
     
        public on() {
            console.log(this._description + " on");
        }
     
        public off() {
            console.log(this._description + " off");
        }
     
        public setVolume(level : number) {
            console.log(this._description + " setting volume to " + level);
        }
    
        public setTuner(tuner :  Tuner) {
            console.log(this._description + " setting tuner to ");
            this._tuner = tuner;
        }
    }

    /**注意这个类的两个方法 */
    class HomeTheaterFacade {
        private _amp : Amplifier;
        private _tuner : Tuner;
        constructor(amplifierDesc : string, tunerDesc : string) 
        {
            this._amp   = new Amplifier(amplifierDesc);
            this._tuner = new Tuner(tunerDesc, this._amp);
        }
        public listenToRadio(frequency : number) {
            console.log("Tuning in the airwaves...");
            this._tuner.on();
            this._tuner.setFrequency(frequency);
            this._amp.on();
            this._amp.setVolume(5);
            this._amp.setTuner(this._tuner);
        }
    
        public endRadio() {
            console.log("Shutting down the tuner...");
            this._tuner.off();
            this._amp.off();
        }
    }

    export class Client
    {
        public static main() {
            let homeTheater : HomeTheaterFacade = 
                    new HomeTheaterFacade("Top-O-Line Amplifier", "Top-O-Line AM/FM Tuner");
                homeTheater.listenToRadio(95);
                setTimeout(()=>{
                    homeTheater.endRadio();
                }, 2000);
        }
    }
}
FacadePattern.Client.main();