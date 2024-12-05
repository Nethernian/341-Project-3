// CMSC 341 - Spring 2021 - Project 3
// RQueue:

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

/**
 * The constructor for the RQueue class, creates a RQueue from the pointer provided
 * @param priFn A pointer to the prioritization function
 */
RQueue::RQueue(prifn_t priFn) {
    priority = priFn;
    _heap = nullptr;
    _size = 0;
}

/**
 * Destructor for the RQueue Class, clears all data and sets all pointers to nullptr
 */
RQueue::~RQueue() {
    clear();
    // Deallocate data
    _heap = nullptr;
    _size = 0;
}

/**
 * A copy constructor for the RQueue class, will create a deep copy of the RQueue
 * @param rhs the Queue to be copied in the copy constructor
 */
RQueue::RQueue(const RQueue& rhs) {
    priority = rhs.getPriorityFn();
    _size = rhs._size;

    // Recursive copy through helper function
    _heap = AssistCopy(_heap, rhs._heap);
    // !!! Issue here need to fix seems to core dump on destruct
}

/**
 * An overloaded assignment operator, functions similarly to the copy constructor
 * @param rhs takes a RQueue as a parameter, will be used to make the deep copy
 * @return Returns the new RQueue, needs to be a deep copy
 */
RQueue& RQueue::operator=(const RQueue& rhs) {
    // !!! need to destroy existing structure to avoid leaks
    this->clear();
    this->_size = rhs._size;
    this->priority = rhs.getPriorityFn();
    this->_heap = nullptr;

    // Recursive copy through helper function
    AssistCopy(this->_heap,  rhs._heap);

    return *this;
}

/**
 * Add a new student to the RQueue data structure, the insert will be provided with a student object.
 * this function must preserve the min-heap property for the RQueue
 * @param input takes the student object as an input
 */
void RQueue::insertStudent(const Student& input) {
    // Create the _heap, if one does not already exist, sets size to 1
    if(_heap == nullptr){
        _heap = new Node(input);
        _size = 1;

    // Create Subsequent nodes below the _heap, increments the size
    }else{
        Node* InsertNode = new Node(input);
        _heap = Merge(_heap, InsertNode);
        _size++;
    }
}

/**
 * Remove the node, and return the student with the highest priority, this function must maintain the
 * min-heap property. Additionally this function should throw an error "domain_error" if the queue is
 * empty when called
 * @return the Student object for the highest priority student in the queue
 */
Student RQueue::getNextStudent() {
     Node* temp = _heap;
     Student temp_St = _heap->getStudent();

     if(_heap == nullptr){
         // Throws an error for an empty Heap
         throw domain_error("Queue is Empty");

     }else{
         // In the case of the heap being the only node
         if(_heap->_right == nullptr && _heap->_left == nullptr){
             delete temp;
             _heap = nullptr;

         // All other cases
         }else{
             _heap = Merge(_heap->_left, _heap->_right);
             delete temp;
         }

         // When removing a student, it must decrease size
         _size--;
         return temp_St;
     }
}

/**
 * Merge the queue object with the specified rhs, the updates should be performed on this object,
 * additionally the Queue should be protected against merging with itself, in the event of a self
 * merge, the function must throw the error "domain_error"
 *
 * I NEED TO KNOW WHAT TO DO WITH RHS AFTER USE
 *
 * @param rhs the function that is to be merged with the current object
 */
void RQueue::mergeWithQueue(RQueue& rhs) {
    // Check for matching priority functions
    if(rhs.priority != priority){
        throw domain_error("Non-matching priority function");

    }else{
        // Check for merging with self
        if(&_heap != &rhs._heap){
            _size = _size + rhs.numStudents();
            // Set the heap to be equal to the merge between the heads of the two structures
            _heap = Merge(_heap, rhs._heap);
            // Disassociate the rhs heap
            rhs._heap = nullptr;
        }else{
            throw domain_error("Potential Self Merge");
        }
    }
}

/**
 * Clears the Queue, must remove all nodes from the skew heap, and leave it empty
 */
void RQueue::clear() {
    AssistClear(_heap);
}

/**
 * Get the current number of students
 * @return the number of students in the queue
 */
int RQueue::numStudents() const {
    // Return the size of the structure
    return _size;
}

/**
 * Prints the contents of the Queue using a preorder traversal, with the caveat that the first student printed
 * should have the highest priority
 */
