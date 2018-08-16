#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#define SwapInt(X,Y) do{\
				int Ftmp=*(Y);	\
				*(Y)=*(X);		\
				*(X)=Ftmp;		\
				}while(0);
#define SwapFloat(X,Y) do{\
				float Ftmp=*(Y);	\
				*(Y)=*(X);		\
				*(X)=Ftmp;		\
				}while(0);
#define Q 0.85

using namespace std;
const char* filename[30]{
"SF1000_1.5 (1)","SF1000_1.5 (2)","SF1000_1.5 (3)","SF1000_1.5 (4)","SF1000_1.5 (5)",\
"SF1000_1.5 (6)","SF1000_1.5 (7)","SF1000_1.5 (8)","SF1000_1.5 (9)","SF1000_1.5 (10)",
"SF1000_2.5 (1)","SF1000_2.5 (2)","SF1000_2.5 (3)","SF1000_2.5 (4)","SF1000_2.5 (5)",
"SF1000_2.5 (6)","SF1000_2.5 (7)","SF1000_2.5 (8)","SF1000_2.5 (9)","SF1000_2.5 (10)",
"SF1000_3.5 (1)","SF1000_3.5 (2)","SF1000_3.5 (3)","SF1000_3.5 (4)","SF1000_3.5 (5)",
"SF1000_3.5 (6)","SF1000_3.5 (7)","SF1000_3.5 (8)","SF1000_3.5 (9)","SF1000_3.5 (10)",
//'SF1000_4.5 (1)';'SF1000_4.5 (2)';'SF1000_4.5 (3)';'SF1000_4.5 (4)';'SF1000_4.5 (5)';
//'SF1000_4.5 (6)';'SF1000_4.5 (7)';'SF1000_4.5 (8)';'SF1000_4.5 (9)','SF1000_4.5 (10)';
//'SF1000_5.5 (1)';'SF1000_5.5 (2)';'SF1000_5.5 (3)';'SF1000_5.5 (4)';'SF1000_5.5 (5)';
//'SF1000_5.5 (6)';'SF1000_5.5 (7)';'SF1000_5.5 (8)';'SF1000_5.5 (9)';'SF1000_5.5 (10)';
//'SF1000_1.5 (11)';'SF1000_1.5 (12)';'SF1000_1.5 (13)';'SF1000_1.5 (14)';'SF1000_1.5 (15)';
//'SF1000_1.5 (16)';'SF1000_1.5 (17)';'SF1000_1.5 (18)';'SF1000_1.5 (19)';'SF1000_1.5 (20)';
//'SF1000_2.5 (11)';'SF1000_2.5 (12)';'SF1000_2.5 (13)';'SF1000_2.5 (14)';'SF1000_2.5 (15)';
//'SF1000_2.5 (16)';'SF1000_2.5 (17)';'SF1000_2.5 (18)';'SF1000_2.5 (19)';'SF1000_2.5 (20)';
//'SF1000_3.5 (11)';'SF1000_3.5 (12)';'SF1000_3.5 (13)';'SF1000_3.5 (14)';'SF1000_3.5 (15)';
//'SF1000_3.5 (16)';'SF1000_3.5 (17)';'SF1000_3.5 (18)';'SF1000_3.5 (19)';'SF1000_3.5 (20)';
//'SF1000_4.5 (11)';'SF1000_4.5 (12)';'SF1000_4.5 (13)';'SF1000_4.5 (14)';'SF1000_4.5 (15)';
//'SF1000_4.5 (16)';'SF1000_4.5 (17)';'SF1000_4.5 (18)';'SF1000_4.5 (19)';'SF1000_4.5 (20)';
//'SF1000_5.5 (11)';'SF1000_5.5 (12)';'SF1000_5.5 (13)';'SF1000_5.5 (14)';'SF1000_5.5 (15)';
//'SF1000_5.5 (16)';'SF1000_5.5 (17)';'SF1000_5.5 (18)';'SF1000_5.5 (19)';'SF1000_5.5 (20)';
};



class Matrix{
public:
	int *m;
	int col_num;
	int row_num;
	int max;
	Matrix(const char* fp){
		col_num=2;
		row_num=Read(fp);
	}
	Matrix(int n){
		m=(int*)malloc(sizeof(int)*n);
		memset(m,0,sizeof(int)*n);
		col_num=1;
		row_num=n;
	} 
	Matrix(int row,int col){
		m=(int*)malloc(sizeof(int)*row*col);
		memset(m,0,sizeof(int)*col*row);
		col_num=col;
		row_num=row;
	}
	~Matrix(){
		free(m);
	}
	
	int Read(const char* fp){
		char buffer[256];
		m=(int*)malloc(sizeof(int)*300000);
		int i=0;
		//ifstream infile("SF1000_1.5_1.txt");
		ifstream infile(fp);
		if (! infile.is_open())
	    {
	        cout << "Error opening file"; exit (1);
	    }
		cout << "opening file\n"; 
		while (!infile.eof()){
			infile.getline(buffer,100);
			//cout<<buffer<<endl;
	    	sscanf(buffer,"%d\t%d",(m+i*2),(m+i*2+1));
	    	(*(m+i*2))--;
	    	(*(m+i*2+1))--;
	    	//cout<<*(m+i*2)<<"\t"<<*(m+i*2+1)<<endl;
	    	i++;
		}
		return i-1;
	}
	void show(){
		for(int i=0;i<col_num*row_num;i++){
			cout<<m[i]<<endl;
		}
	}
	int getMax(){
		int tmp_max=*m;
		for(int i=1;i<row_num*2;i++){
			//cout<<"i="<<i<<"\t max="<<tmp_max<<endl;
			if(m[i]>tmp_max){
				tmp_max=m[i];
			}
		}
		this->max=tmp_max;
		return tmp_max;
	}

};

