/***********************************************
Grzegorz Kakareko
Florida State University
College of Engineering
2525 Pottsdamer Street, Tallahassee, FL 32310
Email: gk15b@my.fsu.edu - Phone: +1-850-570-4683
************************************************/

#include <iostream>
#include "k_truss.h"
#include <string>
#include <cstring>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
 
string decompose_graph_p1(string filename);
string decompose_graph_p2(string filename);
string compose_graph(string p1, string p2);
string bottom_up_truss_decomp(string filename);


int main(int argc, char * argv[]) 
{

	if(argc==3)
	{
		if(string(argv[1])=="-1")
		{
			// The orginal decomposition algorithm
			cout << "-1" <<endl;

		}else if(string(argv[1])=="-2")
		{
			// Improved ine memory decomposition 

			cout << "Calculating the improved truss decomposition: " <<endl;
			string path = argv[2];

			clock_t begin = clock();
			k_truss truss(path);	
			string name = truss.improved_truss_decomp();
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
			cout << "The decomposed truss was saved in: "<<name <<endl;
			cout << "The calculations took: " << elapsed_secs <<" sec."<<endl;

		}else if(string(argv[1])=="-3")
		{
			// bottom_up_truss_decomp
			string path = argv[2];

			clock_t begin = clock();
			string name = bottom_up_truss_decomp(path);
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			
			cout << "The decomposed truss was saved in: "<<name <<endl;
			cout << "The calculations took: " << elapsed_secs <<" sec."<<endl;

		}else if(string(argv[1])=="-4")
		{
			// TOP-DOWN TRUSS DECOMPOSITION
			string path = argv[2];
			k_truss truss(path);	
			truss.top_down_decomp();
		}else if(string(argv[1])=="-h")
		{
			cout<<"main contains the execu";
			cout<<"k_truss_dec <argument> <filename> is the program for K Truss decomposition. The basic algorithms "<<endl;
			cout<<"are based on the “Truss Decomposition in Massive Networks” written by Jia Wang and James Cheng. "<<endl;
			cout<<"The following arguments are available: "<<endl;
			cout<<"-b Basic algorithm for the truss decomposition, prints the results to screen and saves them "<<endl;
			cout<<"into filename-basic_algorithm.txt "<<endl;
			cout<<"-i The improved algorithm for the truss decomposition. The final results are printed to the screen "<<endl;
			cout<<"and save to filename-improved_algorithm.txt "<<endl;
			cout<<"-bu Bottom up truss decomposition algorithm that is I/O effective. The partial results are saved "<<endl;
			cout<<"in filename-p1/2.txt. The final results are saved in the filenam-ebottom_up.txt "<<endl;
			cout<<"-td Top-Down Truss decomposition. The result is saved in filename-top_down.txt "<<endl;
			cout<<"-h Help option, the current message is print to the screen"<<endl;
		}
		else
		{
			cout<<"ERROR: run the program with -h option for help"<<endl;
		}

	}else
	{
		if(string(argv[1])=="-h")
		{
			cout<<"k_truss_dec <argument> <filename> is the program for "<<endl;
			cout<<"K Truss decomposition. The basic algorithms "<<endl;
			cout<<"are based on the “Truss Decomposition in Massive Networks”"<<endl;
			cout<<"written by Jia Wang and James Cheng. "<<endl;
			cout<<"The program operates on the following arguments: "<<endl<<endl;

			cout<<"\t-b Basic algorithm for the truss decomposition,"<<endl;
			cout<<"\tprints the results to screen and saves them "<<endl;
			cout<<"\tinto filename-basic_algorithm.txt "<<endl<<endl;

			cout<<"\t-i The improved algorithm for the truss decomposition. "<<endl;
			cout<<"\tThe final results are printed to the screen "<<endl;
			cout<<"\tand save to filename-improved_algorithm.txt "<<endl<<endl;

			cout<<"\t-bu Bottom up truss decomposition algorithm that is "<<endl;
			cout<<"\tI/O effective. The partial results are saved "<<endl;
			cout<<"\tin filename-p1/2.txt. The final results are saved in "<<endl;
			cout<<"\tthe filenam-ebottom_up.txt "<<endl<<endl;

			cout<<"\t-td Top-Down Truss decomposition. The result is saved "<<endl;
			cout<<"\tin filename-top_down.txt "<<endl<<endl;

			cout<<"\t-h Help option, the current message is print to the screen"<<endl;
		}else
		{
			cout<<"ERROR: run the program with -h option for help"<<endl;
		}
		
	}

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
	cout << "The final decomposed graph: "<<endl;
	while(file_in1 >> u >> v >> truss_cl)
	{
		// file_in >> u >> v >> truss_cl;
		cout << u <<" "<< v <<" "<< truss_cl <<endl;
		combined_truss << u <<" "<< v <<" "<< truss_cl <<endl;
	}
	file_in1.close();

	ifstream file_in2;
	file_in2.open(p2);
	while(file_in2 >> u >> v >> truss_cl)
	{
		// file_in >> u >> v >> truss_cl;
		cout << u <<" "<< v <<" "<< truss_cl <<endl;
		combined_truss << u <<" "<< v <<" "<< truss_cl <<endl;
	}
	file_in2.close();

	return final_graph;
}


string bottom_up_truss_decomp(string filename)
{
	string final_graph = filename;
	final_graph = final_graph.substr(0, final_graph.size()-4);
	final_graph = final_graph + "-bottom_up.txt";

	string p1 = decompose_graph_p1(filename);
	string p2 = decompose_graph_p2(filename);

	cout<<p1<<endl;
	k_truss truss_1(p1);
	string filename_truss_1 = truss_1.improved_truss_decomp();

	cout<<p2<<endl;
	k_truss truss_2(p2);
	string filename_truss_2 = truss_2.improved_truss_decomp();

	string bu_truss_decomp = compose_graph(filename_truss_1, filename_truss_2, final_graph);
	return bu_truss_decomp;
}