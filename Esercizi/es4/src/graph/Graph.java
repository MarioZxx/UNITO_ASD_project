package graph;
import java.util.*;

// @param <Type>: type of the ordered array elements
public class Graph<T, W> {
  private HashMap<T, HashMap<T, W>> nodeMap;
  private int direct;

  public  Graph(int ifdirect) { //creats a empty graph O(1)
    this.nodeMap = new HashMap<T, HashMap<T, W>>();
    this.direct = ifdirect;
  }

  public  void addNode(T node) throws GraphException{//O(1)
    if(node == null)
      throw new GraphException("addNode: node parameter cannot be null");
    if(nodeMap.containsKey(node))
      return;
    HashMap<T, W> arch = new HashMap<T, W>();
    (this.nodeMap).put(node, arch);
  }
  
  public  void addArch(T node1, T node2, W weight) throws GraphException{//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      throw new GraphException("addArch: node parameter doesn't exist");
    if(weight == null)
      throw new GraphException("addArch: weight parameter cannot be null");
    HashMap<T, W> arch = nodeMap.get(node1);
    arch.put(node2, weight);
    if(this.direct == 0){
      arch = nodeMap.get(node2);
      arch.put(node1, weight);
    }
  }
  
  public  int isDirect() {//O(1)
    return this.direct;
  }

  public  boolean containsNode(T node) {//O(1)
    if ((this.nodeMap).containsKey(node))
      return true;
    return false;
  }
  
  public  boolean containsArch(T node1, T node2) {//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      return false;
    HashMap<T, W> arch = nodeMap.get(node1);
    if (arch.containsKey(node2))
      return true;
    return false;
  }
  
  public  void removeNode(T node) {//O(1) expected O(n) because linkedlist
    (this.nodeMap).remove(node);
  }
  
  public  void removeArch(T node1, T node2) {//O(1)
    if(!nodeMap.containsKey(node1) || !nodeMap.containsKey(node2))
      return;
    HashMap<T, W> arch = nodeMap.get(node1);
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
    for(HashMap<T, W> arch : (this.nodeMap).values()){
      result = result + arch.size();
    }
    return result;
  }
  
  public  ArrayList getNodes(){//O(n)
    ArrayList<T> result = new ArrayList<>();
    for(T node : (this.nodeMap).keySet()){
      result.add(node);
    }
    return result;
  }
  
  //return ArrayList with node1, node2, weight
  public  ArrayList getArchs(){//O(n)
    ArrayList<Arch<T, W>> result = new ArrayList<>();
    for(T nodeOne : (this.nodeMap).keySet()){
      HashMap<T, W> arch = (this.nodeMap).get(nodeOne);
      for(T nodeTwo : arch.keySet()){
        Arch<T, W> temp = new Arch<>();
        temp.node1 = nodeOne;
        temp.node2 = nodeTwo;
        temp.weight = arch.get(nodeTwo);
        result.add(temp);
      }
    }
    return result;
  }
  
  public  ArrayList getAdjacentNodes(T node) throws GraphException{ //O(1)
    if(node == null)
      throw new GraphException("getAdjacentNodes: node parameter cannot be null");
    ArrayList<T> result = new ArrayList<>();
    if(containsNode(node)){
      HashMap<T, W> arch = (this.nodeMap).get(node);
      for(T nodeAd : arch.keySet()){
        result.add(nodeAd);
      }
    }
    return result;
  }
  
  public  W getWeight(T node1, T node2){  //O(1)
    if(containsArch(node1,node2)){
      HashMap<T, W> arch = (this.nodeMap).get(node1);
      return arch.get(node2);
    }
    return null;
  }
  
  
  
}











