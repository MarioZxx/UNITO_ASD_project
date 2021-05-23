package unionfindset;
import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;
//java -cp '.;../junit-4.12.jar;../hamcrest-core-1.3.jar'  unionfindset/UnionFindSetTestsRunner

public class UnionFindSetTests {

  private Integer i1,i2,i3;
  private UnionFindSet<Integer> test1, test2, test3;

  @Before
  public void createUnionFindSet() throws UnionFindSetException{
    i1 = 9;
    i2 = 5;
    i3 = 2;
    test1.makeSet(i1);
    test1.makeSet(i2);
    test1.makeSet(i3);
    //test2 = makeSet(i2);
    //test3 = makeSet(i3);
  }

  @Test
  public void firstTest(){
    assertTrue(test1.findSet(9) == 9);
  }


}
