#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED


template <typename V, typename P>
struct Pair
{
    Pair(){}
    Pair(const V& _value, const P& _priority) : value(_value), priority(_priority)
    { }

    V value;
    P priority;
};

template <typename V, typename P>
class PriorityQueue
{
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue&);
    PriorityQueue& operator = (const PriorityQueue&);
    ~PriorityQueue();

    void insert(const V&, const P&);
    bool pop(const V&);
    V peek()const;
    bool empty()const;

private:

    void sink(int);
    void bubble(int);

    void swapElems(int, int);
    bool exist(int)const;

    int leftChild(int x)const;
    int rightChild(int x)const;
    int parent(int x)const;

    void copyPQ(const PriorityQueue&);
    void deletePQ();
    void extend();
    void copyArr(const Pair<V, P>*);

    Pair<V, P>* container;
    int n;
    int capacity;
};

template <typename V, typename P>
PriorityQueue<V, P>:: PriorityQueue() : container(NULL)
{
    this->n = 0;
    this->capacity = 10;
    this->container = new Pair<V,P>[capacity];
}

template <typename V, typename P>
PriorityQueue<V, P>:: PriorityQueue(const PriorityQueue<V, P>& other) : container(NULL)
{
    copyPQ(other);
}

template <typename V, typename P>
PriorityQueue<V, P>& PriorityQueue<V, P>:: operator = (const PriorityQueue<V, P>& other)
{
    if(this != &other)
    {
        deletePQ();
        copyPQ(other);
    }

    return *this;
}

template <typename V, typename P>
PriorityQueue<V, P>:: ~PriorityQueue()
{
    deletePQ();
}

template <typename V, typename P>
void PriorityQueue<V, P>:: copyPQ(const PriorityQueue<V, P>& other)
{
    this->n = other.n;
    this->capacity = other.capacity;
    this->arr = new Pair<V, P>[this->capacity];

    for(int i=0; i<n; ++i)
    {
        this->arr[i] = other.arr[i];
    }
}

template <typename V, typename P>
void PriorityQueue<V, P>:: deletePQ()
{
    delete [] container;
    //arr = NULL;
}

template <typename V, typename P>
V PriorityQueue<V, P>:: peek()const
{
    return container[0].value;
}

template <typename V, typename P>
bool PriorityQueue<V, P>:: empty()const
{
    return n == 0;
}

template <typename V, typename P>
void PriorityQueue<V, P>:: insert(const V& value, const P& priority)
{
    if(capacity == n)
    {
        extend();
    }
    Pair<V, P>*  myPair = new Pair<V, P>(value, priority);

    container[n] = myPair; ++n;

    bubble(n-1);
}

template <typename V, typename P>
bool PriorityQueue<V, P>:: pop(const V& value)
{
    if( empty() )
    {
        return false;
    }

    value = container[0].value;
    swapElems(0, n-1);
    --n;
    sink( 0 );

    return true;
}

template <typename V, typename P>
void PriorityQueue<V, P>:: bubble(int x)
{
    while ( x != 0 )
    {
        int p = parent(x);

        if(container[p] > container[x])
        {
            swapElems(p, x);
            x = p;
        }
    }
}

template <typename V, typename P>
void PriorityQueue<V, P>:: sink(int x)
{
    while(x < n)
    {
        int l = leftChild(x), r = rightChild(x);

        if (exist(l) && exist(r) && container[x] > container[r] && container[x] > container[l])
        {
            if (container[r] > container[l])
            {
                swapElems(l, x);
                x = l;
            }
            else
            {
                swapElems(r, x);
                x = r;
            }
        }else if( exist(l) && container[l] < container[x])
        {
            swapElems(x, l);
            x = l;
        }else if( exist(r) && container[r] < container[x])
        {
            swapElems(x, r);
            x = r;
        }else
        {
            break;
        }
    }

}

template <typename V, typename P>
void PriorityQueue<V, P>:: swapElems(int x, int y)
{
    Pair<V, P> temp = container[x];
    container[x] = container[y];
    container[y] = temp;
}

template <typename V, typename P>
bool PriorityQueue<V, P>:: exist(int x)const
{
    return x < n;
}

template <typename V, typename P>
int PriorityQueue<V, P>:: leftChild(int x)const
{
    return x*2 + 1;
}

template <typename V, typename P>
int PriorityQueue<V, P>:: rightChild(int x)const
{
    return x*2 + 2;
}

template <typename V, typename P>
int PriorityQueue<V, P>:: parent(int x)const
{
    return (x-1) / 2;
}

template <typename V, typename P>
void PriorityQueue<V, P>:: extend()
{
    this->capacity *= 2;
    Pair<V, P>* narr = new Pair<V, P>[this->capacity];

    for(int i=0; i<n; ++i)
    {
        narr[i] = this->container[i];
    }

    this->container = narr;

    delete [] container;
}

template <typename V, typename P>
void PriorityQueue<V, P>:: copyArr(const Pair<V, P>* arr)
{
    for(int i=0; i<this->n; ++i)
    {
        this->container[i] = arr[i];
    }
}




#endif // PRIORITYQUEUE_H_INCLUDED
