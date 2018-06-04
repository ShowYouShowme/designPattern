import java.rmi.*;
import java.rmi.registry.LocateRegistry;

public class GumballMachineTestDrive {

    public static void main(String[] args) {
        GumballMachineRemote gumballMachine = null;
        int count;

        try {
            LocateRegistry.createRegistry(6600);
            count = 100;

            gumballMachine =
                    new GumballMachine("seattle", count);
            Naming.rebind("rmi://127.0.0.1:6600/userService", gumballMachine);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}