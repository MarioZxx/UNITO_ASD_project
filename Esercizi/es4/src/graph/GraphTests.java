package graph;
import java.util.*;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class GraphTests {

  private Integer w1,w2,w3;
  private String s1,s2,s3;
  private Graph<String, Integer> strDirectTest, strIndirectTest;
  private ArrayList<String> strNodes;
  private ArrayList<Arch<String, Integer>> arrayArchs;
  private ArrayList<Arch<String, Integer>> resArchs;
  private Arch<String, Integer> temp;
  /*must be called by Arch*/
  private boolean equalsArch (Arch first, Arch secnd){
    if ((first.node1).equals(secnd.node1) && (first.node2).equals(secnd.node2) &&
      (first.weight).equals(secnd.weight))
      return true;
    return false;
  }

  @Before
  public void createGraph() throws GraphException{
    s1 = "torino";
    s2 = "milano";
    s3 = "bologna";
    w1 = 102;
    w2 = 105;
    w3 = 109;
    strDirectTest = new Graph<>(1);
    strIndirectTest = new Graph<>(0);
    strNodes = new ArrayList<>();
    
    arrayArchs = new ArrayList<>();
    resArchs = new ArrayList<>();
    temp = new Arch<>();
  }


  @Test
  public void testIsEmpty(){
    assertTrue(strDirectTest.numberOfNode() == 0);
  }
  
  @Test
  public void testAddNode() throws Exception{
    strDirectTest.addNode(s1);
    assertTrue(strDirectTest.numberOfNode() == 1);
  }
  
  @Test
  public void testAddArch_direct() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addArch(s1, s2, w1);
    assertTrue(strDirectTest.numberOfArch() == 1);
  }  
  
  @Test
  public void testAddArch_indirect() throws Exception{
    strIndirectTest.addNode(s1);
    strIndirectTest.addNode(s2);
    strIndirectTest.addArch(s1, s2, 34);
    assertTrue(strIndirectTest.numberOfArch() == 2);
  }
  
  @Test
  public void testContainsNode() throws Exception{
    strDirectTest.addNode(s3);
    assertTrue(strDirectTest.containsNode(s3));
  }
  
  @Test
  public void testContainsArch_direct() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addArch(s1, s2, w1);
    assertTrue(strDirectTest.containsArch(s1, s2));
  }
  
  @Test
  public void testContainsArch_indirect() throws Exception{
    strIndirectTest.addNode(s1);
    strIndirectTest.addNode(s2);
    strIndirectTest.addArch(s1, s2, w1);
    assertTrue(strIndirectTest.containsArch(s1, s2) && strIndirectTest.containsArch(s2, s1));
  }
  
  @Test
  public void testRemoveNode() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.removeNode(s1);
    strDirectTest.removeNode("Doesn't exist");
    assertTrue(strDirectTest.numberOfNode() == 0);
  }

  @Test
  public void testRemoveArch_direct() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addArch(s1, s2, w1);
    strDirectTest.removeArch(s1, s2);
    strDirectTest.removeArch("Doesn't exist", s2);
    assertTrue(strDirectTest.numberOfArch() == 0);
  }
  
  @Test
  public void testRemoveArch_indirect() throws Exception{
    strIndirectTest.addNode(s1);
    strIndirectTest.addNode(s2);
    strIndirectTest.addArch(s1, s2, w1);
    strIndirectTest.removeArch(s1, s2);
    assertTrue(strIndirectTest.numberOfArch() == 0);
  }
  
  @Test
  public void testRecoveryNodes() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strNodes.add(s1);
    strNodes.add(s2);
    assertTrue(strNodes.equals(strDirectTest.getNodes()));
  }
  
  @Test
  public void testRecoveryArch_direct() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addArch(s1, s2, w1);
    resArchs = strDirectTest.getArchs();
    temp.node1 = s1;
    temp.node2 = s2;
    temp.weight = w1;
    assertTrue(equalsArch(temp,resArchs.get(0)) );
  }
  
  @Test
  public void testRecoveryArch_indirect() throws Exception{
    strIndirectTest.addNode(s1);
    strIndirectTest.addNode(s2);
    strIndirectTest.addNode(s3);
    strIndirectTest.addArch(s1, s2, w1);
    strIndirectTest.addArch(s2, s3, w3);
    resArchs = strIndirectTest.getArchs();
    temp.node1=s1;
    temp.node2=s2;
    temp.weight=w1;
    arrayArchs.add(temp);
    temp=new Arch<>();
    temp.node1=s2;
    temp.node2=s1;
    temp.weight=w1;
    arrayArchs.add(temp);
    temp=new Arch<>();
    temp.node1=s2;
    temp.node2=s3;
    temp.weight=w3;
    arrayArchs.add(temp);
    temp=new Arch<>();
    temp.node1=s3;
    temp.node2=s2;
    temp.weight=w3;
    arrayArchs.add(temp);
    for(int i=0; i<4; i++){
      if(!equalsArch(arrayArchs.get(i),resArchs.get(i)))
        assertTrue(false);
    }
    assertTrue(true);
  }
  
  @Test
  public void testRecoveryAdjNodes() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addNode(s3);
    strDirectTest.addArch(s1, s2, w1);
    strDirectTest.addArch(s1, s3, w2);
    strNodes.add(s2);
    strNodes.add(s3);
    assertTrue(strNodes.equals(strDirectTest.getAdjacentNodes(s1)));
  }
  
  @Test
  public void testRecoveryAdjNodes_noAdj() throws Exception{
    strDirectTest.addNode(s1);
    assertTrue(strNodes.equals(strDirectTest.getAdjacentNodes(s1)));
  }
  
  @Test
  public void testRecoveryAdjNodes_noExist() throws Exception{
    assertTrue(strNodes.equals(strDirectTest.getAdjacentNodes("Doesn't exist")));
  }
  
  @Test
  public void testGetWeight_direct() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    strDirectTest.addArch(s1, s2, w3);
    assertTrue(strDirectTest.getWeight(s1, s2) == w3);
  }
  
  @Test
  public void testGetWeight_indirect() throws Exception{
    strIndirectTest.addNode(s1);
    strIndirectTest.addNode(s2);
    strIndirectTest.addArch(s1, s2, w3);
    assertTrue(strIndirectTest.getWeight(s1, s2) == w3 && strIndirectTest.getWeight(s2, s1) == w3);
  }
  
  @Test
  public void testGetWeight_noExistArch() throws Exception{
    strDirectTest.addNode(s1);
    strDirectTest.addNode(s2);
    assertTrue(strDirectTest.getWeight(s1, s2) == null);
  }



}
