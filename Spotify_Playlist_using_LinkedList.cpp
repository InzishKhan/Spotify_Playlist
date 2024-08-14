#include<iostream>
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
template<class T,class U>
class LinkedList {
	class Node {
	public:
		T DanceAb; //DATA FOR EACH NODE
		T Energy;
		T Key;
		T Loudness;
		T Speechness;
		T Acoustic;
		T Instrument;
		U Duration;
		T Genre;
		T SongT;
		Node* next=nullptr;
	};
public:
	Node* head;
	Node* tail;
	LinkedList() {
		head = tail = nullptr;
	}
	Node* createNode(T dance, T energy, T key, T loudness, T speech, T acoustic, T instrument, U duration, T genre, T songt) {
		Node* temp = new Node();
		temp->DanceAb = dance;
		temp->Energy = energy;
		temp->Key = key;
		temp->Loudness = loudness;
		temp->Speechness = speech;
		temp->Acoustic = acoustic;
		temp->Instrument = instrument;
		temp->Duration = duration;
		temp->Genre = genre;
		temp->SongT = songt;
		temp->next = nullptr;
		return temp;
	}
	void insertSong(T dance, T energy, T key, T loudness, T speech, T acoustic, T instrument, U duration, T genre, T songt) {
		if (head == nullptr) {
			head = tail = createNode(dance, energy, key, loudness, speech, acoustic, instrument, duration, genre, songt);
		}
		else {
			tail->next = createNode( dance,  energy, key, loudness, speech, acoustic, instrument, duration,  genre,  songt);
			tail = tail->next;
		}
	}
	void insertNode(T songt) {
		if (head == nullptr) {
			head = tail = createNode(" ", " ", " ", " ", " ", " ", " ", 0, " ", songt);
		}
		else {
			tail->next = createNode(" ", " ", " ", " ", " ", " ", " ", 0, " ", songt);
			save(songt);
			tail = tail->next;
			cout << endl;
		}
	}
private:
	void deleteAtHead() {
		Node* ptr = head;
		head = head->next;
		delete ptr;
	}
	void deleteAtTail() {
		Node* ptr = head;
		Node* temp;
		while (ptr->next != tail) {
			ptr = ptr->next;
		}
		temp = ptr->next;
		ptr->next = nullptr;
		tail = ptr;
		delete temp;
	}
	Node * deleteImmediate(T songT) {
		Node* ptr = head;
		while (ptr->next != tail && ptr) {
			if (songT == ptr->next->SongT) {
				return ptr;
			}
			ptr = ptr->next;
		}
		return nullptr;
	}
public:
	void deleteNode( T songt) {
		if (songt == head->SongT) {
			deleteAtHead();
		}
		else if (songt == tail->SongT) {
			deleteAtTail();
		}
		else {
			Node* ptr = deleteImmediate(songt);
			if (ptr != nullptr) {
				Node* temp = ptr->next;
				ptr->next = temp->next;
				delete temp;
			}
		}
	}
	void Shuffle() {
		int ans = 1; 
		Node* h = head;
		while (h != nullptr) {
			ans++;
			h = h->next;
		}
		int arr[2500];
		for (int i = 0; i < ans; i++) {
			arr[i] = i+1 ;
		}
		for (int i = 0; i < ans; i++) {
			//generating random numbers within the range without duplicates
			int index =( rand() % ans)+1;
			int temp = arr[i];
			arr[i] = arr[index];
			arr[index] = temp;
		}
		 //arr is the array that cotains random numbers within the range
		Node* ptr = head;// iterating towards the head
		Node* cx = nullptr;
		Node* tmp = nullptr;
		Node* cy = nullptr;
		Node* py = nullptr;
		Node* px = nullptr;
		int i = 0;
		while (ptr != nullptr && i<ans) {
			cy = currentY(arr, i);
			py = prevY(arr, i);
			px = prevX(ptr);
			cx = ptr;
			if (cx == nullptr || cy == nullptr) {
				return;
			}
			if (ptr == head) {
				head = cy;
				tmp = cy->next;
				cy->next = cx->next;
				py->next = cx;
				cx->next = tmp;
			}
			else if (ptr == tail) {
				tail = cx;
				px->next = cy;
				cy->next = cx->next;
				py->next = cx;
				cx->next = nullptr;
			}
			else {
				tmp = cy->next;
				px->next = cy;
				cy->next = cx->next;
				py->next = cx;
				cx->next = tmp;
			}
			ptr = ptr->next;
			i++;
		}
	}
	private:
	Node* currentY(int* arr,int index) {
		Node* ptr = head;
		index-1 ; //to get the current node at the index
		int i = 0;
		while (ptr != nullptr && i < arr[index]) {
			ptr = ptr->next;
			i++;
		}
		return ptr;
	}
	Node* prevY(int* arr, int index) {
		Node* ptr = head;
		index-2; //to get the current node at the index
		int i = 0;
		while (ptr != nullptr && i < arr[index] ) {
			ptr = ptr->next;
			i++;
		}
		return ptr;
	}
	Node* prevX(Node * ptr) {
		Node* k = head;
		while (k != ptr) {
			k = k->next;
		}
		return k;
	}
	bool search(T songT){
		Node* ptr = head;
		if (head == nullptr) {
			cout << "Song not in the list";
			return false;
		}
		else {
			while (ptr->next != nullptr) {
				if (songT == ptr->SongT) {
					return true;
				}
				ptr = ptr->next;
			}
		}
		return false;
	}
	int  searchHelper(T songt) {
		Node* ptr = head;
		int count = 0;
		if (head == nullptr) {
			cout << "Song not in the list";
			return 0;
		}
		else {
			while (ptr->next != nullptr) {
				if (ptr->SongT == songt) {
					count++;
					return count;
				}
				ptr = ptr->next;
			}
		}

	}
	void SortingList() {
		Node* ptr = head;
		Node* ptr1 = nullptr;
		string temp;
		if (head == nullptr) {
			cout << "List is Empty !" << endl;
		}
		else {
			while (ptr != nullptr) {
				ptr1 = ptr->next;
				while (ptr1 != nullptr) {
					if (ptr->SongT > ptr1->SongT) {
						temp = ptr->SongT;
						ptr->SongT = ptr1->SongT;
						ptr1->SongT = temp;
					}
					ptr1 = ptr1->next;
				}
				ptr = ptr->next;
			}
		}
	}
	void save(T songt) {
		string a = songt;
		ofstream file;
		file.open("text.csv", ios::app);
		file << a << "\n";
	}
	public:
	void removeDuplicate() {
		SortingList();
		Node* ptr = head;
		Node* ptr1 = nullptr;
		Node* temp = nullptr;
		if (head == nullptr) {
			cout << "No duplicates in the linked list ";
			return;
		}
		else {
			while (ptr->next != nullptr) {
				if (ptr->SongT == ptr->next->SongT) {
					temp = ptr->next->next;
					ptr1 = ptr->next;
					delete ptr1;
					ptr->next = temp;
				}
				else {
					ptr = ptr->next;
				}
			}
		}
	}
	void RepeatSong(T songt,int a) {
		removeDuplicate();
		Node* ptr = head;
		Node* ptr1 = head;
		Node* temp = nullptr; //exit next address
		if (search(songt)) {
			while (ptr1 != nullptr) {
				if (ptr1->SongT == songt) {
					temp = ptr1->next;
				}
				ptr1 = ptr1->next;
			}
		}

		if (search(songt)) {
			while (ptr != nullptr && ptr->next != ptr) {
				if (ptr->SongT == songt && a == 0) {
					ptr->next = ptr;
					break;
				}
				else if (ptr->next == ptr && a == 1) {
					ptr->next = temp;
				}
				ptr = ptr->next;
			}
		}
	}
	void PrevRepeat(T songT) {
		//removeDuplicate();
		Node* ptr = head;
		Node* temp = nullptr;
		if (search(songT)) {
			while (ptr->next != nullptr && ptr->next != ptr) {
				if (ptr->next->SongT == songT ) {
					temp = ptr;
				}
				ptr = ptr->next;
			}
			ptr->next = temp;
			temp->next = nullptr;
		}
	}
	void SortDuration() {
		Node* ptr = head;
		Node* ptr1 = nullptr;
		int temp;
		if (head == nullptr) {
			cout<<"List is Empty !"<<endl;
		}
		else {
			while (ptr != nullptr ){
				ptr1 = ptr->next;
				while (ptr1 != nullptr) {
					if (ptr->Duration > ptr1->Duration) {
						temp = ptr->Duration;
						ptr->Duration = ptr1->Duration;
						ptr1->Duration = temp;
					}
					ptr1 = ptr1->next;
				}
				ptr = ptr->next;
			}
		}
	}
	void SortSongT() {
		Node* ptr = head;
		Node* ptr1 = nullptr;
		string temp;
		if (head == nullptr) {
			cout << "List is Empty !" << endl;
		}
		else {
			while (ptr != nullptr) {
				ptr1 = ptr->next;
				while ( ptr1 != nullptr) {
					if (ptr->SongT[0] > ptr1->SongT[0]) {
						temp = ptr->SongT;
						ptr->SongT = ptr1->SongT;
						ptr1->SongT = temp;
					}
					ptr1 = ptr1->next;
				}
				ptr = ptr->next;
			}
		}
	}
	
