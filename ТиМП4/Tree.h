using namespace std;
template<class T>
struct node
{
	T data;
	int id;
	node * parent;
	vector <node *> *children;
};

template <class T>
class Tree
{
	node<T> * root;
	int curr;						//Счётчик текущего идентификатора
	node<T> * findNode(int, node<T>*);
public:
	int addNode(T, int);
	void clear();
	Tree(T x);
	~Tree()
	{
		clear();
	}
};

template<class T>
node<T>* Tree<T>::findNode(int id1, node<T> * begin)
{
	node<T> * temp = NULL;
	if ((begin->id) == id1)
		return begin;
	else
	{
		if (!(begin->children))
			return NULL;
		for (int i = 0; i <= (begin->children)->size() - 1; ++i)
		{
			temp = findNode(id1, (*(begin->children))[i]);
			if (temp)
				return temp;
		}
	}
}

template<class T>
int Tree<T>::addNode(T x, int id)
{
	node<T> * newNode = new node<T>;
	node<T> * parent = findNode(id, root);
	if (parent->children == NULL)
		parent->children = new vector<node*>;
	(parent->children)->push_back(newNode);
	newNode->parent = parent;
	newNode->id = ++curr;
	newNode->data = x;
	newNode->children = NULL;
	cout << "Создан узел с идентификатором " << curr << endl;
	return curr;
}

template<class T>
void Tree<T>::clear()
{
	for (int i = curr; i >= 0; i--)
	{
		node<T> * temp = findNode(i, root);
		if (temp->parent)
		{
			((temp->parent)->children)->pop_back();
			if (!((temp->parent)->children)->size())
				(temp->parent)->children = NULL;
		}
		delete temp;
	}
	curr = -1;
}

template<class T>
Tree<T>::Tree(T x)
{
	root = new node<T>;
	root->data = x;
	curr = 0;
	root->id = 0;
	root->parent = NULL;
	root->children = NULL;
	cout << "Создан корень с идентификатором 0" << endl;
}
