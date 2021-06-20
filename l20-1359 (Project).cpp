#include <iostream>
#include <fstream>

using namespace std;


class Helper // FOR ASSISTANCE IN THE OVERALL CODE 
{

public:

	static int StringLenght(char* str)
	{	// TO DETREMINE THE LENGTH OF THE STRING
		int strlen = 0;
		for (char* i = str; *i != '\0'; i++)
		{
			strlen++;
		}
		return strlen;
	}

	static char* GetStringFromBuffer(char* str)
	{
		// USED IN ORDER TO ALLOCATE MEMORY TO A POINTER FROM THE HEAP
		// RETURNS ARRAY WITH THE SIZE SIZE REQUIRES( NO EXTRA SPACE USED)
		int strlen = StringLenght(str) + 1;
		char* arr = new char[strlen];

		char* set = arr;
		for (char* i = str; *i != '\0'; i++, set++)
		{
			*set = *i;
		}
		*set = '\0';

		return arr;
	}

	static char* StringConcatenate(char* str1, char* str2)
	{
		// USED IN ORDER TO MERGE TO STRINGS TO CHAR POINTERS
		int strlen1 = StringLenght(str1);
		int strlen2 = StringLenght(str2);
		int size = strlen1 + strlen2;

		char* temp = new char[size + 2];
		for (int i = 0; i < strlen1; i++)
		{
			temp[i] = str1[i];
		}

		temp[strlen1] = ' ';
		for (int i = strlen1 + 1, j = 0; i < size + 1; i++, j++)
		{
			temp[i] = str2[j];
		}
		temp[size + 1] = '\0';

		str1 = GetStringFromBuffer(temp);

		delete[] temp;
		temp = 0;

		return str1;
	}

	static bool SearchString(char* str1, char* searchString)
	{
		// RETURNS TRUE IF THE THE TWO VALUES IN THE PARAMETERS MATCH
		int strlen1 = Helper::StringLenght(str1);
		int strlen2 = Helper::StringLenght(searchString);

		if (strlen1 != strlen2)
		{
			return false;
		}
		for (int i = 0; i < strlen1; i++)
		{
			if (str1[i] != searchString[i])
			{
				return false;
			}
		}
		return true;
	}
};

class Books // STORES DATA OF INDIVIDUAL BOOKS
{

private:

	char* ID;
	char* Name;
	char* Type;
	char* Author;
	bool Availability;


public:
	Books()
	{
		//CONSTRUCTOR
		ID = 0;
		Name = 0;
		Type = 0;
		Author = 0;
		Availability = true;
	}

	~Books()
	{
		//DESTRUCTOR
		if (ID)
		{
			delete ID;
			ID = 0;
		}

		if (Name)
		{
			delete Name;
			Name = 0;
		}

		if (Type)
		{
			delete Type;
			Type = 0;
		}

		if (Author)
		{
			delete Author;
			Author = 0;
		}
	}



	char* getID()
	{
		return ID;
	}

	char* getName()
	{
		if(Name)
		{
			return Name;
		}
		
	}

	void setAvailability(bool temp)
	{
		Availability = temp;
	}

	bool getAvailability()
	{
		return Availability;
	}

	void Loading(ifstream& input)
	{
		// LOADS ALL THE DATA IN THE FILE TO THE RESPECTIVE FIELDS
		char _ID[10], _Name[50], _Type[50], _Author[50], _Availability[50];
		//TEMPORARY VARIABLES FOR INPUT

		input >> _ID;
		input.ignore();
		input.getline(_Name, 50, '\t');
		input.getline(_Type, 50, '\t');
		input.getline(_Author, 50, '\t');
		input.getline(_Availability, 50);

		// ALLOCATING MEMORY TO FIELDS IN THE CLASS
		ID = Helper::GetStringFromBuffer(_ID);
		Name = Helper::GetStringFromBuffer(_Name);
		Type = Helper::GetStringFromBuffer(_Type);
		Author = Helper::GetStringFromBuffer(_Author);
		int length = Helper::StringLenght(_Availability);
		if (length == 9) // CHECKS IF THE STRING IS 'AVAILABLE' AS IT IS OF 9 WORDS
		{
			Availability = true;
		}
		else // OTHER WORD CAN BE 'UNAVAILABLE' WHICH HAS 11 LETTERS
		{
			Availability = false;
		}
	}

