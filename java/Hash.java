public class Hash {

    int B;
    Element[] table;
    
    Hash(int b){
	B = b;
	table = new Element[b];
	for(int i = 0 ;i < b ; i++)
	    table[i] = new Element();
    }

   int htf(int var, int val, int left, int right){
	
	int h = 0;
	if (var > -1) { h += var; }
	if (val > -1) { h += val; }
	if (left > -1) { h += left; }
	if (right > -1) { h += right; }
	
	return h % B;
    }

    int insert(int var, int val, int left, int right){	
	int i,k,found = -1;
	State cstate;
	Element e = new Element(var, val, left, right);
	
	k = i = htf(var, val, left, right);
	do{
	    cstate = table[k].getState();
	    if(cstate == State.empty || cstate == State.deleted){
		if(found < 0){ found = k; }
	    }
	    else{
		if(e == table[i]){ return -1; }		
	    }
	    
	    k = (k+1) % B;
	}while(cstate != State.empty && k != i);

	if(found < 0){
	    System.out.println("Error: Dictionary is full.");	    
	    System.exit(1);
	}
	table[found] = e;
	table[found].setOccupied();

	// System.out.println(found);
	return found;
    }
    
    void remove(int var, int val, int left, int right){	
	int i,k;
	State cstate;
	Element e = new Element(var, val, left, right);

	k = i = htf(var, val ,left, right);
	do{
	    cstate = table[k].getState();
	    if(cstate == State.occupied){
		if(e == table[k]){table[k].setDeleted();return;}
	    }
	    k = (k+1) % B;
	}while(cstate != State.empty && k != i);
	return;
    }
    
    int member(int var, int val, int left, int right){	
	int i,k;
	State cstate;
	Element e = new Element(var, val, left, right);       

	k = i = htf(var, val, left, right);
	do{
	    cstate = table[k].getState();
	    if(cstate == State.occupied)
		{ if(var == table[k].getVar() && val == table[k].getVal() && 
		     left == table[k].getLeft() && right == table[k].getRight() ){return k;}
		}
	    k = (k+1) % B;
	}while(cstate != State.empty && k != i);
	return -1;
    }

    Element[] getTable(){ return table; }
    int topVar(int i){ return table[i].getVar(); }
    int topVal(int i){ return table[i].getVal(); }
    int getLeft(int i){ return table[i].getLeft(); }
    int getRight(int i){ return table[i].getRight(); }
}
