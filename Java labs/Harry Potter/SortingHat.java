/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab02;

/**
 *
 * @author syedarahman
 */
public class SortingHat {
    public House getBestHouse(Person person, 
            House a, House b, House c, House d)
    
{     
    House bestHouse = null;
    int bestScore = -1;


     // Alice, aka person 1
     int score = 0;
     score = score + person.bravery      * a.braveryWeight;
     score = score + person.intelligence * a.intelligenceWeight;
     score = score + person.loveOfTacos  * a.loveOfTacosWeight;
     score = score + person.purity       * a.purityWeight;
     score = score + person.wealth       * a.wealthWeight;
     if (score > bestScore)
{

bestScore = score;
bestHouse = a;   
}

// Bob, aka person 2
score = 0;
score = score + person.bravery      * b.braveryWeight;
score = score + person.intelligence * b.intelligenceWeight;
score = score + person.loveOfTacos  * b.loveOfTacosWeight;
     score = score + person.purity  * b.purityWeight;
     score = score + person.wealth  * b.wealthWeight;
     if (score > bestScore)
     {
          bestScore = score;
          bestHouse = b;
     }

// Carol, aka person 3
score = 0;
score = score + person.bravery       * c.braveryWeight;
score = score + person.intelligence  * c.intelligenceWeight;
score = score + person.loveOfTacos   * c.loveOfTacosWeight;
score = score + person.purity        * c.purityWeight;
score = score + person.wealth        * c.wealthWeight;
    if (score > bestScore)
{
    bestScore = score;
    bestHouse = c;
}

System.out.println("  " + person.name + " score for " +
      a.name + " = " + score);
return bestHouse;

}
}
