package graph;
import java.util.*;

// @param <Type>: type of the ordered array elements
public class Graph<T> {
  private HashMap<T, HashMap<T, T>> nodeMap;
  private int direct;

  public  Graph(int ifdirect) { //creats a empty graph O(1)
    this.nodeMap = new HashMap<T, HashMap<T, T>>();
    this.direct = ifdirect;
  }

  public  void addNode(T x) {//O(1)
    if(nodeMap.containsKey(x))
      return;
    HashMap<T, T> arch = new HashMap<T, T>();
    (this.nodeMap).put(x, arch);
  }
  
  public  void addArch(T node1, T node2, T weight) {//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      return;
    HashMap<T, T> arch = nodeMap.get(node1);
    arch.put(node2, weight);
    if(this.direct == 0){
      arch = nodeMap.get(node2);
      arch.put(node1, weight);
    }
  }
  
  public  int isDirect() {//O(1)
    return this.direct;
  }

  public  boolean containsNode(T x) {//O(1)
    if ((this.nodeMap).containsKey(x))
      return true;
    return false;
  }
  
  public  boolean containsArch(T node1, T node2) {//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      return false;
    HashMap<T, T> arch = nodeMap.get(node1);
    if (arch.containsKey(node2))
      return true;
    return false;
  }
  
  public  void removeNode(T x) {//O(1) expected //O(n) because linkedlist
    (this.nodeMap).remove(x);
  }
  
  public  void removeArch(T node1, T node2) {//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      return;
    HashMap<T, T> arch = nodeMap.get(node1);
    arch.remove(node2);
    if(this.direct == 0){
      arch = nodeMap.get(node2);
      arch.remove(node1);
    }
  }
  
  public  int numberOfNode(){//O(1)
    return (this.nodeMap).size();
  }
  
  public  int numberOfArch(){//O(n)
    int result = 0;
    for(HashMap<T, T> arch : (this.nodeMap).values()){
      result = result + arch.size();
    }
    return result;
  }
  
  public  ArrayList getNodes(){//O(n)
    ArrayList<T> result = new ArrayList<T>();
    for(T node : (this.nodeMap).keySet()){
      result.add(node);
    }
    return result;
  }
  
  public  ArrayList getArchs(){//O(n)
    ArrayList<T> result = new ArrayList<T>();
    for(HashMap<T, T> arch : (this.nodeMap).values()){
      for(T weight : arch.values()){
        result.add(weight);
      }
    }
    return result;
  }
  
  public  ArrayList getAdjacentNodes(T node){ //O(1)
    ArrayList<T> result = new ArrayList<T>();
    HashMap<T, T> arch = (this.nodeMap).get(node);
    for(T nodeAd : arch.keySet()){
      result.add(nodeAd);
    }
    return result;
  }
  
  public  T getWeight(T node1, T node2){  //O(1)
    HashMap<T, T> arch = (this.nodeMap).get(node1);
    return arch.get(node2);
  }
  
  
  
}











