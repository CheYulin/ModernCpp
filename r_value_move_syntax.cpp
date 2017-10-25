#include <cstring>
#include <iostream>
using namespace std;

class MyClass {
private:
  int *heap_resource_handle_;
  int size_;

public:
  MyClass() {
    heap_resource_handle_ = nullptr;
    size_ = 0;
  }

  MyClass(int size) {
    cout << "default constructor"
         << ", acquire resource " << endl;
    heap_resource_handle_ = new int[size];
    memset(heap_resource_handle_, 0, size);
    size_ = size;
  }

  MyClass(const MyClass &object) {
    cout << "copy constructor" << endl;
    heap_resource_handle_ = new int[object.size_];
    size_ = object.size_;
    memcpy(heap_resource_handle_, object.heap_resource_handle_,
           sizeof(int) * object.size_);
  }

  MyClass(MyClass &&object) {
    cout << "move constructor" << endl;
    heap_resource_handle_ = object.heap_resource_handle_;
    object.heap_resource_handle_ = nullptr;
    size_ = object.size_;
    object.size_ = 0;
  }

  void release_resource() {
    if (heap_resource_handle_ != nullptr) {
      delete heap_resource_handle_;
      cout << "release resource, size:" << size_ << endl;
    }
  }

  MyClass &operator=(const MyClass &object) {
    release_resource();

    cout << "copy assignment" << endl;
    heap_resource_handle_ = new int[object.size_];
    size_ = object.size_;
    memcpy(heap_resource_handle_, object.heap_resource_handle_,
           sizeof(int) * object.size_);
    return *this;
  }

  MyClass &operator=(MyClass &&object) {
    release_resource();

    cout << "move assignment" << endl;
    heap_resource_handle_ = object.heap_resource_handle_;
    size_ = object.size_;

    object.heap_resource_handle_ = nullptr;
    object.size_ = 0;
    return *this;
  }

  ~MyClass() {
    cout << "destructor" << endl;
    release_resource();
  }
};

MyClass return_by_value() {
  MyClass object(111);
  return object;
}

void case00() {
  cout << "\ncase00" << endl;
  auto a = MyClass();
  a = return_by_value();
}

void case0() {
  cout << "\ncase0" << endl;
  auto a = return_by_value();
}

void case1() {
  cout << "\ncase1" << endl;
  auto a = MyClass(10);
}

void case2() {
  cout << "\ncase2" << endl;
  auto b = MyClass(20);
  auto a = b;
}

void case3() {
  cout << "\ncase3" << endl;
  auto c = MyClass(30);
  auto d = move(c);
}

void case4() {
  cout << "\ncase4" << endl;
  auto b = MyClass(4);
  auto a = MyClass(40);
  a = b;
}

void case5() {
  cout << "\ncase5" << endl;
  auto c = MyClass(5);
  auto d = MyClass(50);
  d = move(c);
}

int main(int argc, char const *argv[]) {
  case0();
  case00();
  case1();
  case2();
  case3();

  // assignment constructor
  case4();
  case5();
  return 0;
}
