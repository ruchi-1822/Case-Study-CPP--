//Ruchi Chaturvedi
//Case Study: Book Shop Management System using File Handling

#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
 
class BOOK
{
  char title[20];
  char author[30]; 
  float price; 
  char publisher[30];
  int stock_position;
  
  public:
  int count = 0;
  BOOK()                   //default constructor
  {
    strcpy(title," ");
    strcpy(author," ");
    price=0.0;
    strcpy(publisher," ");
    stock_position=0;
    count=0;
  }
  
  char *rettit()          //Function to access title of the book
  {
      return title;
  }
  
  char *retaut()          //Function to access author of the book 
  {
      return author;
  }
  int retstk()
  {
      return stock_position;  //to access current stock availability
  }
  float retprice()
  {
      return price;          //to access price of the book
  }
  
  void get_details();        //Function to store details of a book
  void show_details();       //Function to show deatils of a book
  friend BOOK Search();      //Function to search a book
  friend void buy();        //Function to buy a book
  void listb();             //Function to see list of all the books available in the store
  void modify(int c);       //Functio to modify the stock position of a book
};

BOOK null_obj;              //An object with all null values is created
BOOK g_obj;                 //A global object is cerated 

void BOOK::get_details()    //Function defination to get details of a book
{
     cout<<"\nEnter BOOK Details: ";
     cout<<"\n Title: ";
     cin>>title;
     cout<<"Author name: ";
     cin>>author;
     cout<<"Price: ";
     cin>>price;
     cout<<"Publisher name: ";
     cin>>publisher;
     cout<<"Number of BOOKs Availabale: ";
     cin>>stock_position;
     count = count + 1;
}

void BOOK::show_details()    //Function defination to show details of a book
{
    cout<<setw(10)<<"\nBOOK Details are: ";
    cout<<setw(10)<<"\n S.NO. "<<count;
    cout<<setw(10)<<"\n Title: "<<title;
    cout<<setw(10)<<"\n Author name: "<<author;
    cout<<setw(10)<<"\n Price: "<<price;
    cout<<setw(10)<<"\n Publisher name: "<<publisher;
    cout<<setw(10)<<"\n Number of BOOKs Availabale: "<<stock_position;
}

void BOOK::listb()    //Function defination to shoe list of all available books
{
    cout<<setw(10)<<"\n Title: "<<title<<setw(10)<<"\n Author name: "<<author
    <<setw(10)<<"\n Number of BOOKs Availabale: "<<stock_position<<endl<<endl;
}

BOOK Search()    //Function defination to search details of a book
{
    char titl[30];
    char aut[30];
    int newf=0;
    int ch;
    
    cout<<"\nEnter BOOK Title : ";
    cin>>titl;
    cout<<"Enter AUthor's Name : ";
    cin>>aut;
    ifstream fin;
    fin.open("Bshop",ios::in);
    while(!fin.eof())
    {
       
        fin.read((char *)&g_obj, sizeof(BOOK));
        
        if((strcmp(g_obj.retaut(),aut)==0) && (strcmp(g_obj.rettit(),titl)==0))
        {
            g_obj.show_details();
            newf = 1;
            return g_obj;
            break;
        }
    }
    fin.close();
    
    if(newf==0)
        {
            cout<<"No record found";
            return null_obj;
        }
}

void buy()    //Function defination to buy copies of Availabale book
{
    float t_cost=0.0;
    char ch;
    g_obj = Search();
    g_obj.show_details();
    int copies;
    if(g_obj.retprice()==0.0)
    {
        cout<<"Enter valid details !!!"<<endl;
    }
    
    else
    {
        cout<<"\nEnter Number of copies you want: ";
        cin>>copies;
                
        if(g_obj.retstk()>=copies)
        {
            t_cost = copies*g_obj.retprice();
            cout<<"Total Amount is: "<<t_cost<<endl;
            cout<<"******Confirmation required*******"<<endl;
            cout<<"Press 'Y' (to buy) or Press 'N' (go to main menu): ";
            cin>>ch;
            if(ch=='Y' || ch=='y')
            {
                fstream f;
                f.open("Bshop",ios::ate|ios::in|ios::out);
                f.clear();
                int last=f.tellg();
                int object = g_obj.count;
                int location=(object-1)*sizeof(BOOK);
                if(f.eof())
                    f.clear();
                f.seekp(location);
                g_obj.modify(copies);
                f.write((char*)&g_obj, sizeof(BOOK));
                g_obj.show_details();
                f.close();
                cout<<"\n*******Thank you for buying our book******* "<<endl<<endl;
            }
            
        }
                
       else
        {
            cout<<"\nRequired copies not in stock!!!"<<endl;
        }
        
    }
}

void BOOK::modify(int copies)    //Function defination to update stock details of a book
{
    stock_position = stock_position - copies;
}


//*****************************************/*int main*/**************************************************************************************


int main()
{ 
    int flag = 0;
    int ch;
    ofstream fout;
    fout.open("Bshop",ios::app);
    fout.close();
    do{
    cout<<"\n\n\n****Welcome to the BOOK Store****";
    cout<<"\n1. Add BOOK Deatils ";
    cout<<"\n2. Search BOOK Deatils ";
    cout<<"\n3. Buy BOOK ";
    cout<<"\n4. List of all Books available ";    
    cout<<"\n0. Exit ";
    cout<<"\nEnter choice : ";
    cin>>ch;
    switch(ch)
        {
            case 1: {
                    ofstream fout;
                    fout.open("Bshop",ios::app);
                    g_obj.get_details();
                    fout.write((char *)&g_obj,sizeof(BOOK));
                    fout.close();
                    cout<<"\nThank you !"<<endl;
                    break;
                    }
                
            case 2: {
                    g_obj = Search();
                    if(g_obj.retstk() == 0)
                        {
                            cout<<"Enter Valid account details"<<endl;
                        }
                    break;
                    }
        
            case 3: {
                    buy();
                    break;
                    }
                    
            case 4: {
                    ifstream fin;
                    fin.open("Bshop",ios::in);
                    while(fin.read((char *)&g_obj, sizeof(BOOK)))
                    {
                        g_obj.listb();
                    }
                    fin.close();
                    break;
                    }
                    
        }
    }while(ch!=0);
    
    cout<<"\nThank you for using our services";
    return 0;
}    

//*****************************************/*End of program*/************************************************************















