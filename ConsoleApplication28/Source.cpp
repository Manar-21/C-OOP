#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>      //   write & read files
#include <sstream>      //   convert number of string to integer
using namespace std;

class Admin {
protected:
	string username;
	string password;
public:
	int  Choice;
	void admin_login();
	void admin_view();
};

class Book : public Admin{
protected:
	string Id;
	string Department;
	string Title;
	string Author;
public:
	string department, id, title, author;
	char ch;
	void create_Book();
};

class Student : public Book{
protected:
	string user_Name;
	string passward;
	int    num_borr;
private:
	string  name, pass;
	int  num_borr2;
	bool flag = false;
public:
	void student_login();
	void student_View();
	void create_Student();
	void borrow();
	void br();
	void cr_St();
	void check_out();
};

void Admin::admin_login(){
	system("cls");
	cout << "\n --------- Admin Login --------\n";
	cout << "\n Enter username : ";
	cin  >> username;
	cout << "\n Enter password : ";
	cin  >> password;
	if (username == "manar" && password == "manar@21")
		admin_view();
	else{
		cout << "\n Error ! Invalid Credintials..";
		cout << "\n Press any key for main menu ";
		getchar(); getchar();
	}
}

void Admin::admin_view(){
	system("cls");
	cout << "\n 1 Register a Student";
	cout << "\n 2 Add a new book ";
	cout << "\n 3 Exit ";
	cout << "\n 0 Go Back  \n";
	cout << "\n Enter you choice: ";
	cin >> Choice;
	if (Choice == 1){
		Student st;
		st.create_Student();
	}
	else if (Choice == 2){
		Book bk;
		bk.create_Book();
	}
	else if (Choice == 3)
		exit(0);
	else if (Choice == 0);
	else{
		cout << "\n Invalid choice !!!";
		getchar(); getchar();
	}
}

void Book::create_Book(){
	system("cls");
	cout << "\n -------- Add a new book -------- \n\n";
	fstream ofile2("Book.txt", ios::in);     // "in" to read 
	int i = 0;
	cout << "Department .. ";
	cin  >> Department;
	cout << "Title of Book .. ";
	cin  >> Title;
	cout << "Name of Author .. ";
	cin  >> Author;
	while (!ofile2.eof()){
		ofile2 >> department >> id >> title >> author;
		Id = id;
	}
	ofile2.close();
	stringstream ob(Id);                                // The object has the value of Id and stream 
	ob >> i;                                            // it to the integer x 
	fstream ofile3("Book.txt", ios::app);               // "app" to append 
	i++;
	ofile3 << "\n" << setw(11) << Department << setw(9) << i << setw(50) << Title << setw(65) << Author << "\n";
	cout << "\n...Registration completed successfully \n\n";
	cout << "Do you want to add other Book!  y | n \n";
	cin  >> ch;
	if (ch == 'y')
		create_Book();
	else if (ch == 'n'){
		ofile3.close();
		admin_view();
	}
	else{
		cout << "\n Invalid choice !!!";
		getchar();
	}
}

void Student::create_Student(){
	system("cls");
	cout << "\n------- Register a Student -------\n\n";
	fstream ofile1("Student.txt", ios::app | ios::in);     // "app" to append , "in" to read 
	cout << "\nEnter The User Name of The Student \"must be without a separator\"\n";
	cin  >> user_Name;
	cout << "\nEnter The Passward of The Student \"must be without a separator\"\n";
	cin  >> passward;
	cr_St();
	ofile1 << "\n" << setw(20) << user_Name << setw(20) << passward << setw(5) << 0;
	cout << "\n...Registration completed successfully \n\n";
	cout << "Do you want to add another student!  y | n \n";
	cin  >> ch;
	if (ch == 'y')
		create_Student();
	else if (ch == 'n'){
		ofile1.close();
		admin_view();
	}
	else{
		cout << "\n Error ! Invalid Credintials..";
		cout << "\n Press any key for main menu ";
		getchar(); getchar();
		admin_view();
	}
}

void Student::cr_St(){
	fstream ofile("Student.txt", ios::app | ios::in);     // "app" to append , "in" to read 
	while (!ofile.eof()){
		ofile >> name >> pass >> num_borr;
		if (user_Name == name){
			cout << "\nUsername already used, Please enter another .\n";
			cout << "\nEnter another User Name of the Student \n";
			cin  >> user_Name;
			cout << "\nEnter another Passward of the Student \n";
			cin  >> passward;
			cr_St();
		}
	}
	if ((user_Name.length() > 18 ) || (pass.length() > 18)){
		cout << "\nSorry, please again ";
		create_Student();
	}
}

void Student::student_login(){
	system("cls");
	cout << "\n -------- Student Login ---------\n";
	bool flag = false;
	fstream ofile1("Student.txt", ios::in);     //  "in" to read file 
	cout << "\n Enter username : ";
	cin  >> user_Name;
	cout << "\n Enter password : ";
	cin  >> passward;
	while (!ofile1.eof()){
		ofile1 >> name >> pass >> num_borr;
		if (user_Name == name && passward == pass){
			cout << "\nRegistration completed successfully \n";
			flag = true;
			cout << "\n Press any key for main menu ";
			getchar(); getchar();
			student_View();
			break;
		}
	}
	if (flag == false)
		cout << "\nUsername or password error \n";
	ofile1.close();
	cout << "\n Press any key for main menu ";
	getchar(); getchar();
}

