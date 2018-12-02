# COP5725_K-Truss
This repository contains the final project for the [COP5725 Advanced Database Systems](http://www.cs.fsu.edu/~zhao/cop5725/project.html). The final project was the implementation of the K-Truss decomposition algorithms described in [Truss Decomposition in Massive Networks](http://vldb.org/pvldb/vol5/p812_jiawang_vldb2012.pdf). The improved algorithm appliance is based on the orginal [Wang code](https://github.com/cntswj/truss-decomposition)
The implementation contains the following K Truss decomposition:
* The basic decomposition algorithm proposed by [Cohen](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.505.7006&rep=rep1&type=pdf)
* The improved version of the in memory algorithm
* The efficient I/O algorithm Bottom up
* The In memory top-down decomposition 

The data folder contains the graph examples of the smaller networks described in Table 1. All the networks described in the [paper](http://vldb.org/pvldb/vol5/p812_jiawang_vldb2012.pdf) are avaliable [here](https://snap.stanford.edu/data/)
The input files need to follow the standard described below.
#### Input
``
1st line:	n m	// #vertices, #edges 
``
<br />
``
(i+1)th line	u v	// ith edge u v vertexes 
``
#### Output
``
each line contains edge K-truss description, where:
``
<br />
``
u v c	// (u,v) edge that belongs to c-class, (not (c+1)-truss).
`` 
#### Table 1. Graph examples 

|Name	|V_G | E_G |
------|:---|:----|
|P2P	|6.3K	|41.6K|
|HEP	|9.9K	|52.0K|

#### How to run the code
The repository includes the ``makefile`` for the g++  std=c++11. k_truss_dec is the executable that should be run in the following order:
```
./k_truss_dec <argument> <filename>
```
The following arguments are avaliable for the execution:
* ``-b`` Basic algorithm for the truss decomposition, prints the results to screen and saves them into filename-basic_algorithm.txt 
* ``-i`` The improved algorithm for the truss decomposition. The final results are printed to the screen and save to filename-improved_algorithm.txt 
* ``-bu`` Bottom up truss decomposition algorithm that is I/O effective. The partial results are saved in filename-p1/2.txt. The final results are saved in the filenam-ebottom_up.txt 
* ``-td`` Top-Down Truss decomposition. The result is saved in filename-top_down.txt 
* ``-h`` Help option, print the help message to the screen
