package unionfindset;
import java.util.*;

// @param <T>: type of the UnionFindSet nodes
public class UnionFindSet<T> {
  private HashMap<T, T> set = new HashMap<T, T>();
  private HashMap<T, Integer> rank = new HashMap<T, Integer>();

  public  void makeSet(T x) {
    if(!(this.set).containsKey(x)){
      (this.set).put(x, x);
      (this.rank).put(x, 0);
    }
  }

  public  void unionSet(T x, T y) throws UnionFindSetException{
    this.link(this.findSet(x), this.findSet(y));
  }

  public  void link(T x, T y) {
    if(x.equals(y)) return;
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

  public  T findSet(T x) throws UnionFindSetException{
    if(!(this.set).containsKey(x))
      throw new UnionFindSetException("findSet: node parameter doesn't made/exist");
    if (x != (this.set).get(x))
      (this.set).put(x, findSet( (this.set).get(x) ));
    return (this.set).get(x);
  }
}
