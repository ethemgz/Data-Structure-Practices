#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

void Train::create(){
    head = NULL;
}; 

void Train::addMaterial(char material, int weight){
	
	//if there are no wagons added to the list go and add a wagon
	if(head == NULL){
		
		addWagon(material, weight);
		return;
	}
	
	
	materialNode* tempMaterial;
	materialNode* prevTempMaterial;
	
	wagonNode* tempWagon;
	tempWagon = head;
	
	int extraWeight;
	bool materialAdded = false;
	
	
	
	while(tempWagon != NULL){ // traverse all the wagons
		
		tempMaterial = tempWagon->material;
		prevTempMaterial = tempWagon->material;
		
		if(tempMaterial == NULL){//if nothing exist in the wagon
			// cout << "nothing exist in the wagon" << endl;
			materialNode* newMaterial = new materialNode;
			
			tempWagon->material = newMaterial;
			tempMaterial = newMaterial;
			newMaterial->id = material;
			newMaterial->weight = weight;
			newMaterial->next = NULL;
			
			
			
			if(tempMaterial->weight > WEIGHT_CAPACITY){
				
				extraWeight = tempMaterial->weight - WEIGHT_CAPACITY;
				tempMaterial->weight = WEIGHT_CAPACITY;
				addMaterial(material, extraWeight);
				return;
			}
			
			materialAdded = true;
			return;
		}
		
		// find the relevant material
		while((tempMaterial != NULL) && (tempMaterial->id < material)){
			
			prevTempMaterial = tempMaterial;
			tempMaterial = tempMaterial->next;
			// cout << "hi1";
		}
		
		if((tempMaterial == NULL) || (tempMaterial->id < material)){//if the relevent material spot does not exist in this wagon add to end
			
			// cout << "relevent material spot does not exist in this wagon add to end" << endl;
			materialNode* newMaterial = new materialNode;
			
			newMaterial->id = material;
			newMaterial->weight = weight;
			newMaterial->next = prevTempMaterial->next;
			
			prevTempMaterial->next = newMaterial;
			
			if(newMaterial->weight > WEIGHT_CAPACITY){
				
				extraWeight = newMaterial->weight - WEIGHT_CAPACITY;
				newMaterial->weight = WEIGHT_CAPACITY;
				addMaterial(material, extraWeight);
				
			}
			materialAdded = true;
			return;
		}else if((tempMaterial == (prevTempMaterial)) && (prevTempMaterial->id != material)){//if the relevent material spot does not exist in this wagon add to beginning
			
			// cout << "relevent material spot does not exist in this wagon add to beginning" << endl;
			materialNode* newMaterial = new materialNode;
			
			newMaterial->id = material;
			newMaterial->weight = weight;
			newMaterial->next = tempWagon->material;
			
			tempWagon->material = newMaterial;
			
			if(newMaterial->weight > WEIGHT_CAPACITY){
				
				extraWeight = newMaterial->weight - WEIGHT_CAPACITY;
				newMaterial->weight = WEIGHT_CAPACITY;
				addMaterial(material, extraWeight);
				
			}
			materialAdded = true;
			return;
		}else if(tempMaterial->id > material){//if the relevent material spot does not exist in this wagon add to middle
			
			// cout << "relevent material spot does not exist in this wagon add to middle" << endl;
			materialNode* newMaterial = new materialNode;
			
			newMaterial->id = material;
			newMaterial->weight = weight;
			newMaterial->next = prevTempMaterial->next;
			
			prevTempMaterial->next = newMaterial;
			
			if(newMaterial->weight > WEIGHT_CAPACITY){
				
				extraWeight = newMaterial->weight - WEIGHT_CAPACITY;
				newMaterial->weight = WEIGHT_CAPACITY;
				addMaterial(material, extraWeight);
				
			}
			materialAdded = true;
			return;
		}else if(tempMaterial->weight != WEIGHT_CAPACITY){// if the spot for the specific material is not full
			
			// cout << "spot for the specific material is not full" << endl;

			tempMaterial->weight = tempMaterial->weight + weight;
			
			if(tempMaterial->weight > WEIGHT_CAPACITY){
				
				extraWeight = tempMaterial->weight - WEIGHT_CAPACITY;
				tempMaterial->weight = WEIGHT_CAPACITY;
				addMaterial(material, extraWeight);
				// cout << "before return" << endl;
				return;
				// cout << "after return" << endl;
			}
			materialAdded = true;
			return;
		}
		
		tempWagon = tempWagon->next;
	}
	
	
	if(materialAdded == false){
		// cout << "hi7";
		addWagon(material, weight);
		return;
	}
	return;
};


