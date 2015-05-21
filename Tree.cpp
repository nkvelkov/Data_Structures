#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
#include <stack>

using namespace std;

template <class ElemType>
struct TreeNode
{
	ElemType x;
	vector<TreeNode<ElemType>* > children;
	int uid;
	TreeNode ()
	{
		static int currentId = 0;
		uid = currentId;
		currentId++;
	}
};

template <class T>
class Tree
{

private:
	TreeNode<T> *root;
public:
	Tree ():root (NULL)
	{}

	Tree (const Tree<T>& t)
	{
		root = copyTree (t.root);
	}

	Tree<T>& operator = (const Tree<T> &t)
	{
		if (this != &t)
		{
			destroy (root);
			root = copyTree (t.root);
		}

		return *this;
	}

	~Tree ()
	{
		destroy (root);
	}

	bool empty ()
	{
		return root == NULL;
	}

	void setRoot (const T& newRoot)
	{
		/*
			Tree<int> t;
			t.setRoot (2);
			t.setRoot (3);
		*/

		if (root == NULL)
		{
			root = new TreeNode<T>;
		}
		root->x = newRoot;
	}

	void addSubTree (const Tree<T>& t)
	{
		assert (root != NULL);

		root->children.push_back (copyTree(t.root));
	}

	void addNode(const T&, const T&);

	void print (ostream &out)
	{
		out << "digraph{" << endl;
		printNode (out,root);
		out << "}";
	}

	int height()const;
	int count()const;
    int countLeaves()const;
    T sum (const T& null_val)const;
    vector<T> leaves()const;
    vector<T> level (int k)const;

    void insertSorted (const T& x);
    bool isBOT()const;
    bool memberBOT (const T& x)const;
    bool memberGeneral(const T& x)const;
    bool isBOTStack()const;
private:
    int height(const TreeNode<T>* curNode)const;
    int count(const TreeNode<T>*)const;
    int countLeaves(const TreeNode<T>*)const;
    T sum (const TreeNode<T>*,const T& null_val)const;
    void leaves(const TreeNode<T>*, vector<T>&)const;
    void level(const TreeNode<T>* curNode, vector<T>& ans, int k)const;
    void addNode(TreeNode<T>* curNode, const T& rootData, const T& addData);

    void insertSorted (TreeNode<T>*, const T& x);
    bool isBOT(const TreeNode<T>*)const;
    bool memberBOT (const TreeNode<T>* curNode, const T& x)const;
    int getNumChildren(const vector<TreeNode<T>* >& v)const;
    bool memberGeneral(const TreeNode<T>* curNode, const T& x)const;
	void printNode (ostream &out,const TreeNode<T> *currentNode)
	{
		if (currentNode == NULL)
			return;

		out << currentNode->uid
		    << "[label=\"val="
		    << currentNode->x
		    << "\"];"
		    << endl;

		for (int i = 0; i < currentNode->children.size(); i++)
			if (currentNode->children[i] != NULL)
			{
				out << currentNode->uid
				    << " -> "
				    << currentNode->children[i]->uid
				    << endl;

				printNode (out, currentNode->children[i]);
			}


	}

	void destroy (const TreeNode<T> *currentNode)
	{
		if (currentNode == NULL)
			return;

		for (int i = 0; i < currentNode->children.size(); i++)
		{
			destroy (currentNode->children[i]);
		}

		delete currentNode;

	}


	TreeNode<T> *copyTree (const TreeNode<T> *currentNode)
	{
		if (currentNode == NULL)
			return NULL;

		TreeNode<T> *newNode = new TreeNode<T>;

		newNode->x = currentNode->x;

		for (int i = 0; i < currentNode->children.size(); i++)
		{
			newNode->children.push_back (copyTree(currentNode->children[i]));
		}

		return newNode;
	}
};

template <typename T>
int Tree<T>:: height()const
{
    if(root == NULL)
    {
        return 0;
    }
    return height(root);
}

