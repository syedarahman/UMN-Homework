/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author syedarahman
 */
public class Person 
{
    public String name;
    public int attractionToPlayer = 0;
    public String interest;
    
    public Person(String name, String interest)
    {
        this.name = name;
        this.interest = interest;
    }
    
    @Override
    public String toString()
    {
        return this.name;
    }
    
    void receiveGift(Gift aGift)
    {
        //check if gift matches interest 
        if(aGift.interest.equals(interest))
        {
            attractionToPlayer += aGift.value; //add value to attraction 
        }
        else
        {
            attractionToPlayer -= aGift.value;
        }
        
    }
    
    void haveConvo(Conversation convos)
    {
        if(convos.interest.equals(interest))
        {
            attractionToPlayer += convos.value;
        }
        else
        {
            attractionToPlayer -= convos.value;
        }
    }
}
