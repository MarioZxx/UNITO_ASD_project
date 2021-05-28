package graph;
import java.util.*;
public class Arch<T, W extends Comparable<W>> implements Comparable<Arch<T, W>>{  
    private T node1, node2;
    private W weight;
    
    public int compareTo(Arch<T, W> compareArch){
      return (this.weight).compareTo(compareArch.weight);
    }
    
    public T getNode1(){
      return this.node1;
    }
    
    public T getNode2(){
      return this.node2;
    }
    
    public W getWeight(){
      return this.weight;
    }
    
    public void setNode1(T node1){
      this.node1 = node1;
    }
    
    public void setNode2(T node2){
      this.node2 = node2;
    }
    
    public void setWeight(W weight){
      this.weight = weight;
    }
    
    
        
  }
