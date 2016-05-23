/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab10;

/**
 * @author Syeda
 */
public class MyTree<T> 
{
    public MyTreeNode<T> root; //make the root
    
    public MyTreeNode<T> getRoot() 
    {
        return root;
    }
    
    public void setRoot(MyTreeNode<T> root) //declare the root. constructor.
    {
        this.root = root;
    }

	int getSize() 
	{
		if (null == root)
		{
			return 0;
		}
		return root.getNumberOfNodes();
	}

	int getNumberOfLeaves()
	{
		if (null == root)
		{
			return 0;
		}
		return root.getNumberOfLeaves();
	}

	int getNumberOfBrancheNodes()
	{
		if (null == root)
		{
			return 0;
		}
		return root.getNumberOfBrancheNodes();
	}
}
