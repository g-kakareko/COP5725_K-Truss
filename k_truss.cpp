/***********************************************
Grzegorz Kakareko
Florida State University
College of Engineering
2525 Pottsdamer Street, Tallahassee, FL 32310
Email: gk15b@my.fsu.edu - Phone: +1-850-570-4683

This file contains the class functions for the k_truss class.
The description of the functions is in the k_truss.h 
************************************************/

#include "k_truss.h"
k_truss::k_truss(string fn)
{
	path=fn;
	path_name=path;
	path_name = path_name.substr(0, path_name.size()-4);
}
k_truss::~k_truss(void) 
{
   //cout << "Object is being deleted"<<" "<<path << endl;
}
bool k_truss::compVertex( int i,  int j) 
{
    return deg[i]<deg[j] || (deg[i]==deg[j] && i<j);
}

void k_truss::updateSupport(int u, int v, int delta) 
{
	Adj[u][v]+=delta;
	Adj[v][u]+=delta;
}   

void k_truss::removeEdge(int u, int v) 
{
    Adj[u].erase(v);
    Adj[v].erase(u);
}

void k_truss::orderPair(int &u, int &v) 
{
    if (!compVertex(u,v)) swap(u,v);
}

void k_truss::init_Adj()
{
	// Open the file
	ifstream file_in;
	file_in.open(path);
	file_in >> n >> m;

	int vMax=0;
	int u,v;

	for (int i=0; i<m; ++i) 
	{
		file_in >> u >> v;
		if (u==v) 
			continue;
		vMax=max(vMax,max(u,v));
	}
	n=vMax+1;
	file_in.close();
	file_in.open(path);
	int junk;
	file_in>>junk>>junk;
	deg.clear(); 

	deg.resize(n,0);
	Adj.resize(n); 			// Initialize here
	for (int i=0; i<n; ++i) 
		Adj[i].clear();

	for (int i=0; i<m; ++i) 
	{
		file_in >> u >> v;
		if (u==v) continue; // same does not matter

		if (Adj[u].find(v)==Adj[u].end()) 
		{
			Adj[u][v]=0;
			Adj[v][u]=0;
			++deg[u]; 
			++deg[v];
		}
	}
}

void k_truss::reorder() 
{
	mapto.resize(n);
	for (int i=0; i<n; ++i) 
		mapto[i]=i;
	
	sort(mapto.begin(), mapto.end(), [this](int i, int j) {return deg[i]<deg[j] || (deg[i]==deg[j] && i<j); });
}

void k_truss::intersect(const vector<int> &a, const vector<int> &b, vector<int> &c) 
{
	c.clear();
	unsigned j=0;
	for (unsigned i=0; i<a.size(); ++i) 
	{
		while (j<b.size() && b[j]>a[i]) 
			++j;
		if (j>=b.size()) 
			break;
		if (b[j]==a[i]) 
			c.push_back(a[i]);
	}
}

void k_truss::countTriangles()
{
	bool temp1;
	A.resize(n); // Initialize A

	for (int i=0; i<n; ++i) 
		A[i].clear();

	int nDeltas=0;
	for (int vi=n-1; vi>=0; --vi)	// For each vertex 
	{
		int v=mapto[vi];

		auto tmp1 = Adj[v].begin();
		auto tmp2 = Adj[v].end();

		int u1 = tmp1-> first;
		int u2 = tmp2-> first;

		for (auto it = Adj[v].begin(); it!=Adj[v].end(); ++it)  // For each vertex
		{

			int u = it->first;
			temp1 = !compVertex(u,v);
			if (!compVertex(u,v)) 
				continue;
			
			vector<int> common;
			intersect(A[u], A[v], common);
			for (unsigned i=0; i<common.size(); ++i) {
				int w=mapto[common[i]];
				++nDeltas;
				updateSupport(u,v,1);
				updateSupport(v,w,1);
				updateSupport(w,u,1);
			}
			A[u].push_back(vi);
		}
	}
	cout << nDeltas << "triangles found.\n";
}