	void AddABook()
	{
		// THIS FUNCTIONS ADDS A BOOK TO THE TO THE NEW BOOK POINTER CREATED IN THE LIBRARY 

		char _ID[10], _Name[50], _Type[50], _Author[50];
		//TEMPORARY VARIABLES FOR INPUT

		cout << "Please Enter New Book's ID: ";
		cin >> _ID;
		cin.ignore();
		cout << "Please Enter New Book's Name: ";
		cin.getline(_Name, 50);
		cout << "Please Enter New Book's Type: ";
		cin.getline(_Type, 50);
		cout << "Please Enter New Book's Author: ";
		cin.getline(_Author, 50);

		// ALLOCATING MEMORY TO FIELDS IN THE CLASS
		ID = Helper::GetStringFromBuffer(_ID);
		Name = Helper::GetStringFromBuffer(_Name);
		Type = Helper::GetStringFromBuffer(_Type);
		Author = Helper::GetStringFromBuffer(_Author);
		Availability = true; // WHEN BOOK WILL BE ADDED IT BE AVAILBALE BY DEFAULT
	}

	void EditABook()
	{
		// THIS FUNCTIONS PROVIDES THE CONVINIENCE TO CHANGE ONE CHARACTERSISTIC OF THE BOOK

		int num = 0;


		cout << "Edit Book:\n";
		// USER HAS 4 OPTIONS TO CHOOSE AND CHANGE
		cout << "Select 1 for Unique Code\nSelect 2 for Name of the Book\nSelect 3 for Type/Genre\nSelect 4 for Author\nPlease Choose: ";
		cin >> num;

		if (num == 1) // IF USER WANTS TO CHANGE ID
		{
			char _temp[5];
			cout << "Enter new ID: ";
			cin >> _temp;

			delete[] ID;
			ID = Helper::GetStringFromBuffer(_temp);
		}

		cin.ignore();
		if (num == 2) // IF USER WANTS TO CHANGE NAME
		{
			char _Name[50];
			cout << "Enter new Book Name: ";
			cin.getline(_Name, 50);

			delete[] Name;
			Name = Helper::GetStringFromBuffer(_Name);
		}

		if (num == 3) // IF USER WANTS TO CHANGE TYPE
		{
			char _Type[50];
			cout << "Enter new Type Name: ";
			cin.getline(_Type, 50);

			delete[] Type;
			Type = Helper::GetStringFromBuffer(_Type);
		}

		if (num == 4) // IF USER WANTS TO CHANGE AUTHOR
		{
			char _Author[50];
			cout << "Enter new Author's Name: ";
			cin.getline(_Author, 50);

			delete[] Author;
			Author = Helper::GetStringFromBuffer(_Author);
		}


	}

	void printListissue()
	{
		// PRINTS ALL THE INFORMATION REGARDING THE PARTICULAR BOOK WHEN ISSUING
		cout << ID << "\t";
		cout << Name << "\t";
		cout << Type << "\t";
		cout << Author << "\t";
		if (Availability) // CHECKS WHETHER THE BOOKS IS AVAILABLE TO PRINT THE STATUS
		{
			cout << "Available";
		}
		else // OTHERWISE PRINTS 'UNAVAILABLE'
		{
			cout << "UnAvailable";
			cout << "\nSorry You Cannot Issue This Book";
		}

		cout << endl;

	}

	void printListreturn()
	{
		// PRINTS ALL THE INFORMATION REGARDING THE PARTICULAR BOOK WHEN RETURNING
		cout << ID << "\t";
		cout << Name << "\t";
		cout << Type << "\t";
		cout << Author << "\t";
		if (Availability) // CHECKS WHETHER THE BOOKS IS AVAILABLE TO PRINT THE STATUS
		{
			cout << "Available";
		}
		else // OTHERWISE PRINTS 'UNAVAILABLE'
		{
			cout << "UnAvailable";
			cout << "\nThank You for returning the book";
		}

		cout << endl;
	}

