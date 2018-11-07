# Network_LaurinePlanat
Projet NETWORK				 
Laurine Planat 
DeadLine: 7th nov, 11:00 pm 

    A. Presentation of the program  

Main goal of the program:  

The aim of the program is to create, according to a number of nodes random links between these nodes following poisson distribution. The number of nodes and the mean of poisson distribution will be given by the user or are default ones.  

Each link is bidirectional, so A to B implies B to A. Furthermore, each nodes has a value and an index. The value is generated following to Normal law N(0,1). 

During this program, some of the functions throw exeptions, all of those are treated in the main file.  

    B. Compilation of the program  

To execute the program 
	cmake .. 
	make
	./NetSim -n 10 -d 3 

(numbers after -n and -d are just given as example. -n corresponds to nodes number, -d corresponds to mean of poisson distribution). 

  
