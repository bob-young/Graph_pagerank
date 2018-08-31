#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class Fun{
	public:
		vector<int> def;//x value 
		vector<double> val;//y value
};
/*
vector<int>* AandB(vector<int>* A,vector<int>* B){
	vector<int> *ret=new vector<int>();
	int mindef=min(A[0],B[0]);
	int maxdef=max(A[A->size()-1],B[B->size()-1]);
	for(int i=mindef;i<=maxdef;i++){
		ret->push_back(i);
	}
	return ret;
}*/

Fun* roll(Fun* l,Fun* r){
	Fun* roll=new Fun();
	int mindef=min(l->def[0],r->def[0]);
	int maxdef=max(l->def[l->def.size()-1],r->def[r->def.size()-1]);
	for(int i=mindef;i<=maxdef+l->def.size();i++){
		roll->def.push_back(i);
		//roll sum
		//l range(x) = l def
		//r range(i-x)
		//get new r range 
		vector<int> r_range;
		vector<double> r_val;
		for(int j=0;j<l->def.size();j++){
			if((i-l->def[j])<r->def[0]){
				break;
			}
			if((i-l->def[j])>r->def[r->def.size()-1]){
				continue;
			}
			r_range.push_back(l->def[j]);
		}
		//reverse r_range
		/*
		vector<int> rr_range;
		vector<int>::reverse_iterator riter;
    	for (riter=r_range.rbegin();riter!=r_range.rend();riter++)
    	{
        	rr_range.push_back(*riter);
    	}
    	*/
		//r_range n l_range
	//	vector<int> *def_r_and_l=AandB(l->def,&rr_range);
		//
		double sum=0.0;
		for(int j=0;j<r_range.size();j++){
			int index_l=r_range[j];
			double value_l=l->val[(index_l-l->def[0])];
			int index_r=i-index_l;
			double value_r=r->val[(index_r-r->def[0])];
			
			sum+=value_l*value_r;
		}
		roll->def.push_back(i);
		cout<<i<<"s:"<<sum<<endl;
		roll->val.push_back(sum);
		//
		
	}
	return roll;
}

int main(){
	Fun f;
	f.def=vector<int>{1,2,3,4,5,6};
	f.val=vector<double>{1.0/6,1.0/6,1.0/6,1.0/6,1.0/6,1.0/6};
	Fun* f2=roll(&f,&f);
	cout<<"______\n";
	roll(&f,f2);
	return 0;
}
