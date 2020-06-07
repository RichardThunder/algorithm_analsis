#include <iostream>
using namespace std;
int counter1=0;
int counter2=0;

template<class T>
class TreeNode                         
{
private:
    T                value;  //z       
    TreeNode<T>* parent;                 
    int        nCount;                     
public:
    TreeNode();                          
    virtual ~TreeNode() {};             
    T    getValue();                        
    void  setValue(const T& val);          
    TreeNode<T>*  getParent();           
    void  setParent(TreeNode<T>* par);  
    int   getCount();                       
    void  setCount(const int count);        
};
 

template<class T>
TreeNode<T>::TreeNode()               
{
    parent = NULL;
    nCount = 1;
}
template<class T>
T TreeNode<T>::getValue()                
{
    return value;
}
template<class T>
void TreeNode<T>::setValue(const T& val) 
{
    value = val;
}
template<class T>
TreeNode<T>* TreeNode<T>::getParent() 
{
    return parent;
}
template<class T>
void TreeNode<T>::setParent(TreeNode<T>* par) 
{
    parent = par;
}
template<class T>
int TreeNode<T>::getCount()                      
{
    return nCount;
}
template<class T>
void TreeNode<T>::setCount(const int count)      
{
    nCount = count;
}
 
 

template<class T>
class Tree                                       
{
public:
    TreeNode<T>* array;                         
    int    Size;                                    
    Tree(const int size);                       
    virtual ~Tree();                           
    TreeNode<T> *Find(TreeNode<T>* node)const;
    TreeNode<T> *FindPC(TreeNode<T> *node) const; //压缩
 
    void Union(int i,int j);                    
    void UnionPC(int i, int j);    //压缩             
    bool Different(int i,int j);                
 
    int getSize()                               
    {
        return Size;
    }
};
 

template <class T>
Tree<T>::Tree(const int size)            
{
    Size = size;
    array = new TreeNode<T>[size];
}
 
template <class T>
Tree<T>::~Tree()                          
{
    delete []array;
}
 

template <class T>
TreeNode<T>*    Tree<T>::Find(TreeNode<T>* node) const
{
    TreeNode<T>* pointer = node;
    while(pointer->getParent() != NULL)
       { pointer = pointer->getParent();
       counter1++;
       }return pointer;
}
 

template <class T>
TreeNode<T> *Tree<T>::FindPC(TreeNode<T> *node) const
{
    if (node->getParent() == NULL)
    {   counter2++;
        return node;
    }
    
    node->setParent(FindPC(node->getParent()));
    return node->getParent();
}
 

template<class T>
bool Tree<T>::Different(int i,int j)
{
    TreeNode<T>* pointeri = Find(&array[i]);      
    TreeNode<T>* pointerj = Find(&array[j]);       
    return pointeri != pointerj;
}
 

template<class T>
void Tree<T>::Union(int i,int j)
{
    TreeNode<T>* pointeri = Find(&array[i]);       
    TreeNode<T>* pointerj = Find(&array[j]);        
    if(pointeri != pointerj)
    {
        if(pointeri->getCount()>=pointerj->getCount())
        {
            pointerj->setParent(pointeri);
            pointeri->setCount(pointeri->getCount()+pointerj->getCount());
        }
        else
        {
            pointeri->setParent(pointerj);
            pointerj->setCount(pointeri->getCount()+pointerj->getCount());
        }
    }
}
 
//压缩合并
template <class T>
void Tree<T>::UnionPC(int i, int j)
{
    TreeNode<T> *pointeri = FindPC(&array[i]);
    TreeNode<T> *pointerj = FindPC(&array[j]);
 
    if (pointeri != pointerj)
    {
        if (pointeri->getCount() >= pointerj->getCount())
        {
            pointerj->setParent(pointeri);
            pointeri->setCount(pointeri->getCount() + pointerj->getCount());
        }
        else
        {
            pointeri->setParent(pointerj);
            pointerj->setCount(pointeri->getCount() + pointerj->getCount());
        }
    }
}
using namespace std;
const int N = 10;
char StrName[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

int GetNum(char ch)
{
    for (int i = 0; i < N; i++)
        if (ch == StrName[i])
            return i;
    return -1;
}
void Display(Tree<char> &TreeM)
{
    for (int i = 0; i < N; i++)
    {
        if (TreeM.array[i].getParent() == NULL)
            cout << "\\"
                 << " ";
        else
        {
            char ch = TreeM.array[i].getParent()->getValue();
            cout << GetNum(ch) << " ";
        }
    }
    cout << endl;
}
int main()
{
    Tree<char> TreeM(N);

    int i;
    for (i = 0; i < N; i++)
    {
        TreeM.array[i].setValue(StrName[i]);
        cout << StrName[i] << " ";
    } cout << endl;
     for (i = 0; i < N; i++)
        cout << i << " ";
   
    cout << endl;

   

    //####################父指针表示法的加权合并##############################
    
    cout<<"Union (A,B),(C,H),(G,F),(D,E),(I,F)\n";
    TreeM.Union(GetNum('A'), GetNum('B'));
    TreeM.Union(GetNum('C'), GetNum('H'));
    TreeM.Union(GetNum('F'), GetNum('G'));
    TreeM.Union(GetNum('F'), GetNum('I'));
    TreeM.Union(GetNum('D'), GetNum('E'));
    
    Display(TreeM);

    cout << "\nUnion (H,A),(E,G)\n";
    TreeM.Union(GetNum('A'), GetNum('H'));
    TreeM.Union(GetNum('E'), GetNum('G'));
    Display(TreeM);    
     cout << "\nUnion (H,E)\n";
     TreeM.Union(GetNum('H'), GetNum('E'));

     
     Display(TreeM);   
     for (i = 0; i < N; i++)
    {
        TreeM.array[i].setValue(StrName[i]);
        cout << StrName[i] << " ";
    } cout << endl;
     for (i = 0; i < N; i++)
        cout << i << " ";
    cout<<"\nThis is the result 1 \n" << endl;

    //#########################路径压缩#############################################
     cout<<"Union (A,B),(C,H),(G,F),(D,E),(I,F)\n";
    TreeM.Union(GetNum('A'), GetNum('B'));
    TreeM.Union(GetNum('C'), GetNum('H'));
    TreeM.Union(GetNum('F'), GetNum('G'));
    TreeM.Union(GetNum('F'), GetNum('I'));
    TreeM.Union(GetNum('D'), GetNum('E'));
    
    Display(TreeM);

    cout << "\nUnion (H,A),(E,G)\n";
    TreeM.Union(GetNum('A'), GetNum('H'));
    TreeM.Union(GetNum('E'), GetNum('G'));
    Display(TreeM);    
     cout << "\nUnion (H,E)\n";
     TreeM.UnionPC(GetNum('H'), GetNum('E'));
     Display(TreeM);   
      for (i = 0; i < N; i++)
    {
        TreeM.array[i].setValue(StrName[i]);
        cout << StrName[i] << " ";
    } cout << endl;
     for (i = 0; i < N; i++)
        cout << i << " ";
   cout<<"\nThis is the result 2\n" << endl;
    cout << endl;
  
  cout<<"the times of FIND of  is"<<counter1<<endl;

    return 0; //记得加断点
}