void RQueue::printStudentQueue() const {
    cout << "Contents of the student queue:" << endl;
    if(_heap != nullptr) {
        // Uses the recursive AssistPrint, to print the Heap
        AssistPrint(_heap);
    }else{
        cout << "The Skew Heap is empty, and cannot be displayed." << endl;
    }
}

/**
 * Get the current priority function
 * @return the current priority function
 */
prifn_t RQueue::getPriorityFn() const {
    // Return the priority function
    return priority;
}

/**
 * Set a new priority function, and rebuilds the heap
 * @param priFn the priority function that will replace the existing priority function.
 */
void RQueue::setPriorityFn(prifn_t priFn) {
    Node* temp = _heap; // Create a temp for the rebuild
    priority = priFn;
    // Begins Rebuild
    _heap = nullptr;
    Rebuild(temp);
    // Clear the temp data
    AssistClear(temp);
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

// PRIVATE FUNCTION DECLARATIONS

/**
 * Assists in the recursive printing of the Skew Heap, will operate in Preorder
 * @param node the passed node starts at highest priority and works recursively through the
 * structure printing with the overloaded << operator
 */
void RQueue::AssistPrint(Node* node) const {
    // Print Center
    cout << "["<< priority(node->getStudent()) << "] " << node->getStudent() << endl;
    // Print Left
    if(node->_left != nullptr){
        AssistPrint(node->_left);
    }
    // Print Right
    if(node->_right != nullptr){
        AssistPrint(node->_right);
    }
}

/**
 * Recursively clears the Skew Heaps, clears self last
 * @param node used in recursion, should start at _heap
 */
void RQueue::AssistClear(Node* node){
    // Clears while the node is not nullptr
    if(node != nullptr){
        // Recursion to the right
        AssistClear(node->_right);
        // Recursion to the left
        AssistClear(node->_left);
        // Delete Self
        delete node;
    }
}

/**
 * Copies from Left to Right, does so recursively
 * @param LHS
 * @param RHS
 */
Node* RQueue::AssistCopy(Node* LHS,Node* RHS){
    LHS = new Node(RHS->getStudent());

    if(RHS->_left != nullptr){
        LHS->_left = AssistCopy(LHS->_left, RHS->_left);
    }else{
        LHS->_left = nullptr;
    }

    if(RHS->_right != nullptr){
        LHS->_right = AssistCopy(LHS->_right, RHS->_right);
    }else{
        LHS->_right = nullptr;
    }
    return LHS;
}

/**
 * A Merge Function used to merge a single node with the rest of the Heap structure
 * @param Left Should contain nodes that are part of the main structure
 * @param Right Should contain nodes that are being integrated with the structure
 * @return Returns a pointer to the _heap of the rebalanced Skew Heap or root of the Sub-Heap
 */
Node* RQueue::Merge(Node* Left, Node* Right){
    // Create a variable to use as a temp pointer
    Node* new_heap = nullptr;
    if(Left != nullptr && Right != nullptr){
        // Checks for priority
        // Merges to the left
        if(priority(Left->getStudent()) <= priority(Right->getStudent())){
            Left->_right = Merge(Left->_right, Right);
            new_heap = Left;
        // Merges to the right
        }else{
            Right->_right = Merge(Right->_right, Left);
            new_heap = Right;
        }
    // Sets the heap value, and returns
    }else if(Left != nullptr){
        new_heap = Left;
    }else if(Right != nullptr){
        new_heap = Right;
    }
    // Swap, and then return the new heap
    Swap(new_heap);
    return new_heap;
}

/**
 * Swap the nodes of a parent, Right will become Left, and Left will become Right
 * @param node : A Node that will have it's children swapped
 */
void RQueue::Swap(Node* node){
    // Temp to assist in swap
    Node* TempR = node->_right;
    node->_right = node->_left;
    node->_left = TempR;
}

/**
 * A Rebuild Function to recursively rebuild the tree with a new priority function
 * @param node To be used in recursion, and will be copied from
 * @return
 */
void RQueue::Rebuild(Node* node){
    // Inserts to the right into new structure
    if(node->_right != nullptr){
        Rebuild(node->_right);
    }

    // Inserts self into new structure
    insertStudent(node->getStudent());

    // Inserts Left into new structure
    if(node->_left != nullptr){
        Rebuild(node->_left);
    }
}
