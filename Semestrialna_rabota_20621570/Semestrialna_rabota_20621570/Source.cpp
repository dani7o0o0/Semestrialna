#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include <stdlib.h> 
#include <stdio.h> 
#include <ctype.h>
using namespace std;

const  int MAX_SHIPS = 20;									//definirane na konstanti
const int MAX_CONTAINERS = 10;
const string NAME = "ships.bin";							//ime na faila v tekuhstata papka

struct date {												//struktura za datata
	int year;
	int month;
	int day;
};

struct container {											//struktura za konteiner
	char contNum[10];										//nomer na konteiner
	double contSize;										//golemina na tovar na konteiner
};

struct ship {												//osnovna struktura za korabni prevozi
	char shipNum[10]{};										//nomer na korab
	char shipName[20]{};									//ime na korab
	date depDate{};											//data na poteglqne
	double cargoCap{};										//tovaren kapacitet
	int contCount{};										//broi konteineri s tovar
	double remCap{};										//ostavash kapacitet sled natovarvane
	container contList[MAX_CONTAINERS]{};					//masiv s konteinerite s tovari
};

//PROTOTIPI NA FUNKCII

void addOne(ship arrayShips[], int&n);
void addGroup(ship arrayShips[], int&n);
void showAll(ship arrayShips[], int n);
void showMaxCap(ship arrayShips[], int n);
void showByName(ship arrayShips[], int n);
void load(ship arrayShips[], int n);
void remove(ship arrayShips[], int &n);
bool dateComp(date date1, date date2);
void sortDate(ship arrayShips[], int n);
void sortCap(ship arrayShips[], int n);
void showMinCap(ship arrayShips[], int n);
void showMaxRemCap(ship arrayShips[], int n);
void saveFile(ship arrayShips[], int n);
void loadFile(ship arrayShips[], int&n);


