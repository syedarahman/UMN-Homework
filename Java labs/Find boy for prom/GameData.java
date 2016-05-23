import java.util.LinkedList;
import java.util.List;

public class GameData
{
	public List<Person> getBoys()
	{
		List<Person> people = new LinkedList<>();

		people.add( new Person("Damon", "gold") ); // (name, //interests = blood foot or killing)
		people.add( new Person("Matt", "silver") ); 
		people.add( new Person("Klaus", "diamonds") ); 

		return people;
	}

	List<Action> getActions()
	{
		List<Action> actions = new LinkedList<>(); //options 1-3 to pick from

		actions.add(new Action("gift",  "Find a weapon"));
		actions.add(new Action("speak", "Talk to someone & maybe duel"));
		actions.add(new Action("quit",  "Leave game"));
                
                //new actions = Find a weapon, Talk to someone & maybe duel, Leave game

		return actions;
	}
        
    List<Conversation> getConvos()
    {
        List<Conversation> convos = new LinkedList<>();
        convos.add(new Conversation("Damon", "I want to randomly fight you", 
            15, "gold"));
        convos.add(new Conversation("Matt", "Wanna battle?", 20, "silver"));
        convos.add(new Conversation("Klaus", "Let's fight, yo.", 25, "diamonds"));
        
        return convos;
    }

	List<Gift> getGifts()
	{
		List<Gift> gifts = new LinkedList<>();

		gifts.add(new Gift("sword", 5, "gold")); //(gift, attraction, interest)
		gifts.add(new Gift("nun chuck", 10, "silver"));
		gifts.add(new Gift("gun", 20, "diamonds"));
		
		return gifts;
	}
	
	public String getEndingText(String id)
	{
        List<Person> boyz = getBoys();
        String textReturned = "Your statistics are whatever was last printed for you. You gained the most strength points by conversing with ";
		if (id.equals("You didn't play enough"))
		{
			return "Oh no, you should play a couple more rounds to get a good strength point score. ";
		}
                
        for (int i = 0; i < boyz.size(); i++) 
        {
            Person tempBoy = boyz.get(i); //boy that currently are on.
            if(id.contains(tempBoy.name))
            {
                textReturned += tempBoy.name + " ";
            }
        
        }

        return textReturned;	  
	}
}