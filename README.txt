1.To compile, you need to install the curl and nlohmann libraries
2 Compilation example:
	g++ -Wall -fexceptions -g  -c /home/badbad/ProjectsC++/PackagesComprassion/cli.cpp -o obj/Debug/cli.o
	g++  -o bin/Debug/PackagesComprassion obj/Debug/branch.o obj/Debug/cli.o   -lcurl
Usage example:
	cd /PackagesComprassion/bin/Release/
	In this case, the json structure will be written to the output.txt file:
		./PackagesComprassion -1sisyphus -2p10 -foutput.txt
	If you omit the f parameter or do not specify a file name, then json will be output to the standard stream
	
At the moment there are problems with comparing package versions, so for now I commented out the code that adds package comparison to json
