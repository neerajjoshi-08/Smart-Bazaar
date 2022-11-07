#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std ;

struct Stock
{
    int Item_No ;
    float Price ;
    char Item_Name[15];
    int Qty ;
};

class Customer
{    int Cust_No, Item_No [30], Qnt [30], Item, no_stocks;
     char Cust_Name [30], Item_Name[30][15];
     float Price[30], Total ;
     ifstream fin;
     ofstream fout;
     Stock stocks[30];

   public :
      Customer();
      ~Customer();
      void Input();
      void Display();
      void Add();
      void Modify();
      void View_qty();
};

Customer::Customer()
{
    fin.open("item.dat", ios::in|ios::binary);
    Stock temp;
    int i = 0;

    if (fin.good())
    {
        while (!fin.eof())
        {
            fin.read((char*) &temp, sizeof(temp));
            stocks[i] = temp;
            ++i;
        }
        fin.close();
    }
    no_stocks = i;
}

Customer::~Customer()
{
    fout.open("item.dat", ios::out|ios::binary);
    Stock temp;
    for (int i = 0; i < no_stocks; ++i)
    {
        temp = stocks[i];
        fout.write((char*) &temp, sizeof(temp));
    }
    fout.close();
}

void Customer::Input()
{
    cout << endl;

    cout << "\t\t!!!!!! HELLO SMART BUYER !!!!!!!" << endl;
    cout << "\nEnter Customer's Number: ";
    cin  >> Cust_No;
    cout << "Enter Customer's Name: ";
    cin.sync();
    gets(Cust_Name);
    cout << endl;
    cout << "For How many Items: ";
    cin  >> Item;
    Total  = 0;

    int flag = 0, i;
    for(int j = 0; j < Item; ++ j)
    {
       cout << "Enter Item Number of " << j + 1 << ": ";
       cin  >> Item_No [j];
       for (i = 0; i < no_stocks; ++i)
       {
           if (stocks[i].Item_No == Item_No[j])
           {
               flag = 1;
               break;
           }
       }
      if (!flag)
      {
        cerr << "\nFirst add this on database";
        stocks[no_stocks].Item_No = Item_No[j];
        cout << "Enter Item Name: " ;
        cin.sync();
        gets (stocks[no_stocks].Item_Name) ;

        do
        {
            cout << "Enter Its Price: ";
            cin  >> stocks[no_stocks].Price ;
            if ( stocks[no_stocks].Price < 0)
            cout << "Price cannot be negative!\n";

        }while (stocks[no_stocks].Price < 0);

        do
        {
            cout << "Enter Quantity present: ";
            cin  >> stocks[no_stocks].Qty ;
            if (stocks[no_stocks].Qty < 0)
                cout << "Quantity cannot be negative!\n\n";

        } while (stocks[no_stocks].Qty < 0);
        ++no_stocks;
      }

        do
        {
            cout << "Enter Quantity Purchased: " ;
            cin  >> Qnt [j] ;
            if (Qnt[j] < 0)
                cout << "Quantity cannot be negative!\n";
            else if (Qnt[j] > stocks[i].Qty)
                cout << "Only " << stocks[i].Qty << " items in stock! Kindly enter a lesser amount.\n";

       }while (Qnt[j] < 0 || Qnt[j] > stocks[i].Qty);

        stocks[i].Qty -= Qnt[j] ;
        Price[j] = stocks[i].Price;
        strcpy(Item_Name[j], stocks[i].Item_Name);
        Total  +=  ( Price[j] *  Qnt [j] ) ;
        cout << endl ;
    }
       cout << endl ;
}

void Customer::Display()
{
	 if (!Item)
	 {   cout << "No Bill Exists!" << endl;
	     return ;
	 }

	 cout << "\t\t\t  BILL ---- BILL ---- BILL ---- BILL -----BILL "  << endl << endl ;
	 cout << endl ;
	 cout << "\t\t\t" ;
	 cout << "Customer 's Number: " << Cust_No   << endl ;
	 cout << "\t\t\t" ;
	 cout << "Customer 's Name: " << Cust_Name  << endl ;
	 cout << endl ;
	 cout.setf (ios :: left) ;
	 cout.setf(ios :: fixed) ;
	 cout << '\t'
	      << setw(8) << "S.No"
	      << setw(13) << "Item No."
	      << setw(13) << "Item Name"
	      << setw(12) << "Quantity"
	      << setw(9) << "Price"
	      << setw(8) << "Cost"
	      << endl  ;

	      for ( int j = 0 ; j < Item ; ++j )
			{    cout << '\t'
				  << setw(8) << j+1
				  << setw(13) << Item_No [j]
				  << setw(13) << Item_Name[j]
				  << setprecision (0)
				  << setw(12) << Qnt [j]
				  << setw(9) << Price[j]
				  << "Rs." << setw(5) << Price[j] * Qnt [j]
				  << endl ;
			}

		cout << "\n\t\t  TOTAL AMOUNT IS: Rs. "
		     << setprecision ( 2 )
		     << Total  ;
		cout << "\n\n\n -----THANKS FOR VISITING US :) :) :) " ;
		cout << endl ;
}

