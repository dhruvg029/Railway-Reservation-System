#include<bits/stdc++.h>
using namespace std;

void viewinfo();
void bookticket();
void cancelticket();
void admin();
void password();
void viewpassenger();
void addtrain();
void deleteTrain();
void awrite();
void aread();
void bookticket_write();
void viewpassengers_read();

struct adddata {
	int seat;
	char serialNumber[10];
	char trainNumber[10];
	char trainName[20];
	char boardingPoint[10];
	char destinationPoint[10];
	char price[10];
	char time[10];
} add[1000];

struct bookticket {
	char trainNumber[20];
	char name[20];
	char phoneNumber[20];
	char date[20];
	int seat;
} book[1000];

int k = 0,u = 0;
char trn_nmbr[100],name[100],phn[100];

int main() {
	aread();
	viewpassengers_read();

	int choice;

    cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl;

    cout<<endl;
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout<<ctime(&timenow)<<endl;

    cout<<"--- WELCOME TO RAILWAY RESERVATION --- "<<endl;

	cout<<"[1] VIEW INFORMATION"<<endl;
	cout<<"[2] BOOK TICKET"<<endl;
	cout<<"[3] CANCEL TICKET"<<endl;
	cout<<"[4] ADMIN"<<endl;
	cout<<"[5] EXIT"<<endl;

	cout<<"ENTER YOUR CHOICE: ";
	cin>>choice;

    switch(choice) {
        case 1:
			viewinfo();
			break;

		case 2:
			bookticket();
			break;

		case 3:
			cancelticket();
			break;

		case 4:
			password();
			break;

        case 5:
            exit(0);
            break;

        default:
            cout<<"--- INVALID CHOICE ENTERED!! ENTER AGAIN :( ---"<<endl;
    }

    return 0;
}

void bookticket() {
	int choice, j, n, i, found = -1;
	char trainNumber[10];
	
	aread();
	cout<<"------------------------------------------"<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"WELCOME!! :) WE ARE HAPPY TO HAVE YOU HERE!!"<<endl;
    cout<<"SO HOW MANY TICKETS DO YOU WANT TO BUY? ";
	cin>>n;

	for(j = 0;j < n; j++) {
		cout<<"ENTER TRAIN NUMBER: ";
		cin>>book[j].trainNumber;

		for(i=0; i < k; i++) {
			if(strcmp(book[j].trainNumber,add[i].trainNumber) == 0) {
				if(add[i].seat == 0) {
					cout<<"SORRY NO SEATS ARE AVAILABLE :("<<endl;
					main();
				} else {
	    			found = 1;
					cout<<"-- TICKET DETAILS --"<<endl;
					cout<<"ENTER DATE: ";
					cin>>book[j].date;

					cout<<"ENTER NAME: ";
					cin>>book[j].name;

					cout<<"ENTER PHONE NUMBER: ";
					cin>>book[j].phoneNumber;

					cout<<"SEAT NUMBER: "<<add[i].seat;
					book[j].seat=add[i].seat;
					bookticket_write();
					add[i].seat--;
					awrite();
					cout<<endl;
					cout<<"Ticket booked for "<<book[j].name<<"!! Happy Journey :)"<<endl;
					cout<<"----------"<<endl;
				}
			}
		}

		if(found == -1) {
		cout<<"SORRY!!! TRAIN NOT FOUND :( PLEASE TRY AGAIN!!"<<endl;
		// system("cls");
		main();
		}
	}

	u = j;
	bookticket_write();
	cout<<"[1] MAIN MENU "<<endl;
	cout<<"[0] EXIT "<<endl;
	cout<<"ENTER YOUR CHOICE: ";
	cin>>choice;

	if(choice == 1) {
		// system("cls");
		main();
	}

	if(choice == 0) {
		exit;
	}			
}