	void OutputFile(ofstream& output)
	{
		// OUTPUTS ALL THE INFORMATION ABOUT A BOOK ONTO THE FILE 'Books.txt'
		output << ID << "\t";
		output << Name << "\t";
		output << Type << "\t";
		output << Author << "\t";
		if (Availability) // CHECKS WHETHER THE BOOKS IS AVAILABLE TO OUTPUTS THE STATUS
		{
			output << "Available" ;
		}
		else // OTHERWISE OUTPUTS 'UNAVAILABLE'
		{
			output << "UnAvailable" ;
		}

		output << endl;
	}


};


class User
{

private:
	char* ID;
	char* Name;
	char* Password;
	Books* issuedBooks;

public:
	User()
	{
		//CONSTRCTOR
		ID = 0;
		Name = 0;
		Password = 0;
		issuedBooks = NULL;

	}

	~User()
	{
		//DESTRUCTOR
		if (ID)
		{
			delete ID;
			ID = 0;
		}

		if (Name)
		{
			delete Name;
			Name = 0;
		}

		if (Password)
		{
			delete Password;
			Password = 0;
		}

		if (issuedBooks)
		{
			delete issuedBooks;
			issuedBooks = 0;
		}
	}

	char* getID()
	{
		return ID;
	}

	void setissuedBooks(Books* temp)
	{
		// SETS THE BOOKS ISSUED BY THE USER
		issuedBooks = temp;
	}

	void Loading(ifstream& input)
	{
		// LOADS ALL THE INFORMATION ABOUT A MEMBER FROM THE 'Members.txt'
		char _ID[50], _Name[50], _Password[50], _issuedBooks[50];
		//TEMPORARY VARIABLE FOR INPUT

		input >> _ID;
		input.ignore();
		input.getline(_Name, 50, '\t');
		input.getline(_Password, 50, '\t');

		// ALLOCATING MEMORY TO FIELDS IN THE CLASS
		ID = Helper::GetStringFromBuffer(_ID);
		ID = Helper::GetStringFromBuffer(_ID);
		Name = Helper::GetStringFromBuffer(_Name);
		Password = Helper::GetStringFromBuffer(_Password);
	}

	bool Authentication()
	{
		// CHECKS WHETHER THE PASSWORD USER ENTERS IS CORRENT 
		// IF YES RETURNS TRUE ELSE ASKS AGAIN TILL CORRECT PASSWORD IS ENTERED
		while (1)
		{
			char temp[15];
			cout << "Welcome " << Name << " To The Library\n";
			cout << "Please Enter Your Password: ";
			cin.ignore();
			cin.getline(temp, 15);

			if (Helper::SearchString(temp, Password)) // CHECKS IF USER'S PASSWORD AND THE PASSWORD ENTER MATCHES OR NOT
			{
				return true;
			}

			else // IF NOT PRINTS "Invalid Password!"
			{
				cout << "Invalid Password!\n";
				continue;
			}
		}

		return false;
	}

	void OutputFile(ofstream& output)
	{
		// OUTPUTS ALL THE INFORMATION ONTO THE 'Members.txt' FILE 
		char temp[50] = "No issued Books";
		char* _temp = Helper::GetStringFromBuffer(temp);
		output << ID << "\t";
		output << Name << "\t";
		output << Password;
		if(issuedBooks) // IS ELSE STATEMENT OUTPUTS THE ID OF THE BOOK THE USER HAS ISSUED
		{
			output << "\t" <<  issuedBooks->getID();
		}
		else // OTHERWISE PRINTS "No issued Books"
		{
			output << "\t" << _temp;
		}

		output << endl;
	}

	void SigningUp()
	{
		// FOR NEW MEMBER ENTERING INTO THE LIBRARY SYSTEM

		char _ID[10], _Name[50], _Password[50];
		//TEMPORARY VARIABLE FOR INPUT

		// SETTING USERNAME, ID AND PASSWORD
		cout << "Please Set Your Unique ID: ";
		cin >> _ID;
		cin.ignore();
		cout << "Please Enter Your Full Name: ";
		cin.getline(_Name, 50);
		cout << "Please Enter Your Password: ";
		cin.getline(_Password, 50);

		// ALLOCATING MEMORY TO FIELDS IN THE CLASS
		ID = Helper::GetStringFromBuffer(_ID);
		Name = Helper::GetStringFromBuffer(_Name);
		Password = Helper::GetStringFromBuffer(_Password);

	}

};

