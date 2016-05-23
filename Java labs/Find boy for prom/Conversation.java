/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author syedarahman
 */
public class Conversation 
{
    public String person;
    public String convo; 
    public int value; 
    public String interest;

    public Conversation(String person, String convo, int value, String interest) //value is attraction to increase
    // want to see if gift matches interest, like sports, then add one to attraction of guy
    {
        this.person = person;
        this.convo = convo;
        this.value = value;
        this.interest = interest;
        
    }
    
}
