# COP5725_K-Truss
This repository contains the final project for the [COP5725 Advanced Database Systems](http://www.cs.fsu.edu/~zhao/cop5725/project.html). The final project was the implementation of the K-Truss decomposition algorithms described in [Truss Decomposition in Massive Networks] (http://vldb.org/pvldb/vol5/p812_jiawang_vldb2012.pdf).
The implementation contains the following K Truss decomposition:
* The basic decomposition algorithm proposed by [Cohen] (http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.505.7006&rep=rep1&type=pdf)
* The improved version of the in memory algorithm
* The efficient I/O algorithm Bottom up
* The In memory top-down decomposition 

The data folder contains the graph examples described in Table 1.
The input files need to follow the standart described below
#### Input
``
1st line:	n m	// #vertices, #edges
(i+1)th line	u v	// ith edge (u,v)
``
#### Output
m lines containing:
u v c	// (u,v) belongs to c-class,
		meaning it's in c-truss but not (c+1)-truss.
    
Table 1. Graph examples
|Name	|V_G | E_G |
------|:---|:----|
|P2P	|6.3K	|41.6K|
|HEP	|9.9K	|52.0K|
|Amzaon	|0.4M	|3.4M|
|Wiki	|2.4M	|5.0M|
|Skitter	|1.7M	|11.0M|
|Blog	|1.0M	|12.8M|
