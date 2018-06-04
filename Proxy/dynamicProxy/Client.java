import java.lang.reflect.*;
import java.util.*;
public class Client
{
    private Hashtable datingDB = new Hashtable();

    public Client()
    {
        this.initializeDatabase();
    }

    public static void main(String[] args)
    {
        Client cl = new Client();
        cl.drive();
    }

    PersonBean getPersonFromDatabase(String name) {
        return (PersonBean)datingDB.get(name);
    }

    public void drive()
    {
        PersonBean joe = this.getPersonFromDatabase("Joe Javabean");
        PersonBean ownerProxy = this.getOwnrProxy(joe);
        System.out.println("Name is " + ownerProxy.getName());
        ownerProxy.setInterests("having sex");
        System.out.println("Interests set");
        ownerProxy.setInterests("having sex");
        try{
            ownerProxy.setHotOrNotRating(15);
        }
        catch (Exception e)
        {
            System.out.println("Can't set rating from owner proxy");
        }
    }



    void initializeDatabase() {
        PersonBean joe = new PersonBeanImpl();
        joe.setName("Joe Javabean");
        joe.setInterests("cars, computers, music");
        joe.setHotOrNotRating(7);
        datingDB.put(joe.getName(), joe);

        PersonBean kelly = new PersonBeanImpl();
        kelly.setName("Kelly Klosure");
        kelly.setInterests("ebay, movies, music");
        kelly.setHotOrNotRating(6);
        datingDB.put(kelly.getName(), kelly);
    }

    private PersonBean getOwnrProxy(PersonBean person)
    {
        return (PersonBean) Proxy.newProxyInstance(person.getClass().getClassLoader(), person.getClass().getInterfaces(), new OwnerInvocationHandler(person));
    }

}
