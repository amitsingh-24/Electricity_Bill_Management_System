#include<iostream> 
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<string.h>
using namespace std;
class electricity_bill{
    char name[50];
    char month[12], address[50];
    int units;
    float total;
    public:
    void get();
    friend float calculate_bill(int units);   
    void display();
    void add();
    void display_all();
    void search_name();
    void menu();
    void heading();
};
void electricity_bill::heading()
{
cout<<"NAME"<<setw(10)<<"ADDRESS"<<setw(30)<<"MONTH"<<setw(12)<<"UNITS"<<setw(10)<<"TOTAL"<<endl;
    for(int i=0;i<=80;i++)
        cout<<"-";
    cout<<endl;    
}
float calculate_bill(int units)
{  
    float total;
    if(units<100)
    {
        total = 0.6*units;
    }
    else if(units>100 && units<=200)
    {
        units=units-100;
        total = 60 + 0.8*units;
    }
    else
    {
        units=units-300;
        total = 0.9*units + 220;
    }

    if(total<50)
        return 50;
    else if(total>300)
        return (total + 0.15*total);    
    else
    return total;
}
void electricity_bill::get()
{
    cin.ignore();
    cout<<"Enter name: ";
    cin>>name;
     cin.ignore();
    cout<<"Enter address: ";
    cin>>address;
    cout<<"Enter the month of billing: ";
    cin>>month;
    cout<<"Enter the total units consumed: ";
    cin>>units;
    total = calculate_bill(units);
    }
void electricity_bill:: display()
{
cout<<name<<setw(10)<<address<<setw(30)<<month<<setw(12)<<units<<setw(10)<<total<<endl;
}
void electricity_bill::add()
{
    fstream bill;
    electricity_bill e1;
    bill.open("bill1.txt",ios::in);
    if(bill.fail())
    {
        cout<<"File does not exist"<<endl;
        bill.open("bill1.txt", ios::out);
    }
    else
    {
       // cout<<"File is present"<<endl;
        bill.close();
        bill.open("bill1.txt",ios::app);
        e1.get();
        bill.write((char*)&e1, sizeof(e1));
    }
}
void electricity_bill::display_all()
{
    fstream bill;
    electricity_bill e1;
    heading();
    bill.open("bill1.txt", ios::in);
    bill.read((char*)&e1, sizeof(e1));
    while(!bill.eof())
    {
        e1.display();
        bill.read((char*)&e1, sizeof(e1));
    }
    bill.close();
}
void electricity_bill::search_name()
{
    fstream bill;
    electricity_bill e1;
    int z=0;
    char sname[50];
    cout<<"Enter the name of the cunsumer: ";
    cin>>sname;
    heading();
    bill.open("bill1.txt", ios::in);
    bill.read((char*)&e1, sizeof(e1));
    while(!bill.eof())
    {
        if(strcmpi(e1.name,sname)==0)
        {
            z=1;
            e1.display();
        }
        bill.read((char*)&e1, sizeof(e1));
    }
    bill.close();
    if(z==0)
        cout<<"Record not found"<<endl;
}

void electricity_bill::menu()
{
    cout<<"Main Menu"<<endl;
    cout<<"1. Add a record"<<endl;
    cout<<"2. Display Records"<<endl;
    cout<<"3. Display bill by name"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"\nEnter your choice: ";
    }
int main()
{
   int ch=0;
   electricity_bill e;
   while(ch!=4)
   {
    e.menu();
    cin>>ch;
    system("cls");
    switch(ch)
    {
       case 1:
          e.add();
          break;
       case 2:
          e.display_all();
          break;
       case 3:
          e.search_name();
          break;
     case 4:
         cout<<"Thanks!"<<endl;
          break;         
       default :
          cout<<"Enter a valid choice"<<endl;
          break;
    }
    getch();
   }
    return 0;
}

