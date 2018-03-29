#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
Implement the "studentList" data structure with a doubly linked list implementation.

You must implement all methods and they must work as described in the comments.  You must also achieve the stated run times, and know the big-Oh run times for each of your methods.
*/

class student
{
public:
	string name;
	unsigned int id;
	double gpa;

	student()
	{
		name = "ghost";
		id = 0;
		gpa = 0;
	}
	student(string _name, unsigned int _id, double _gpa)
	{
		id = _id;
		gpa = _gpa;
		name = _name;
	}

};


ostream& operator<<(ostream& output, const student& profile)
{
	output << profile.id << ": " << profile.name << ' ' << profile.gpa << endl;
	return output;
}

class studentList
{
private:
	//Implement a doubly linked list of students
	unsigned int numStudents;
	class node
	{
	public:
		student data;
		node * next;
		node * prev;

		node()
		{
			data = student();
			//next = NULL;
			//prev = NULL;
		}
		node(student x)
		{
			data = x;
			next = NULL;
			prev = NULL;
		}
	};

	node * head;
	node * tail;

public:
	studentList()
	{
		numStudents = 0;
		head = NULL;
		tail = NULL;
	}

	//add a student to the list.
	//Must run in O(1) time.
	void insert(student s)
	{
		node * tmp = new node(s);
		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			node * before = tail;
			tail = tmp;
			tail->prev = before;
			before->next = tail;
		}
		numStudents++;
	}
	

	//find the student with the given id number and return it
	//What is the worst case run time of this? O(n)
	//What is the average case run time of this?
	student retrieveStudent(unsigned int idnumber)
	{
		node * current = head;
		while (current->data.id != idnumber)
		{
			current = current->next;
		}
		return (current->data);
	}

	//Change the gpa of the student with given id number to newGPA
	//What is the run time? O(n) [worst case]
	void updateGPA(unsigned int idnumber, double newGPA)
	{
		node * current = head;
		//Search
		while (current->data.id != idnumber && current != NULL)
		{
			current = current->next;
		}
		//Replace
		if (current != NULL)
		{
			current->data.gpa = newGPA;
		}
	}

	//Add all students from otherlist to this list.
	//otherlist should be empty after this operation.
	//Must run in O(1) time.
	void mergeList(studentList &otherlist)
	{
		//Connect them O(1)
		if (otherlist.head != NULL)
		{
			tail->next = otherlist.head;
			otherlist.head->prev = tail;
			tail = otherlist.tail;
			otherlist.head = NULL;
			otherlist.tail = NULL;
		}
	}

	//create a list of students whose gpa is at least minGPA.
	//Return this list.  The original list should
	//not be modified (do not remove the students from the original list).
	//Run time? O(n^2+n) [worst case: sorting + going throught everything to find lowest and insert to other list. actually inserting is just O(1)]
	studentList honorRoll(double minGPA)
	{
		studentList HONORS;
		sort("gpa"); //sort if unsorted for ease of access. COULD DO MERGE SORT FOR O(N*LOG(N))
		node * current = head;
		while (current->data.gpa < minGPA) //Was thinking of divide and conquering, but think it'll be slower than if I were doing it with arrays due to the list addresses being radmon.
		{
			current = current->next;
		}
		for (node * tmp = current; tmp != NULL; tmp = tmp->next) //BEST OUTPUTTER I CAN THINK OF
		{
			HONORS.insert(tmp->data);
		}
		return HONORS;
	}

	//sort the list by the given field ("name", "id", or "gpa").
	//Run time? O(n^2) [worst case]
	void sort(string field)
	{
		quickSort(head, tail, field);
	}
	
	//Tried doing mergeSort, but am bad at it. Need to practice/learn to implement it...
	//Quick Sort. Wow did not expect to get it working.

	node * partition(string type, node * localhead, node * localtail)
	{
		node * selectorL = localhead;
		node * selectorR = localtail;
		if (type == "id")
		{
			node * pivotPoint = new node; //stores data just for comparison purposes
			pivotPoint = localhead;
			node * output = localhead; //pointer to pivot's location
			unsigned int pivot = localhead->data.id;
			while (selectorL != selectorR)
			{
				while (selectorL->data.id < pivot)
				{
					if (selectorL == selectorR) //This would mean they're about to cross each other
					{
						selectorL = selectorL->prev;
						goto DONE;
					}
					else
					{
						selectorL = selectorL->next;
					}
				}
				while (selectorR->data.id > pivot)
				{
					if (selectorL == selectorR)  //This would mean they're about to cross each other
					{
						selectorR = selectorR->next;
						goto DONE;
					}
					else
					{
						selectorR = selectorR->prev;
					}
				}
			DONE:
				node * prevPivot = pivotPoint;
				if (selectorL == pivotPoint)
				{
					prevPivot = selectorL;
					pivotPoint = selectorR;
				}
				else if (selectorR == pivotPoint)
				{
					prevPivot = selectorR;
					pivotPoint = selectorL;
				}
				swap(selectorL->data, selectorR->data);
				if (selectorR == pivotPoint)
				{
					output = selectorR;
					selectorL = prevPivot;
				}
				else if (selectorL == pivotPoint)
				{
					output = selectorL;
					selectorR = prevPivot;
				}
			}
			return pivotPoint;
		}
		else if (type == "gpa")
		{
			node * pivotPoint = new node; //stores data just for comparison purposes
			pivotPoint = localhead;
			node * output = localhead; //pointer to pivot's location
			double pivot = localhead->data.gpa;
			while (selectorL != selectorR)
			{
				while (selectorL->data.gpa < pivot)
				{
					if (selectorL == selectorR) //This would mean they're about to cross each other
					{
						selectorL = selectorL->prev;
						goto DONE2;
					}
					else
					{
						selectorL = selectorL->next;
					}
				}
				while (selectorR->data.gpa > pivot)
				{
					if (selectorL == selectorR)  //This would mean they're about to cross each other
					{
						selectorR = selectorR->next;
						goto DONE2;
					}
					else
					{
						selectorR = selectorR->prev;
					}
				}
			DONE2:
				node * prevPivot = pivotPoint;
				if (selectorL == pivotPoint)
				{
					prevPivot = selectorL;
					pivotPoint = selectorR;
				}
				else if (selectorR == pivotPoint)
				{
					prevPivot = selectorR;
					pivotPoint = selectorL;
				}
				swap(selectorL->data, selectorR->data);
				if (selectorR == pivotPoint)
				{
					output = selectorR;
					selectorL = prevPivot;
				}
				else if (selectorL == pivotPoint)
				{
					output = selectorL;
					selectorR = prevPivot;
				}
			}
			return pivotPoint;
		}
		else if (type == "name")
		{
			node * pivotPoint = new node; //stores data just for comparison purposes
			pivotPoint = localhead;
			node * output = localhead; //pointer to pivot's location
			string pivot = localhead->data.name;
			while (selectorL != selectorR)
			{
				while (selectorL->data.name < pivot)
				{
					if (selectorL == selectorR) //This would mean they're about to cross each other
					{
						selectorL = selectorL->prev;
						goto DONE3;
					}
					else
					{
						selectorL = selectorL->next;
					}
				}
				while (selectorR->data.name > pivot)
				{
					if (selectorL == selectorR)  //This would mean they're about to cross each other
					{
						selectorR = selectorR->next;
						goto DONE3;
					}
					else
					{
						selectorR = selectorR->prev;
					}
				}
			DONE3:
				node * prevPivot = pivotPoint;
				if (selectorL == pivotPoint)
				{
					prevPivot = selectorL;
					pivotPoint = selectorR;
				}
				else if (selectorR == pivotPoint)
				{
					prevPivot = selectorR;
					pivotPoint = selectorL;
				}
				swap(selectorL->data, selectorR->data);
				if (selectorR == pivotPoint)
				{
					output = selectorR;
					selectorL = prevPivot;
				}
				else if (selectorL == pivotPoint)
				{
					output = selectorL;
					selectorR = prevPivot;
				}
			}
			return pivotPoint;
		}
		else
		{
			cout << "Please only sort by gpa, name, or id..." << endl;
			return NULL;
		}
	}

	void quickSort(node * hed, node * tel, string type)
	{
		if (hed != tel && tel != NULL && hed != tel->next)
		{
			node * part = partition(type, hed, tel); //works (at least for the first partition
			quickSort(hed, part->prev, type);
			quickSort(part->next, tel, type);
		}
	}
	//Print out each student in the list.  This is mainly for testing purposes.
	void printList()
	{
		for (node * current = head; current != NULL; current = current->next)
		{
			cout << current->data;
		}
	}
};