	void printList(T songt) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->SongT == songt) {
				cout <<"Danceability :\t" << temp->DanceAb << "\n";
				cout <<"Energy :\t" << temp->Energy << "\n";
				cout <<"Key :\t"<< temp->Key << "\n";
				cout <<"Loudness :\t"<< temp->Loudness << "\n";
				cout << "Speechness :\t"<< temp->Speechness << "\n";
				cout << "Acousticness :\t"<< temp->Acoustic << "\n";
				cout << "Insturmentalness :\t"<< temp->Instrument << "\n";
				cout << "Duration _ms :\t"<< temp->Duration << "\n";
				cout << "Genre :\t"<< temp->Genre << "\n";
				cout << "Song Tile :\t"<< temp->SongT << "\n";
				cout << endl;
			}
			temp = temp->next;
		}
		cout << endl;
	}
	void PRINTl() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << "Danceability :\t" << temp->DanceAb << "\n";
			cout << "Energy :\t" << temp->Energy << "\n";
			cout << "Key :\t" << temp->Key << "\n";
			cout << "Loudness :\t" << temp->Loudness << "\n";
			cout << "Speechness :\t" << temp->Speechness << "\n";
			cout << "Acousticness :\t" << temp->Acoustic << "\n";
			cout << "Insturmentalness :\t" << temp->Instrument << "\n";
			cout << "Duration _ms :\t" << temp->Duration << "\n";
			cout << "Genre :\t" << temp->Genre << "\n";
			cout << "Song Tile :\t" << temp->SongT << "\n";
			cout << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	void printR() {
		Node* temp = head;
		while (temp != nullptr && temp->next!=temp ) {
			cout << temp->SongT << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	void PrintD() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->Duration << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	void Print() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->SongT <<"\n";
			temp = temp->next;
		}
		cout << endl;
	}
	void SaveUS() {
		SortingList();
		removeDuplicate();
		Node* temp = head;
		while (temp != nullptr) {
			ofstream File;
			File.open("UniqueSongs.csv", ios::app);
			File << temp->SongT << "\n";
			temp = temp->next;
		}
	}

};
int Menu() {
	int choice=0;
	do {
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "                MENU                   " << endl;
		cout << "---------------------------------------" << endl;
		cout << endl;
		cout << "1. Insert Node      " << endl;
		cout << "2. Delete Node      " << endl;
		cout << "3. Shuffle List     " << endl;
		cout << "4. Sort (Duration)      " << endl;
		cout << "5. Sort (Name Initials) " << endl;
		cout << "6. Repeat Song       "<<endl;
		cout << "7. Previous Song     "<<endl;
		cout << "8. PLay Linked List(Song)  "<<endl;
		cout << "9. Play Linked List     " << endl;
		cout << "10.Save              "<<endl;
		cout << "11.Exit              "<<endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "Enter your choice : " << endl;
		cin >> choice;
	} while (choice < 1 || choice>11);
	return choice;
}
string Title() {
	string a;
	cout << "Enter the Song Title : ";
	cin >> a;
	return a;
}
int main() {

	ifstream myFileStream("Songs Information.csv");
	if (!myFileStream.is_open()) {
		cout << "File Failed to open" << endl;
		return 0;
	}
	int count = 2;
	string Acous,Instru,genre,songt;
	string dance, energy, speech;
	string key, duration,loud;
	string line;
	int d;
	LinkedList <string,int> l; //linked list object
	while (getline(myFileStream, line) && count<=2000) {
		stringstream ss(line);
		getline(ss, dance, ','); //danceability
		getline(ss, energy, ','); //energy
		getline(ss, key,',');  //key
		getline(ss, loud,',');//loudness
		getline(ss, speech,','); //speechness
		getline(ss, Acous,','); //acoustic
		getline(ss, Instru,','); //intrumentalness
		getline(ss, duration,',');//duration
		d = stoi(duration);
		getline(ss, genre,','); //genre
		getline(ss, songt,','); //song title
		count++;
		l.insertSong(dance, energy, key, loud, speech, Acous, Instru, d, genre, songt);
	}
	int choice = 0;
	string a;
	do {
		choice = Menu();
		if (choice == 1) {
			cout << "Enter the Song Title : ";
			cin >> a;
			l.insertNode(a);
			cout << "Song successfully Added !" << endl;
		}
		else if (choice == 2) {
			l.deleteNode("Call Of The Baphomet");
			cout << "Song Successfully deleted !" << endl;
		}
		else if (choice == 3) {
			l.Shuffle();
			cout << "Song Successfully shuffled !" << endl;
			l.Print();
		}
		else if (choice == 4) {
			l.SortDuration();
			cout << "Successfully Sorted (Duration) ! " << endl;
			l.PrintD();
		}
		else if (choice == 5) {
			l.SortSongT();
			cout << "Succesfully Sorted (Initials) ! " << endl;
			l.Print();
		}
		else if(choice== 6) {
			cout << "Repeating the recent song" << endl;
			l.RepeatSong("Call Of The Baphomet", 0); // 0- repeat 1-exit
			l.printR();
		}
		else if (choice == 7) { //prev repeat
			cout << "Exiting repeatition by moving onto previous song" << endl;
			l.PrevRepeat("Call Of The Baphomet");
			l.printR();
		}
		else if (choice == 8) {
			l.printList("Call Of The Baphomet");
		}
		else if (choice == 9) {
			//l.PRINTl(); //whole data
			l.Print(); //song display
		}
		else if (choice == 10) {
			l.SaveUS();
			cout << "Saved Successfully" << endl;
		}

	} while (choice != 11);
	cout << "Exited....." << endl;
	exit(0);
	Sleep(-1);
	return 0;
}