import java.util.*;
import java.io.*;

public class ZDD {
    
    Hash hash;
    int osize;
    int numberOfNode;
    int root;
    int[] f;
    HashMap<int[],Integer> cache;
    HashMap<Integer,Integer> countCache;

    ZDD(ArrayList<String> rulelist,int hsize,int osize){
	hash = new Hash(hsize);
	osize = osize;
	numberOfNode = 0;
	f = new int[hsize];
	cache = new HashMap<int[],Integer>();
	for(int i = 0; i <= rulelist.size(); i++){
	    hash.insert(-1,i,-1,-1);
	    ++numberOfNode;
	}


	for(int i = 1; i <= rulelist.size(); i++){
	    int node = hash.member(-1,i,-1,-1);
	    // System.out.println(node);
	    for(int j = rulelist.get(0).length()-1; j > -1; --j) {
		if(rulelist.get(i-1).charAt(j) == '1') {
		    node = hash.insert(j+1,-1,0,node);
		    ++numberOfNode;
		}
		if(rulelist.get(i-1).charAt(j) == '*') {
		    node = hash.insert(j+1,-1,node,node);
		    ++numberOfNode;
		}
	    }		
	    f[i-1] = node;
	}

	int node = f[0];
	for (int i = 1; i < rulelist.size(); ++i)
	    node = unification(node,f[i]);
	root = node;

	    

    }
    
    
    int getNode(int var, int val, int left, int right){
	if ( 0 == right) { return left; }

	int P = hash.member(var, val, left, right);
	if (-1 != P) { return P; }
	P = hash.insert(var, val, left, right);
	++numberOfNode;
	return P;
    }
        
    int unification(int P, int Q){
	int R = 0;
	int[] o = {P,Q};

	// System.out.println(P + ", " + Q);
	if(0 == P) {
	    return Q;
	}
	if (0 == Q || P == Q) {
	    return P;
	}
	if (-1 == hash.topVar(P) && -1 == hash.topVar(Q)) {
	    if (P < Q) { return P; }
	    else { return Q; }
	}
	if( null != cache.get(o) ){
	    return cache.get(o);
	}
	if ((hash.topVar(P) < hash.topVar(Q) && hash.topVar(P) != -1) || hash.topVar(Q) == -1) {
	    // System.out.println(hash.topVar(P) + " (<) " + hash.topVar(Q));
	    R = getNode(hash.topVar(P),hash.topVal(P),unification(hash.getLeft(P),Q),hash.getRight(P) );	    
	}
	else if((hash.topVar(Q) < hash.topVar(P) && hash.topVar(Q) != -1) || hash.topVar(P) == -1) {
	    // System.out.println(hash.topVar(P) + " (>) " + hash.topVar(Q));
	    R = getNode(hash.topVar(Q),hash.topVal(Q),unification(P,hash.getLeft(Q)),hash.getRight(Q) );	    
	}
	else if( hash.topVar(P) == hash.topVar(Q) ){
	    // System.out.println(hash.topVar(P) + " (=) " + hash.topVar(Q));
	    R =  getNode(hash.topVar(P),hash.topVal(P),unification(hash.getLeft(P),hash.getLeft(Q)),unification(hash.getRight(P),hash.getRight(Q)) );
	}

	cache.put(o,R);
	if(cache.size() > osize)
	    cache.clear();

	return R;
    }

    int count(int n){
	
    	int m = countSub(n,root,hash.getTable());
    	countCache.clear();
	return m;
    }

    int countSub(int n, int P, Element[] tb){
	if(0 == P){ return 0; }
	else if(n == P){ return 1; }
	if(tb[P].getVal() != 1){ return 0;}
	if( null != countCache.get(P) ){return cache.get(P);}
	int sum  = countSub(n, hash.getLeft(P), tb) + countSub(n, hash.getRight(P), tb);
	countCache.put(P,sum);
	return sum;
    }
    
    
    void print(){
	HashSet<Integer> hs = new HashSet<Integer>();
	printSub(root,hs);
    }

    void printSub(int i,HashSet<Integer> hs){
	if (-1 == i) { return; }
	if (hs.contains(i)) { return; }
	hs.add(i);
        System.out.println(i + ", " + hash.topVar(i) + ", " + hash.topVal(i) + ", " + hash.getLeft(i) + ", " + hash.getRight(i));
	printSub(hash.getLeft(i), hs);
	printSub(hash.getRight(i), hs);
    }
	

    
    public static void main(String[] args){ 	  
	try{
	    ArrayList<String> ruleList = new ArrayList<String>();
	    File input = new File(args[0]);
	    BufferedReader br = new BufferedReader(new FileReader(input));
	    //File output = new File(args[1]);
	    //BufferedWriter bw = new BufferedWriter(new FileWriter(output));
	    String rule;
	    int ruleNum,bit;

	    
	    while((rule = br.readLine()) != null)
		ruleList.add(rule);	
	    
	    ZDD bdd = new ZDD(ruleList,Integer.parseInt(args[1]),Integer.parseInt(args[2]));
	    
	    bdd.print();
	    
	}catch(FileNotFoundException e) {
	    e.printStackTrace();
	}catch(IOException e) {
	    e.printStackTrace();
	}	
      }
    
}
