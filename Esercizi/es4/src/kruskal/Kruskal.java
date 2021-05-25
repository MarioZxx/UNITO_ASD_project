package kruskal;
import java.util.*;
import graph.*;

public class Kruskal{

  
  public static Graph kruskal(Graph<String, Float> inputGraph){
    ArrayList<Arch<String, Float>> arrayArchs = new ArrayList<>();
    Graph<String, Float> resultGraph = new Graph<>(0);
    arrayArchs = inputGraph.getArchs();
    MergeSort ms = new MergeSort();
    printArrayList(arrayArchs);
    ms.mergeSort(arrayArchs, 0, inputGraph.numberOfArch()-1);
    while(!arrayArchs.isEmpty()){
      
    }
    return resultGraph;
  }
  
  public static void printArrayList(ArrayList<Arch<String, Float>> arrayArchs){
    Arch<String, Float> temp = new Arch<>();
    System.out.println("start print");
    for(int i = 0; i<arrayArchs.size(); i++){
      temp = arrayArchs.get(i);
      System.out.println(temp.node1 +" "+ temp.node2 +" "+ temp.weight);
    }
    System.out.println("end print");
  }
  
  public static void main(String[] args) {
    Graph<String, Float> testGraph = new Graph<>(0);
    String s1,s2,s3;
    Float w1,w2,w3;
    s1 = "torino";
    s2 = "milano";
    s3 = "bologna";
    w1 = 202.02f;
    w2 = 505.05f;
    w3 = 909.09f;
    testGraph.addNode(s1);testGraph.addNode(s2);testGraph.addNode(s3);
    testGraph.addArch(s1,s3,w1);testGraph.addArch(s2,s3,w3);testGraph.addArch(s2,s1,w2);
    kruskal(testGraph);
    System.out.println("end");
    
  }
  

}


