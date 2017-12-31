It helps the rare disease patients to find their physicians.
We developed a machine learning algorithm to find the best rare disease physician from the given dataset.

Information regarding files:-
1. patientjourneyfinder.csv contains the diagnosis data of patients. 
2. symptoms.csv contains the symptoms of a rare disease.
3. doctorlist.csv contains the details of the physicians.
4. mtp.cpp or mtp.py contains the implementation of the algorithm.
5. To execute the program mtp.cpp follow the following steps:
	- Install c++ compilier (g++ for Linux/Unix & mingw for windows)
	- open the terminal and go to the directory in which you had extracted the rarediseasefinder.zip
	- type cammand cd rarediseasefinder
	- now run "g++ -std=c++14 -o target mtp.cpp" or write "make".
6. run "./target >output.txt" it will generate an output file.
7. To execute the program mtp.py run "python mtp.py >output.txt"
8. Open output.txt to check the results.