void Train::deleteFromWagon(char material, int weight){
	
	materialNode* tempMaterial;
	materialNode* prevTempMaterial;
	
	wagonNode* tempWagon;
	wagonNode* prevTempWagon;
	tempWagon = head;
	prevTempWagon = head;
	
	
	int extraWeight;
	
	while(tempWagon != NULL){
		
		tempMaterial = tempWagon->material;
		
		// find the relevant material
		while((tempMaterial != NULL) && (tempMaterial->id < material)){
			
			prevTempMaterial = tempMaterial;
			tempMaterial = tempMaterial->next;
			// cout << "hi1";
		}
		
		if(tempMaterial == NULL || tempMaterial->id != material){// if the relevent material spot is not exist in this wagon go to the previous wagon
			
			// cout << "relevent material spot is not exist in this wagon go to the previous wagon" << endl;
			
			
			prevTempMaterial = prevTempWagon->material;
			tempMaterial = prevTempWagon->material;
			
			// find the relevant material
			while(tempMaterial->id != material){
				
				prevTempMaterial = tempMaterial;
				tempMaterial = tempMaterial->next;
			}
			tempMaterial->weight = tempMaterial->weight - weight;
			
			
			if(tempMaterial->weight < 0){
				
				extraWeight = -tempMaterial->weight;
				
				if(tempWagon->material == tempMaterial){
					
				tempWagon->material = tempMaterial->next;
				}else{
					prevTempMaterial->next = tempMaterial->next;
				}
				
				deleteFromWagon(material, extraWeight);
			}else if(tempMaterial->weight == 0){
				
				if(tempWagon->material == tempMaterial){
					
				tempWagon->material = tempMaterial->next;
				}else{
					prevTempMaterial->next = tempMaterial->next;
				}
			}
			return;
			
		}else if((tempMaterial->id == material) && (tempMaterial->weight < WEIGHT_CAPACITY)){// if relevant material does exist in this wagon and it is not full
			
			// cout << "relevant material does exist in this wagon and it is not full" << endl;
			
			tempMaterial->weight = tempMaterial->weight - weight;
			
			
			if(tempMaterial->weight < 0){
				
				extraWeight = -tempMaterial->weight;
				
				if(tempWagon->material == tempMaterial){
					
				tempWagon->material = tempMaterial->next;
				}else{
					prevTempMaterial->next = tempMaterial->next;
				}
				
				if(tempWagon->material == NULL){
					deleteWagon(tempWagon->wagonId);
					// prevTempWagon->next = NULL;
				}
				deleteFromWagon(material, extraWeight);
			}else if(tempMaterial->weight == 0){
				// cout << "is equal to zero";
				if(tempWagon->material == tempMaterial){
					
				tempWagon->material = tempMaterial->next;
				}else{
					prevTempMaterial->next = tempMaterial->next;
				}
				
				if(tempWagon->material == NULL){
					deleteWagon(tempWagon->wagonId);
					// prevTempWagon->next = NULL;
					// if(prevTempWagon == head){
						// head = NULL;
					// }
				}
			}
			
			return;
		}
		
		prevTempWagon = tempWagon;
		tempWagon = tempWagon->next;
	}
	// if last wagon has 2000 items of the relevant material
	
	// cout << "last wagon has 2000 items of the relevant material" << endl;
	
	tempWagon = prevTempWagon;
	tempMaterial = tempWagon->material;
	
	// find the relevant material
	while(tempMaterial->id != material){
		
		prevTempMaterial = tempMaterial;
		tempMaterial = tempMaterial->next;
	}
	tempMaterial->weight = tempMaterial->weight - weight;
			
	// cout << "something";
	if(tempMaterial->weight < 0){
		
		extraWeight = -tempMaterial->weight;
		
		if(tempWagon->material == tempMaterial){
			
		tempWagon->material = tempMaterial->next;
		}else{
			prevTempMaterial->next = tempMaterial->next;
		}
		
		if(tempWagon->material == NULL){
			deleteWagon(tempWagon->wagonId);
			// prevTempWagon->next = NULL;
		}
		deleteFromWagon(material, extraWeight);
	}else if(tempMaterial->weight == 0){
		// cout << "is equal to zero";
		if(tempWagon->material == tempMaterial){
			
		tempWagon->material = tempMaterial->next;
		}else{
			prevTempMaterial->next = tempMaterial->next;
		}
		
		if(tempWagon->material == NULL){
			deleteWagon(tempWagon->wagonId);
			// prevTempWagon->next = NULL;
			// if(prevTempWagon == head){
				// head = NULL;
			// }
		}
	}
	
	return;
	
};  


void Train::addWagon(char material, int weight){
	
	wagonNode* tempWagon;
	wagonNode* prevTempWagon;
	tempWagon = head;
	int wagonNumber = 1;
	
	wagonNode* newWagon = new wagonNode;
	
	if(head == NULL){
		wagonNumber = 1;
		head = newWagon;
		
	}else {
		while(tempWagon != NULL){
		
		prevTempWagon = tempWagon;
		tempWagon = tempWagon->next;
		wagonNumber++;
		}
	}
	
	prevTempWagon->next = newWagon;
	newWagon->wagonId = wagonNumber;
	newWagon->material = NULL;
	newWagon->next = NULL;
	
	
	addMaterial(material, weight);
}; 


void Train::deleteWagon(int id){
        //FILL THIS FUNCTION ACCORDINGLY
		
		wagonNode* tempWagon;
		wagonNode* prevTempWagon;
		tempWagon = head;
		prevTempWagon = tempWagon;
		
		if(id == 1){
			head = NULL;
		}else {
			while(tempWagon){
				if(tempWagon->wagonId == id){
					prevTempWagon->next = NULL;
				}
				prevTempWagon = tempWagon;
				tempWagon = tempWagon->next;
			}
		}
}; 

void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
		
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 