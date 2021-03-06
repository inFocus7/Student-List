#include <iostream>
#include <string>
#include "Students.h"
using namespace std;

int main()
{
	studentList moralorel;
	student Orel("Orel", 0, 4.00), X("X", 12, 4.00), Clay("Clay", 1, 3.55), Bloberta("Bloberta", 2, 3.62), Nursula("Nursula", 3, 2.95), Doctor("Doctor", 4, 3.99), Stephanie("Stephanie", 5, 2.65), Sculptham("Sculptham", 6, 3.12), Creepler("Creepler", 7, 1.95), Doughy("Doughy", 8, 2.32), Daniel("Daniel", 9, 2.31), Shapey("Shapey", 10, 1.23), Block("Block", 11, 1.00);
	studentList bhorse;
	student Bojack("Bojack", 0, 3.0), Caroline("Caroline", 24, 3.87), Peanutbutter("Peanutbutter", 14, 2.89), Diane("Diane", 15, 3.7), Todd("Todd", 23, 2.6);
	bhorse.insert(Bojack);
	bhorse.insert(Caroline);
	bhorse.insert(Peanutbutter);
	bhorse.insert(Diane);
	bhorse.insert(Todd);

	cout << "Students System 2.0" << endl;
	cout << "<ID>: <NAME> <GPA>" << endl;
	cout << "---------------------------------" << endl;

		//Insert Test
	cout << "UNSORTED..." << endl;
	moralorel.insert(Bloberta);
	moralorel.insert(Doctor);
	moralorel.insert(Clay);
	moralorel.insert(Daniel);
	moralorel.insert(Orel);
	moralorel.insert(Stephanie);
	moralorel.insert(Nursula);
	moralorel.insert(Creepler);
	moralorel.insert(Doughy);
	moralorel.insert(Sculptham);
	moralorel.insert(Block);
	moralorel.insert(Shapey);
	moralorel.insert(X);
	moralorel.printList();

		//Sort Test
	cout << "SORTED BY  ID..." << endl;
	moralorel.sort("id"); 
	cout << endl;

		//Update Test
	cout << "UPDATED GPA..." << endl;
	moralorel.updateGPA(1, 2.56);
	moralorel.updateGPA(5, 1.24);
	moralorel.updateGPA(0, 3.98);
	moralorel.printList();
	cout << endl;

		//Retriever Test
	cout << "RETRIEVER..." << endl;
	cout << "Retrieving ID 2..." << endl << moralorel.retrieveStudent(2);
	cout << "Retrieving ID 7..." << endl << moralorel.retrieveStudent(7);
	cout << "Retrieving ID 6..." << endl << moralorel.retrieveStudent(6);
	cout << endl;

		//Merge Test (will have two people with ID = 0, since I didn't make some exception for conflicting ID's and to make sure everthing still works as usual)
	moralorel.mergeList(bhorse);
	cout << "MERGED...  what is this a crossover episode?" << endl;
	moralorel.printList();
	cout << endl;

		//Honor moralorel Test
	cout << "HONORROLL FOR GPA >= 3... (AFTER MERGER TO SHOW THEY STILL WORK TOGETHER)" << endl;
	studentList HONORS = moralorel.honorRoll(3);
	HONORS.printList();
	cout << endl;
		
		//Lists Proof
	cout << "MAIN LIST: " << endl;
	moralorel.printList(); //PROOF THAT THEY'RE MERGED (And in order by GPA since honors sorted them.)
	cout << "OLD WASTE LIST: " << endl;
	bhorse.printList(); //PROOF THAT NOTHING IS IN 

	return 0;
}