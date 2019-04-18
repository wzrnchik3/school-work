#include <iostream>
#include <string>
using namespace std;

int const MAX_CHILDREN = 10;
int const MAX_NODE = 100;

struct pnode // person node
{
    int p, m, pid; // parent marraige index and person id
    pnode() // constructor
    {
        p = -1;
        m = -1;
        pid = -1;
    }
};

struct fnode // family node
{
    int h, w, numChildren, fid; // husband or wife index number, number of children, and family ID
    int c[MAX_CHILDREN]; // child nodes max of 10
    fnode() //constructor set all 0
    {
        h = -1;
        w = -1;
        numChildren = 0;
        fid = -1;
        for (int i = 0; i < MAX_CHILDREN; i++)
            c[i] = -1;
    }
};

struct queue {
    int contents[MAX_NODE];
    int front, rear;
    queue() {
        front = 0;
        rear = 0;
        for (int i = 0; i < MAX_NODE; i++) {
            contents[i] = 0;
        }
    }
};

class famTree
{
    public:
        // famTree(); // constructor
        // ~famTree(); // destructor
        void insert(int personid, int parent, int marriage); // insert function
        void family(int famid, int hid, int wid, int cid[], int numC); // family function
        void check(); // check data for consistency
        void relate(int start, int end); // find shortest path between 2 people
        bool isPQEmpty();
        bool isFQEmpty();
        int advance(int index);
        void insertPQ(int data);
        void insertFQ(int data);
        int deletePQ();
        int deleteFQ();
        void resetQ();
        void printRelate(int fPath[], int pPath[], int start, int end);

    private:
        fnode fams[MAX_NODE];
        pnode people[MAX_NODE];
        queue pQueue;
        queue fQueue;
};