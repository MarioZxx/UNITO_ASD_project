package graph;
import java.util.*;
public class Arch<T, W extends Comparable<W>> implements Comparable<Arch<T, W>>{  
    public T node1, node2;
    public W weight;
    public int compareTo(Arch<T, W> compareArch)
        {
            return (this.weight).compareTo(compareArch.weight);
        }
  }
