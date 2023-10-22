# HomologyGeneratorsCpp
# Requirements 
You need to have "g++" and "make" to be installed to compile this project 
Then you could run **run.sh** script and follow the instructions 

## Input file format :
	The first line of the input file gives a number of points N, then N lines with information for each point.
	The first column is X coordinate, and the second column is Y coordinate.
	Since we initially worked with capacitated vehicle routing problems, the third column contains the demand of this point.
	The first point is considered as depot and the demand of this point represents the capacity of the vehicle.
	if you don't need capacity you may just put 1 in this column (or any other number). 
## Output
All figures are automatically saved in the "output" folder.
In the directory "ComputationOfHomology(cpp)/output" you could find files that were generated during execution of the program. <br />
More precisely : <br />
	Persistant_Diagram_Data.txt - contains life span information for simplex-es <br />
	H1_homology_generators.txt - contains chains that surround topological features <br />

	
