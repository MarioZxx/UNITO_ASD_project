package kruskal;
import java.util.*;
import graph.*;

public class MergeSort{
	public void merge(ArrayList<Arch<String, Double>> arrayArchs, int l, int m, int r)	{
		int n1 = m - l + 1;
		int n2 = r - m;
		ArrayList<Arch<String, Double>> left = new ArrayList<>();
		ArrayList<Arch<String, Double>> right = new ArrayList<>();

		for (int i = 0; i < n1; ++i)
			left.add(arrayArchs.get(l+i));
		for (int j = 0; j < n2; ++j)
			right.add(arrayArchs.get(m+1+j));

		int i = 0, j = 0;
		int k = l;
		while (i < n1 && j < n2) {
			if (left.get(i).weight <= right.get(j).weight) {
				arrayArchs.set(k, left.get(i));
				i++;
			}
			else {
				arrayArchs.set(k, right.get(j));
				j++;
			}
			k++;
		}

		while (i < n1) {
			arrayArchs.set(k, left.get(i));
			i++;
			k++;
		}

		while (j < n2) {
			arrayArchs.set(k, right.get(j));
			j++;
			k++;
		}
	}

	public void mergeSort(ArrayList<Arch<String, Double>> arrayArchs, int l, int r) throws KruskalException{
	  if(arrayArchs == null)
      throw new KruskalException("mergeSort: arrayArchs parameter cannot be null");
		if (l < r) {
			int m =l+ (r-l)/2;
			mergeSort(arrayArchs, l, m);
			mergeSort(arrayArchs, m + 1, r);
			merge(arrayArchs, l, m, r);
		}
	}
}


