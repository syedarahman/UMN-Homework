/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package hw2.q1;

/**
 * @author Syeda Rahman
 */

public class PalindromeChecker 
{
    public boolean isAPalindrome(String candidate)
    {
        if (candidate == null) // check if String is null.
        {
            return false;
        }
        
        candidate = candidate.toLowerCase(); //now entire string is lower case.
        
        boolean isAPalindrome = false; // set to false initially.
        if(candidate == reverse(candidate)) // if the string is the same in reverse.
        {
            return true;
        }
        return isAPalindrome;
    }

    public String clean (String aString)
    // Remove everything except letters.
    {
        if (aString.equals("")) // note: not using ==
        {
            return "Empty String";
        }
        String newstringOnlyLetters = aString.replaceAll("[^A-Za-z]+", "");
        return newstringOnlyLetters;
    }
    
    public String reverse(String aString)
    {
        String reversedString = ""; //checking if empty
        if((aString == null) || aString.length() == 1) 
        {
            return aString;
        }
        else
        {
            // length -1, keep decrementing until 0.
            for (int i = aString.length() - 1; i >= 0; i--) 
            {
                reversedString = reversedString + aString.charAt(i);                
            }
        }
        return reversedString;
    }
}
