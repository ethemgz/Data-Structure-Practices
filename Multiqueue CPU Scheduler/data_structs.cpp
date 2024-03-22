#include "data_structs.h"

void Stack::init(){
	
	head = NULL;
}

void Stack::push(Subtask* in){
	
	in->next = head;
	head = in;
}
Subtask* Stack::pop(){
	
	Subtask* ret_this;
	ret_this = head;
	head = head->next;
	return ret_this;
}
bool Stack::isEmpty(){
	if(head == NULL){
		return true;
	}else{
		return false;
	}
}
void Stack::close(){
	
	Subtask* del_this;
	while(head){
		del_this = head;
		head = head->next;
		delete del_this;
	}
}


/////////////////////////////////////////////////


void Queue::init(){
	head = NULL;
	tail = NULL;
}

void Queue::queue(Process* in){
	
	if(head == NULL){
		tail = in;
	}
	in->next = head;
	head = in;
}

Process* Queue::dequeue(){
	
	Process* ret_this;
	ret_this = tail;
	tail = tail->next;
	return ret_this;
}

bool Queue::isEmpty(){
	if(head == NULL){
		return true;
	}else{
		return false;
	}
}

// TODO front fonksiyonun ne yaptığı anla ve tamamla
Process* front();

void Queue::close(){
	
	Process* del_this;
	
	while(head){
		del_this = head;
		head = head->next;
		delete del_this;
	}
}


////////////////////////////////////////


void MultiQueue::init(){
	int i;
	
	for(i = 1; i < 4; i++){
		
		queues[i].head = NULL;
		queues[i].tail = NULL;
	}
}

void MultiQueue::queue(Process* in){
	
	int queue_num = (in->priority) - 1;
	
	if(queues[queue_num].head == NULL){
		queues[queue_num].head = in;
	}
	if(!queues[queue_num].head){
		queues[queue_num].tail->next = in;
	}
	queues[queue_num].tail = in;
	in->next = NULL;
}

Process* MultiQueue::dequeue(int priority){
	
	int queue_num = priority - 1;
	
	Process* ret_this;
	ret_this = queues[queue_num].head;
	queues[queue_num].head = queues[queue_num].head->next;
	
	return ret_this;
}

// bool MultiQueue::isempty(){
	// if(head == null){
		// return true;
	// }else{
		// return false;
	// }
// }

// TODO front fonksiyonun ne yaptığı anla ve tamamla
// process* front(int priority);

void MultiQueue::close(){
	
	Process* del_this;
	
	int i;
	
	for(i = 1; i < 4; i++){
		while(queues[i].head){
		del_this = queues[i].head;
		queues[i].head = queues[i].head->next;
		delete del_this;
		}
	}
	
}