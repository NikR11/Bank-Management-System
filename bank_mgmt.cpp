//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
 
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cctype>
using namespace std;
 
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
 
class account
{
    long acno;
    char name[100];
    float balance;
    char type;
public:
    void create_account();  //function to get data from user
    void show_account() const;  //function to show data on screen
    void modify();  //function to add new data
    void dep(float);  //function to accept amount and add to balance amount
    void draw(float); //function to accept amount and subtract from balance amount
    void report() const;    //function to show data in tabular format
    int retacno() const;    //function to return account number
    float retbalance() const; //function to return balance amount
    char rettype() const;   //function to return type of account
                            /*
     * Write the member variables to stream objects
     */
    friend std::ostream &operator<<(std::ostream &out, const account &obj)
    {
        out << obj.acno << " "<< obj.name << " "<< obj.type << " "<< obj.balance << "\n";
        return out;
    }
    /*
     * Read data from stream object and fill it in member variables
     */
    friend std::istream &operator>>(std::istream &in, account &obj)
    {
        in >> obj.acno;
        in >> obj.name;
        in >> obj.type;
        in >> obj.balance;
        return in;
    }
};         //class ends here
 
void account::create_account()
{
    std::cout<<"\nEnter The account No. : "; std::cin>>acno;
    std::cout<<"\n\nEnter The Name of The account Holder : ";
    std::cin.ignore();
    std::cin.getline(name,100);
    std::cout<<"\nEnter the Type of account ('C' for Current, 'S' for Savings) : "; std::cin>>type;
    type=toupper(type);
    while(!(type=='C'||type=='S'))
    {
        std::cout<<"Invalid input, Re-enter";
        std::cout << "\nEnter the Type of account ('C' for Current, 'S' for Savings) : ";
        std::cin >> type;
        type = toupper(type);
    }
    std::cout<<"\nEnter The Initial amount(>=500 for Savings and >=1000 for Current ) : ";
    std::cin>>balance;
    while(!((type=='C'&&balance>=1000.0)||(type=='S'&&balance>=500.0)))
    {
        std::cout<<"\nInvalid input, Re-enter";
        std::cout << "\nEnter The Initial amount(>=500 for Savings and >=1000 for Current ) : ";
        std::cin >> balance;
    }
    std::cout<<"\n\n\nAccount Created..";
}
 
void account::show_account() const
{
    std::cout<<"\nAccount No. : "<<acno;
    std::cout<<"\nAccount Holder Name : "<<name;
    std::cout<<"\nType of Account : "<<type;
    std::cout<<"\nBalance amount : "<<balance;
}
 
 
void account::modify()
{
    std::cout<<"\nAccount No. : "<<acno;
    std::cout<<"\nModify Account Holder Name : ";
    std::cin.ignore();
    std::cin>>name;
    std::cout<<"\nModify Type of Account : "; std::cin>>type;
    type=toupper(type);
    while (!(type == 'C' || type == 'S'))
    {
        std::cout << "Invalid input, Re-enter";
        std::cout << "\nEnter the Type of account ('C' for Current, 'S' for Savings) : ";
        std::cin >> type;
        type = toupper(type);
    }
    }
 
     
void account::dep(float x)
{
    balance+=x;
}
     
void account::draw(float x)
{
    balance-=x;
}
     
void account::report() const
{
    std::cout<<acno<<setw(10)<<" "<<name<<setw(14)<<" "<<type<<setw(10)<<balance<<endl;
}
     
int account::retacno() const
{
    return acno;
}
 
float account::retbalance() const
{
    return balance;
}
 
char account::rettype() const
{
    return type;
}
 
 
//***************************************************************
//      function declaration
//****************************************************************
void write_account();   //function to write record in binary file
void display_sp(long);   //function to display account details given by user
void modify_account(long);   //function to modify record of file
void delete_account(long);   //function to delete record of file
void display_all();     //function to display all account details
void deposit_withdraw(long, int); // function to desposit/withdraw amount for given account
void intro();   //introductory screen function
 
//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************
 
int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        std::cout<<"\n\tMAIN MENU";
        std::cout<<"\n\n\t01. NEW ACCOUNT";
        std::cout<<"\n\n\t02. DEPOSIT AMOUNT";
        std::cout<<"\n\n\t03. WITHDRAW AMOUNT";
        std::cout<<"\n\n\t04. BALANCE ENQUIRY";
        std::cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        std::cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        std::cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        std::cout<<"\n\n\t08. EXIT";
        std::cout<<"\n\n\tSelect Your Option (1-8): "; std::cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            std::cout<<"\n\n\tEnter The account No. : "; std::cin>>num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            std::cout<<"\n\n\tEnter The account No. : "; std::cin>>num;
            deposit_withdraw(num, 2);
            break;
        case '4': 
            std::cout<<"\n\n\tEnter The account No. : "; std::cin>>num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            std::cout<<"\n\n\tEnter The account No. : "; std::cin>>num;
            delete_account(num);
            break;
         case '7':
            std::cout<<"\n\n\tEnter The account No. : "; std::cin>>num;
            modify_account(num);
            break;
         case '8':
            std::cout<<"\n\n\tThanks for using this Bank Managemnt System";
            break;
         default :std::cout<<"\nIncorrect Choice";
        }
        std::cin.ignore();
        std::cin.get();
    }while(ch!='8');
    return 0;
}
 
 
//***************************************************************
//      function to write in file
//****************************************************************
 
