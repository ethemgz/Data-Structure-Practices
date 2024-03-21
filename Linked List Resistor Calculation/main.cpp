#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>

using namespace std;

struct resistor{
	char group;
	double value;
	int quantity;
	resistor *next;
};

struct circuit{
	
	resistor *head;
	void create(char, double);
	void add_resistor(char, double);
	void remove_resistor(char);
	void delete_resistor(char);
	void circuit_info();
	void clear();
};

typedef circuit Datastructure;

Datastructure list;


int main(int argc, char **argv){
	
	ifstream file_p;
	
	file_p.open(argv[1]);
	if (!file_p) {
		cout << "File could not open!";
		exit(1);
	}
	
	
	char read_group;
	double read_value;
	
	//These reads from the file for the create function to initialize the list
	file_p >> read_group;
	file_p >> read_value;
	
	list.create(read_group, read_value);
	
	 
	while(file_p >> read_group){
		
		file_p >> read_value;
		
		if(read_group == 'A' && read_value == 0){
			list.circuit_info();
			
		}else if(read_value > 0){
			list.add_resistor(read_group, read_value);
			
		}else {
			list.remove_resistor(read_group);
			
		}
	}
	file_p.close();
	
	return 0;
}

void circuit::create(char group, double value){
	
	head = NULL;
	
	
	resistor *first = new resistor;

	first->group = group;
	first->value = value;
	
	first->quantity = 1;
	first->next = NULL;
	
	head = first;
}

void circuit::add_resistor(char group, double value){
	
	resistor *res_p;
	resistor *back_res_p;
	
	res_p = head;

	while(res_p){
		
		if(group == res_p->group){//If the group of the resistor that is going to be added already exists.
			
			res_p->quantity++;
			
			return;
		}else if( value < res_p-> value){//while looping through the list the moment a larger valued resistor have seen, new resistor should added before that one.
		
			resistor *add = new resistor;//create the new resistor
			add->value = value;
			add->group = group;
			add->quantity = 1;
			add->next = res_p;
			
			
			if(res_p == head){//If new resistor will be placed to head of the list head should point new resistor
				head = add;
			}else{//res_p ten ayrıca res_p in 1 arkasındaki pointerı tutmamın sebebi bu kısım. Önceki resistor'un yeni resistoru göstermesi.
				back_res_p->next = add;
			}
			
			return;
		}
		
		back_res_p = res_p;
		res_p = res_p->next;
	}
	
	//If we could get out of that loop this means there is no larger value than new resistor's value in the list. So, we should add new resistor to the end of the list.
	resistor *add = new resistor;
	
	add->value = value;
	add->group = group;
	back_res_p->next = add;
	add->quantity = 1;
	add->next = NULL;//or res_p
}

void circuit::remove_resistor(char group){
	
	resistor *res_p = head;
	
	while(res_p){
		
		if(group == res_p->group){
			
			if(res_p->quantity > 1){
				
				res_p->quantity--;
				
			}else if(res_p->quantity == 1){
				delete_resistor(group);
			}
			return;
		}
		
		res_p = res_p->next;
	}
	cout << "NO_RESISTOR" << endl;
}

void circuit::delete_resistor(char group){
	
	// cout << "NO_RESISTOR" << endl;
	
	resistor *res_p = head;
	// resistor *back_res_p;
	
	while(res_p){
		
		if(res_p->group == group){
			
			// if(res_p == head){//If the resistor that is going to be deleted is the head of the list
				
				// head = res_p->next;
				
			// }else{
				// back_res_p->next = res_p->next;
			// }
			
			*res_p = *res_p->next;
		}
		// back_res_p = res_p;
		res_p = res_p->next;
	}
}

void circuit::circuit_info(){
	
	// resistor *res_p = head;
	
	
	resistor *res_p = head;
	resistor *next_res_p = res_p->next;
	double total_value = 0;
	double same_quantity = 0;
	double same_value = 0;
	
	int i;
	
	while(res_p){
		i = 0;
		same_quantity = 0;
		same_value = 0;
		
		if(next_res_p != NULL){
			while(res_p->value == res_p->next->value){
				if(i == 0){
					same_quantity = res_p->quantity;
					same_value = (res_p->value / res_p->quantity);
				}
				i = 1;
				
				same_quantity = same_quantity + res_p->next->quantity;
				same_value = same_value + (res_p->next->value / res_p->next->quantity);
				
				res_p = res_p->next;
				next_res_p = res_p->next;
				
			}
			
			if(i == 1){
				cout << res_p->value << ":" << same_quantity << endl;
				total_value = total_value + same_value;
				res_p = res_p->next;
				continue;
			}
		}
		
		cout << res_p->value << ":" << res_p->quantity << endl;
		total_value = total_value + (res_p->value / res_p->quantity);
		res_p = res_p->next;
			
		if(res_p != NULL){
			next_res_p = res_p->next;
		}
	}
	cout << "Total resistance=" << total_value << " ohm" << endl;
}

void circuit::clear(){
	
	resistor *res_p;
	while (head){
		res_p = head;
		head = head->next;
		delete res_p;
	}
}