template <typename T>
int Tree<T>:: height(const TreeNode<T>* curNode)const
{
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        return 1;
    }
    int maxHeight = 0;
    for(int i = 0; i < children.size(); ++i)
    {
        int curHeight = height(children[i]);
        if(maxHeight < curHeight)
        {
            maxHeight = curHeight;
        }
    }
    return maxHeight + 1;
}
template <typename T>
int Tree<T>:: count()const
{
    if(root == NULL)
    {
        return 0;
    }
    return count(root);
}
template <typename T>
int Tree<T>:: count(const TreeNode<T>* curNode)const
{
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        return 1;
    }
    int s = 1;
    for(int i = 0; i < children.size(); ++i)
    {
        s += count(children[i]);
    }
    return s;
}
template <typename T>
int Tree<T>:: countLeaves()const
{
    if(root == NULL)
    {
        return 0;
    }
    return countLeaves(root);
}
template <typename T>
int Tree<T>:: countLeaves(const TreeNode<T>* curNode)const
{
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        return 1;
    }
    int s = 0;
    for(typename vector<TreeNode<T>*>:: iterator it = children.begin(); it != children.end(); ++it)
    {
        s += countLeaves(*it);
    }
    return s;
}
template <typename T>
T Tree<T>:: sum (const T& null_val)const
{
    if(root == NULL)
    {
        return null_val;
    }
    return sum(root, null_val);
}
template <typename T>
T Tree<T>:: sum(const TreeNode<T>* curNode, const T& null_val)const
{
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        return curNode->x;
    }
    T s = curNode->x;
    for(typename vector<TreeNode<T>* >:: iterator it = children.begin(); it != children.end(); ++it)
    {
        s = s + sum(*it, null_val);
    }
    return s;
}
template <typename T>
vector<T> Tree<T>:: leaves()const
{
    vector<T> ans;
    if(root == NULL)
    {
        return ans;
    }
    leaves(root, ans);
    return ans;
}
template <typename T>
void Tree<T>:: leaves(const TreeNode<T>* curNode, vector<T>& res)const
{
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        res.push_back(curNode->x);
        return;
    }
    for(typename vector<TreeNode<T>* >:: iterator it = children.begin(); it != children.end(); ++it)
    {
        leaves(*it, res);
    }
    return;
}
template <typename T>
vector<T> Tree<T>::level (int k)const
{
    vector<T> ans;
    if(root == NULL)
    {
        return ans;
    }
    level(root, ans, k);
    return ans;
}
template <typename T>
void Tree<T>:: level(const TreeNode<T>* curNode, vector<T>& ans, int k)const
{
    if(k == 0)
    {
        ans.push_back(curNode->x);
        return;
    }
    vector<TreeNode<T>* > children = curNode->children;
    if(children.size() == 0)
    {
        return;
    }
    for(typename vector<TreeNode<T>* >::iterator it = children.begin(); it != children.end(); ++it)
    {
        level(*it, ans, k-1);
    }
}
template <typename T>
void Tree<T>:: addNode(const T& rootData, const T& addData)
{
    if(root == NULL)
    {
        setRoot(addData);
        return;
    }
    addNode(root, rootData, addData);
}
template <typename T>
void Tree<T>:: addNode(TreeNode<T>* curNode, const T& rootData, const T& addData)
{
    if(curNode->x == rootData)
    {
        TreeNode<T>* newElem = new TreeNode<T>();
        newElem->x = addData;
        curNode->children.push_back(newElem);
        return;
    }
    vector<TreeNode<T>* >& children = curNode->children;
    if(children.size() == 0)
    {
        return;
    }
    for(typename vector<TreeNode<T>* >:: iterator it=children.begin(); it != children.end(); ++it)
    {
        addNode(*it, rootData, addData);
    }
}
template <typename T>
void Tree<T>:: insertSorted (const T& x)
{
    if(root == NULL)
    {
        this->setRoot(x);
        return;
    }
    insertSorted(root, x);
}
template <typename T>
void Tree<T>:: insertSorted(TreeNode<T>* curNode, const T& x)
{
    vector<TreeNode<T>* >& children = curNode->children;
    int numChildren = getNumChildren(children);
    /*if(curNode == NULL)
    {
        TreeNode<T>* newElem = new TreeNode<T>();
        newElem->x = x;
        curNode = newElem;
        return;
    }*/
    if(numChildren == 0)
    {
        if(x < curNode->x)
        {
            TreeNode<T>* newElem = new TreeNode<T>();
            newElem->x = x;
            children.push_back(newElem);
            return;
        }else
        {
            TreeNode<T>* newElem = new TreeNode<T>;
            newElem->x = x;
            TreeNode<T>* nullElem = new TreeNode<T>;
            nullElem->uid = -1;
            children.push_back(nullElem);
            children.push_back(newElem);
            return;
        }
    }else if(numChildren == 1)
    {
        if(x < curNode->x)
        {
            if(children[0]->uid == -1)
            {
                TreeNode<T>* newElem = new TreeNode<T>();
                newElem->x = x;
                children[0] = newElem;
                return;
            }else
            {
                insertSorted(children[0], x);
            }
        }else
        {
            if(children[0]->uid != -1)
            {
                TreeNode<T>* newElem = new TreeNode<T>();
                newElem->x = x;
                children.push_back(newElem);
                return;
            }else
            {
                insertSorted(children[1], x);
            }
        }
        return;
    }
    if(numChildren == 2)
    {
        if(x < curNode->x)
        {
            insertSorted(children[0], x);
        }else
        {
            insertSorted(children[1], x);
        }
    }
}
template <typename T>
bool Tree<T>:: isBOT()const
{
    if(root == NULL)
    {
        return true;
    }
    return isBOT(root);
}
template <typename T>
int Tree<T>:: getNumChildren(const vector<TreeNode<T>* >& v)const
{
    int s = 0;
    for(int i = 0; i < v.size(); ++i)
    {
        if(v[i]->uid != -1 )
            ++s;
    }
    return s;
}
template <typename T>
bool Tree<T>:: isBOT(const TreeNode<T>* curNode)const
{
    vector<TreeNode<T>* > children = curNode->children;
    int numChildren = getNumChildren(children); //children.size();
    if(numChildren == 0)
    {
        return true;
    }else if(numChildren == 2)
    {
        /*if(children[0]->x >= children[1]->x)
        {
            return false;
        }else*/
        if(children[0]->x >= curNode->x || children[1]->x < curNode->x)
        {
            return false;
        }else
        {
            return isBOT(children[0]) && isBOT(children[1]);
        }
    }else if(numChildren == 1)
    {
        if(children[0]->uid == -1)
        {
            if(children[1]->x < curNode->x)
            {
                return false;
            }
            return isBOT(children[1]);
        }else// children[0] != -1
        {
            if(children[0]->x >= curNode->x)
            {
                return false;
            }
            return isBOT(children[0]);
        }
    }else
    {
        return false;
    }
}
template <typename T>
bool Tree<T>:: isBOTStack()const
{
    if(root == NULL)
    {
        return false;
    }
    stack<TreeNode<T>* > st;
    st.push(root);

    while(!st.empty())
    {
        TreeNode<T>* top = st.top();
        st.pop();
        int numChildren = getNumChildren(top->children);
        if(numChildren == 2)
        {
            if(top->children[0]->x >= top->x)
            {
                return false;
            }else
            {
                st.push(top->children[0]);
            }
            if(top->children[1]->x < top->x)
            {
                return false;
            }else
            {
                st.push(top->children[1]);
            }
        }else if(numChildren == 1)
        {
            if(top->children[0]->uid == -1)
            {
               if(top->children[1]->x < top->x)
               {
                   return false;
               }else
               {
                   st.push(top->children[1]);
               }
            }else
            {
                if(top->children[0]->x >= top->x)
                {
                    return false;
                }else
                {
                    st.push(top->children[0]);
                }
            }
        }
    }
    return true;
}
template <typename T>
bool Tree<T>:: memberBOT (const T& x)const
{
    if(root == NULL)
    {
        return false;
    }
    return memberBOT(root, x);
}
template <typename T>
bool Tree<T>:: memberBOT (const TreeNode<T>* curNode, const T& x)const
{
    if(curNode->x == x)
    {
        return true;
    }
    int numChildren = getNumChildren(curNode->children);
    if(numChildren == 0)
    {
        return false;
    }
    if(numChildren == 1)
    {
        if(curNode->children[0]->uid == -1)
        {
            if(curNode->x <= x)
                return memberBOT(curNode->children[1], x);
            return false;
        }else
        {
            if(curNode->x > x)
                return memberBOT(curNode->children[0], x);
            return false;
        }
    }
    if(x < curNode->x)
    {
        return memberBOT(curNode->children[0], x);
    }else
    {
        return memberBOT(curNode->children[1], x);
    }
}
template <typename T>
bool Tree<T>:: memberGeneral (const T& x)const
{
    if (root == NULL)
    {
        return false;
    }
    return memberGeneral(root, x);
}
template <typename T>
bool Tree<T>:: memberGeneral(const TreeNode<T>* curNode, const T& x)const
{
    if(curNode->x == x)
    {
        return true;
    }
    const vector<TreeNode<T>* > &children = curNode->children;
    if(children.size() == 0)
    {
        return false;
    }
    bool b = false;
    for(typename vector<TreeNode<T>*>::const_iterator it = children.begin(); !b && it != children.end(); ++it)
    {
        b = memberGeneral(*it, x);
    }
    return b;
}
template <typename T>
ostream& operator << (ostream& out, const vector<T>& v)
{
    for(int i = 0; i < v.size(); ++i)
    {
        out << v[i] << " ";
    }// out << endl;
    return out;
}
template <typename T>
ostream& operator << (ostream& out, const pair<T, T>& p)
{
    out << "[" << p.first << " " << p.second << "]";
    return out;
}

