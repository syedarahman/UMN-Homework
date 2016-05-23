import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Game
{
	static final int numberOfDays = 40;
	List<Person> boys;
        List<Gift> gifts;
	List<Action> actions;
        List<Conversation> convos;
	Scanner input = new Scanner(System.in);

	public void run()
	{
		loadData();

		System.out.println("****************************");
		System.out.println("***       Fight me       ***");
		System.out.println("****************************");

		int day = 1;
		boolean shouldContinue = true;
		while (shouldContinue && (day <= numberOfDays))
		{
			System.out.println();
			System.out.println("War day " + day);

			Action action = getAction();
			if (action.id.equals("quit"))
			{
				shouldContinue = false;
			}
			else if (action.id.equals("gift"))
			{
				Person luckyBoy = boys.get(day % boys.size());
				Gift aGift = gifts.get(day % gifts.size());
                                luckyBoy.receiveGift(aGift);
				System.out.println("You steal from " + luckyBoy.name + " a " +
						aGift.name + " and you can see this on your PaperDoll. ");
				System.out.println("After your disputation, your newly earned strength is " +
						luckyBoy.attractionToPlayer);
			}
                        
                        else if (action.id.equals("speak"))
			{
				Person luckyBoy = boys.get(day % boys.size());
				Conversation convo = convos.get(day % convos.size());

                                luckyBoy.haveConvo(convo);
				System.out.println("You approached someone fellow named " + luckyBoy.name + " and said, " +
						convo.convo);
				System.out.println(luckyBoy + " started fist fighting you, Now your newly earned stamina is " +
						luckyBoy.attractionToPlayer);
			}


			day++;
		}

		String endingID = getEndingID();
		GameData dataLoader = new GameData();
		String endingText = dataLoader.getEndingText(endingID);
		System.out.println(endingText);
		System.out.println("Game Over");
	}

	/**
	 * There are several different possible endingings. We'll give each one an ID.
	 * To determine what to print, look in the DataLoader.
	 */
	public String getEndingID()
	{
            
            int threshold = 50; //what they have to get to/attraction they have to be at.
            String id = "";
            
            for (int i = 0; i < boys.size(); i++) //goes through list
            {
                Person tempPerson = boys.get(i); //what person you are at. holder person.
                if(tempPerson.attractionToPlayer > threshold)
                {
                    id += tempPerson.name;
                }
                
            }
            if(id.isEmpty())
            {
                return "You didn't play enough";
            }
            return id;
	}
	
	private Action getAction()
	{
                
		System.out.println("You're back in battle.");
		for (int i = 0; i < actions.size(); i++)
		{
			Action action = actions.get(i);
			System.out.println((i + 1) + ". " + action.output);
		}
		System.out.print("Pick 1, 2, or 3: ");
		int choice = input.nextInt() - 1;

		return actions.get(choice);
	}

	private void loadData()
	{
		GameData dataLoader = new GameData();
                actions = dataLoader.getActions();
		boys    = dataLoader.getBoys();
                convos = dataLoader.getConvos();
                gifts    =dataLoader.getGifts();
	}
}