package unionfindset;
import java.util.*;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;
//java -cp '.;../junit-4.12.jar;../hamcrest-core-1.3.jar'  unionfindset/UnionFindSetTestsRunner

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
  public void testFindInt(){
    assertTrue(intTest.findSet(i1) == i1);
  }
  
  @Test
  public void testUnionInt_oneAndOne(){
    intTest.union(i1, i2);
    assertTrue(intTest.findSet(i1) == i2);
  }
  
  @Test
  public void testUnionInt_twoAndOne(){
    intTest.union(i1, i2);
    intTest.union(i3, i2);
    assertTrue(intTest.findSet(i3) == i2);
  }
  
  @Test
  public void testFindStr(){
    assertTrue(strTest.findSet(s1) == s1);
  }
  
  @Test
  public void testUnionStr_oneAndOne(){
    strTest.union(s1, s2);
    assertTrue(strTest.findSet(s1) == s2);
  }
  
  @Test
  public void testUnionStr_twoAndOne(){
    strTest.union(s1, s2);
    strTest.union(s2, s3);
    assertTrue(strTest.findSet(s3) == s2);
  }
  
  @Test
  public void testRepeatElem(){
    intTest.union(i1, i2);
    intTest.makeSet(i1);
    assertFalse(intTest.findSet(i1) == i1);
  }
  
  @Test
  public void testNoExistElem(){
    assertTrue(strTest.findSet("Doesn't exist") == null);
  }



}
