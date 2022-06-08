#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	ifstream fin; ofstream fout;
	fin.open("map_3.tmx");
	fout.open("map.txt");

	if(!fin) cout <<  "Read error";
	while(!fin.eof())
    {
        string str;
        getline(fin,str);
        while(str[1]!=',' && !fin.eof()) getline(fin,str);
        fout << str << endl;
    }

    cout << "Converting successful";
}
