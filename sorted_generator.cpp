#include<bits/stdc++.h>
#include<fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc!=2){
		cout<<"Expected format: ./<exe_file> <number of entries>"<<endl;
		cout<<"Please reenter properly\n";
		exit(0);
	}
	vector <unsigned int> v;
	srand(time(NULL));
	long long int i,num;
	num = (long long int)atoll(argv[1]);
	for(i=0;i<num;i++)
	{
		v.push_back(rand() % (num*10));
	}
	sort(v.begin(),v.end());
	ofstream fout;
	fout.open("AVL/sorted_dataset.txt");
	for(i=0;i<num-1;i++)
	{
		fout<<v[i]<<endl;
	}
	fout<<v[i];
	fout.close();

	fout.open("Red-Black-Tree/sorted_dataset.txt");
	for(i=0;i<num-1;i++)
	{
		fout<<v[i]<<endl;
	}
	fout<<v[i];
	fout.close();
	return 0;
}
