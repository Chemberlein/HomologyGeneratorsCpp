# HomologyGeneratorsCpp
# Requirements 
You need to have "g++" and "make" to be installed to compile this project 
Then you could run **run.sh** script and follow the instructions 

## Input file format :
	Same file format to represent point space used.
	On the first line of the file gives number of points N , then N lines with information for each point.
	First column is X coordinate second column id Y coordinate.
	Since initially to work with capacitated vehicle routing problems third column contain demand of this point.
	First point considered as depot and demand of this point represent capacity of the vehicle.
	if you don't in capacity you may just put 1 in this column (or any other number). 
## Output
All figures automatically saved in "output" folder.
In directory "ComputationOfHomology(cpp)/output" you could find file that were generated during execution of the program. _
More precisely : _
	Persistant_Diagram_Data.txt - contains life span information for simplex-es <br />
	H1_homology_generators.txt - contains chains that surround topologycal features <br />

	
