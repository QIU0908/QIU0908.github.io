#include<iostream>
using namespace std;

int main(void){
	int A[2][2][2]={{{95,85},{66,78}},{{89,77},{60,83}}};
	int ans,sum;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				ans=A[i][j][k];
				sum+=ans;
				cout<<"A["<<i<<"]["<<j<<"]["<<k<<"]="<<ans<<endl;	
			}
		}
	}
	cout<<"sum="<<sum;
}