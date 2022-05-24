#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

struct node
{
    int key;
    int degree;
    bool mark;
    char c;
    node* parent;
    node* child;
    node* left;
    node* right;
};

class FibHeap
{
protected:
    int n;
    node* minRoot;
public:

    FibHeap() : n(0), minRoot(nullptr) {}

    node* get_root()
    {
        return minRoot;
    }

    void insertion(int);
    void linkList(node*, node*);
    void consolidate();
    void extractMin();
    void cut(node*, node*);
    void cascadeCut(node*);
    void decreaseKey(node*, int);
    void findNode(node*, int, int);
    void deletion(int);
    void display();
    void heapUnion(FibHeap&);
    node* mergeNode(node*, node*);
};

void FibHeap :: insertion(int value)
{

    node* x = (struct node*)malloc(sizeof(struct node));

    x->key = value;
    x->degree = 0;
    x->mark = 0;
    x->c = 'N';
    x->parent = nullptr;
    x->child = nullptr;
    x->left = x;
    x->right = x;

    if (minRoot != nullptr)
    {
        (minRoot->left)->right = x;
        x->right = minRoot;
        x->left = minRoot->left;
        minRoot->left = x;

        if (x->key < minRoot->key)
            minRoot = x;
    }
    else
    {
        minRoot = x;
    }

    n++;
}

void FibHeap :: linkList(node* x, node* y)
{

    (x->left)->right = x->right;
    (x->right)->left = x->left;

    if (y->right == y)
        minRoot = y;

    x->left = x;
    x->right = x;
    x->parent = y;

    if (y->child == nullptr)
        y->child = x;

    x->right = y->child;
    x->left = (y->child)->left;
    ((y->child)->left)->right = x;
    (y->child)->left = x;

    if (x->key < (y->child)->key)
        y->child = x;

    y->degree++;
}

void FibHeap :: consolidate()
{

    int temp1, temp3;
    float temp2 = (log(n)) / (log(2));
    temp3 = temp2;
    node* v[temp3];

    for (int i = 0; i <= temp3; i++)
        v[i] = nullptr;

    node* p1 = minRoot;
    node* p2;
    node* p3;
    node* p4 = p1;

    do
    {
        p4 = p4->right;
        temp1 = p1->degree;

        while (v[temp1] != nullptr)
        {
            p2 = v[temp1];

            if (p1->key > p2->key)
            {
                p3 = p1;
                p1 = p2;
                p2 = p3;
            }

            if (p2 == minRoot)
                minRoot = p1;

            linkList(p2, p1);

            if (p1->right == p1)
                minRoot = p1;

            v[temp1] = nullptr;
            temp1++;
        }

        v[temp1] = p1;
        p1 = p1->right;

    }
    while (p1 != minRoot);

    minRoot = nullptr;

    for (int i = 0; i <= temp3; i++)
    {
        if (v[i] != nullptr)
        {
            v[i]->left = v[i];
            v[i]->right = v[i];

            if (minRoot != nullptr)
            {
                (minRoot->left)->right = v[i];
                v[i]->right = minRoot;
                v[i]->left = minRoot->left;
                minRoot->left = v[i];

                if (v[i]->key < minRoot->key)
                    minRoot = v[i];
            }
            else
            {
                minRoot = v[i];
            }

            if (minRoot == nullptr)
                minRoot = v[i];

            else

                if (v[i]->key < minRoot->key)
                    minRoot = v[i];
        }
    }
}

void FibHeap :: extractMin()
{

    if (minRoot == nullptr)
        cout << "The heap is empty.\n";

    else
    {
        node* root = minRoot;
        node* temp;
        temp = root;
        node* x = nullptr;

        if (root->child != nullptr)
        {
            x = root->child;

            do
            {
                temp = x->right;
                (minRoot->left)->right = x;
                x->right = minRoot;
                x->left = minRoot->left;
                minRoot->left = x;

                if (x->key < minRoot->key)
                    minRoot = x;

                x->parent = nullptr;
                x = temp;

            }
            while (temp != root->child);
        }

        (root->left)->right = root->right;
        (root->right)->left = root->left;
        minRoot = root->right;

        if (root == root->right && root->child == nullptr)
            minRoot = nullptr;

        else
        {
            minRoot = root->right;
            consolidate();
        }

        n--;
    }
}

void FibHeap :: cut(node* x, node* temp)
{

    if (x == x->right)
        temp->child = nullptr;

    (x->left)->right = x->right;
    (x->right)->left = x->left;

    if (x == temp->child)
        temp->child = x->right;

    temp->degree --;
    x->right = x;
    x->left = x;
    (minRoot->left)->right = x;
    x->right = minRoot;
    x->left = minRoot->left;
    minRoot->left = x;
    x->parent = nullptr;
    x->mark = 1;
}

