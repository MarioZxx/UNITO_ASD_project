package kruskal;
import java.util.*;
import graph.*;
import unionfindset.*;

public class Kruskal<T, W extends Comparable<W>>{
  
  public  Graph kruskal(Graph<T, W> inputGraph, int direct) 
  throws KruskalException, Exception{
    if(inputGraph == null)
      throw new KruskalException("kruskal: inputGraph parameter cannot be null");
    UnionFindSet<T> uFSetGraph = new UnionFindSet<>();
    Graph<T, W> resultGraph = new Graph<>(direct);
    ArrayList<Arch<T, W>> arrayArchs;//node1, node2, weight
    ArrayList<T> arrayNode;
    Arch<T, W> minArch;
    
    arrayNode = inputGraph.getNodes();
    for(int i = 0; i < arrayNode.size(); i++){
      T setNode = arrayNode.get(i);
      uFSetGraph.makeSet(setNode);
    }
    arrayArchs = inputGraph.getArchs();
    Collections.sort(arrayArchs);
    
    for(int i = 0; i < arrayArchs.size(); i++){
      minArch = arrayArchs.get(i);
      T firstNode = uFSetGraph.findSet(minArch.node1);
      T secndNode = uFSetGraph.findSet(minArch.node2);
      if(!firstNode.equals(secndNode)){
        resultGraph.addNode(minArch.node1);
        resultGraph.addNode(minArch.node2);
        resultGraph.addArch(minArch.node1, minArch.node2, minArch.weight);
        uFSetGraph.unionSet(firstNode, secndNode);
      }
    }
    //printArrayList(resultGraph.getArchs());
    return resultGraph;
  }
  
  /*public void printArrayList(ArrayList<Arch<T, W>> arrayArchs){
    Arch<T, W> temp = new Arch<>();
    System.out.println("start print");
    for(int i = 0; i < arrayArchs.size(); i++){
      temp = arrayArchs.get(i);
      System.out.println(temp.node1 +", "+ temp.node2 +", "+ temp.weight);
    }
    System.out.println("end print");
  }*/ 

}


