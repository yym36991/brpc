#include<iostream>
#include<mutex>

// 预加载只有一条语句return instance,这显然可以保证线程安全。
// 但是，我们知道预加载会造成内存的浪费。
class UniqueSingleTon{
 public:
  static UniqueSingleTon* getInstanse(){
    return instanse;
  }

 private:
  static UniqueSingleTon* instanse;
  UniqueSingleTon(){} //构造函数是私有的，因此不能在类外部直接创建该类的对象。这也是单例模式的关键之一，它能够确保该类只有一个实例存在。
};

UniqueSingleTon* UniqueSingleTon::instanse = new UniqueSingleTon();

// 懒加载
// 不浪费内存，但是无法保证线程的安全。首先，if判断以及其内存执行代码是非原子性的。其次，new Singleton()无法保证执行的顺序性。
// 不满足原子性或者顺序性，线程肯定是不安全的，这是基本的常识

class LazySingleTon{
 public:
  static LazySingleTon* getInstanse(){
    if (instanse == nullptr) {
        instanse = new LazySingleTon();
    }
    return instanse;
  }
 private:
  static LazySingleTon* instanse;
  LazySingleTon() {}
};

// 懒加载加锁
/*
实现了一个线程安全的懒汉式单例模式（Lazy Singleton），其中 instanse 是该类的唯一实例指针，mtx 是控制并发访问的互斥锁。
在 getInstanse() 方法中，如果实例指针为空，则会获取锁对象 lock，然后再次检查实例指针是否为空。这样可以保证只有一个线程能够在同一时间内创建实例，并且其他线程需要等待该线程释放锁之后才能进入临界区。
如果实例指针不为空，则直接返回该指针。由于该方法是静态方法，所以可以通过类名直接调用，而不需要先创建类的对象。
该类的构造函数是私有的，因此不能在类外部直接创建该类的对象。这也是单例模式的关键之一，它能够确保该类只有一个实例存在。
最后两行代码定义了静态成员变量 instanse 和 mtx，并初始化为 nullptr 和默认构造函数创建的未锁定状态的互斥锁对象。这些静态成员变量必须在类外部进行定义，以便为其分配存储空间。LazySingleTon::instanse 和 SafeLazySingleTon::mtx 分别表示类 SafeLazySingleTon 中的静态成员变量 instanse 和 mtx。
总之，这段代码实现了一个线程安全的单例模式，确保只有一个类的实例被创建，并且可以通过类名直接访问该实例。这种方法的优点是简单易懂，缺点是每次调用 getInstanse() 方法时都需要获取锁对象，如果频繁地调用该方法，可能会影响性能。


std::lock_guard<std::mutex> 是一个标准库提供的模板类，用于在其构造函数中获取一个互斥锁的锁对象，并在其析构函数中自动释放该锁对象。它的主要作用是在获取锁对象时保证线程安全，同时避免忘记释放锁对象导致死锁等问题的发生。
在这段代码中，std::lock_guard<std::mutex> 类型的对象 lock 在构造函数中获取了互斥锁对象 mtx 的锁，即在调用 lock_guard 的构造函数时，会自动调用 mtx.lock() 方法来获取锁，从而保证同一时间内只有一个线程能够访问临界区。
当 lock 对象被销毁时，会自动调用 lock_guard 的析构函数，释放互斥锁对象 mtx。这样可以确保在任何情况下都能释放锁，包括异常、返回等情况。因此，在使用互斥锁时，应该优先使用 std::lock_guard 来避免锁对象未被释放。
综上所述，std::lock_guard<std::mutex> lock(mtx); 表示获取互斥锁对象 mtx 的锁，lock 对象在超出作用域时自动释放锁，从而确保了线程安全。
*/
class SafeLazySingleTon{
 public:
  static SafeLazySingleTon* getInstanse(){
    if (instanse == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        instanse = new SafeLazySingleTon();
    }
    return instanse;
  }
  void showName(){
    std::cout<< "name is SafeLazySingleTon ";
  }
 private:
  static SafeLazySingleTon* instanse;
  static std::mutex mtx;
  SafeLazySingleTon() {}
};
SafeLazySingleTon* SafeLazySingleTon::instanse = nullptr;
std::mutex SafeLazySingleTon::mtx;

int main(){
    SafeLazySingleTon* single;
    single->getInstanse()->showName();

    return 0;
}




