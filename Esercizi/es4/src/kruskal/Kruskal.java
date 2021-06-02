package kruskal;
import java.util.*;
import graph.*;
import unionfindset.*;

//MST kruskal
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
      T setOfNode = arrayNode.get(i);
      uFSetGraph.makeSet(setOfNode);
    }
    arrayArchs = inputGraph.getArchs();
    Collections.sort(arrayArchs);
    
    for(int i = 0; i < arrayArchs.size(); i++){
      minArch = arrayArchs.get(i);
      T firstNode = uFSetGraph.findSet(minArch.getNode1());
      T secndNode = uFSetGraph.findSet(minArch.getNode2());
      if(!firstNode.equals(secndNode)){
        resultGraph.addNode(minArch.getNode1());
        resultGraph.addNode(minArch.getNode2());
        resultGraph.addArch(minArch.getNode1(), minArch.getNode2(), minArch.getWeight());
        uFSetGraph.unionSet(firstNode, secndNode);
      }
    }
    return resultGraph;
  }
  
}