void Customer::Add()      //Function to add new items to file
{
   int flag = 0, i;
   char ch = 'y' ;
   Stock temp;

   while( ch == 'y')
   {
       flag = 0;
       cout << "\nEnter Item Code: " ;
       cin  >> temp.Item_No ;

	   for (i = 0; i < no_stocks; ++i)
	     {
		    if ( stocks[i].Item_No == temp.Item_No )
              {
                  flag = 1 ;
			      break ;
		      }
	     }
			if ( flag == 1 )
			 {
			    cout << "Item already Exists!\n\n" ;
			    system("pause") ;
			 }

			else
			 {
			    cout << "Enter Item Name: " ;
			    cin.sync();
			    gets (temp.Item_Name) ;

			    do {
				cout << "Enter Its Price: ";
				cin  >> temp.Price ;
				    if ( temp.Price < 0)
					cout << "Price cannot be negative!\n";
				} while (temp.Price < 0);

			    do {
				cout << "Enter Quantity present: ";
				cin  >> temp.Qty ;
				    if (temp.Qty < 0)
					cout << "Quantity cannot be negative!\n\n";

				} while (temp.Qty < 0);
				stocks[no_stocks] = temp;
				++no_stocks;

			  }
	 cout << "Enter More Items (y/n): " ;
	 cin  >> ch ;
   }

}
void Customer::View_qty()
{
    if (no_stocks == 0)
    {
        cout << "No stock available!\n";
        return;
    }

    cout << setw(16) << "ItemName"
         << setw(8) << "Quantity" << endl ;

    for (int i = 0; i < no_stocks; ++i)
     {
        cout << setw(16) << stocks[i].Item_Name
	         << setw(8) << stocks[i].Qty << endl ;
     }
       cout << endl ;
}
void Customer::Modify()
{
    int flag = 0;
    char input[20];
    cout << "Enter Item Number which has to be modified: " ;
    cin  >> Item_No[0] ;

    for (int i = 0; i < no_stocks; ++i)
    {
          if ( stocks[i].Item_No == Item_No[0])
           {
               flag = 1;
               cout << "!!!NOTE ::: Enter '.' if unchanged!" << endl ;
               cout << "Enter Item name : ";
               cin.sync();
               gets(input);
                 if (strcmp(input, ".") != 0)
                    strcpy (stocks[i].Item_Name, input);
               do
               {
                   cout << "Enter Price: ";
                   cin.sync();
                   gets(input);
                     if (strcmp(input, ".") != 0)
                     {
                         int len = strlen(input);
                         stocks[i].Price = 0;
                         while (len > 0)
                         {
                             stocks[i].Price = stocks[i].Price*10 + input[len-1] - '0';
                             --len;
                         }
                         if (stocks[i].Price < 0)
                            cout << "Price cannot be negative!\n";
                     }
                } while (stocks[i].Price < 0);
               do
               {
                   cout << "Enter quantity in stock: ";
                   cin.sync();
                   gets(input);
                   if (strcmp(input, ".") != 0)
                   {
                         int len = strlen(input);
                         stocks[i].Qty = 0;
                         while (len > 0)
                         {
                             stocks[i].Qty = stocks[i].Qty*10 + input[len-1] - '0';
                             --len;
                         }
                         if (stocks[i].Qty < 0)
                            cout << "Quantity cannot be negative!\n";
                   }
               } while (stocks[i].Qty < 0);
           }
    }
    if (!flag)
    {
        cout << "Item not found in database!\n";
    }
}

// main() starts from here.
int main()
{
    char ch = 'y' ;
    int choice  ;
    Customer Y ;

    do {
	    system("cls") ;
	    cout << "------------- Welcome to SMART BAZZAR ----------" << endl ;
	    cout << "\n1.Pay Bill"
             << "\n2.Add Items to file"
		     << "\n3.Check Available Stock"
		     << "\n4.Modify Items"
		     << "\n5.Exit\n"
             << "\nEnter Choice (1-5): " ;
	    cin  >> choice ;

      switch (choice)
       {
	   case 1 : Y.Input() ;
                cout << "Do you Want to Generate Bill (y/n): " ;
                cin  >> ch ;
                cout << endl ;
               if ( ch == 'y' || ch == 'Y'  )
                    Y.Display () ;
                cout << endl ;
                break ;

	   case 2 : Y.Add() ;
		        break ;

	   case 3 : Y.View_qty() ;
                break ;

	   case 4 : Y.Modify();
                break ;

	   case 5 : cout << "Exiting from the program!\n" ;
                break;

	  default : cout << "Please select appropriate choice!"
                     << "Let's continue again--\n\n";
       }
	system("pause");
     } while ( choice != 5 ) ;

    return 0;
}