int main() {
	int ch;
	ship arrayShips[MAX_SHIPS];													//Definirane na osnoven masiv ot strukturi
	int listSize=0;																//Duljina na masiva
	//MENU
	do {
		cout << "\n ***********SHIP CARRIAGE***********\n";
		cout << "\n Added ships: " << listSize;
		cout << "\n Menu\n";
		cout << "\n 1. Add ships";
		cout << "\n 2. Show ships";
		cout << "\n 3. Load a container";
		cout << "\n 4. Remove a ship";
		cout << "\n 5. Inquiries";
		cout << "\n 6. Save/Load a file";
		cout << "\n 7. Exit";
		do {
			cout << "\n\nYour choice (1-7) is: ";
			while (1)																//Cikul za validaciq na chislo
			{
				cin >> ch;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input " << endl;
					cout << "Try again" << endl;
				}
				else break;
			}
		} while (ch < 1 || ch > 7);
		system("cls");
		switch (ch) {
		case 1:																		//Podmenu
			cout << "\n Added ships:" << listSize;
			cout << "\n Menu\n";
			cout << "\n 1. Add one ship";
			cout << "\n 2. Add group of ships";
			cout << "\n 3. Back";
			do {
				cout << "\n\nYour choice (1-3) is: ";
				while (1)														//Cikul za validaciq na chislo
				{
					cin >> ch;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (ch < 1 || ch > 3);
			switch (ch) 
			{
			case 1:	 system("cls"); addOne(arrayShips, listSize); break;
			case 2:  system("cls"); addGroup(arrayShips, listSize); break;
			case 3:  system("cls"); break;
			}
			break;
		case 2:																									//Podmenu
			if (listSize == 0) { cout << "\nNo available ships!\n"; system("pause"); system("cls"); break; }	//Proverka za nalichni korabi
			cout << "\n Added ships:" << listSize;
			cout << "\n Menu\n";
			cout << "\n 1. Show all ships";
			cout << "\n 2. Show ships with largest cargo capacity";
			cout << "\n 3. Show ships by name";
			cout << "\n 4. Back";
			do {
				cout << "\n\nYour choice (1-4) is: ";
				while (1)																						//Cikul za validaciq na chislo
				{
					cin >> ch;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (ch < 1 || ch > 4);
			switch (ch)
			{
			case 1:	 system("cls"); showAll(arrayShips, listSize); break;
			case 2:  system("cls"); showMaxCap(arrayShips, listSize); break;
			case 3:  system("cls"); showByName(arrayShips, listSize); break;
			case 4:  system("cls"); break;
			}
			break;
		case 3: load(arrayShips, listSize); break;
		case 4: remove(arrayShips, listSize); break;
		case 5:																										//Podmenu
			if (listSize == 0) { cout << "\nNo available ships!\n"; system("pause"); system("cls"); break; }		//Proverka za nalichni korabi
			cout << "\n Added ships:" << listSize;
			cout << "\n Menu\n";
			cout << "\n 1. Sort by departure date (ascending)";
			cout << "\n 2. Sort by cargo capacity (ascending)";
			cout << "\n 3. Show ships with smallest cargo capacity";
			cout << "\n 4. Show ships with largest available capacity";
			cout << "\n 5. Back";
			do {
				cout << "\n\nYour choice (1-5) is: ";
				while (1)																						//Cikul za validaciq na chislo
				{
					cin >> ch;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (ch < 1 || ch > 5);
			switch (ch)
			{
			case 1:	 system("cls"); sortDate(arrayShips, listSize); break;
			case 2:	 system("cls"); sortCap(arrayShips, listSize); break;
			case 3:  system("cls"); showMinCap(arrayShips, listSize); break;
			case 4:  system("cls"); showMaxRemCap(arrayShips, listSize); break;
			case 5:  system("cls"); break;
			}
			break;
		case 6:																										//Podmenu
			cout << "\n Added ships:" << listSize;
			cout << "\n Menu\n";
			cout << "\n 1. Save a file";
			cout << "\n 2. Load a file";
			cout << "\n 3. Back";
			do {
				cout << "\n\nYour choice (1-3) is: ";
				while (1)																						//Cikul za validaciq na chislo
				{
					cin >> ch;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (ch < 1 || ch > 3);
			switch (ch)
			{
			case 1:	 system("cls"); saveFile(arrayShips, listSize); break;
			case 2:	 system("cls"); loadFile(arrayShips, listSize); break;
			case 3:  system("cls"); break;
			}
			break;
		}
	} while (ch != 7);
	return 0;
}


void addOne(ship arrayShips[], int& n) {										//DOBAVQNE NA 1 KORAB
	if (n >= MAX_SHIPS) return;
	double remainingcapacity;
	char ans;
	do {
		cout << "Adding one ship\n\n";
		cout << "Enter ship number:\t";
		cin >> arrayShips[n].shipNum;																//Tekusht element na masiva = n
		cin.ignore();													
		cout << "Enter ship name:\t";
		cin.getline(arrayShips[n].shipName, 20);
		do {
			cout << "Enter ship daparture date  (dd mm yyyy):\t";
			while (1)																				//Cikul za validaciq na chislo
			{
				cin >> arrayShips[n].depDate.day;  cin >> arrayShips[n].depDate.month; cin >> arrayShips[n].depDate.year;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input " << endl;
					cout << "Try again" << endl;
				}
				else break;
			}
		} while ((arrayShips[n].depDate.day < 1 || arrayShips[n].depDate.day > 31) || (arrayShips[n].depDate.month < 1 || arrayShips[n].depDate.month > 12) || (arrayShips[n].depDate.year < 1900 || arrayShips[n].depDate.year > 2100));			//Validaciq za data
		do {
			cout << "Enter ship cargo capacity (Max " << MAX_CONTAINERS << " ton(s)):\t";
			while (1)																							//Cikul za validaciq na chislo
			{
				cin >> arrayShips[n].cargoCap;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input " << endl;
					cout << "Try again" << endl;
				}
				else break;
			}
		} while (arrayShips[n].cargoCap > MAX_CONTAINERS || arrayShips[n].cargoCap < 0);											//Validaciq za tovaren kapacitet
		do {
			cout << "Enter the number of ship containers (1-" << MAX_CONTAINERS << " containers):\t";
			while (1)																												//Cikul za validaciq na chislo
			{
				cin >> arrayShips[n].contCount;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input " << endl;
					cout << "Try again" << endl;
				}
				else break;
			}
		} while (arrayShips[n].contCount < 1 || arrayShips[n].contCount > MAX_CONTAINERS);								//Validaciq za broi konteineri
		remainingcapacity = arrayShips[n].cargoCap;
		for (int i = 0; i < arrayShips[n].contCount; i++) {																//for cikul za vuvejdane na tovari
			cout << "Container "<< i+1 << " number: " << " \t";
			cin >> arrayShips[n].contList[i].contNum;
			do {
				cout << "Size: (Value 0-" << remainingcapacity << " ton(s)): ";
				while (1)																								//Cikul za validaciq na chislo
				{
					cin >> arrayShips[n].contList[i].contSize;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (arrayShips[n].contList[i].contSize < 0 || arrayShips[n].contList[i].contSize > remainingcapacity);				//Validaciq za golemina na konteinera
			remainingcapacity -= arrayShips[n].contList[i].contSize;																//Aktualizaciq na ostavashtiq kapacitet
		}
		arrayShips[n].remCap = remainingcapacity;
		n++;
		cout << "\nDo you want to add another ship? (y/n) ";
		cin >> ans;
		system("cls");
	} while ((ans == 'y') || (ans == 'Y'));											//PITANE ZA POVTORENIE NA FUNKCIQTA
}

void addGroup(ship arrayShips[], int& n) {											//DOBAVQNE NA GRUPA OT KORABI
	if (n >= MAX_SHIPS) return;														//Proverka za nadvishavane na limita ot korabi
	int numShips;
	double remainingcapacity;
	char ans;
	do {
		int index = 0;																//BROQCH NA CIKULA
		cout << "\nAdding group of ships";
		do {
		cout << "\nNumber of ships(1-" << MAX_SHIPS-n << "): ";						//Zadavame broi korabi
		cin >> numShips;
		} while (numShips<0 || numShips+n> MAX_SHIPS);								//Proverka za nadvishavane na maksimalen broi korabi
		for (int i=0; i < numShips; i++) {
			cout << "\n\nShip " << i + 1;
			cout << "\nEnter ship number:\t";
			cin >> arrayShips[i + n].shipNum;										//TEKUSHT ELEMENT NA MASIVA = i + n
			cin.ignore();								
			cout << "Enter ship name:\t";
			cin.getline(arrayShips[i + n].shipName, 20); //strcpy strcat strcmp strncpy strlen
			do {
				cout << "Enter ship daparture date  (dd mm yyyy):\t";
				while (1)
				{
					cin >> arrayShips[i + n].depDate.day;  cin >> arrayShips[i + n].depDate.month; cin >> arrayShips[i + n].depDate.year;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break; //break return exit(0) exit(1) continue
				}
			} while ((arrayShips[i + n].depDate.day < 1 || arrayShips[i + n].depDate.day > 31) || (arrayShips[i + n].depDate.month < 1 || arrayShips[i + n].depDate.month > 12) || (arrayShips[i + n].depDate.year < 1900 || arrayShips[i + n].depDate.year > 2100));			//Validaciq za data
			do {
				cout << "Enter ship cargo capacity (Max " << MAX_CONTAINERS << " ton(s)):\t";
				while (1)																							//Cikul za validaciq na chislo
				{
					cin >> arrayShips[i + n].cargoCap;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (arrayShips[i + n].cargoCap > MAX_CONTAINERS || arrayShips[i + n].cargoCap < 0);								//Validaciq za tovaren kapacitet
			do {
				cout << "Enter the number of ship containers (1-" << MAX_CONTAINERS << " containers):\t";
				while (1)																											//Cikul za validaciq na chislo
				{
					cin >> arrayShips[i + n].contCount;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input " << endl;
						cout << "Try again" << endl;
					}
					else break;
				}
			} while (arrayShips[i + n].contCount < 1 || arrayShips[i + n].contCount > MAX_CONTAINERS);								//Validaciq za broi konteineri < maksimalen
			remainingcapacity = arrayShips[i + n].cargoCap;
			for (int j = 0; j < arrayShips[i + n].contCount; j++) {																	//for cikul za vuvejdane na tovari
				cout << "Container " << j + 1 << " number:\t";
				cin >> arrayShips[i + n].contList[j].contNum;
				do {
					cout << "Size: (Value 0-" << remainingcapacity << " ton(s)): ";
					while (1)																										//Cikul za validaciq na chislo
					{
						cin >> arrayShips[i + n].contList[j].contSize;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout << "Invalid input " << endl;
							cout << "Try again" << endl;
						}
						else break;
					}
				} while (arrayShips[i + n].contList[j].contSize < 0 || arrayShips[i + n].contList[j].contSize > remainingcapacity);					//Validaciq za golemina na tovara
				remainingcapacity -= arrayShips[i + n].contList[j].contSize;																	//Aktualizaciq za ostavash kapacitet
			}
			arrayShips[i + n].remCap = remainingcapacity;
			index++;
		}
		n += index;																				//Dobavqme broqcha kum duljinata na masiva
		cout << "\nDo you want to add more ships? (y/n) ";
		cin >> ans;
		system("cls");
	} while ((ans == 'y') || (ans == 'Y'));														//Pitane za povtorenie na funkciqta
}

void showAll(ship arrayShips[], int n) {														//IZVEJDANE NA VSICHKI PREVOZI
	for (int i = 0; i < n; i++) {
		cout << "\nNumber of ship:\t" << arrayShips[i].shipNum;
		cout << "\nName of ship:\t" << arrayShips[i].shipName;
		cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
		cout << "\nCargo capacity:\t" << arrayShips[i].cargoCap << " ton(s)";
		cout << "\nList of containers:";
		cout << "\n" << arrayShips[i].contCount << " containers";
		for (int j = 0; j < arrayShips[i].contCount; j++) {
			cout << "\nContainer number: " << arrayShips[i].contList[j].contNum;
			cout << "\nSize:\t" << arrayShips[i].contList[j].contSize << " ton(s)";
		}
		cout << "\n\nGo to next page \n";															//Vseki prevoz na nova stranica
		system("pause");
		system("cls");
	}
}

void showMaxCap(ship arrayShips[], int n) {															//IZVNEJDANE NA PREVOZI S NAI-GOLQM KAPACITET
	double maxCap = arrayShips[0].cargoCap;
	for (int i = 1; i < n; i++) {																	//cikul za namirane na maksmilaniq capacitet
		if (arrayShips[i].cargoCap > maxCap) {
			maxCap = arrayShips[i].cargoCap;
		}
	}
	for (int i = 0; i < n; i++) {
		if (arrayShips[i].cargoCap == maxCap) {														//izvejdane na vsichki prevozi s kapacitet = maksmimalniq
			cout << "\nShips with largest cargo capacity:";
			cout << "\n\nNumber of ship:\t" << arrayShips[i].shipNum;
			cout << "\nName of ship:\t" << arrayShips[i].shipName;
			cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
			cout << "\nCargo capacity:\t" << arrayShips[i].cargoCap << " ton(s)";
			cout << "\nList of containers:";
			cout << "\n" << arrayShips[i].contCount << " containers";
			for (int j = 0; j < arrayShips[i].contCount; j++) {
				cout << "\nContainer number: " << arrayShips[i].contList[j].contNum;
				cout << "\nSize:\t" << arrayShips[i].contList[j].contSize << " ton(s)";
			}
			cout << "\n\nGo to next page \n";
			system("pause");
			system("cls");
		}
	}
}

void showByName(ship arrayShips[], int n) {															//IZVEJDANE NA PREVOZI PO IME NA KORAB
	char name[20];
	bool found = false;	//flag
	cout << "\nNames of available ships:\n";
	for (int i = 0; i < n; i++) {																	//Izvejdane imenata na vsichki korabi
		cout << "\nName of ship:\t" << arrayShips[i].shipName;
	}
	cout << "\n\nEnter ship name: ";
	cin.ignore();
	cin.getline(name, 20);																			//vuvejdame ime

	for (int i = 0; i < n; i++) {																	//izvejdane na vsichki prevozi s vuvedeno ime
		if (!strcmp(arrayShips[i].shipName, name)) {
			system("cls");
			cout << "\nShips with name: " << name;
			cout << "\n\nNumber of ship:\t" << arrayShips[i].shipNum;
			cout << "\nName of ship:\t" << arrayShips[i].shipName;
			cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
			cout << "\nCargo capacity:\t" << arrayShips[i].cargoCap << " ton(s)";
			cout << "\nList of containers:";
			cout << "\n" << arrayShips[i].contCount << " containers";
			for (int j = 0; j < arrayShips[i].contCount; j++) {
				cout << "\nContainer number: " << arrayShips[i].contList[j].contNum;
				cout << "\nSize:\t" << arrayShips[i].contList[j].contSize << " ton(s)";
			}
			found = true;
			cout << "\n\nGo to next page \n";
			system("pause");
			system("cls");
		}
	}
	if (!found && n > 0) {																				//pitane za povtorienie pri nenamirane na korab
		char ch;
		cout << "\nShip not found!";
		cout << "\nDo you want to try again? (y/n) ";
		cin >> ch;
		if (ch != 'n' && ch != 'N') showByName(arrayShips, n);
	}
	system("cls");
}

void load(ship arrayShips[], int n) {																	//DOBAVQNE NA KONTEINER
	char ncontnum[10]; 
	double ncontsize;
	int br = 0;
	if (n == 0) { cout << "\nNo available ships!\n"; system("pause"); system("cls"); return; }			//proverka za nalichie na korabi
	cout << "Loading new container";
	cout << "\nEnter container number:\t";																//vuvejdame nomer
	cin >> ncontnum;
	do {
		cout << "\nEnter container size (Value 0-" << MAX_CONTAINERS << " ton(s)):\t";					//vuvejdame golemina 
		while (1)																						//Cikul za validaciq na chislo
		{
			cin >> ncontsize;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input " << endl;
				cout << "Try again" << endl;
			}
			else break;
		}
	} while (ncontsize < 0 || ncontsize > MAX_CONTAINERS);												//validaciq za golemina
	cout << "\nAvailable ships:";
	for (int i = 0; i < n; i++) {																		//izvejdame nalichnite korabi s dostatuchen kapacitet
		if (arrayShips[i].remCap >= ncontsize) {
			cout << "\n\nShip number: " << arrayShips[i].shipNum;
			cout << "\nShip name: " << arrayShips[i].shipName;
			cout << "\nAvailable capacity: " << arrayShips[i].remCap << " ton(s)";
			br++;
		}
	}
	if (br > 0) {																						//ako ima nalichni
		char choice[10];
		bool load = false;	//flag
		while (!load) {
			cout << "\n\nEnter ship number to load the container: ";									//vuvejdame nomer na korab
			cin >> choice;
			for (int i = 0; i < n; i++) {
				if (!strcmp(choice, arrayShips[i].shipNum)) {											//dobavqme konteinera v spisuka  s tovari
					strcpy_s(arrayShips[i].contList[arrayShips[i].contCount].contNum, ncontnum);
					arrayShips[i].contList[arrayShips[i].contCount].contSize = ncontsize;
					arrayShips[i].contCount++;
					arrayShips[i].remCap -= ncontsize;													//aktualizaciq na kapacitet
					load = true;
					cout << "\nContainer loaded succesfully!\n";
					system("pause");
					system("cls");
				}
			}
		}
	}
	else																								//ako nqma nalichni korabi
	{
		char ans;
		cout << "\nThere are no ships with enough capacity!";
		cout << "\nDo you want to split the container cargo (y/n)? ";
		cin >> ans;
		if (ans == 'N' || ans == 'n') { system("cls"); return; }										//pitane za razdelqne na tovara na konteinera
		else {
			double allCap = 0;																			//namirame sbora na celiq svoboden kapacitet na vsichki korabi
			for (int i = 0; i < n; i++) {
				allCap += arrayShips[i].remCap;
			}
			if (allCap < ncontsize) {																	//ako nqma dostatuchno prekusvame funkciqta
				cout << "\nNo enough capacity on all ships!\n";
				system("pause");
				system("cls");
				return;
			}
			do {
				double shipMostRemCap = arrayShips[0].remCap;											//namirame koraba s nai-golqma nalichen kapacitet i negoviq index
				int indexMax=0;
				for (int i = 1; i < n; i++) {
					if (arrayShips[i].remCap > shipMostRemCap) {
						shipMostRemCap = arrayShips[i].remCap;
						indexMax = i;
					}
				}
				if (ncontsize >= arrayShips[indexMax].remCap) {											//ako konteinera e po-golqm ot nalichniq kapacitet na koraba
					cout << "\n\nNew container number: " << ncontnum;
					cout << "\nNew container size: " << arrayShips[indexMax].remCap << " ton(s)";
					cout << "\n\nShip number: " << arrayShips[indexMax].shipNum;
					cout << "\nShip name: " << arrayShips[indexMax].shipName;
					cout << "\nAvailable capacity: " << arrayShips[indexMax].remCap << " ton(s)";
					strcpy_s(arrayShips[indexMax].contList[arrayShips[indexMax].contCount].contNum, ncontnum);
					arrayShips[indexMax].contList[arrayShips[indexMax].contCount].contSize = arrayShips[indexMax].remCap;
					arrayShips[indexMax].contCount++;													//dobavqme 1 konteiner v spisuka s koraba
					ncontsize = ncontsize - arrayShips[indexMax].remCap;								//aktualizaciq na tovara v konteinera
					arrayShips[indexMax].remCap = 0;													//aktualizaciq na ostavash kapacitet
					cout << "\nContainer loaded succesfully!\n\n";
					system("pause");
				}
				else {																					//ako konteinera e po-maluk ot nalichniq kapacitet na koraba
					cout << "\n\nNew container number: " << ncontnum;
					cout << "\nNew container size: " << ncontsize << " ton(s)";
					cout << "\n\nShip number: " << arrayShips[indexMax].shipNum;
					cout << "\nShip name: " << arrayShips[indexMax].shipName;
					cout << "\nAvailable capacity: " << arrayShips[indexMax].remCap << " ton(s)";
					strcpy_s(arrayShips[indexMax].contList[arrayShips[indexMax].contCount].contNum, ncontnum);
					arrayShips[indexMax].contList[arrayShips[indexMax].contCount].contSize = ncontsize;
					arrayShips[indexMax].contCount++;													//dobavqme 1 konteiner v spisuka s koraba
					arrayShips[indexMax].remCap -= ncontsize;											//aktualizaciq na tovara v konteinera
					ncontsize = 0;																		//aktualizaciq na ostavash kapacitet
					cout << "\nContainer loaded succesfully!\n";
					system("pause");
				}
			} while (ncontsize != 0);																	//dokato tovara na konteinera e raven na 0
			system("cls");
		}
	}
}

void remove(ship arrayShips[], int&n) {																	//OTKAZ OT PREVOZ I RAZPREDELENIE NA TOVARITE
	char numchoice[10];
	char arraynum[MAX_CONTAINERS][10];
	double arraysize[MAX_CONTAINERS];
	int contcount=0;
	bool remove = false;	//flag
	if (n == 0) { cout << "\nNo available ships!\n"; system("pause"); system("cls"); return; }			//proverka za nalichie na korabi
	cout << "Removing a ship and splitting cargo to other ships";
	cout << "\n\nShips list:";
	for (int i = 0; i < n; i++) {																		//izvejdane na nomerata na korabite
		cout << "\nShip number: " << arrayShips[i].shipNum;
	}
	do {
		cout << "\n\nEnter ship number: ";
		cin >> numchoice;
		for (int i = 0; i < n; i++) {
			if (!strcmp(numchoice, arrayShips[i].shipNum)) {											
				for (int j = 0; j < arrayShips[i].contCount; j++) {									//vzimame broq i spisuka s tovarite na dadeniq korab
					contcount++;
					strcpy_s(arraynum[j], arrayShips[i].contList[j].contNum);
					arraysize[j] = arrayShips[i].contList[j].contSize;
				}		
				cout << "\nShip with number " << arrayShips[i].shipNum << " removed succcesfully!"; //premahvame koraba ot masiva
				n = n - 1;																					//aktualizaciq na duljinata na masiva
				for (int j = i; j < n; j++) {
						arrayShips[j] = arrayShips[j + 1];
				}	
				remove = true;
			}
		}
	} while (!remove);
	cout << "\n\nSplitting cargo";
	int nocap = 0;																					//broi konteineri za koito nqma dostatuchno kapacitet na nikoi korab
	for (int i = 0; i < contcount; i++) {															//cikul za razpredelnie na konteineri
		int br = 0;																					//broi korabi s nalichen kapacitet
		cout << "\n\n\nContainer number: " << arraynum[i];
		cout << "\nSize: " << arraysize[i] << " ton(s)";
		for (int j = 0; j < n; j++) {																//izvejdame vsichki nalichni korabi
			if (arrayShips[j].remCap >= arraysize[i]) {
				cout << "\n\nShip number: " << arrayShips[j].shipNum;
				cout << "\nShip name: " << arrayShips[j].shipName;
				cout << "\nAvailable capacity: " << arrayShips[j].remCap << " ton(s)";
				br++;
			}
		}
		if (br > 0) {																				//ako ima nalichni korabi
			char choice[10];
			bool load = false;
			while (!load) {
				cout << "\n\nEnter ship number to load current container: ";						//izbirame nomera na koraba za dobavqne na konteinera
				cin >> choice;
				for (int j = 0; j < n; j++) {
					if (!strcmp(choice, arrayShips[j].shipNum)) {
						strcpy_s(arrayShips[j].contList[arrayShips[j].contCount].contNum, arraynum[i]);
						arrayShips[j].contList[arrayShips[j].contCount].contSize = arraysize[i];
						arrayShips[j].contCount++;
						arrayShips[j].remCap -= arraysize[i];
						load = true;
						cout << "\nContainer loaded succesfully!\n";
					}
				}
			}
		}
		else {																					//ako nqma nalichni korabi
			nocap++;
			cout << "\nThere are no ships with enough capacity for this container!\n";
			system("pause");
		}
	}
	if (nocap > 0) {																			//predlojenie za suzdavane na nov prevoz
		char choice;
		cout << "\n" << nocap << " containers could not be loaded on any ship!\n Do you want to add a new ship? (y/n) ";
		cin >> choice;
		system("cls");
		if (choice != 'n' && choice != 'N') {
			addOne(arrayShips,n);
		}
	}
	system("cls");
}

bool dateComp(date date1, date date2) {															//True ako date2 > date1
	if (date1.year < date2.year) return true;
	if (date1.year == date2.year && date1.month < date2.month)	return true;
	if (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day) return true;
	return false;
}

void sortDate(ship arrayShips[], int n) {														//SORTIRANE PO DATA
	ship buf; bool flag = true;
	for (int k = n; k > 1; k--) {																//BUBBLE SORT s flag
		if (!flag) break; else flag = false;
		for (int i = 0; i < k - 1; i++) {
			if (!dateComp(arrayShips[i].depDate, arrayShips[i + 1].depDate)) {					//proverka za po-golqma data
				buf = arrayShips[i];
				arrayShips[i] = arrayShips[i + 1];
				arrayShips[i + 1] = buf;
				flag = true;
			}
		}
	}
	cout << "Ships sorted by departure date\n\n";
	for (int i = 0; i < n; i++) {																//izvejdane na korabi
		cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
		cout << "\nNumber of ship:\t" << arrayShips[i].shipNum;
		cout << "\nName of ship:\t" << arrayShips[i].shipName;
		cout << "\nCargo capacity:\t" << arrayShips[i].cargoCap << " ton(s)";
		cout << "\n" << arrayShips[i].contCount << " containers\n\n\n";
	}
	system("pause");
	system("cls");
}

void sortCap(ship arrayShips[], int n) {														//SORTIRANE PO KAPACITET
	ship buf; bool flag = true;
	for (int k = n; k > 1; k--) {																//Bubble sort s flag
		if (!flag) break; else flag = false;
		for (int i = 0; i < k - 1; i++) {
			if (arrayShips[i].cargoCap > arrayShips[i+1].cargoCap) {
				buf = arrayShips[i];
				arrayShips[i] = arrayShips[i + 1];
				arrayShips[i + 1] = buf;
				flag = true;
			}
		}
	}
	cout << "Ships sorted by cargo capacity\n\n";
	for (int i = 0; i < n; i++) {
		cout << "\nCargo capacity:\t" << arrayShips[i].cargoCap << " ton(s)";
		cout << "\nNumber of ship:\t" << arrayShips[i].shipNum;
		cout << "\nName of ship:\t" << arrayShips[i].shipName;
		cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
		cout << "\n" << arrayShips[i].contCount << " containers\n\n\n";
	}
	system("pause");
	system("cls");
}

void showMinCap(ship arrayShips[], int n) {													//IZVEJDANE NA KORAB S MINIMALEN KAPACITET
	double minCap = arrayShips[0].cargoCap;
	for (int i = 1; i < n; i++) {															//cikul za namirane na minimalen capacitet
		if (arrayShips[i].cargoCap < minCap) {
			minCap = arrayShips[i].cargoCap;
		}
	}
	cout << "Ships with smallest cargo capacity:\n\n";
	cout << "\nCargo capacity:\t" << minCap << " ton(s)\n";
	for (int i = 0; i < n; i++) {															//izvejdane na korabi s minimalen kapacitet
		if (arrayShips[i].cargoCap == minCap) {
			cout << "\nNumber of ship:\t" << arrayShips[i].shipNum;
			cout << "\nName of ship:\t" << arrayShips[i].shipName;
			cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
			cout << "\n" << arrayShips[i].contCount << " containers\n\n\n";
		}
	}
	system("pause");
	system("cls");
}

void showMaxRemCap(ship arrayShips[], int n) {												//IZVEJDANE NA KORAB S NAI-GOLQMA RAZLIKA V TOVAR I KAPACITET
	double maxRemCap = arrayShips[0].remCap;
	for (int i = 1; i < n; i++) {															//cikul za namirane na nai-golqm nalichen kapacitet
		if (arrayShips[i].remCap > maxRemCap) {
			maxRemCap = arrayShips[i].remCap;
		}
	}
	cout << "Ships with largest remaining capacity:\n\n";
	cout << "\nRemaining capacity:\t" << maxRemCap << " ton(s)\n";
	for (int i = 0; i < n; i++) {															//izvejdane na korabi s nai-golqma razlika v tovar i kapacitet
		if (arrayShips[i].remCap == maxRemCap) {
			cout << "\nNumber of ship:\t" << arrayShips[i].shipNum;
			cout << "\nName of ship:\t" << arrayShips[i].shipName;
			cout << "\nDeparture date:\t" << arrayShips[i].depDate.day << "/" << arrayShips[i].depDate.month << "/" << arrayShips[i].depDate.year;
			cout << "\n" << arrayShips[i].contCount << " containers\n\n\n";
		}
	}
	system("pause");
	system("cls");
}

void saveFile(ship arrayShips[], int n) {												//ZAPAZVANE NA KORABITE VUV DVOICHEN FILE
	fstream shipfile;																	//ukazatel kum file
	shipfile.open(NAME, ios::binary | ios::out);
	if (!shipfile)																		//proverka za greshka
	{
		cout << endl << "Could not create file." << endl;
		exit(1);
	}

	shipfile.write((char*)arrayShips, (double)n*sizeof(ship));							//zapis na masiv
	shipfile.close();
	system("pause");
	system("cls");
}

void loadFile(ship arrayShips[], int &n) {												//ZAREJDANE NA KORABITE OT DVOICHEN FILE
	fstream shipfile;																	//ukazatel kum file
	long pos;
	ship currship;																		//lokalna promenliva za 1 korab
	shipfile.open(NAME, ios::binary | ios::in);
	if (!shipfile)																		//proverka za greshka
	{
		cout << endl << "Could not load file." << endl;
		exit(1);
	}
	shipfile.seekg(0, ios::end);
	pos = shipfile.tellg();																//vzimane na broi byte zapisani vuv file
	shipfile.seekg(0, ios::beg);
	n = pos / (sizeof(ship));															//namirane na broi korabi
	for (int i = 0; i < n; i++) {
		shipfile.read((char*)&currship, sizeof(ship));									//chetat se dannite za 1 korab
		arrayShips[i] = currship;														//populvane na masiva
	}
	shipfile.close();
	cout << "File loaded succesfully\n";
	system("pause");
	system("cls");
}
