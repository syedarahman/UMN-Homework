/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// GOAL: take a group of students. See what house they should go in.

// DATA TYPES: need more data types than just Strings and ints, we need 
    //to make some new data types. We'll use three types of data: 
    //Person (the student to put in a group), 
    //House (the group the student goes in) and 
    //SortingHat (decides which house the student goes in)

package lab02;

/**
 *
 * @author syedarahman
 */
public class Application {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Application app = new Application();
        app.runSortingHatDemo();
    }
    private void runSortingHatDemo()
    {
        Person alice = new Person();
        alice.name = "Alice";
        alice.bravery = 4;
        alice.intelligence = 8;
        alice.loveOfTacos = 2;
        alice.purity = 0;
        alice.wealth = 6;
        
        Person bob = new Person();
        bob.name = "Bob";
        bob.bravery = 3;
        bob.intelligence = 4;
        bob.loveOfTacos = 7;
        bob.purity = 10;
        bob.wealth = 8;
        
        Person carol = new Person();
        carol.name = "Carol";
        carol.bravery = 1;
        carol.intelligence = 2;
        carol.loveOfTacos = 10;
        carol.purity = 5;
        carol.wealth = 5;
        
        House griffindor = new House();
        griffindor.name = "Griffindor";
        griffindor.braveryWeight = 10;
        
        House slytherin = new House();
        slytherin.name = "Slytherin";
        slytherin.purityWeight = 8;
        slytherin.wealthWeight = 8;
        
        House ravenclaw = new House();
        ravenclaw.name = "Ravenclaw";
        ravenclaw.intelligenceWeight = 8;
        
        House hufflepuff = new House();
        hufflepuff.name = "Hufflepuff";
        hufflepuff.loveOfTacosWeight = 5;
        
        SortingHat hat = new SortingHat();
        House bestHouse = hat.getBestHouse(
        alice, griffindor, slytherin, ravenclaw, hufflepuff);
        
        System.out.println("Alice is assigned to " + bestHouse.name);
        
        bestHouse = hat.getBestHouse(bob, griffindor, slytherin, ravenclaw,
                hufflepuff);
        
        System.out.println("Bob is assigned to " + bestHouse.name);
        
        bestHouse = hat.getBestHouse(carol, griffindor, slytherin, ravenclaw,
                hufflepuff);
        
        System.out.println("Carol is assigned to " + bestHouse.name);          
    }
    
    public class SortingHatTest 
{
    //@Test
    public void testGetBestHouse()
    {
        SortingHat instance = new SortingHat();

        Person person = new Person();
        person.bravery = 10;
        
        House a = new House();
        a.name = "Stark";
        a.braveryWeight = 10;
        
        House b = new House();
        b.name = "CSE";
        b.intelligenceWeight = 10;
        
        House c = new House();
        c.name = "Pikachu";
        c.purityWeight = 10;
        
        House d = new House();
        d.name = "Skywalker";
        d.wealthWeight  = 6;
        d.braveryWeight = 5;

        House expected = a;
        House actual = instance.getBestHouse(person, a, b, c, d);
        assertEquals("brave person", expected, actual);
        
        //--- Second test: change person to smart
        person.bravery = 0;
        person.intelligence = 10;
        expected = b;
        actual   = instance.getBestHouse(person, a, b, c, d);
        assertEquals("smart person", expected, actual);
        
        //--- Third test: brave but a little smarter
        person.bravery = 7;
        person.intelligence = 8;
        expected = b;
        actual   = instance.getBestHouse(person, a, b, c, d);
        assertEquals("brave but smarter", expected, actual);
    }

        private void assertEquals(String brave_person, House expected, House actual) {
            throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }
    }

}