void FibHeap :: cascadeCut(node* x)
{
    node* temp = x->parent;

    if (temp != nullptr)
    {
        if (x->mark == 0)
        {
            x->mark = 1;
        }

        else
        {
            cut(x, temp);
            cascadeCut(temp);
        }
    }
}

void FibHeap :: decreaseKey(node* x, int value)
{

    if (minRoot == nullptr)
        cout << "The heap is empty.\n";

    if (x == nullptr)
        cout << "Node with key value "<<x->key<<" doesn't exist in heap\n";

    x->key = value;
    node* temp = x->parent;

    if (temp != nullptr && x->key < temp->key)
    {
        cut(x, temp);
        cascadeCut(temp);
    }

    if (x->key < minRoot->key)
        minRoot = x;
}

void FibHeap :: findNode(struct node* minRoot, int oldValue, int value)
{

    node* temp = nullptr;
    node* root = minRoot;
    root->c = 'Y';
    node* temp1 = nullptr;

    if (root->key == oldValue)
    {
        temp1 = root;
        root->c = 'N';
        temp = temp1;
        decreaseKey(temp, value);
    }

    if (temp1 == nullptr)
    {
        if (root->child != nullptr)
            findNode(root->child, oldValue, value);

        if ((root->right)->c != 'Y')
            findNode(root->right, oldValue, value);
    }

    root->c = 'N';
    temp = temp1;
}

void FibHeap :: deletion(int value)
{

    if (minRoot == nullptr)
        cout << "The heap is empty.\n";
    else
    {
        findNode(minRoot, value, 0);
        extractMin();
        cout << "Key Deleted\n";
    }
}

void FibHeap :: display()
{
    node* root = minRoot;

    if (root == nullptr)
        cout << "The heap is empty.\n";

    else
    {
        cout << "The root nodes are: ";

        do
        {
            cout << root->key;
            root = root->right;

            if (root != minRoot)
            {
                cout << "-->";
            }
        }

        while (root != minRoot && root->right != nullptr);

        cout <<"\nThe heap has "<<n<< " nodes\n\n";
    }
}

node* FibHeap :: mergeNode(node* x, node* y)
{
    if(x == nullptr)
        return y;

    if(y == nullptr)
        return x;

    if(x->key > y->key)
    {
        node* temp = x;
        x = y;
        y = temp;
    }

    node* temp1 = x->right;
    node* temp2 = y->left;
    x->right = y;
    y ->left = x;
    temp1->left = temp2;
    temp2->right = temp1;

    return x;
}

void FibHeap :: heapUnion(FibHeap& H1)
{
    minRoot = mergeNode(minRoot, H1.minRoot);
    n += H1.n;
    H1.n = 0;
    H1.minRoot = nullptr;
}

int main()
{
    FibHeap FH, H;

    cout<<"Fibonacci Heap Menu\nChoose an option:\n";
    cout<<"1 - insert node in heap\n";
    cout<<"2 - extract min from heap\n";
    cout<<"3 - delete node from heap\n";
    cout<<"4 - union two heaps\n";
    cout<<"5 - display heap\n";
    cout<<"Press 0 to exit the menu\n";

    int op;

    do
    {
        cin>>op;
        system("cls");

        switch(op)
        {
        case 0:
            break;

        case 1:

            cout<<"Choose the number of nodes you wish to insert in the heap: ";
            int nr;
            cin>>nr;

            for(int i = 1; i <= nr; ++i)
            {
                cout<<"\nValue for node "<<i<<": ";
                int val;
                cin>>val;
                FH.insertion(val);
            }

            system("cls");
            cout<<"Choose another option:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";
            break;

        case 2:

            if(FH.get_root() != nullptr)
                cout<<"Min is: "<<FH.get_root()->key<<"\n";

            FH.extractMin();
            cout<<"Choose another option:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";
            break;

        case 3:

            cout<<"Choose the node you wish to delete from the heap: ";
            int val;
            cin>>val;
            FH.deletion(val);

            cout<<"Choose another option:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";
            break;

        case 4:

            cout<<"Chose number of nodes for heap 2: ";
            int nr1;
            cin>>nr1;

            for(int i = 1; i <= nr1; ++i)
            {
                cout<<"\nValue for node "<<i<<": ";
                int val;
                cin>>val;
                H.insertion(val);
            }
            FH.heapUnion(H);
            FH.display();

            cout<<"Choose another option:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";
            break;

        case 5:

            FH.display();
            cout<<"Choose another option:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";
            break;

        default:

            system("cls");
            cout<<"INVALID CHOICE!\n";
            cout<<"Choose again:\n";
            cout<<"1 - insert node in heap\n";
            cout<<"2 - extract min from heap\n";
            cout<<"3 - delete node from heap\n";
            cout<<"4 - union two heaps\n";
            cout<<"5 - display heap\n";
            cout<<"Press 0 to exit the menu\n";

        }
    }while(op != 0);

    return 0;
}
