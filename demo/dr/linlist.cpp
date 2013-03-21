#include <iostream>
#include <string>
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
        insert(const T &item, int pos);
        T delete(int pos);
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
    if (pos < -1 || pos > size) {
        cout << "参数 pos 越界" << endl;
        exit(0);
    }

    if (pos == -1) {
        return head;
    }

    ListNode<T> *p = head->next;
    int i = 0;
    while (p != NULL && i < pos) {
        p = p->next;
        ++i;
    }
    return p;
};

template <class T> LinList<T>::insert(const T &item, int pos) {
    if (pos < 0 || pos > size) {
        cout << "参数 pos 越界" << endl;
        exit(0);
    }

    ListNode<T> *p = getNodeByIndex(pos - 1);
    ListNode<T> *newNode = new ListNode<T>(item, p->next);
    p->next = newNode;
    ++size;
};

template <class T> T LinList<T>::delete(int pos) {
    if (pos < 0 || pos > size) {
        cout << "参数 pos 越界" << endl;
        exit(0);
    }

    ListNode<T> *q, *p = getNodeByIndex(pos - 1);
    q = p->next
    p-next = p->next->next;
    --size;
    return data;
};

struct PARAM {
    string key;
    string value;
};

int main() {
    LinList<PARAM> mylist;
    cout << mylist.isEmpty() << endl;
    cout << mylist.getlistSize() << endl;

    PARAM t;
    t.key = "username";
    t.value = "sam";
    mylist.insert(t, mylist.getlistSize());
    cout << mylist.getNodeByIndex(0)->data.key << '\t'
        << mylist.getNodeByIndex(0)->data.value << endl;
	return 0;
}