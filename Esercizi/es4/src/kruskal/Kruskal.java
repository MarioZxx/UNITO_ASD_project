package kruskal;
import java.util.*;
import graph.*;
import unionfindset.*;

public class Kruskal{

  
  public static Graph kruskal(Graph<String, Float> inputGraph){
    UnionFindSet<String> uFSetGraph = new UnionFindSet<>();
    Graph<String, Float> resultGraph = new Graph<>(0);
    ArrayList<Arch<String, Float>> arrayArchs;//node1, node2, weight
    ArrayList<String> arrayNode;
    Arch<String, Float> minArch;
    
    arrayNode = inputGraph.getNodes();
    for(int i = 0; i < arrayNode.size(); i++){
      String setNode = arrayNode.get(i);
      uFSetGraph.makeSet(setNode);
    }
    arrayArchs = inputGraph.getArchs();
    MergeSort ms = new MergeSort();
    ms.mergeSort(arrayArchs, 0, inputGraph.numberOfArch()-1);
    //printArrayList(arrayArchs);
    
    for(int i = 0; i < arrayArchs.size(); i++){
      minArch = arrayArchs.get(i);
    //System.out.println("for1: "+ minArch.node1 +" "+ minArch.node2 +" "+ minArch.weight);
      String firstNode = uFSetGraph.findSet(minArch.node1);
      String secndNode = uFSetGraph.findSet(minArch.node2);
    //System.out.println("for2: "+firstNode +" "+ secndNode +" "+ minArch.weight);
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
  
  public static void printArrayList(ArrayList<Arch<String, Float>> arrayArchs){
    Arch<String, Float> temp = new Arch<>();
    System.out.println("start print");
    for(int i = 0; i < arrayArchs.size(); i++){
      temp = arrayArchs.get(i);
      System.out.println(temp.node1 +" "+ temp.node2 +" "+ temp.weight);
    }
    System.out.println("end print");
  }
  
  public static void main(String[] args) {
    Graph<String, Float> testGraph = new Graph<>(0);
    Graph<String, Float> printGraph = new Graph<>(0);
    String s1,s2,s3,s4,s5,s6,s7;
    Float w1,w2,w3,w4;
    s1 = "torino";
    s2 = "milano";
    s3 = "bologna";
    s4 = "genova";
    s5 = "roma";
    s6 = "napoli";
    s7 = "udine";
    w1 = 101f;
    w2 = 202f;
    w3 = 303f;
    w4 = 151f;
    testGraph.addNode(s1);testGraph.addNode(s2);testGraph.addNode(s3);testGraph.addNode(s4);
    testGraph.addArch(s1,s2,w1);testGraph.addArch(s2,s3,w2);testGraph.addArch(s3,s1,w4);
    testGraph.addArch(s4,s2,w2);testGraph.addArch(s3,s4,w3);
    testGraph.addNode(s5);testGraph.addNode(s6);testGraph.addNode(s7);
    testGraph.addArch(s5,s6,w1);testGraph.addArch(s5,s7,w3);testGraph.addArch(s6,s7,w4);
    
    printGraph = kruskal(testGraph);
    ArrayList<Arch<String, Float>> minimo = printGraph.getArchs();
    printArrayList(minimo);
    
  }
  

}


