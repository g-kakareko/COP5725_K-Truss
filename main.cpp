#include <iostream>
#include "k_truss.h"
#include <string>
#include <cstring>
#include <list>
#include <algorithm>
using namespace std;
 
string decompose_graph_p1(string filename);
string decompose_graph_p2(string filename);
string compose_graph(string p1, string p2);
string bottom_up_truss_decomp(string filename);


int main(int argc, char * argv[]) 
{
	
	string path = argv[1];
	//string path = "paper_example.txt";
	string path1 = "paper_example.txt";
	string path2 = "paper_example-p2.txt";
	k_truss truss(path);	

	//truss.improved_truss_decomp();
	truss.top_down_decomp();

	// k_truss truss_1(path1);
	// cout<<"One function:"<<endl;
	// bottom_up_truss_decomp(path);

	return 0;
}


string decompose_graph_p1(string filename)
{

	struct Edge 
    {
        int u,v;
    };
    string file_out = filename;
    file_out = file_out.substr(0, file_out.size()-4);
	//file_out.pop_back(4);

	string filename_p1 = file_out+"-p1.txt";
	ifstream file_in;

	file_in.open(filename);
	int n,m;
	file_in >> n >> m;
	int vMax=0;
	int u,v;

	list<int> ver_1;

	list<Edge> edge_1;

	int edge_num_1 = 0;
	int vertex_num_1 = 0;
	int mid_m = m/2;
	for (int i=0; i<mid_m; ++i) 
	{
		file_in >> u >> v;
		// cout << u << v<<endl;
		Edge e={u,v};
		edge_1.push_back(e);
		edge_num_1++;

		if(find(ver_1.begin(), ver_1.end(), u) == ver_1.end())
		{
			ver_1.push_back(u);
			vertex_num_1++;
		}

		if(find(ver_1.begin(), ver_1.end(), v) == ver_1.end())
		{
			ver_1.push_back(v);
			vertex_num_1++;
		}
	}


	for (int i=mid_m+1; i<m; ++i) 
	{
		file_in >> u >> v;
		Edge e={u,v};
		bool b1 = find(ver_1.begin(), ver_1.end(), u) == ver_1.end();
		bool b2 = find(ver_1.begin(), ver_1.end(), v) == ver_1.end();

		if(b1 || b2)
		{
			edge_1.push_back(e);
			vertex_num_1++;
			edge_num_1++;
		}

	}
	file_in.close();

	ofstream fout_p1;
	fout_p1.open(filename_p1);
	fout_p1 << vertex_num_1  <<' ' <<edge_num_1<< endl;

	for (auto const& i : edge_1) 
	{
    	fout_p1 << i.u << ' ' << i.v<<endl;
    	// cout << i.u << ' ' << i.v<<endl;
	}
	fout_p1.close();

	return filename_p1;
}

string decompose_graph_p2(string filename)
{

	struct Edge 
    {
        int u,v;
    };
    string file_out = filename;
    file_out = file_out.substr(0, file_out.size()-4);
	//file_out.pop_back(4);

	string filename_p2 = file_out+"-p2.txt";
	ifstream file_in;

	file_in.open(filename);
	int n,m;
	file_in >> n >> m;
	int vMax=0;
	int u,v;

	list<int> ver_2;

	list<Edge> edge_2;

	int edge_num_2 = 0;
	int vertex_num_2 = 0;
	int mid_m = m/2;

	for (int i=0; i<mid_m; ++i) 
		file_in >> u >> v;

	for (int i=mid_m+1; i<m; ++i) 
	{
		file_in >> u >> v;
		// cout << u << v<<endl;
		Edge e={u,v};
		edge_2.push_back(e);
		edge_num_2++;

		if(find(ver_2.begin(), ver_2.end(), u) == ver_2.end())
		{
			ver_2.push_back(u);
			vertex_num_2++;
		}

		if(find(ver_2.begin(), ver_2.end(), v) == ver_2.end())
		{
			ver_2.push_back(v);
			vertex_num_2++;
		}
	}
	file_in.close();
	file_in.open(filename);

	for (int i=0; i<mid_m; ++i)  
	{
		file_in >> u >> v;
		Edge e={u,v};
		bool b1 = find(ver_2.begin(), ver_2.end(), u) == ver_2.end();
		bool b2 = find(ver_2.begin(), ver_2.end(), v) == ver_2.end();

		if(b1 || b2)
		{
			edge_2.push_back(e);
			vertex_num_2++;
			edge_num_2++;
		}

	}
	file_in.close();

	ofstream fout_p2;
	fout_p2.open(filename_p2);
	fout_p2 << vertex_num_2  <<' ' <<edge_num_2<< endl;

	for (auto const& i : edge_2) 
	{
    	fout_p2 << i.u << ' ' << i.v<<endl;
    	// cout << i.u << ' ' << i.v<<endl;
	}
	fout_p2.close();

	return filename_p2;
}
string compose_graph(string p1, string p2, string final_graph)
{
	ifstream file_in1;
	file_in1.open(p1);
	ofstream combined_truss;
	combined_truss.open(final_graph);
	int u,v,truss_cl;
	while(file_in1 >> u >> v >> truss_cl)
	{
		// file_in >> u >> v >> truss_cl;
		//cout << u <<" "<< v <<" "<< truss_cl <<endl;
		combined_truss << u <<" "<< v <<" "<< truss_cl <<endl;
	}
	file_in1.close();

	ifstream file_in2;
	file_in2.open(p2);
	while(file_in2 >> u >> v >> truss_cl)
	{
		// file_in >> u >> v >> truss_cl;
		//cout << u <<" "<< v <<" "<< truss_cl <<endl;
		combined_truss << u <<" "<< v <<" "<< truss_cl <<endl;
	}
	file_in2.close();

	return final_graph;
}


string bottom_up_truss_decomp(string filename)
{
	string final_graph = filename;
	final_graph = final_graph.substr(0, final_graph.size()-4);
	// final_graph.pop_back(4);
	final_graph = final_graph + "-bu_decomposed.txt";

	string p1 = decompose_graph_p1(filename);
	string p2 = decompose_graph_p2(filename);

	//string p1 = "paper_example-p1.txt";
	//string p2 = "paper_example-p2.txt";

	cout<<p1<<endl;
	k_truss truss_1(p1);
	string filename_truss_1 = truss_1.improved_truss_decomp();
	//cout<<"done with decomp"<<endl;

	cout<<p2<<endl;
	k_truss truss_2(p2);
	string filename_truss_2 = truss_2.improved_truss_decomp();
	//cout<<"done with decomp"<<endl;

	//k_truss truss_1(p1);
	//k_truss truss_2(p2);

	//string filename_truss_1 = truss_1.improved_truss_decomp();
	//string filename_truss_2 = truss_2.improved_truss_decomp();
	string bu_truss_decomp = compose_graph(filename_truss_1, filename_truss_2, final_graph);
	return bu_truss_decomp;
}