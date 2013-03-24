#include <iostream>
using namespace std;

template <class T> class LinList;

template <class T> class ListNode {
    friend class LinList<T>;

    private:
        ListNode *next;
    public:
        T data;

        ListNode(ListNode<T> *ptrNext = NULL);
        ListNode(const T &item, ListNode<T> *ptrNext = NULL);
        ~ListNode(){};
};

template <class T> ListNode<T>::ListNode(ListNode<T> *ptrNext):next(ptrNext){};

template <class T> ListNode<T>::ListNode(const T &item, ListNode<T> *ptrNext) {
    data = item;
    next = ptrNext;  
};

template <class T> class LinList {
    private:
        ListNode<T> *head;
        ListNode<T> *currPtr;
        int size;
    public:
        LinList(void);
        ~LinList(void);

        int getlistSize(void) const;
        int isEmpty(void) const;
        ListNode<T> *getNodeByIndex(int pos);
        void insert(const T &item, int pos);
        void remove(int pos);
        void clearList(void);
};

template <class T> LinList<T>::LinList() {
    head = new ListNode<T>();
    size = 0;
};

template <class T> LinList<T>::~LinList() {
    delete head;
    size = 0;
};

template <class T> int LinList<T>::getlistSize(void) const {
    return size;
};

template <class T> int LinList<T>::isEmpty(void) const {
    return size == 0;
};

template <class T> ListNode<T>* LinList<T>::getNodeByIndex(int pos) {
    ListNode<T> *p;
    if (-1 < pos && pos <= size) {
        p = head->next;
        int i = 0;
        while (p != NULL && i < pos) {
            p = p->next;
            ++i;
        }
    } else if (pos == -1) {
        p = head;
    } else {
        cout << "参数 pos 越界" << endl;
        p = NULL;
    }
    return p;
};

template <class T> void LinList<T>::insert(const T &item, int pos) {
    if (0 <= pos && pos <= size) {
        ListNode<T> *p = getNodeByIndex(pos - 1);
        ListNode<T> *newNode = new ListNode<T>(item, p->next);
        p->next = newNode;
        ++size;
    } else {
        cout << "参数 pos 越界" << endl;
    }
};

template <class T> void LinList<T>::remove(int pos) {
    if (0 <= pos && pos <= size) {
        ListNode<T> *q, *p = getNodeByIndex(pos - 1);
        q = p->next;
        delete q;
        --size;
    } else {
        cout << "参数 pos 越界" << endl;
    }
};

template <class T> void LinList<T>::clearList(void) {
    ListNode<T> *p, *p1;

    p = head->next;
    while(p != NULL) {
        p1 = p;
        p = p->next;
        delete p1;
    }
    size = 0;
};