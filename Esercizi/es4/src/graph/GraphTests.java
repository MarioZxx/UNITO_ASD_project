package graph;
import java.util.*;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class GraphTests {

  private Integer i1,i2,i3,w1,w2,w3;
  private String s1,s2,s3;
  private Graph<Integer> intDirectTest, intIndirectTest;
  private Graph<String>  strTest;
  private ArrayList<Integer> intNodes,intArchs;

  @Before
  public void createGraph() throws GraphException{
    i1 = 2;
    i2 = 5;
    i3 = 9;
    w1 = 102;
    w2 = 105;
    w3 = 109;
    intDirectTest = new Graph<>(1);
    intIndirectTest = new Graph<>(0);
    intNodes = new ArrayList<>();
    intArchs = new ArrayList<>();
  }


  @Test
  public void testIsEmpty(){
    assertTrue(intDirectTest.numberOfNode() == 0);
  }
  
  @Test
  public void testAddNode(){
    intDirectTest.addNode(i1);
    assertTrue(intDirectTest.numberOfNode() == 1);
  }
  
  @Test
  public void testAddArch_direct(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addArch(i1, i2, w1);
    assertTrue(intDirectTest.numberOfArch() == 1);
  }  
  
  @Test
  public void testAddArch_indirect(){
    intIndirectTest.addNode(i1);
    intIndirectTest.addNode(i2);
    intIndirectTest.addArch(i1, i2, 34);
    assertTrue(intIndirectTest.numberOfArch() == 2);
  }
  
  @Test
  public void testContainsNode(){
    intDirectTest.addNode(i3);
    assertTrue(intDirectTest.containsNode(i3));
  }
  
  @Test
  public void testContainsArch_direct(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addArch(i1, i2, w1);
    assertTrue(intDirectTest.containsArch(i1, i2));
  }
  
  @Test
  public void testContainsArch_indirect(){
    intIndirectTest.addNode(i1);
    intIndirectTest.addNode(i2);
    intIndirectTest.addArch(i1, i2, w1);
    assertTrue(intIndirectTest.containsArch(i1, i2) && intIndirectTest.containsArch(i2, i1));
  }
  
  @Test
  public void testRemoveNode(){
    intDirectTest.addNode(i1);
    intDirectTest.removeNode(i1);
    assertTrue(intDirectTest.numberOfNode() == 0);
  }
  
  @Test
  public void testRemoveArch_direct(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addArch(i1, i2, w1);
    intDirectTest.removeArch(i1, i2);
    assertTrue(intDirectTest.numberOfArch() == 0);
  }
  
  @Test
  public void testRemoveArch_indirect(){
    intIndirectTest.addNode(i1);
    intIndirectTest.addNode(i2);
    intIndirectTest.addArch(i1, i2, w1);
    intIndirectTest.removeArch(i1, i2);
    assertTrue(intIndirectTest.numberOfArch() == 0);
  }
  
  @Test
  public void testRecoveryNodes(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intNodes.add(i1);
    intNodes.add(i2);
    assertTrue(intNodes.equals(intDirectTest.getNodes()));
  }
  
  @Test
  public void testRecoveryArch_direct(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addArch(i1, i2, w1);
    intArchs.add(w1);
    assertTrue(intArchs.equals(intDirectTest.getArchs()));
  }
  
  @Test
  public void testRecoveryArch_indirect(){
    intIndirectTest.addNode(i1);
    intIndirectTest.addNode(i2);
    intIndirectTest.addArch(i1, i2, w1);
    intArchs.add(w1);
    intArchs.add(w1);
    assertTrue(intArchs.equals(intIndirectTest.getArchs()));
  }
  
  @Test
  public void testRecoveryAdjNodes(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addNode(i3);
    intDirectTest.addArch(i1, i2, w1);
    intDirectTest.addArch(i1, i3, w2);
    intNodes.add(i2);
    intNodes.add(i3);
    assertTrue(intNodes.equals(intDirectTest.getAdjacentNodes(i1)));
  }
  
  @Test
  public void testGetWeight_direct(){
    intDirectTest.addNode(i1);
    intDirectTest.addNode(i2);
    intDirectTest.addArch(i1, i2, w3);
    assertTrue(intDirectTest.getWeight(i1, i2) == w3);
  }
  
  @Test
  public void testGetWeight_indirect(){
    intIndirectTest.addNode(i1);
    intIndirectTest.addNode(i2);
    intIndirectTest.addArch(i1, i2, w3);
    assertTrue(intIndirectTest.getWeight(i1, i2) == w3 && intIndirectTest.getWeight(i2, i1) == w3);
  }



}