void cancelticket() {
	viewpassengers_read();
    char pnnmbr[100];
    int location = -1,e;

    cout<<"ENTER PHONE NUMBER: "<<endl;
    cin>>pnnmbr;

    for (e=0;e<u;e++) {
        if (strcmp(pnnmbr,book[e].phoneNumber) == 0) {
            location=e;
            break;
        }
    }

    if (location==-1) {
        cout<<"--- NO DATA AVAILABLE!! :( ---"<<endl;
        // system("cls");
        main();
	} else {
        for (e=location;e<u;e++) {
            strcpy(book[e].date,book[e+1].date);
            strcpy(book[e].trainNumber,book[e+1].trainNumber);
            strcpy(book[e].name,book[e+1].name);
            strcpy(book[e].phoneNumber,book[e+1].phoneNumber);
            bookticket_write();
        }

        u--;
        bookticket_write();
        cout<<"--- YOUR TICKET IS CANCELLED :) ---"<<endl;
        // system("cls");
        main();
    }
}

//-------------------------------------admin portal function----------------------------------------
void admin() {
	int ch;
	cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl; 
	cout<<"--- WELCOME TO ADMIN MODE!! ---"<<endl;
	cout<<"[1] VIEW PASSENGERS"<<endl;
	cout<<"[2] ADD TRAIN"<<endl;
	cout<<"[3] DELETE TRAIN"<<endl;
	cout<<"[4] BACK"<<endl;
	cout<<"ENTER YOUR CHOICE: ";
	cin>>ch;

	switch(ch) {
		case 1:
			viewpassenger();
			break;
		case 2:
			addtrain();
			break;
		case 3:
			deleteTrain();
			break;
		case 4:
			// system("cls");
			main();
			break;
		default:
			cout<<"INVALID CHOICE :( PLEASE ENTER AGAIN!!"<<endl;
			// system("cls");
			main();
	}
	
}

void password() {
	int number = 123;
	int pass;
	cout<<"ENTER ADMIN PASSWORD PLZ: ";
	cin>>pass;

	if(pass == number) {
		cout<<"WELCOME ADMIN!! NICE TO MEET YOU AGAIN :)"<<endl;
		// system("cls");
		admin();
	} else {
		cout<<"SORRY!! WRONG PASSWORD!! LOGIN AGAIN :("<<endl;
		// system("cls");
		main();
	}
}

// This function is for deleting any available train
void deleteTrain() {
	aread();
    char train[100];
    int location = -1;

	cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"ENTER TRAIN NUMBER OF THE TRAIN YOU WANT TO DELETE: ";
	cin>>train;

    for (int f = 0; f < k; f++) {
        if (strcmp(train, add[f].trainNumber) == 0) {
            location = f;
            break;
        }
    }

    if (location == -1) {
		cout<<"------------------------------------------"<<endl;
        cout<<"SORRY!!! TRAIN NOT FOUND :("<<endl;
        // system("cls");
        admin();
    } else {
        for (int f = location; f < k; f++) {
            strcpy(add[f].serialNumber, add[f+1].serialNumber);
            strcpy(add[f].trainNumber, add[f+1].trainNumber);
            strcpy(add[f].trainName, add[f+1].trainName);
            strcpy(add[f].boardingPoint, add[f+1].boardingPoint);
            strcpy(add[f].destinationPoint, add[f+1].destinationPoint);
            strcpy(add[f].price, add[f+1].price);
            strcpy(add[f].time, add[f+1].time);
            awrite();
        }
        k--;
        awrite();
		cout<<"--- TRAIN DELETED SUCCESSFULLY!! ---"<<endl;
		// system("cls");
		admin();
    }
}

void viewpassenger() {
	int a;
	// system("cls");
	viewpassengers_read();

	cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl;
	cout<<"THE DETAILS ARE AS FOLLOWS!! :)"<<endl;

	for(int j = 0; j < u; j++) {
		cout<<book[j].trainNumber<<"   "<<book[j].name<<"   "<<book[j].phoneNumber<<"   "<<book[j].date<<"   "<<book[j].seat<<endl;
		book[j].seat++;
	}

	cout<<"[1] MAIN MENU "<<endl;
	cout<<"[0] BACK"<<endl;
	cout<<"ENTER YOUR CHOICE: "<<endl;
	cin>>a;

	if(a == 1) {
		// system("cls");
		main();
	}

	if(a == 0) {
		// system("cls");
		admin();
	}
}

