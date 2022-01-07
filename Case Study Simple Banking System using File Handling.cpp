//Ruchi Chaturvedi
//Case Study: Simple Banking System using File Handling
#include <iostream>
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class BANK
{
  int account = 0;
  char name[30];
  float balance;
  
  public:
  BANK()
  { 
    account = 0;
    strcpy(name," ");
    balance = 0;
  }
  void OpenAccount();
  void ShowAccount();
  void Deposite();
  void Withdraw(float wd_amt);
  BANK friend search();
  int retacc()
  {
      return account;
  }
  float returnbal()
  {
      return balance;
  }
};

BANK null_obj;
BANK g_obj;

void BANK::OpenAccount()
{
    ofstream fout;
    fout.open("Bank",ios::app);
    account = account +1;
    cout<<"\nEnter name: ";
    cin>>name;
    cout<<"Enter Opening balance: ";
    cin>>balance;
    fout.write((char *)&g_obj,sizeof(BANK));
    fout.close();
    ShowAccount();
}

void BANK :: ShowAccount()
{
    cout<<"\n****Customer Details****";
    cout<<"\nAccount Number : "<<account;
    cout<<"\nName : "<<name;
    cout<<"\nBalance : "<<balance<<endl;
}

void BANK::Deposite()
{
    float amt;
    cout<<"\nEnter Amount to be deposited : ";
    cin>>amt;
    balance = balance+amt;
}

void BANK :: Withdraw(float wd_amt)
{
    balance = balance-wd_amt;
}

BANK search()
{
    int acc,newflg=0,pos;
    cout<<"\nEnter Account Number : ";
    cin>>acc;
    ifstream iof;
    iof.open("Bank",ios::in);
    while(!iof.eof())
    {
        iof.read((char*)&g_obj, sizeof(BANK));
        if(acc==g_obj.retacc())
        {
            g_obj.ShowAccount();
            newflg=1;
            return g_obj;
            break;
        }
    }
    iof.close();
    if(newflg == 0)
    {
        cout<<"No account found!!!"<<endl;
        return null_obj;
    }
}

void Depo()
{
    g_obj = search();
    if(g_obj.retacc()==0)
    {
        cout<<"Enter valid account details !!!"<<endl;
    }
    else
    {
        fstream f;
        f.open("Bank",ios::ate|ios::in|ios::out);
        f.clear();
        int object = g_obj.retacc();
        int location=(object-1)*sizeof(g_obj);
        if(f.eof())
            f.clear();
         f.seekp(location);
        g_obj.Deposite();
        f.write((char*)&g_obj, sizeof(BANK));
        g_obj.ShowAccount();
        f.close();
        cout<<"Money sucsessfully deposited"<<endl;
    }
}

void Withd()
{
    BANK a = search();
    if(g_obj.retacc()==0)
    {
        cout<<"\nEnter valid account details !!!"<<endl;
    }
    
    else
    {
        fstream f;
        f.open("Bank",ios::ate|ios::in|ios::out);
        f.clear();
        int object = g_obj.retacc();
        int location=(object-1)*sizeof(g_obj);
        if(f.eof())
            f.clear();
        f.seekp(location);
        g_obj.Withdraw();
        float wd_amt;
        cout<<"\nEnter Amount to be withdrawn : ";
        cin>>wd_amt;
        if(wd_amt>g_obj.returnbal())
        {
            cout<<"Sorry, You don't have enough balance"<<endl;
        }
        else
        {
            g_obj.Withdraw(wd_amt);
        }
        f.write((char*)&g_obj, sizeof(BANK));
        a.ShowAccount();
        f.close();
        cout<<"Money sucsessfully Withdrawn"<<endl;
    }
}


int main()
{
    int no,ch;
    ofstream fout;
    fout.open("Bank",ios::app);
    fout.close();
    do{
    cout<<"****Welcome to the RUchi's bank****";
    cout<<"\n1. Open Account ";
    cout<<"\n2. Show Account Details ";
    cout<<"\n3. Deposite Amount ";
    cout<<"\n4. Withdraw Amount ";
    cout<<"\n5. Show list ";
    cout<<"\n0. Exit ";
    cout<<"\nEnter choice : ";
    cin>>ch;
    switch(ch)
        {
            case 1: {
                    g_obj.OpenAccount();
                    break;
                    }
                
            case 2: {
                    g_obj = search();
                    if(g_obj.retacc() == 0)
                        {
                            cout<<"Enter Valid account details"<<endl;
                        }
                    break;
                    }
        
            case 3: {
                    Depo();
                    break;
                    }
                    
            case 4: {
                    Withd();
                    break;
                    }
            
            case 5: {
                    ifstream fin;
                    fin.open("Bank",ios::in);
                    while(fin.read((char*)&g_obj, sizeof(BANK)))
                    {
                        g_obj.ShowAccount();
                    }
                    fin.close();
                    break;
                    }
        }
        
    }while(ch!=0);
    
    return 0;
}













