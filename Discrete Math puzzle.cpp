// Discrete Math puzzle.cpp : 

#include <iostream>
#include<string>
using namespace::std;

struct node
{
	int array[9];
	node* parent;

	node()
	{
		this->parent = NULL;
	}
};

class set   //class that will be used to store visited states and also will be used as queue
{
	struct setNode
	{
		node* state;
		setNode*next;
		setNode*prev;

		setNode()
		{
			next = NULL;
			prev = NULL;
		}
	};

	setNode* setHead;
	setNode* setTail;
	int arrSize;


public:

	int setSize;

	//adds at head
	void add(node *data)  //function to add data to set linked list
	{
		if (setHead == NULL)
		{
			setHead = new setNode;
			setHead->state = data;
			setTail = setHead;
		}

		else
		{
			setNode *newNode = new setNode;
			newNode->state = data;

			newNode->next = setHead;
			setHead->prev = newNode;
			setHead = newNode;
		}

		setSize++;
	}

	node* top()  
	{
		//return top value when class used as queue
		if(setTail!=NULL)
		return setTail->state;

		else return NULL;
	}

	//removes from tail
	void dequeue()
	{
		setNode*temp = setTail;
		if (setTail != setHead)
		{
			setTail->prev->next = NULL;
			setTail = setTail->prev;
			delete temp;
		}

		else
		{
			delete setTail;

			setHead = NULL;
			setTail = NULL;
		}

		setSize--;
		
	}

	bool search(int *matrix)  //function to search in set
	{
		setNode*trav = this->setHead;
		bool same;

		while (trav != NULL)
		{
			same = true;
			
			for (int i = 0; i < arrSize; i++)
			{
				if (matrix[i] != trav->state->array[i])
				{
					same = false;
					break;
				}
			}

			if (same == true)
			{
				return true;
			}
				
			trav = trav->next;
		}

		return false;
	}

	void dispPuzzle() //function to display all states stored in a set
	{
		setNode* temp = setHead;
		while (temp != NULL)
		{
			int*matrix = temp->state->array;

			cout << "\n ---------\n ";
			for (int i = 0; i < arrSize; i++)
			{
				if (matrix[i] == 0)
				{
					cout << "|" << " " << "|";
				}

				else
					cout << "|" << matrix[i] << "|";

				if ((i + 1) % 3 == 0)
					cout << endl << " ";
			}
			cout << "---------\n ";

			temp = temp->next;
		}
	}

	set()
	{
		setHead = NULL;
		setTail = NULL;
		arrSize = 9;
		setSize = 0;
	}

	~set()
	{
		setNode* temp;

		while (setHead != NULL)
		{
			temp = setHead;
			setHead = setHead->next;
			delete temp;
		}
	}

};

class graph
{
	int arrSize;
	node *root;
	set usedSet;  //set to keep track of visited states
	set queue;

	bool checkSolvability(int *input)   //function to check if the input by user is solvable or not
	{
		int invCount = 0;

		for (int i = 0; i < arrSize; i++)
		{
			if (input[i] == 0)
				continue;

			for (int j = i + 1; j < arrSize; j++)
			{
				if (input[j] == 0)
					continue;

				if (input[i] > input[j])
					invCount++;
			}
		}

		if (invCount % 2 == 0)
			return true;

		else
			return false;
	}

	void dispPuzzle(int *matrix)  //function to print matrix state
	{
		cout << "\n ---------\n ";		
		for (int i = 0; i < arrSize; i++)
		{
			if (matrix[i] == 0||matrix[i] == -1)
			{
				cout << "|" <<" "<< "|";
			}
			
			else
			cout << "|" << matrix[i] << "|";

			if ((i + 1) % 3 == 0)
				cout << endl<<" ";
		}
		cout << "---------\n ";
	}

