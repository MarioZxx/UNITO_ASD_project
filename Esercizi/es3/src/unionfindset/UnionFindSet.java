package unionfindset;
import java.util.*;

// @param <Type>: type of the ordered array elements
public class UnionFindSet<T> {
  private HashMap<T, T> set = new HashMap<T, T>();
  private HashMap<T, Integer> rank = new HashMap<T, Integer>();

  public  void makeSet(T x) {
    (this.set).put(x, x);
    (this.rank).put(x, 0);
  }

  public  void union(T x, T y) {
    this.link(this.findSet(x), this.findSet(y));
  }

  public  void link(T x, T y) {
    if ((this.rank).get(x) > (this.rank).get(y)){
      (this.set).put(y, x);
    } else {
      (this.set).put(x, y);
      if ((this.rank).get(x) == (this.rank).get(y)){
        int temp = (this.rank).get(y) + 1;
        (this.rank).put(y, temp);
      }
    }
    
  }

  public  T findSet(T x) {
    if (x != (this.set).get(x))
      (this.set).put(x, findSet( (this.set).get(x) ));
    return (this.set).get(x);
  }
}
