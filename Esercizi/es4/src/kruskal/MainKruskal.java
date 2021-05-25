package kruskal;
import java.util.*;
import graph.*;
import unionfindset.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class MainKruskal {

  private static final Charset ENCODING = StandardCharsets.UTF_8;

  private static void loadArray(String filepath, Graph<String, Double> inputGraph) 
  throws IOException, KruskalException, Exception{
    System.out.println("\nLoading data from file...\n");
    Path inputFilePath = Paths.get(filepath);
    try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
      String line = null;
      while((line = fileInputReader.readLine()) != null){      
        String[] lineElements = line.split(",");  
        inputGraph.addNode(lineElements[0]);  
        inputGraph.addNode(lineElements[1]);   
        inputGraph.addArch(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2]));
      }
    } 
    System.out.println("\nData loaded\n");
  }
  
  public static void main(String[] args) throws IOException, KruskalException, Exception{
    if(args.length < 1)
      throw new Exception("Usage: MainKruskal <file_name>");
    Graph<String, Double> inputGraph = new Graph<>(0);
    Graph<String, Double> KruskalMSTGraph;
    ArrayList<Arch<String, Double>> MSTArrayList;
    Kruskal kruskal = new Kruskal();
    Double totalWeight = 0d;
    
    loadArray(args[0], inputGraph);
    KruskalMSTGraph = kruskal.kruskal(inputGraph);
    MSTArrayList = KruskalMSTGraph.getArchs();
    for(int i = 0; i < MSTArrayList.size(); i++)
      totalWeight = totalWeight + MSTArrayList.get(i).weight;
    System.out.println("N° nodes: " + KruskalMSTGraph.numberOfNode() + ", N° archs: " + KruskalMSTGraph.numberOfArch()/2 + ", total weight: " + totalWeight/2000 + " kilometre.");
  }
  
}