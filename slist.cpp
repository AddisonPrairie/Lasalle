#include "slist.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
Class Library File
*/

struct node {
  node* next;
  void* value;
};

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};

class slist {
  public:
  node* root;

  slist() {
    
  }

  ~slist() {
    
  }

  void add(void* value) {
    node* l = last();

    if (l == nullptr) {
      root = new node();
      root->value = value;
      root->next = nullptr;
      return;
    }
    l->next = new node();
    l->next->next = nullptr;
    l->next->value = value;
  }

  //returns pointer to last value
  node* last() {
    node* prev = root;

    //cout << "hello from here" << root << endl;

    while (prev != nullptr) {
      if (prev->next == nullptr) {
        return prev;
      }
      prev = prev->next;
    }
    return nullptr;
  }

  //clear the list
  void clear() {
    node* l = last();
    while (l != nullptr) {
      delete l;
      l = last();
    }
    root = nullptr;
  }

  node* get(int index) {
    node* cur = root;
    for (int i = 0; i < index; i++) {
      if (cur == nullptr) {
        return nullptr;
      }
      cur = cur->next;
    }
    return cur;
  }

  void insert(int index, void* value) {
    if (index == 0) {
      node* curRoot = root;
      node newItem;

      root = &newItem;
      root->next = curRoot;
      root->value = value;
      return;
    }

    node* before = get(index - 1);
    node* after = get(index);

    if (before == nullptr) {
      cout << "error in insert" << endl;
    }

    node newItem;
    newItem.value = value;
    newItem.next = after;

    before->next = & newItem;
  }

  bool isEmpty() {
    return root == nullptr;
  }

  void exchg(int i1, int i2) {
    node* f = get(i1);
    node* s = get(i2);

    void* temp = f->value;
    f->value = s->value;
    s->value = temp;
  }

  void remove(int index) {
    node* before = get(index - 1);
    node* after = get(index + 1);

    if (before == nullptr) {
      cout << "error in remove" << endl;
    }

    delete get(index);

    before->next = after;
  }

  void set(int index, void* value) {
    node* toSet = get(index);
    if (toSet == nullptr) {
      cout << "setting null" << endl;
    }

    toSet->value = value;
  }

  int size() {
    node* prev = root;
    int count = 0;
    while (prev != nullptr) {
      prev = prev->next;
      count++;
    }
    return count;
  }

  string toString() {
    string ret = "";
    node* cur = root;
    while (cur != nullptr) {
      Airport* curValue = (Airport*) cur->value;
      string code = "";
      for (int i = 0; i < 5; i++) {
        code += curValue->code[i];
      }
      ret += code + " " + "latitude: " + to_string(curValue->latitude) + " longitude: " + to_string(curValue->longitude) + "\n";
      cur = cur->next;
    }
    return ret;
  }

  slist* subList(int start, int length) {
    slist* returned = new slist();

    if (get(start) == nullptr) {
      return returned;
    }

    node* prev = nullptr;
    
    for (int i = 0; i < length; i++) {
      node* cur = get(start + i);
      if (cur == nullptr) {
        cout << "sublist is longer than list";
        return returned;
      }
      node newNode;
      
      if (i == 0) {
        returned->root = &newNode;
        returned->root->value = cur->value;
        prev = returned->root;
      } else {
        prev->next = &newNode;
        newNode.value = cur->value;
        prev = &newNode;
      }
    }

    return returned;
  }
};

