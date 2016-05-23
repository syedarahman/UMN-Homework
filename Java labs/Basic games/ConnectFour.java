/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package hw2.q2;

/**
 *
 * @author Syeda Rahman
 */
public class ConnectFour 
{
    public int currentPlayer;
    public int[][] board = new int[7][6]; //make board 7 columns, 6 rows.
    public boolean stateOfGame = false;
    
    public String getCurrentPlayer()
    //Return either"Red"or"Blue"
    {
        String getCurrentPlayer = null; 
        if (currentPlayer == 1) 
        {
            return "Red";
        }
        
        if (currentPlayer == 2)
        {
            return "Blue";
        }
        return getCurrentPlayer;
    }
    
    public boolean isTheGameTied() // see if game is tied/over.
    {
        for (int i = 0; i < board.length; i++) 
        // go through the columns, starting at index 0, going as far as 
        //the board length, checking each box with i++.
        {
            for (int j = 0; j < board[0].length; j++) 
            // now go through rows j, starting at index 0, until board is over. 
            {
                if (board[i][j]!= -1)
                {
                    return false;
                }
            }
        }
      return true;
    }
    
    public boolean isOver()
    {
        if (stateOfGame == true) // if game is over and stateOfGame returned true.
            return true;
        else
        {
            if (isTheGameTied())
            {
                return true;
            }
        }
        return false;
    }
    
    public String getWinner()
    //Return either "Red", "Blue" or the empty string "" for a tie
    {
        if (isOver())
        {
            if(stateOfGame)
               return getCurrentPlayer(); // who ever made the last winning move.
            else
               {
                   return "";
               }
        }
        return null;
    } 
    
    public boolean checkingHorizontally(int currentPlayer, int x, int y)
    {
        int countColumnsGoingLeft = 0;
        int countColumnsGoingRight = 0;
        
        for(int i = 0; i < y; i++) //check from left to the spot
        {
            if(board[x][i] == currentPlayer)
            {
                countColumnsGoingLeft = countColumnsGoingLeft + 1;
            }
            else 
            { 
                break; 
            }
        }   
        for(int i = y; i < 6; i++)
        {
            if(board[x][i] == currentPlayer)
            {
                countColumnsGoingRight = countColumnsGoingRight + 1;
            }
            else
            {
                break;
            }
        }
        if((countColumnsGoingLeft >= 4) || (countColumnsGoingRight >= 4))
        {
            return true;
        }
        return false;
    }
    
    public boolean checkingVertically(int currentPlayer, int x, int y)
    {
        int countRowsGoingUp = 0;
        int countRowsGoingDown = 0;
        
        for(int i = 0; i < x; i++)
        {
            if(board[i][y] == currentPlayer)
            {
                countRowsGoingUp = countRowsGoingUp + 1;
            }
            else 
            {
                break;
            }
        }
            
        for (int i = x; i < 7; i++) {
            if(board[i][y] == currentPlayer)
            {
                countRowsGoingDown = countRowsGoingDown + 1;
            }
            else
            {
                break;
            }
            
        }
        
        if ((countRowsGoingUp >= 4) || (countRowsGoingDown >= 4))
        { 
            return true;
        }
        
        return false;
    }
    
    public boolean checkingDiagonallyRight(int currentPlayer, int x, int y)
    {
        int xForDiagRight = x-1; // x you are currently at
        int yForDiagRight = y+1; // y you are currently at
        // moves the current position
        
        int sumUpRight = 0; // counts going up right, starting at 0.
        
        while ( (xForDiagRight >= 0) && (yForDiagRight < 6) )
        {
          if (board[xForDiagRight][yForDiagRight] == currentPlayer)
          // if the position it is at now is the current player...
          {
            sumUpRight = sumUpRight + 1; 
            xForDiagRight = xForDiagRight-1;
            yForDiagRight = yForDiagRight+1;
          }
          else
          {
              break; // stops the loop.
          }
          
        }
        
        int sumDownLeft = 0;
        int xForDiagLeft = x+1;
        int yForDiagLeft = y-1;
        while((xForDiagLeft<7) && (yForDiagLeft>=0))
        {
            if(board[xForDiagLeft][yForDiagLeft] == currentPlayer)
            // if the position it is at now is the current player. 
            {
                sumDownLeft = sumDownLeft + 1;
                xForDiagLeft = xForDiagLeft+1;
                yForDiagLeft = yForDiagLeft-1;
            }
            else
            {
              break; 
            }
        }
        
        if((sumUpRight >= 4) || (sumDownLeft >= 4))
        {
            return true;
        }
        
        return false;
    }
    
    public boolean checkingLeftDiagonally(int currentPlayer, int x, int y)
    {
        int xForDiagRight = x-1;
        int yForDiagRight = y-1;
        
        int sumUpLeft = 0;
      
        while((xForDiagRight>=0) && (yForDiagRight>=0))
        {
          if(board[xForDiagRight][yForDiagRight] == currentPlayer)
          {
            sumUpLeft = sumUpLeft + 1;
            xForDiagRight = xForDiagRight-1;
            yForDiagRight = yForDiagRight-1;
          }
          else
          {
              break;
          }
          
        }
        
        int countRightDown = 0;
        int xForDiagLeft = x+1;
        int yForDiagLeft = y+1;
        while((xForDiagLeft<7) && (yForDiagLeft<6))
        {
            if(board[xForDiagLeft][yForDiagLeft] == currentPlayer)
          {
            countRightDown++;
            xForDiagLeft=xForDiagLeft+1;
            yForDiagLeft=yForDiagLeft+1;}
          else
          {
              break;}
        }
        
        if((sumUpLeft >= 4) || (countRightDown >= 4))
            
        {
            return true;
        }
        
        return false;   
    }  

    public void makeMove(int columnIndex)
    //Place the current players mark at the specified column on the lowest 
    //  free row in the column. The next player becomes the current player.
    {
        for(int i = 0; i < board[0].length; i++)
        {
            if (board[columnIndex][i] == -1) //checks where on the board there
                                             // are empty spots (where -1s are).
            {
                board[columnIndex][i] = currentPlayer;  
                if(checkingLeftDiagonally(currentPlayer,columnIndex,i) || checkingDiagonallyRight(currentPlayer,columnIndex,i) || checkingHorizontally(currentPlayer,columnIndex,i) 
                        || checkingVertically(currentPlayer,columnIndex,i))
                {
                    stateOfGame = true;
                    break; //break the loop bc a player has won. 
                }
                
                // now see who won, aka who is the last one to make a move.
                // switch players, so now 2 is current player and will go next.
                if (currentPlayer == 1)
                {
                    currentPlayer = 2;
                }
                else
                {
                    currentPlayer = 1;
                }
            }
        }
    }
    
    public void wipeBoard()
    // Fills the entire board with -1 (empty spaces)
    {
        for (int i = 0; i < board.length; i++)
        {
            for (int j = 0; j < board[0].length; j++)
            {
                board[i][j] = -1;
            }
        }
    }
    
}
