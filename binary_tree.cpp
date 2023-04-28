#include <vector>
#include <cstdio>

template <typename T>
struct Node{
  T value;
  int id;
  Node<T>* l;
  Node<T>* r;
  Node<T>* parent;
};

template <typename T>
class BinaryTree 
{
  // l<=v<r
  private:
    Node<T>* _find_allocation_node(T a) {
      Node<T>* p = root;
      while(true) {
        if (p->value >= a && p->l != nullptr) {
          p = p->l;
        }
        else if(p->value < a && p->r != nullptr) {
          p = p->r;
        } else {
          return p;
        }
      }
    }

    int id = 0;

  public:
    Node<T>* root = nullptr;

    void insert(T a) {
      if (root == nullptr) {
        root = new Node<T>{a, id};
        id++;
        return;
      }

      auto p = _find_allocation_node(a);
      if (p->value < a) {
        p->r = new Node<T>{a, id};
        p->r->parent = p;
      } else {
        p->l = new Node<T>{a, id}; 
        p->l->parent = p;
      }
      id++;
    }

    Node<T>* find_node(T a) {
      Node<T>* p = root;
      Node<T>* q = nullptr;
      while (true) {
        if (p->value == a) {
          q = p;
        }
        
        if (p->value >= a && p->l != nullptr) {
          p = p->l;
        }
        else if (p->value < a && p->r != nullptr) {
          p = p->r;
        }
        else {
          break;
        }
      }

      return q;
    }
    
    Node<T>* erase(T a) {
      Node<T>* p = find_node(a);
      if (p == nullptr)return nullptr;

      Node<T>* rep_p = nullptr;
      if (p->r != nullptr) {
        p->r->parent = p->parent;
        p->r->l = p->l;
        p->l->parent = p->r;

        rep_p = p->r;
      }
      else if(p->l != nullptr) {
        p->l->parent = p->parent;

        rep_p = p->l;
      }

      if (p->parent->l == p) {
        p->parent->l = rep_p;
      } else {
        p->parent->r = rep_p;
      }

      return p;
    }

    ~BinaryTree() {
      auto f = [](auto f, Node<T>* p) -> void {
        Node<T>* l = p->l;
        Node<T>* r = p->r;
        delete p;
        if (l != nullptr)f(f, l);
        if (r != nullptr)f(f, r);
      };
      f(f, root);
    }
};

template <typename T>
void printTree(Node<T>* r, int lr) {
  if (r != nullptr) {
    printf("value:%d, id:%d, %c\n", r->value, r->id, lr == 0 ? 'l':'r');
    printTree(r->l, 0);
    printTree(r->r, 1);
  }
}

int main(void) {
  BinaryTree<int> bt;
  for (int i = 0;i < 10;i++) {
    bt.insert(i);
  }
  for (int i = -1;i > -10;i--) {
    bt.insert(i);
  }
  for (int i = 0;i < 10;i++) {
    bt.insert(0);
  }

  printf("%d\n", bt.find_node(0)->value);
  auto p = bt.erase(0);
  printTree(bt.root, 0);
  return 0;
}