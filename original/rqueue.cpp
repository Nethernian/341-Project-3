// CMSC 341 - Spring 2021 - Project 3
// RQueue:

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
    /************************
     * To be implemented
     * *********************/
}

RQueue::~RQueue()
{
    /************************
     * To be implemented
     * *********************/
}

RQueue::RQueue(const RQueue& rhs)
{
    /************************
     * To be implemented
     * *********************/
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
    /************************
     * To be implemented
     * *********************/
}

void RQueue::insertStudent(const Student& input) {
    /************************
     * To be implemented
     * *********************/
}

Student RQueue::getNextStudent() {
    /************************
     * To be implemented
     * *********************/
}


void RQueue::mergeWithQueue(RQueue& rhs) {
    /************************
     * To be implemented
     * *********************/
}

void RQueue::clear() {
    /************************
     * To be implemented
     * *********************/
}

int RQueue::numStudents() const
{
    /************************
     * To be implemented
     * *********************/
}

void RQueue::printStudentQueue() const {
    /************************
     * To be implemented
     * *********************/
}

prifn_t RQueue::getPriorityFn() const {
    /************************
     * To be implemented
     * *********************/
}

void RQueue::setPriorityFn(prifn_t priFn) {
    /************************
     * To be implemented
     * *********************/
}

// for debugging
void RQueue::dump() const
{
    if (_size == 0) {
        cout << "Empty skew heap.\n" ;
    } else {
        dump(_heap);
        cout << endl;
    }
}

// for debugging
void RQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->_left);
        cout << priority(pos->_student) << ":" << pos->_student.getName();
        dump(pos->_right);
        cout << ")";
    }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
    sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
         << ", year: " << student.getYear() << ", major: " << student.getMajorStr()
         << ", group: " << student.getGroupStr();
    return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getStudent();
    return sout;
}