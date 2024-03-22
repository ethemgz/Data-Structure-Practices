#include "data_structs.h"

int TIME;
int SPECIAL_CONDITION;

Queue Queue;
MultiQueue MultiQueue;

void next_process();
void execute_subtask(Process* run);

int main(int argc, char **argv){
	
	ifstream file_p;
	
	file_p.open(argv[1]);
	if (!file_p) {
		cout << "File could not open!";
		exit(1);
	}
	
	string process_name;
	int i;
	
	MultiQueue.init();
	
	while(file_p >> process_name){
		
		
		Process* npro = new Process;
		
		npro->name = process_name;
		file_p >> npro->priority;
		file_p >> npro->arrival_time;
		file_p >> npro->task_count;
		
		
		npro->task_stack.init();
		
		for(i = 0; i < npro->task_count; i++){
			
			Subtask* nsub = new Subtask;
			
			file_p >> nsub->name;
			file_p >> nsub->duration;
			
			npro->task_stack.push(nsub);
		}
		
		//send Processes to multiqueue. I am aware of in the homework it wasn't stated like that but I didn't see any reason not to do this way.
		MultiQueue.queue(npro);
		cout << "hi";
	}
	cout << endl << MultiQueue.queues[0].tail->name;
	
	
	while(MultiQueue.queues[0].head || MultiQueue.queues[1].head || MultiQueue.queues[2].head){// If there there is an element at least one of the queues keep looping
		
		
		next_process();
		
	}
	
}

void next_process(){
	
	// cout << MultiQueue.queues[0].tail->arrival_time;
	
	
	if((MultiQueue.queues[0].tail) && (TIME >= MultiQueue.queues[0].tail->arrival_time)){// If priority 1 is waiting on the line execute it directly
		// cout << "O1O ";
		execute_subtask(MultiQueue.queues[0].tail);
		
		
		
		if((MultiQueue.queues[2].tail)&&(TIME >= MultiQueue.queues[2].tail->arrival_time)){
			SPECIAL_CONDITION = 0;
		}
		
	}else if((MultiQueue.queues[1].tail)&&(MultiQueue.queues[2].tail)&&(TIME >= MultiQueue.queues[1].tail->arrival_time) && (TIME >= MultiQueue.queues[2].tail->arrival_time)){// If both priorty 3 and 2 are waiting
		
		// cout << "O23O ";
		
		if(SPECIAL_CONDITION >= 2){
			SPECIAL_CONDITION = 0;
			execute_subtask(MultiQueue.queues[2].tail);
			
		}else {
			SPECIAL_CONDITION++;
			execute_subtask(MultiQueue.queues[1].tail);
		}
	}else if((MultiQueue.queues[1].tail)&&(TIME >= MultiQueue.queues[1].tail->arrival_time)){//only priority 2 is waiting
		// cout << "O2O ";
		execute_subtask(MultiQueue.queues[1].tail);
		
	}else if((MultiQueue.queues[2].tail) && (TIME >= MultiQueue.queues[2].tail->arrival_time)){//only priority 3 is waiting
		// cout << "O3O ";
		SPECIAL_CONDITION = 0;
		
		execute_subtask(MultiQueue.queues[2].tail);
		
	}else{//No one is waiting. Find which process will come next and update TIME
		
		int pri1, pri2, pri3;
		
		pri1 = MultiQueue.queues[0].tail->arrival_time;
		pri2 = MultiQueue.queues[1].tail->arrival_time;
		pri3 = MultiQueue.queues[2].tail->arrival_time;
		
		SPECIAL_CONDITION = 0;
		
		
		if(pri1 <= pri2){
			if(pri1 <= pri3){
				TIME = pri1;
			}else{
				TIME = pri3;
			}
		}else {
			if(pri2 <= pri3){
				TIME = pri2;
			}else{
				TIME = pri3;
			}
		}
	}
}

void execute_subtask(Process* run){
	
	Subtask* removed_subtask;
	
	removed_subtask = run->task_stack.pop();
	TIME = TIME + removed_subtask->duration;
	
	cout << run->name << " " << removed_subtask->name << endl;
	
	// cout << MultiQueue.queues[0].tail->name;
	if(run->task_stack.isEmpty()){
		MultiQueue.dequeue(run->priority);
	}
	
}
