void addtrain() {
	// system("cls");
	int ch;
	aread();
	int i, a;

	cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl;
	cout<<"WELCOME!! HOW MANY TRAINS DO YOU WANT TO ADD? ";
	cin>>a;

	for(i = 0; i < a; i++) {
		cout<<"---------------------------------"<<endl;
		cout<<"---------------------------------"<<endl;

		cout<<"--- ENTER TRAIN DETAILS ---"<<endl;

		cout<<"ENTER SERIAL NUMBER: ";
		cin>>add[i].serialNumber ;

		cout<<"ENTER TRAIN NUMBER: ";
		cin>>add[i].trainNumber;

		cout<<"ENTER TRAIN NAME: ";
		cin>>add[i].trainName;

		cout<<"ENTER BOARDING POINT: ";
		cin>>add[i].boardingPoint;

		cout<<"ENTER DESTINATION POINT: ";
		cin>>add[i].destinationPoint;

		cout<<"ENTER PRICE: ";
		cin>>add[i].price;

		cout<<"ENTER SEAT: ";
		cin>>add[i].seat;

		cout<<"ENTER TIME: ";
		cin>>add[i].time;
	}

		cout<<"ADD THIS TRAIN?"<<endl;
		cout<<"[1] YES"<<endl;
		cout<<"[0] NO"<<endl;
		cout<<"ENTER YOUR CHOICE: ";
		cin>>ch;

		if(ch == 1) {
			awrite();
			k = i;
			awrite();
			// system("cls");

			cout<<"------------------------------------------"<<endl;
			cout<<"CONGRATS!! TRAIN ADDED SUCCESSFULLY!! :)"<<endl;
			
			// system("cls");
			main();
		}

		if(ch == 0) {
			// system("cls");
			admin();
		}

		if((ch != 1 ) && (ch != 0)) {
			// system("cls");
			main();
		}
}

void viewinfo() {
	int ch;
	// system("cls");
	aread();

	cout<<"------------------------------------------"<<endl;
    cout<<"------------------------------------------"<<endl;
	cout<<"THIS IS THE INFORMATION THAT IS PRESENT CURRENTLY!! :)"<<endl;

	for(int i = 0; i<k; i++) {
		cout<<endl;
		cout<<add[i].serialNumber<<"   "<<add[i].trainNumber<<"   "<<add[i].trainName<<"   "<<add[i].boardingPoint<<"   "<<add[i].destinationPoint<<"   "<<add[i].price<<"   "<<add[i].seat<<"   "<<add[i].time;
		cout<<endl;
	}
	cout<<endl;
	cout<<"1       -> MAIN MENU"<<endl;
	cout<<"ANY KEY -> EXIT"<<endl;
	cout<<"ENTER YOUR CHOICE: ";
	cin>>ch;

	switch(ch) {
		case 1:
			// system("cls");
			main();
			break;

		default:
			exit(0);
	}
}

void bookticket_write() {
	FILE *booklist;
	booklist = fopen("booklist.txt","w");
	fwrite(&book,sizeof(book),1,booklist);
	fclose(booklist);

	FILE *booklistreport;
	booklistreport = fopen("booklistreport.txt","w");
	fwrite(&u,sizeof(u),1,booklistreport);
	fclose(booklistreport);
}

void viewpassengers_read() {
	FILE *booklist;
	booklist=fopen("booklist.txt","r");
	fread(&book,sizeof(book),1,booklist);
	fclose(booklist);

	FILE *booklistreport;
	booklistreport=fopen("booklistreport.txt","r");
	fread(&u,sizeof(u),1,booklistreport);
	fclose(booklistreport);
}

void awrite() {
	FILE *train_details;
	train_details = fopen("train_details.txt","w");
	fwrite(&add,sizeof(add),1,train_details);
	fclose(train_details);

	FILE *train_report;
	train_report = fopen("train_report.txt","w");
	fwrite(&k,sizeof(k),1,train_report);
	fclose(train_report);
}

void aread() {
	FILE *train_details;
	train_details = fopen("train_details.txt","r");
	fread(&add,sizeof(add),1,train_details);
	fclose(train_details);

	FILE *train_report;
	train_report = fopen("train_report.txt","r");
	fread(&k,sizeof(k),1,train_report);
	fclose(train_report);
}
