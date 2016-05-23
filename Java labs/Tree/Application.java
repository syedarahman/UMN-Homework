/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab10;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Syeda
 */
public class Application 
{

    public static void main(String[] args)
	{
        Application app = new Application();
		app.runTreeDemo();
    }
	private void runTreeDemo()
	{
		MyTree<String> tree = getSampleTree();

		System.out.println("size = " + tree.getSize());
		System.out.println("# leaves = " + tree.getNumberOfLeaves());
		System.out.println("# branches = " + tree.getNumberOfBrancheNodes());
		System.out.println(tree);
	}

	private MyTree<String> getSampleTree()
	{
		MyTree<String> tree = new MyTree<>();
		MyTreeNode<String> node;
		node = new MyTreeNode("A");
		tree.root = node;
		tree.root.children.add(new MyTreeNode<>("B1"));
		tree.root.children.add(new MyTreeNode<>("B2"));

		MyTreeNode<String> parent, child;
		parent = new MyTreeNode<>("C1");
		child  = new MyTreeNode<>("E");
		parent.children.add(child);
		tree.root.children.get(0).children.add(parent);
		tree.root.children.get(0).children.add(new MyTreeNode<>("C2"));
		tree.root.children.get(1).children.add(new MyTreeNode<>("D1"));
		tree.root.children.get(1).children.add(new MyTreeNode<>("D2"));
		tree.root.children.get(1).children.add(new MyTreeNode<>("D3"));
		return tree;
	}
        
        public MyTree<String> getSmallAnimalTree()
    {
        MyTree<String> tree = new MyTree<>();

        // put data in tree
        Map<String,MyTreeNode> nodes = new HashMap<>();
        nodes.put("root", new MyTreeNode("Animal"));
        nodes.put("Mammal", new MyTreeNode("Mammal"));
        nodes.put("Bird", new MyTreeNode("Bird"));
        nodes.put("Reptile", new MyTreeNode("Reptile"));
        nodes.put("Canine", new MyTreeNode("Canine"));
        nodes.put("Feline", new MyTreeNode("Feline"));
        nodes.put("Flying", new MyTreeNode("Flying"));
        nodes.put("Not Flying", new MyTreeNode("Not Flying"));

        Map<String,String> parentage = new HashMap<>();
        parentage.put("root", null);
        parentage.put("Mammal", "root");
        parentage.put("Bird", "root");
        parentage.put("Reptile", "root");
        parentage.put("Canine", "Mammal");
        parentage.put("Feline", "Mammal");
        parentage.put("Flying", "Bird");
        parentage.put("Not Flying", "Bird");

        tree.setRoot(TreeLoader.buildTree(nodes, parentage));
        return tree;
    }
    
}