class FloatMatrix{
public:
	float *m;
	int col_num;
	int row_num;
	float max;
	FloatMatrix(int row,int col){
		m=(float*)malloc(sizeof(float)*row*col);
		memset(m,0,sizeof(float)*col*row);
		col_num=col;
		row_num=row;
	}
	FloatMatrix(FloatMatrix& fm){
		col_num=fm.col_num;
		row_num=fm.row_num;
		m=(float*)malloc(sizeof(float)*row_num*col_num);
		memcpy(m,fm.m,sizeof(float)*row_num*col_num);
	}
	~FloatMatrix(){
		free(m);
	}
	void init(int n){
		for(int i=0;i<col_num*row_num;i++){
			m[i]=(1.0-Q)/n;
		}
		
	}
	void ones(){
		for(int i=0;i<col_num*row_num;i++){
			m[i]=1.0;
			//cout<<m[i]<<endl;;
		}
	}
	void trans(){
		for(int i=0;i<row_num;i++){
			for(int j=i+1;j<col_num;j++){
				SwapFloat(m+i*col_num+j,m+j*col_num+i);
			}
		}
	}
	void neibour(Matrix& a,Matrix& v){
		for(int i=0;i<a.col_num*a.row_num;i+=2){
			int out=a.m[i];
			int in=a.m[i+1];
			*(m+out*col_num+in)=1.0/v.m[out];
		}
		for(int i=0;i<col_num*row_num;i++){
			if(v.m[i/col_num]==0){
				m[i]=1.0/col_num;
			}
		}
	}
	void show(){
		for(int i=0;i<row_num;i++){
			for(int j=0;j<col_num;j++){
				printf("%8f",m[i*col_num+j]);
				cout<<"\t";
			}
			cout<<endl;
		}
	}
};


int Write(){
	return 0;
}

int combine(FloatMatrix& a,FloatMatrix& b){
	for(int i=0;i<a.col_num*a.row_num;i++){
		a.m[i]=(1-Q)/a.col_num+Q*b.m[i];
	}
	
	return 0;
}
FloatMatrix* MatrixTimes(FloatMatrix& NN,FloatMatrix& N1){
	FloatMatrix *N2=new FloatMatrix(N1);
	for(int i=0;i<NN.row_num;i++){
		float sum=0;
		for(int j=0;j<NN.col_num;j++){
			float tmp=NN.m[i*NN.col_num+j]*N1.m[j];
				//cout<<"--"<<NN.m[i*NN.col_num+j]<<N1.m[j]<<endl;
			sum+=tmp;
		
		}
		N2->m[i]=sum;
	}
	delete(&N1);
	return N2;
}
double pagerank(){
	Matrix a("SF1000_1.5_1.txt");
	cout<<a.row_num;
	//time
	
	int n=a.getMax();
	n++;
	cout<<"MAX:"<<n<<endl;
	if(n>2000){
		exit(0);
	}
	Matrix in(n);
	Matrix out(n);
	cout<<"in out:"<<n<<endl;
	for(int i=0;i<a.row_num*a.col_num;i+=2){
		out.m[a.m[i]]+=1;
		in.m[a.m[i+1]]+=1;
	}
	cout<<"in out ok"<<endl;
	FloatMatrix b(n,n);
	b.neibour(a,out);
	cout<<"b get neibour"<<endl;
	b.show();
	FloatMatrix b2(b);
	b2.trans();
	cout<<"b tranx:"<<endl;

	combine(b,b2);
	cout<<b.row_num<<":"<<b.col_num<<endl;
	b.show();
	cout<<"combine"<<endl;
	//b.init(n);
	FloatMatrix *pr=new FloatMatrix(n,1);
	cout<<"pr col:"<<pr->col_num<<"\trow:"<<pr->row_num<<endl;
	pr->ones();
	
	float thr=0.975*n;
	float dirflg=0;
	int whileno=0;
	getchar();
	//b.show();
	double dur;
    double start,stop;
    start=time(NULL);
	while(dirflg<thr){
		//pr->show();
		FloatMatrix tmppr(*pr);
		//b.show();
		pr=MatrixTimes(b,*pr);
		dirflg=0;
		for(int i=0;i<pr->row_num;i++){
			float dif=pr->m[i]-tmppr.m[i];
			//cout<<"---------dif:"<<dif<<endl;
			if(dif<0.00001 && dif>-0.00001){
				dirflg++;
			}
		}
		
		whileno++;
	}
	stop=time(NULL);
	//pr->show();
	cout<<"shousuo:"<<whileno<<"\ttime:"<<stop<<":"<<start<<"'s" <<endl;
	return 0.0;
}

int main()
{
	pagerank();
	return 0;
}
