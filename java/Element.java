public class Element{
    
    int var,val,left,right;
    State state;

    Element(){
    	var = -1;
    	val = -1;
    	left = -1;
    	right = -1;
    	state = State.empty;
    }
    
    Element(int vr, int vl,int l,int r){
	var = vr;
	val = vl;
	left = l;
	right = r;
	state = State.empty;
    }

    void setEmpty(){ state = State.empty; }
    void setOccupied(){	state = State.occupied; }
    void setDeleted(){ state = State.deleted; }
    int getVar(){ return var; }
    int getVal(){ return val; }
    int getLeft(){ return left; }
    int getRight(){ return right; }
    State getState(){ return state; }
}
