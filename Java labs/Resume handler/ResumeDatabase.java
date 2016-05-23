/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab05;

import java.util.List;
import java.util.Map;
// map is like a dictionary. key (interger) is the word.
// thing associated with word= use get.
// map is 2 lists next to eachotther. here: keys (ints) & values (names). 

/**
 *
 * @author syedarahman
 */
public class ResumeDatabase 
{
    public Map<String, Person> applicants;
    public Map<Integer, String> education;
    public Map<String, Integer> employerReputation;
    public Map<Integer, String> previousEmployer;
    public Map<String, Integer> schoolReputation;
    public Map<String, List<String>> skills; //takes in person's name. outputs skills.

    public Person getBest(String skill) 
    // takes in skill as String. 
    // getBest is method name.
    // Will return person w/best skill, after looking at rest of info 
                //for everyone in the list with that skill.
    // use each person's ID # to get their score - for each loop
    // Return the *person* who has the skill and has the highest score.
    {
        int bestScore = 0; // new variable called bestScore
        Person bestPerson = new Person(); //creating new person using Person class null constructor.
        List<String> names = skills.get(skill); //list of names w/that skill u want.
        
        for (String name : names) //for each name in "names" list...
        // for each variable name in names list, get a person from person list.
        {
            Person currentPerson = applicants.get(name); 
                //applicants is/takes in things from variable above. 
            int id = currentPerson.id; //getting id from Person class
            int currentScore = getScore(id); // using get score method from below that factors in everything.
            
            if(currentScore > bestScore)
            {
                bestScore = currentScore;// replacing new best score as the
                //score you currently encountered. also..:
                bestPerson = currentPerson;
            }
        
        }
        return bestPerson;
    }
    
    private int getEducationScore(int id) //step 1.
    // passing in int id, outputting name of school.
    {
        String school = education.get(id); 
        if(school == null)
        { 
            return 0;
        }
        //else: return the reputation of the school (schoolReputation)
        int schoolScore = schoolReputation.get(school);
        // getting school's schoolRep, and calling that schoolScore.
        return schoolScore;
        
    }
    
    private int getExperienceScore(int id)
    // passing in int id, getting back name of previous employer
    {
        String employer = previousEmployer.get(id);
        //value(name of employer) associated with the id. 
        //calling this name "employer", which is a String.
        if(employer == null)
        { 
            return 0;
        }
        //else: return the reputation of the employer (employerReputation)
        int employerRep = employerReputation.get(employer);
        //getting employer's rep, which is an int.
        return employerRep;
    }
    
    private int getScore(int id)
    // adding up both:
    {
        int score = getEducationScore(id) + getExperienceScore(id);
        return score;
    }
}