class Librarian
{
private:
	char* ID;
	char* username;
	char* password;

public:
	
	Librarian()
	{
		//CONSTRUCTOR
		ID = 0;
		username = 0;
		password = 0;
	}

	~Librarian()
	{
		//DESTRUCTOR

		if (ID)
		{
			delete ID;
			ID = 0;
		}

		if (username)
		{
			delete username;
			username = 0;
		}

		if (password)
		{
			delete password;
			password = 0;
		}
	}

	void Loading(ifstream& input)
	{
		// LOADS ALL THE INFORMATION ABOUT THE LIBRARIAN FROM 'Librarian.txt'

		char _ID[10], _username[50], _password[50];
		//TEMPORARY VARIABLE FOR INPUT
		input >> _ID;
		input.ignore();
		input.getline(_username, 50, '\t');
		input >> _password;

		// ALLOCATING MEMORY TO FIELDS IN THE CLASS
		ID = Helper::GetStringFromBuffer(_ID);
		username = Helper::GetStringFromBuffer(_username);
		password = Helper::GetStringFromBuffer(_password);
	}

	bool Authentication()
	{
		// CHECKS WHETHER THE PASSWORD LIBRARIAN ENTERS IS CORRENT 
		// IF YES RETURNS TRUE ELSE ASKS AGAIN TILL CORRECT PASSWORD IS ENTERED
		
		char _ID[5];
		char _password[50];
		
		cout << "Enter Your Unique ID: ";
		cin >> _ID;
		while (1)
		{
			if (Helper::SearchString(_ID, ID)) //CHECKS IF USER'S ID AND THE ID ENTER MATCHES OR NOT
			{
				cout << username << " Wlecome To Librarian Portal \n";
				cout << "Please Enter Your Password: ";
				cin >> _password;
				if (Helper::SearchString(_password, password)) //CHECKS IF USER'S PASSWORD AND THE PASSWORD ENTER MATCHES OR NOT
				{
					cout << "Authentiaction Successful!\n";
					return true;
				}

				else // IF NOT PRINTS "Invalid Password!"
				{
					cout << "Invalid Password!\n";
					continue;
				}
			}
			else // IF NOT PRINTS "Invalid ID!"
			{
				cout << "Invalid ID!\n";
				continue;
			}
		}

		return false;

	}
};

class Library
{
	Books** RecordofBooks;
	User** Members;
	Librarian* librarian;
	int totalBooks;
	int totalMembers;

public:

	Library()
	{
		//CONSTRUCTOR
		RecordofBooks = 0;
		Members = 0;
		librarian = 0;
		totalBooks = 0;
		totalMembers = 0;
	}

	~Library()
	{
		//DESTRUCTOR 

		if (RecordofBooks)
		{
			delete[] RecordofBooks;
			RecordofBooks = 0;
		}

		if (Members)
		{
			delete[] Members;
			Members = 0;
		}

		if (librarian)
		{
			delete librarian;
			librarian = 0;
		}

	}

	void LoadDataBooks()
	{
		// LOADS ALL THE INFORMATION ABOUT ALL THE BOOKS FROM "Books.txt"
		ifstream input("Books.txt");
		input >> totalBooks;

		RecordofBooks = new Books * [totalBooks];

		for (int i = 0; i < totalBooks; i++) // INITIALISING RecordofBooks
		{
			RecordofBooks[i] = new Books;
		}

		for (int i = 0; i < totalBooks; i++) // PRINTS ALL THE BOOKS ONE BY ONE BY LOOP
		{
			RecordofBooks[i]->Loading(input);
		}
	}

