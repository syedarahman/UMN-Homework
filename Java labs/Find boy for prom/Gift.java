/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author syedarahman
 */
public class Gift 
{
    public String name; //name of gift
    public int value; 
    public String interest;

    public Gift(String name, int value, String interest) //value is attraction to increase
    // want to see if gift matches interest, like sports, then add one to attraction of guy
    {
        this.name = name;
        this.value = value;
        this.interest = interest;
        
    }
    
    
}