void write_account()
{
    account ac;
    ofstream outFile,oFile;
    outFile.open("account.txt",ios::out|ios::app);
    oFile.open("readableAccount.txt",ios::out|ios::app);
    ac.create_account();
    outFile.write((char *)&ac, sizeof(ac));
    oFile << ac;
    outFile.close();
    oFile.close();
}
 
//***************************************************************
//      function to read specific record from file
//****************************************************************
 
void display_sp(long n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.txt",ios::in);
    if(!inFile)
    {
        std::cout<<"File could not be open !! Press any Key...";
        return;
    }
    std::cout<<"\nBALANCE DETAILS\n";
    while (inFile.read((char *)&ac, sizeof(ac)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        std::cout<<"\n\nAccount number does not exist";
}
 
 
//***************************************************************
//      function to modify record of file
//****************************************************************
 
void modify_account(long n)
{
    bool found=false;
    account ac;
    fstream File;
    ifstream i;
    ofstream o;
    File.open("account.txt",ios::in|ios::out);
    if (!File)
    {
        std::cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read((char *)&ac, sizeof(ac));
        if(ac.retacno()==n)
        {
            ac.show_account();
            std::cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos = (-1) * (int)(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write((char *)&ac, sizeof(ac));
            i.open("readableAccount.txt", ios::in);
            size_t p;
            string line;
            while (getline(i, line))
            {
                p = line.find(n);
            }
            o.open("readableAccount.txt",ios::app);
            o.seekp(p, ios::beg);
            o << ac;
            o.close();
            std::cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    File.close();
    if(found==false)
        std::cout<<"\n\n Record Not Found ";
}
 
//***************************************************************
//      function to delete record of file
//****************************************************************
 
 
void delete_account(long n)
{
    account ac;
    ifstream inFile, rFile;
    ofstream outFile, wFile;
    inFile.open("account.txt",ios::in);
    rFile.open("readableAccount.txt",ios::in);
    if (!inFile)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    int flag = -1;
    outFile.open("temp.txt",ios::out);
    wFile.open("readableTemp.txt",ios::out);
    inFile.seekg(0, ios::beg);
    rFile.seekg(0, ios::beg);
    while (rFile >> ac)
    {
        if (ac.retacno() != n)
        {
            wFile << ac;
        }
    }
    while (inFile.read((char *)&ac, sizeof(ac)))
    {
        if (ac.retacno() != n)
        {
            outFile.write((char *)&ac, sizeof(ac));
        }
        else
            flag = 0;
    }
    inFile.close();
    rFile.close();
    outFile.close();
    wFile.close();
    remove("account.txt");
    remove("readableAccount.txt");
    rename("temp.txt", "account.txt");
    rename("readableTemp.txt", "readableAccount.txt");
    if (flag == 0)
        std::cout << "\n\n\tRecord Deleted ..";
    else
        std::cout << "\n\n\tAccount Not Found";
}

//***************************************************************
//      function to display all accounts deposit list
//****************************************************************
 
void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.txt",ios::in);
    if(!inFile)
    {
        std::cout<<"File could not be open !! Press any Key...";
        return;
    }
    std::cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    std::cout<<"====================================================\n";
    std::cout<<"A/c no.      NAME           Type  Balance\n";
    std::cout<<"====================================================\n";
    while (inFile.read((char *)&ac, sizeof(ac)))
    {
        ac.report();
    }
    inFile.close();
}
 
//***************************************************************
//      function to deposit and withdraw amounts
//****************************************************************
 
void deposit_withdraw(long n, int option)
{
    float amt;
    bool found=false;
    account ac;
    fstream File;
    ifstream i;
    ofstream o;
    File.open("account.txt",ios::in|ios::out);
    if(!File)
    {
        std::cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read((char *)&ac, sizeof(ac));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                std::cout<<"\n\n\tTO DEPOSIT AMOUNT ";
                std::cout<<"\n\nEnter The amount to be deposited\n"; std::cin>>amt;
                while(amt<0.0)
                {
                  std::cout<<"Incorrect Amount, Re-enter\n"; std::cin>>amt;
                }
                ac.dep(amt);
            }
            if(option==2)
            {
                std::cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                std::cout<<"\n\nEnter The amount to be withdrawn\n"; std::cin>>amt;
                while(amt<0)
                {
                    std::cout<<"Incorrect amount, Re-enter\n";
                    std::cin>>amt;
                }
                float bal=ac.retbalance()-amt;
                if((bal<500.0 && ac.rettype()=='S') || (bal<1000.0 && ac.rettype()=='C'))
                    std::cout<<"Insufficience balance";
                else
                    ac.draw(amt);
              }
              int pos = (-1) * (int)(sizeof(account));
              File.seekp(pos, ios::cur);
              File.write((char *)&ac, sizeof(ac));
              i.open("readableAccount.txt", ios::in);
              size_t p;
              string line;
              while (getline(i, line))
              {
                  p = line.find(n);
              }
              o.open("readableAccount.txt", ios::app);
              o.seekp(p, ios::beg);
              o << ac;
              o.close();
              std::cout << "\n\n\t Record Updated";
              found = true;
           }
         }
    File.close();
    if(found==false)
        std::cout<<"\n\n Record Not Found ";
}
 
 
//***************************************************************
//      INTRODUCTION FUNCTION
//****************************************************************
 
void intro()
{
    std::cout<<"\n\n\n\t  BANK";
    std::cout<<"\n\n\tMANAGEMENT";
    std::cout<<"\n\n\t  SYSTEM";
    std::cout<<"\n\n\n\nCreated By : Nikita Rai\n\n\t\tPress Enter to Continue";
    std::cin.get();
}
 
//***************************************************************
//              END OF PROJECT
//***************************************************************
