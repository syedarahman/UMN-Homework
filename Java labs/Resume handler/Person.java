/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab05;

/**
 * @author syedarahman
 */
public class Person {
    public String address;
    public int age;
    public int id;
    public String name;
    public String phone;
    
    public Person()
    {
        
    } //space to create the person by putting in skills
         
   //constructors for Person: 
   public Person(String address, int age, int id, String name, String phone)
   {
       this.address = address;
       this.age = age;
       this.id = id;
       this.name = name;
       this.phone = phone;
   }
}