	void LoadDataMembers()
	{
		// LOADS ALL THE INFORMATION ABOUT ALL THE MEMBERS FROM "MembersData.txt"
		ifstream input("MembersData.txt");
		input >> totalMembers;

		Members = new User * [totalMembers];

		for (int i = 0; i < totalMembers; i++) // INITIALISING Members
		{
			Members[i] = new User;
		}

		for (int i = 0; i < totalMembers; i++) // PRINTS ALL THE BOOKS ONE BY ONE BY LOOP
		{
			Members[i]->Loading(input);

			char temp[50];
			input.getline(temp, 50);
			for (int j = 0; j < totalBooks; j++)
			{
				if (Helper::SearchString(temp, RecordofBooks[j]->getID())) // CHECKS WHETHER BOTH ID'S MATCH OR NOT
				{
					Members[i]->setissuedBooks(RecordofBooks[j]); // IF YES SETS THE MEMBERS
					break;
				}
				else
				{
					Members[i]->setissuedBooks(0); // ELSE SETS 0
				}
			}
		}
	}

	void LoadLibrarianData()
	{
		// LOADS ALL THE INFORMATION ABOUT ALL THE MEMBERS FROM "LibrarianData.txt"
		ifstream input("LibrarianData.txt");

		librarian = new Librarian;
		librarian->Loading(input); // SETS ID, NAME AND PASSWORD OF THE LIBRARIAN

	}

	bool LibrarianAuthentication()
	{
		// VERIFIES WHTHER THE PASSWORD WILL BE CORRECT OR NOT
		return librarian->Authentication();

	}

	void AddABook()
	{
		// THIS FUNCTION ADDS BOOKS TO THE BOOK LIST
		totalBooks++; //INCREMENT

		Books** temp = new Books * [totalBooks]; // CREATING A BIGGER ARRAY OF SIZE + 1 TO ACCOMODATE THE NEW BOOK 
		for (int i = 0; i < totalBooks - 1; i++) // DEEP COPYING ALL THE VALUES ONTO TEMP
		{
			temp[i] = RecordofBooks[i];
		}
		delete[] RecordofBooks; // DELETING THE PREVIOUS ORIGINAL ONE
		RecordofBooks = temp;	// POINTING IT TOWARDS THE NEW CREATED ONE (TEMP)

		RecordofBooks[totalBooks - 1] = new Books; // INITIALISES ADDITIONAL SPACE REQUIRED TO ACCODATE EXTRA BOOK
		RecordofBooks[totalBooks - 1]->AddABook(); // ADDS ALL THE DETAILS

	}

	void RemoveABook()
	{
		// THIS FUNCTION ADDS BOOKS TO THE BOOK LIST
		char temp[5];
		cout << "Please Enter ID you want to remove: ";
		cin >> temp;

		int i;
		for (i = 0; i < totalBooks; i++)
		{
			char* _ID = RecordofBooks[i]->getID();
			if (Helper::SearchString(temp, _ID)) // CHECKS WHETHER THE ID ENTERED MATCHES THE EXISTING ONE
			{
				delete RecordofBooks[i]; // DELETEING THE POINTER WHEN FOUND
				RecordofBooks[i] = RecordofBooks[i + 1]; // AND POINTING IT TOWARDS THE NEXT ONE
				break;
			}
		}
		totalBooks--; // DECREMENT

		for (int j = i + 1; j < totalBooks; j++) 
		{
			RecordofBooks[j] = RecordofBooks[j + 1]; // POINTING THE REMAINING POINTERS TO THE NEXT ONE
		}

		Books** _temp = new Books * [totalBooks]; // CREATING A BIGGER ARRAY OF SIZE - 1 AS NOW LESS SPACE IS REQUIRED
		for (int i = 0; i < totalBooks ; i++)	  // DEEP COPYING ALL THE VALUES ONTO TEMP
		{
			_temp[i] = RecordofBooks[i];
		}
		delete[] RecordofBooks; // DELETING THE PREVIOUS ORIGINAL ONE
		RecordofBooks = _temp;  // POINTING IT TOWARDS THE NEW CREATED ONE(TEMP)
	}