void k_truss::binSort() 
{
	bin.clear(); bin.resize(n,0);
	int nBins=0;
	int mp=0;
	for (int u=0; u<n; ++u) 
	{
		auto tadj = Adj[u];
		for (auto it=tadj.begin(); it!=tadj.end(); ++it) 
		{
			int v=it->first;
			if (!compVertex(u,v)) 
				continue;

			int sup=it->second;
			if (sup==0) 
			{
				printClass(u,v,2);
				removeEdge(u,v);
				continue;
			}
			++mp;
			++bin[sup];
			nBins=max(sup,nBins);
		}
	}
	m=mp;
	++nBins;
	int count=0;
	for (int i=0; i<nBins; ++i) 
	{
		int binsize=bin[i];
		bin[i]=count;
		count+=binsize;
	}
	pos.clear(); pos.resize(n);
	for (int i=0; i<n; ++i) 
		pos[i].clear();

	binEdge.resize(m);
	for (int u=0; u<n; ++u)
	{
		for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
		{
			int v=it->first;
			if (!compVertex(u,v)) 
				continue;
			int sup=it->second;
			Edge e={u,v};
			int &b=bin[sup];
			binEdge[b]=e;
			pos[u][v]=b++;
		}
	}
	for (int i=nBins; i>0; --i) 
	{
		bin[i]=bin[i-1];
	}
	bin[0]=0;
}

void k_truss::binSort_top_down() 
{
	bin.clear(); bin.resize(n,0);
	int nBins=0;
	int mp=0;
	for (int u=0; u<n; ++u) 
	{
		auto tadj = Adj[u];
		for (auto it=tadj.begin(); it!=tadj.end(); ++it) 
		{
			int v=it->first;
			if (!compVertex(u,v)) 
				continue;

			int sup=it->second;
			if (sup==0) 
			{
				removeEdge(u,v);
				continue;
			}
			++mp;
			++bin[sup];
			nBins=max(sup,nBins);
		}
	}
	m=mp;
	++nBins;
	int count=0;
	for (int i=0; i<nBins; ++i) 
	{
		int binsize=bin[i];
		bin[i]=count;
		count+=binsize;
	}
	pos.clear(); pos.resize(n);
	for (int i=0; i<n; ++i) 
		pos[i].clear();

	binEdge.resize(m);
	for (int u=0; u<n; ++u)
	{
		for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
		{
			int v=it->first;
			if (!compVertex(u,v)) 
				continue;
			int sup=it->second;
			Edge e={u,v};
			int &b=bin[sup];
			binEdge[b]=e;
			pos[u][v]=b++;
		}
	}
	for (int i=nBins; i>0; --i) 
	{
		bin[i]=bin[i-1];
	}
	bin[0]=0;
}

void k_truss::trussDecomp() 
{
	for (int s=0; s<m; ++s) 
	{
		int u=binEdge[s].u;
		int v=binEdge[s].v;
		orderPair(u,v);
		int supuv=Adj[u][v];
		printClass(u,v,supuv+2);
		int nfound=0;
		for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
		{
			if (nfound==supuv) 
				break;
			int w=it->first;
			if (w==v) 
				continue;
			if (Adj[v].find(w)!=Adj[v].end()) 
			{
				++nfound;
				updateEdge(u,w,supuv);
				updateEdge(v,w,supuv);
			}
		}
		removeEdge(u,v);
	}
}

void k_truss::trussDecomp_top_down() 
{
	for (int s=m; s>0; --s) 
	{
		int u=binEdge[s].u;
		int v=binEdge[s].v;
		orderPair(u,v);
		int supuv=Adj[u][v];
		printClass(u,v,supuv+2);
		int nfound=0;
		for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
		{
			if (nfound==supuv) 
				break;
			int w=it->first;
			if (w==v) 
				continue;
			if (Adj[v].find(w)!=Adj[v].end()) 
			{
				++nfound;
				updateEdge(u,w,supuv);
				updateEdge(v,w,supuv);
			}
		}
		removeEdge(u,v);
	}
}

void k_truss::updateEdge(int u, int v, int minsup) 
{
	orderPair(u,v);
	int sup=Adj[u][v];
	if (sup<=minsup) return;
	int p=pos[u][v];
	int posbin=bin[sup];
	Edge se=binEdge[posbin];
	Edge e={u,v};
	if (p!=posbin) {
		pos[u][v]=posbin;
		pos[se.u][se.v]=p;
		binEdge[p]=se;
		binEdge[posbin]=e;
	}
	++bin[sup];
	updateSupport(u,v,-1);
}

string k_truss::improved_truss_decomp()
{
	string filename_out = path_name + "-improved_algorithm.txt";
	file_out.open(filename_out);
	init_Adj();
	reorder();
	countTriangles();
	binSort();
	trussDecomp();
	file_out.close();

	return filename_out;
}

string k_truss::top_down_decomp()
{
	string filename_out = path_name + "-top_down.txt";
	file_out.open(filename_out);
	init_Adj();
	reorder();
	countTriangles();
	binSort_top_down();
	trussDecomp_top_down();
	file_out.close();
	return filename_out;
}

void k_truss::printClass(int u, int v, int cls) 
{
    ++cntClass[cls];
    file_out << u << " " << v << " " << cls << endl;
    cout << u << " " << v << " " << cls << endl;
}