	bool getPermutations(node *trav)  //function to get possible moves and add them to queue and used set
	{
		int zeroIndex;
		node* tempPerm=new node;
		tempPerm->parent = trav;
	
		for (int i = 0; i < arrSize; i++)
		{
			if (trav->array[i] == 0)
			{
				zeroIndex = i;
				break;
			}
		}

		int horG, horL;

		if (zeroIndex >= 0 && zeroIndex <= 2)
		{
			horG = 2;
			horL = 0;
		}

		else if (zeroIndex >= 3 && zeroIndex <= 5)
		{
			horG = 5;
			horL = 3;
		}

		else if (zeroIndex >= 6 && zeroIndex <= 8)
		{
			horG = 8;
			horL = 6;
		}

		if ((zeroIndex + 1) >= horL &&(zeroIndex + 1) <= horG)  //condition for right move
		{
			tempPerm->array[zeroIndex] = trav->array[zeroIndex + 1];
			tempPerm->array[zeroIndex + 1] = 0;
			
			for (int i = 0; i < arrSize; i++)
			{
				if (i == zeroIndex || i == (zeroIndex + 1))
					continue;
				
				tempPerm->array[i] = trav->array[i];
			}


			if (!usedSet.search(tempPerm->array))
			{

				if (solved(tempPerm))
					return true;
				
				queue.add(tempPerm);
				usedSet.add(tempPerm);
			}
		}

		if ((zeroIndex-1) >= horL && (zeroIndex-1) <= horG)  //condition for left move
		{
			node* tempPerm = new node;
			tempPerm->parent = trav;
			
			tempPerm->array[zeroIndex] = trav->array[zeroIndex - 1];
			tempPerm->array[zeroIndex - 1] = 0;

			for (int i = 0; i < arrSize; i++)
			{
				if (i == zeroIndex || i == (zeroIndex - 1))
					continue;

				tempPerm->array[i] = trav->array[i];
			}

			if (!usedSet.search(tempPerm->array))
			{
				
				if (solved(tempPerm))
					return true;

				queue.add(tempPerm);
				usedSet.add(tempPerm);
			}
		}

		if ((zeroIndex + 3) >= 0 && (zeroIndex + 3) <= 8)  //condition for up move
		{
			node* tempPerm = new node;
			tempPerm->parent = trav;
			
			tempPerm->array[zeroIndex] = trav->array[zeroIndex + 3];
			tempPerm->array[zeroIndex + 3] = 0;

			for (int i = 0; i < arrSize; i++)
			{
				if (i == zeroIndex || i == (zeroIndex + 3))
					continue;

				tempPerm->array[i] = trav->array[i];
			}

			if (!usedSet.search(tempPerm->array))
			{
				
				if (solved(tempPerm))
					return true;
				
				queue.add(tempPerm);
				usedSet.add(tempPerm);
			}
		}

		if ((zeroIndex - 3) >= 0 && (zeroIndex - 3) <= 8)   //condition for down move
		{
			node* tempPerm = new node;
			tempPerm->parent = trav;
			
			tempPerm->array[zeroIndex] = trav->array[zeroIndex - 3];
			tempPerm->array[zeroIndex - 3] = 0;

			for (int i = 0; i < arrSize; i++)
			{
				if (i == zeroIndex || i == (zeroIndex - 3))
					continue;

				tempPerm->array[i] = trav->array[i];
			}


			if (!usedSet.search(tempPerm->array))
			{
				if (solved(tempPerm))
					return true;
				
				queue.add(tempPerm);
				usedSet.add(tempPerm);
			}
		}

		return false;
	}

	bool solved(node *perm) //function to check for final state and print the moves inorder
	{
		for (int i = 0; i < 9; i++)
		{
			if (perm->array[i] != i)
				return false;
		}

		node *temp = perm;
		set solveMoves;
		
		while (temp != NULL)
		{
			solveMoves.add(temp);
			temp = temp->parent;
		}

		system("cls");
		cout << "\n The steps to solve are :";
		solveMoves.dispPuzzle();

		return true;
	}

	void input()  //function to take users input for initial state
	{
		dispPuzzle(root->array);

		int temp;
		bool repeat = false;

		for (int i = 0; i < arrSize; i++)
		{	
			cout << "\n Enter numb for position " << i<<" (0 for gap) : ";
			cin >> temp;

			repeat = false;

			for (int i = 0; i < arrSize; i++)
			{
				if (temp == root->array[i])
				{
					repeat = true;
					break;
				}
			}

			if (repeat == true || temp < 0 || temp>8)
			{
				cout << " \n Repeated value or value less than 0 or greater than 8 \n\n ";
				i--;
				system("pause");
				system("cls");
				dispPuzzle(root->array);
				continue;
			}

			else
				this->root->array[i] = temp;

			system("cls");
			dispPuzzle(root->array);
		}
	}

	void findSteps() //function to call queue and dequeue
	{
		if (!checkSolvability(this->root->array))
		{
			cout << "\n The given puzzle is not solvable because it has odd no of inversions";
			return;
		}
		
		queue.add(this->root);
		usedSet.add(this->root);

		node* current;

		while (true)
		{
			current = queue.top();
			queue.dequeue();

			if (this->getPermutations(current))
				break;

			system("cls");
			cout << endl;
			cout << "\n Processing..";
			cout << "\n Queued = " << queue.setSize;
			cout << "\n visited = " << usedSet.setSize;

		}
	}
public:

	graph()
	{
		arrSize = 9;

		root = new node;

		for (int i = 0; i < arrSize; i++)
		{
			root->array[i] = -1;
		}
	}

	~graph()
	{

	}

	void menu()
	{
		this->input();
		this->findSteps();
	}
};

int main()
{
	graph obj;
	obj.menu();
}

