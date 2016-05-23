/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab10;

import java.util.Map;

/**
 *
 * @author Syeda
 */
public class TreeLoader
{
    static public MyTreeNode buildTree(Map<String,MyTreeNode> nodes, Map<String,String> parentage)
    {
        for (String x : nodes.keySet())
        {
            for(String child : parentage.keySet())
            {
                if(parentage.get(child).equals(x))
                {
                   
                    nodes.get(x).children.add(nodes.get(child));
                }
            }//end inner for loop
        } //end first for loop        
        return nodes.get("root");
    }
}