	void EditABook()
	{
		// THIS FUNCTION LETS THE LIBRARIAN CHANGE ANY ELEMENT OF A SPECIFIC BOOK
		char temp[5];
		cout << "Please Enter ID you want to Edit: ";
		cin >> temp;

		int i = 0;
		for (; i < totalBooks; i++)
		{
			char* _ID = RecordofBooks[i]->getID();
			if (Helper::SearchString(temp, _ID)) // CHECKS IF THE ID ENTERED MATCHES THE ID'S EXISTING
			{
				RecordofBooks[i]->EditABook(); // IF YES LETS THE LIBRARIAN MAKE CHANGES THROUGH A FUNCTION
				break;
			}

		}
	}

	void OutputList()
	{
		// OUTPUTS ALL THE INFORMATION OF THE BOOKS ONTO THE FILE "Books.txt"
		ofstream output("Books.txt");
		output << totalBooks << endl;

		for (int i = 0; i < totalBooks; i++)
		{
			RecordofBooks[i]->OutputFile(output);
		}
	}

	void OutputMembersList()
	{
		// OUTPUTS ALL THE INFORMATION OF THE MEMBERS ONTO THE FILE "MembersData.txt"
		ofstream output("MembersData.txt");
		output << totalMembers << endl;

		for (int i = 0; i < totalMembers; i++)
		{
			Members[i]->OutputFile(output);
		}

	}

	void MemberLogin(bool& check, int& memberindex)
	{
		// THIS FUNCTION INVOLVES LOGINA AND AUTHENTICATION
		cout << "Please Enter Your Unique ID: ";
		char temp[5];
		cin >> temp;
		for (int i = 0; i < totalMembers; i++)
		{
			if (Helper::SearchString(Members[i]->getID(), temp)) // CHECKS IF THE ID ENTERED MATCHES THE ID'S EXISTING
			{
				if (Members[i]->Authentication()) // CHECKS WHETHER THE PASSWORD ENTERED IS CORRECT OR NOT
				{
					cout << "Authentication Successful\n";
					check = true;
					memberindex = i;
					break;
				}
				else // ELSE PUTS AN ERROR MESSAGE
				{
					cout << "Password Does Not Match with the Current ID and Name\n";
					check = false;
					break;
				}
			}
		}

	}

	void MemberSignUp()
	{
		// PROVIDES FUNCTIONALITY TO LET ANOTHER MEMBER INTO THE SYSTEM
		totalMembers++;

		User** temp = new  User* [totalMembers]; // CREATING A BIGGER ARRAY OF SIZE + 1 TO ACCOMODATE THE NEW MEMBER
		for (int i = 0; i < totalMembers - 1; i++) // DEEP COPYING ALL THE VALUES ONTO TEMP
		{
			temp[i] = Members[i];
		}
		delete[] Members; // DELETING THE PREVIOUS ORIGINAL ONE
		Members = temp;	// POINTING IT TOWARDS THE NEW CREATED ONE (TEMP)

		Members[totalMembers - 1] = new User; // INITIALISES ADDITIONAL SPACE REQUIRED TO ACCODATE EXTRA BOOK
		Members[totalMembers - 1] -> SigningUp(); // ADDS ALL THE DETAILS


		cout << "-------------------------Issuing A Book-------------------------\n";
		IssuingABook(totalMembers - 1); //	NEW MEMBER ISSUING BOOK

	}

	void IssuingABook(int i)
	{
		// LETS THE LOGIN MEMBER ISSUE A BOOK
		char _ID[5];
		cout << "Enter the Id of the book you want to issue: ";
		cin >> _ID; // ASKS USER TO ENTER THE ID


		for (int j = 0; j < totalBooks; j++)
		{
			if (Helper::SearchString(RecordofBooks[j]->getID(), _ID)) // CHECKS IF THE ID ENTERED ENTERED MATCHES ANY EXISTING ONE
			{
				RecordofBooks[j]->printListissue(); // PRINTS THE RELEVANT DETAILS

				if (RecordofBooks[j]->getAvailability()) // CHECKS IF THE BOOK IS AVILABLE OR NOT
				{
					Members[i]->setissuedBooks(RecordofBooks[j]); // ISSUES THE BOOK
					RecordofBooks[j]->setAvailability(false); // SETS IT TO FALSE (NOT AVAILABLE)
					break;
				}
			}
		}
	}

