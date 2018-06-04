import java.rmi.*;
import java.rmi.server.*;

public class GumballMachine
        extends UnicastRemoteObject implements GumballMachineRemote
{
    int count = 0;
    String location;

    public GumballMachine(String location, int numberGumballs) throws RemoteException {

        this.count = numberGumballs;
        this.location = location;
    }

    public int getCount() {
        return count;
    }

    public String getLocation() {
        return location;
    }
}
