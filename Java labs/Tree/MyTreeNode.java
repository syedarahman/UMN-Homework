/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab10;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Syeda
 */
public class MyTreeNode<T> 
{
    //data is the new information that you put in the tree. 
    //a tree has a root and children. 
    //children = subtrees (they are also trees themselves) = array lists.
    
    T data; 
    List<MyTreeNode<T>> children = new ArrayList<>(); //arraylist of subtrees / children.

	public MyTreeNode(T data) //constructor
	{
		this.data = data;
	}

	int getNumberOfNodes()
	{
		if (isLeaf()) //if empty, then only top exists, which is 1.
		{
			return 1;
		}

		int count = 1; //start at one, bc at least have top node.
		for (int i = 0; i < children.size(); i++)
		{
			MyTreeNode<T> child = children.get(i); //"child" is the name of that spot you are indexing.
			count += child.getNumberOfNodes(); //count = index #s that you keep adding up w/for loop.
		}
		return count;
	}

    //used to getNumberOfLeaves() in MyTree class. (prechecks for null root)
	int getNumberOfLeaves()
	{
		if (isLeaf()) 
		{
			return 1;
		}

		int count = 0; 
		
        for (int i = 0; i < children.size(); i++)
		{
			MyTreeNode<T> child = children.get(i);
			count += child.getNumberOfLeaves();
                        //start w/0 count, which is at your parent node (index 0),so it doesn't contribute to "count".
		}
		return count;
	}

	int getNumberOfBrancheNodes()
	{
		if (isLeaf())
		{
			return 0;
		}
		int count = 1;
		for (int i = 0; i < children.size(); i++)
		{
			MyTreeNode<T> child = children.get(i);
			count += child.getNumberOfBrancheNodes();
                        //
		}
		return count;
	}

	private boolean isLeaf()
	{
		return children.isEmpty();
	}

	@Override
	public String toString()
	{
		return data.toString();
	}
}