	void ReturnABook(int i)
	{
		// LETS THE LOGIN MEMBER RETURN A BOOK
		char _ID[5];
		cout << "Enter the Id of the book you want to return: ";
		cin >> _ID; // ASKS USER TO ENTER THE ID


		for (int j = 0; j < totalBooks; j++)
		{
			if (Helper::SearchString(RecordofBooks[j]->getID(), _ID))  // CHECKS IF THE ID ENTERED ENTERED MATCHES ANY EXISTING ONE
			{
				RecordofBooks[j]->printListreturn(); // PRINTS THE RELEVANT DETAILS

				if (!(RecordofBooks[j]->getAvailability())) // CHECKS IF THE BOOK IS AVILABLE OR NOT
				{
					Members[i]->setissuedBooks(0);
					RecordofBooks[j]->setAvailability(true); // SETS IT TO FALSE (NOT AVAILABLE)
					break;
				}
			}
		}
	}

};


void main()
{
	Library A;
	A.LoadDataBooks(); // LAODS BOOKS
	A.LoadDataMembers(); // LOADS MEMBERS
	A.LoadLibrarianData(); // LOAD LIBRARIAN DATA

	int option;
	while (1)
	{
		system("CLS");
		cout << "-------------------------WELCOME TO THE MAIN MENU-------------------------\n";
		cout << "1.Librarian\n";
		cout << "2.Member\n";
		cout << "3.Exit\n";
		cout << "Please Select from the Options: ";
		cin >> option;
		if (option == 1)
		{

			if (A.LibrarianAuthentication())
			{
					int choice;
					cout << "-------------------------Librarian Portal-------------------------\n";
					cout << "1.Add A Book\n";
					cout << "2.Remove A Book\n";
					cout << "3.Edit A Book\n";
					cout << "4.Return to Main Menu\n";
					cout << "Please Select from the Options: ";
					cin >> choice;

					if (choice == 1)
					{
						cout << "-------------------------Adding A Book-------------------------\n";
						A.AddABook();
					}
					if (choice == 2)
					{
						cout << "-------------------------Removing A Book-------------------------\n";
						A.RemoveABook();
					}
					if (choice == 3)
					{
						cout << "-------------------------Editing A Book-------------------------\n";
						A.EditABook();
					}
					if (choice == 4)
					{
						continue;
					}
			}
		}

		if (option == 2)
		{
			int choice;
			cout << "-------------------------Member Portal-------------------------\n";
			cout << "1.Sign Up\n";
			cout << "2.Login\n";
			cout << "3.Return to Main Menu\n";
			cout << "Please Select from the Options: ";
			cin >> choice;

			if (choice == 1)
			{
				cout << "-------------------------Signing Up-------------------------\n";
				A.MemberSignUp();
			}
			if (choice == 2)
			{
				cout << "-------------------------Login In Page-------------------------\n";
				bool check = false;
				int memberindex= -1;
				A.MemberLogin(check, memberindex);
				if (!check)
				{
					break;
				}
				if (check)
				{
					int n;
					cout << "1.Issuing A Book\n";
					cout << "2.Returning A Book\n";
					cout << "Please Select from the Options: ";
					cin >> n;

					if (n == 1)
					{
						cout << "-------------------------Issuing A Book-------------------------\n";
						A.IssuingABook(memberindex);
					}

					if (n == 2)
					{
						cout << "-------------------------Returning A Book-------------------------\n";
						A.ReturnABook(memberindex);
					}

				}
			}
			if (choice == 3)
			{
				continue;
			}
		}

		
		if (option == 3)
		{
			cout << "------------------------THANK YOU-------------------------\n";
			A.OutputList(); // OUTPUTS BOOKS DATA ONTO 'Books.txt' BY OVERWRITING THE PREVOUS FILE
			A.OutputMembersList(); // OUTPUTS BOOKS Members ONTO 'Members.txt' BY OVERWRITING THE PREVOUS FILE
			break;
		}





		A.OutputList(); // OUTPUTS BOOKS DATA ONTO 'Books.txt' BY OVERWRITING THE PREVOUS FILE
		A.OutputMembersList(); // OUTPUTS BOOKS Members ONTO 'Members.txt' BY OVERWRITING THE PREVOUS FILE
	}




	system("pause");
}