void Student::student_View(){
	ifstream ofile1("Student.txt", ios::in);	       //  "in" to read file 
	system("cls");
	cout << "1 Borrow a Book \n";
	cout << "2 The Number of Book Metaphors \n";
	cout << "3 Check out! \n";
	cout << "4 Exit \n";
	cout << "0 Go Back  \n";
	cout << "\n Enter you choice: ";
	cin >> Choice;
	if (Choice == 1)
		borrow();
	else if (Choice == 2){
		system("cls");
		while (!ofile1.eof()){
			ofile1 >> name >> pass >> num_borr;
			if (user_Name == name && passward == pass){
				cout << "\nThe number of borrowed books : " << num_borr2;
				cout << "\n Press any key for main menu ";
				getchar(); getchar();
				student_View();
			}
		}
	}
	else if (Choice == 3)
		check_out();
	else if (Choice == 4)
		exit(0);
	else if (Choice == 0);
	else{
		cout << "\n Invalid choice !!!";
		getchar();
	}
}

void Student::borrow(){
	system("cls");
	cout << " \n-------- Borrow a Book --------\n\n";
	fstream ofile2("Book.txt", ios::in);     //  "in" to read 
	cout << " 1- Action \n 2- Fiction \n 3- History \n 4- Novels \n 5- Science \n 6- Programming\n\n";
	cout << " Enter the name of the Department  :  ";
	cin  >> Department;
	cout << "\n\n  num.  " << "		  Title				       Author \n\n";
	while (!ofile2.eof()){
		ofile2 >> department >> id >> title >> author;
		if (department == Department){
			cout << setw(3)<<Choice << "  .  " << setw(40) << title << setw(40) << author << "\n";
			Choice++;
			flag = true;
		}
	}
	if (flag == false){
		cout << "Sorry, Department of " << Department << " not found \n";
		cout << "Do you want to search for another department ?  y | n \n";
		cin  >> ch;
		if (ch == 'y' || 'Y')
			borrow();
		else if (ch == 'n' || 'N')
			student_View();
		else{
			cout << "\n Invalid choice. Enter again ";
			getchar(); getchar();
		}
	}
	else{
		br();
		cout << "\n You borrowed \"" << num_borr << "\" books \n";
	}
	cout << "\n Press any key for main menu ";
	getchar(); getchar();
	student_View();
}

void Student::br(){
	ifstream ofile1("Student.txt", ios::in);	       //  "in" to read file 
	ofstream ofile("Student1.txt", ios::app);          //  "app" to write in file
	int  x,j = 0;
	cout << "\nChoose the numbers of the books you want to borrow.  The numbers must be consecutive without a break as \"123\"\n";
	cin  >> Choice;
	while (Choice > 0)
	{
		x = Choice % 10;
		j++;
		x = Choice - x;
		Choice = x;
		Choice = Choice / 10;
	}
	num_borr2 = j;
	while (!ofile1.eof()){
		ofile1 >> name >> pass >> num_borr;
		if (user_Name == name && passward == pass){
			ofile << setw(14) << name << setw(14) << pass << setw(5) << j << "\n";
			cout << "\n you borrowed " << j <<" book/s.";
		}
		else
			ofile << setw(14) << name << setw(14) << pass << setw(5) << num_borr << "\n";
	}
	ofile1.close();
	ofile.close();
	remove("Student.txt");
	rename("Student1.txt", "Student.txt");
	cout << "\n Press any key for main menu ";
	getchar(); getchar();
	student_View();
}

void Student::check_out(){
	system("cls");
	cout << "Sign out successful.. \n";
	ifstream ofile1("Student.txt", ios::in);	       //  "in" to read file 
	ofstream ofile("Student1.txt", ios::app);          //  "app" to write in file
	while (!ofile1.eof()){
		ofile1 >> name >> pass >> num_borr;
		if (user_Name != name){
			flag = true;
			ofile << setw(14) << name << setw(14) << pass << setw(5) << num_borr << "\n";
		}
	}
	ofile1.close();
	ofile.close();
	remove("Student.txt");
	rename("Student1.txt", "Student.txt");
	cout << "\n Press any key for main menu ";
	getchar(); getchar();
}

void main(){	
	Student st;
	Admin admen;
	while (1){
		system("cls");
		cout << "\n Library Management System \n";
		cout << "-------------------------------------\n\n";
		cout << "1. Admin Login\n";
		cout << "2. Student Login\n";
		cout << "0. Exit\n";
		int choice;
		cout << "\n Enter you choice: ";
		cin  >> choice;
		switch (choice){
		case 1: admen.admin_login();
			break;
		case 2: st.student_login();
			break;
		case 0:
			while (1){
				system("cls");
				cout << "\n Are you sure, you want to exit? y | n \n";
				char ex;
				cin >> ex;
				if (ex == 'y' || ex == 'Y')
					exit(0);
				else if (ex == 'n' || ex == 'N')
					break;
				else{
					cout << "\n Invalid choice !!!";
					getchar();
				}
			}
			break;
		default: cout << "\n Invalid choice. Enter again ";
			getchar(); 
		}
	}
}