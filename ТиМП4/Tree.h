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
	int curr;									//Счётчик текущего идентификатора
	node<T> * findNode(int, node<T>*);
	int getIncNumber(T, node<T>*);				//Поиск кол-ва вхождений по указателю на корень поддерева
	void clear(node<T> *);						//Удаление по указателю на корень поддерева
public:
	void clear(int subtree_id);
	int getIncNumber(T value, int subtree_id);	//Поиск кол-ва вхождений по id поддерева
	int addNode(T value, int subtree_id);		//Удаление по id поддерева
	Tree(T value);
	~Tree()
	{
		clear(root);
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
		return NULL;
	}
}

template<class T>
int Tree<T>::addNode(T x, int id)
{
	if (id > curr)
	{
		cout << "Нет узла с таким id\n";
		return NULL;
	}
	node<T> * newNode = new node<T>;
	node<T> * parent = findNode(id, root);
	if (parent->children == NULL)
		parent->children = new vector<node<T>*>;
	(parent->children)->push_back(newNode);
	newNode->parent = parent;
	newNode->id = ++curr;
	newNode->data = x;
	newNode->children = NULL;
	cout << "Создан узел с идентификатором " << curr << endl;
	return curr;
}

template<class T>
void Tree<T>::clear(int id)						//Перегрузка для пользователя
{
	node<T> * deleting = findNode(id, root);
	clear(deleting);
	if (!id)									//Если удаляем с корня
		root = NULL;
}

template<class T>
void Tree<T>::clear(node<T> *deleting)
{
	if (!deleting)
		return;
	if (deleting->children)
	{
		int size = (deleting->children)->size() - 1;
		for (int i = size; i >= 0; --i)
			clear((*(deleting->children))[i]);
		clear(deleting);
	}
	else
	{
		if (deleting->parent)
		{
			((deleting->parent)->children)->pop_back();
			if (!((deleting->parent)->children)->size())
				(deleting->parent)->children = NULL;
		}
		delete deleting;
	}
}

template<class T>
int Tree<T>::getIncNumber(T x, int id)			//Перегрузка для пользователя
{
	node<T> * checking = findNode(id, root);
	return getIncNumber(x, checking);
}

template<class T>
int Tree<T>::getIncNumber(T x, node<T> * checking)
{
	int incNumber = 0;
	if (x == checking->data)
		++incNumber;
	if (!checking->children)
		return incNumber;
	else
	{
		for (int i = 0; i <= (checking->children)->size() - 1; ++i)
			incNumber += getIncNumber(x, (*(checking->children))[i]);
		return incNumber;
	}
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
	cout << "Создан корень с идентификатором " << curr << endl;
}
