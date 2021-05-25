package unionfindset;
import java.util.*;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class UnionFindSetTests {

  private Integer i1,i2,i3;
  private String s1,s2,s3;
  private UnionFindSet<Integer> intTest;
  private UnionFindSet<String>  strTest;

  @Before
  public void createUnionFindSet() throws UnionFindSetException{
    i1 = 9;
    i2 = 5;
    i3 = 2;
    intTest = new UnionFindSet<>();
    intTest.makeSet(i1);
    intTest.makeSet(i2);
    intTest.makeSet(i3);
    s1 = "aria";
    s2 = "acqua";
    s3 = "fuoco";
    strTest = new UnionFindSet<>();
    strTest.makeSet(s1);
    strTest.makeSet(s2);
    strTest.makeSet(s3);
  }

  @Test
  public void testFindInt() throws Exception{
    assertTrue(intTest.findSet(i1) == i1);
  }
  
  @Test
  public void testUnionInt_oneAndOne() throws Exception{
    intTest.unionSet(i1, i2);
    assertTrue(intTest.findSet(i1) == i2);
  }
  
  @Test
  public void testUnionInt_twoAndOne() throws Exception{
    intTest.unionSet(i1, i2);
    intTest.unionSet(i3, i2);
    assertTrue(intTest.findSet(i3) == i2);
  }
  
  @Test
  public void testFindStr() throws Exception{
    assertTrue(strTest.findSet(s1) == s1);
  }
  
  @Test
  public void testUnionStr_oneAndOne() throws Exception{
    strTest.unionSet(s1, s2);
    assertTrue(strTest.findSet(s1) == s2);
  }
  
  @Test
  public void testUnionStr_twoAndOne() throws Exception{
    strTest.unionSet(s1, s2);
    strTest.unionSet(s2, s3);
    assertTrue(strTest.findSet(s3) == s2);
  }
  
  @Test
  public void testUnionStr_repeatUnion() throws Exception{
    strTest.unionSet(s1, s2);
    strTest.unionSet(s1, s2);
    strTest.unionSet(s1, s1);
    strTest.unionSet(s2, s2);
    assertTrue(strTest.findSet(s1) == s2);
  }
  
  @Test
  public void testRepeatElem() throws Exception{
    intTest.unionSet(i1, i2);
    intTest.makeSet(i1);
    assertFalse(intTest.findSet(i1) == i1);
  }

}
