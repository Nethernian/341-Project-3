#include "rqueue.h"
#include "ctime"

class Tester {
public:
    bool testBasicRQueueInsert(RQueue& rQueue);

    bool testBasicRQueueCopyConstructor(RQueue& rQueue);

    bool testBasicRQueueRemove(RQueue& rQueue);

    bool testBasicRQueueMerge(RQueue& rQueue, RQueue& lQueue);

    bool testBasicRQueuePriorityChange(RQueue& rQueue, prifn_t newFunc);

    void testRQueueTime(RQueue& rQueue, int trials, int N);

};

bool Tester::testBasicRQueueInsert(RQueue &rQueue) {
    bool inserted;

    rQueue.insertStudent(Student("", 0, 0, 0, 0));

    if(rQueue._size > 0){
        inserted = true;
    }else{
        inserted = false;
    }

    return  inserted;
}

bool Tester::testBasicRQueueCopyConstructor(RQueue &rQueue) {
    bool copied;
    RQueue copyQueue(rQueue);

    cout << "   rQueue: " << endl;
    rQueue.dump();
    cout << "   copyQueue: " << endl;
    copyQueue.dump();

    if(&rQueue == &copyQueue){
        copied = false;
    }else{
        copied = true;
    }

    return copied;
}

bool Tester::testBasicRQueueRemove(RQueue &rQueue) {
    bool removed;
    int originalSize = rQueue._size;\

    rQueue.getNextStudent();

    if(originalSize > rQueue._size){
        removed = true;
    }else{
        removed = false;
    }

    return removed;
}

// A tester for the mergeWithQueue function.
bool Tester::testBasicRQueueMerge(RQueue &rQueue, RQueue &lQueue) {
    bool merged;
    int ideal_size = rQueue.numStudents() + lQueue.numStudents();

    rQueue.mergeWithQueue(lQueue);

    if(rQueue.numStudents() == ideal_size){
        merged = true;
    }else{
        merged = false;
    }

    return merged;
}


bool Tester::testBasicRQueuePriorityChange(RQueue& rQueue, prifn_t newFunc){
    bool prioritycheck;
    prifn_t funct = rQueue.getPriorityFn();

    rQueue.setPriorityFn(newFunc);

    if(funct != rQueue.getPriorityFn()){
        prioritycheck = true;
    }else{
        prioritycheck = false;
    }

    return prioritycheck;
}

void Tester::testRQueueTime(RQueue& rQueue, int trials, int N){
    double time;
    clock_t begin, end;

    for(int i = 0; i < trials; i++){
        cout << "Trial: " << i+1 << " : " << N << " Elements" << endl;
        begin = clock();
        for(int x = 0; x < N; x++){
            rQueue.insertStudent(Student("T", 1,0,0,0));
        }
        end = clock();
        time = end - begin;
        cout << "Enqueueing: " << N << " Elements took: " << time << " Ticks (" << time/CLOCKS_PER_SEC << " sec)" << endl;
        N = N * 2;
    }
}

//

int priorityFn1(const Student &tudent);
int priorityFn2(const Student &student);

int main(){
    Tester tester;

    RQueue Queue1(priorityFn1);
    RQueue Queue2(priorityFn1);

    cout << "Testing Basic Insert function: " << endl;
    if(tester.testBasicRQueueInsert(Queue1)){
        cout << "   Passed Test" << endl;
    }else{
        cout << "   Failed Test" << endl;
    }

    cout << endl << "QUEUE WITH 1 INSERT: " << endl;
    Queue1.printStudentQueue();

    cout << endl << "Testing Basic Remove function: " << endl;
    if(tester.testBasicRQueueRemove(Queue1)){
        cout << "   Passed Test" << endl;
    }else{
        cout << "   Failed Test" << endl;
    }

    cout << endl << "QUEUE WITH 1 REMOVE: " << endl;
    Queue1.printStudentQueue();

    cout << endl << "Filling Queue 1 & 2 to test a merge:" << endl;

    Queue1.insertStudent(Student("bob", 1,1,1,0));
    Queue1.insertStudent(Student("bill", 2,2,1,0));
    Queue1.insertStudent(Student("boris", 3,2,2,0));
    Queue1.insertStudent(Student("benson", 4,2,2,1));
    Queue1.insertStudent(Student("barry", 5,3,1,1));

    Queue2.insertStudent(Student("cassius", 1,1,0,0));
    Queue2.insertStudent(Student("carl", 6,2,2,0));
    Queue2.insertStudent(Student("carry", 5,1,0,1));

    if(tester.testBasicRQueueMerge(Queue1, Queue2)){
        cout << "   Merge Test Passed" << endl;
    }else{
        cout << "   Merge Test Failed" << endl;
    }

    cout << endl << "Test Copy Constructor:" << endl;
    if(tester.testBasicRQueueCopyConstructor(Queue1)){
        cout << "   Test Passed" << endl;
    }else{
        cout << "   Test Failed" << endl;
    }

    cout << endl << "Test Priority Function Change:" << endl;
    if(tester.testBasicRQueuePriorityChange(Queue1, priorityFn2)){
        cout << "   Test Passed" << endl;
    }else{
        cout << "   Test Failed" << endl;
    }

    cout << endl << "Testing the Insert time for new Queues: " << endl;
    tester.testRQueueTime(Queue1, 10, 1000);
}

int priorityFn1(const Student&student) {
    //priority value is determined based on some criteria
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    int priority = student.getYear() + student.getMajor() + student.getGroup();
    return priority;
}

int priorityFn2(const Student&student) {
    //priority is determined by an officer in registrar office
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    return student.getPriority();
}