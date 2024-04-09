#include<iostream>

/* 简单工厂：
一个抽象产品类 多个具体产品类（披萨，奶酪披萨、胡椒披萨、希腊披萨）
一个具体工厂类
使用一个抽象产品类的多态，一个工厂简单生产多种产品

工厂方法：
一个抽象产品类 多个具体产品类（披萨，奶酪披萨、胡椒披萨、希腊披萨）
一个抽象工厂类 多个具体工厂类 （工厂，郑州工厂、深圳工厂）
使用一个抽象产品类和一个抽象工厂类的多态，多个工厂生产多种产品

抽象工厂：
多个抽象产品类，多个具体产品类（披萨，奶酪披萨、胡椒披萨、希腊披萨）+（球类，篮球、羽毛球、乒乓球）
一个抽象工厂类 多个具体工厂类 （工厂，郑州工厂、深圳工厂）
使用多个抽象产品类和一个抽象工厂类的多态，多个工厂生产多种产品

参考：https://zhuanlan.zhihu.com/p/575645658
https://segmentfault.com/a/1190000023963515
https://cloud.tencent.com/developer/article/1523363

*/
class Pissz{
 public:
  ~Pissz(){};
  virtual void bike()=0;
  // void prepare()=0;
 private:
  std::string name;
};

class CheesePissz : public Pissz{
 public:
  CheesePissz(){
    std::cout << " Cheese Pissz ";
  }
  void bike(){
    std::cout <<" Production method : Cook for ten minutes use Cheese";
  }
};

class PepperPissz : public Pissz{
 public:
  PepperPissz(){
    std::cout << " PepperPissz ";
  }
  void bike(){
    std::cout <<"Production method :  use Pepper ";
  }
  void feature(){
    std::cout <<  " Pepper pizza features are pepper ";
  }
};

class GreakPissz : public Pissz{
 public:
  GreakPissz(){
    std::cout << " GreakPissz";
  };
  GreakPissz(std::string name){
    std::cout << "GreakPissz Structure with parameters ";
  }
  void bike(){
    std::cout <<"Production method :  From Greece  ";
  }
};

class Ball{
 public:
  ~Ball(){};
  virtual void showName() = 0;
  virtual void play() = 0;
};

class BasketBall : public Ball{
 public:
  void showName(){
    std::cout << "my name is basketball ";
  }
  void play(){
    std::cout << "need five person together ";
  }
  
};

class Badminton : public Ball{
 public:
  void showName(){
    std::cout << "my name is Badminton ";
  }
  void play(){
    std::cout << "need only person two ";
  }  
};

class PingPong : public Ball {
 public:
  void showName(){
    std::cout << "my name is PingPong ";
  }
  void play(){
    std::cout << "need only person two, and use table ";
  } 
};

class Factory{
 public:
  virtual ~Factory(){};
  virtual Pissz* createProduct(std::string name) = 0;
  virtual Ball* createBall(std::string name) = 0;
  virtual void show () = 0;

//  private:
//   Pissz* pissz;
};

class ZhengZhouFactory : public Factory{
 public:
  ZhengZhouFactory():pissz(nullptr){};
  Pissz* createProduct(std::string product) {
    if (product == "cheesepissz") {
        pissz = new CheesePissz(); 
    }
    if (product == "pepperpissz") {
        pissz = new PepperPissz(); 
    }
    if (product == "greakpissz") {
        pissz = new GreakPissz(); 
    }
    return pissz;    
  }

  Ball* createBall(std::string ball_name) {
    Ball* ball = nullptr;
    if (ball_name == "basketball") {
      return new BasketBall();
    } else if (ball_name == "badminton") {
      return new Badminton();
    } else if(ball_name == "pingpong") {
      return new PingPong();
    }
  }

  void show(){
    std::cout <<"city： ZhengZhou ";
  }

  ~ZhengZhouFactory(){
    delete pissz;
    pissz = nullptr;
  }

 private:
  Pissz* pissz; 
};

class ShenZhenFactory : public Factory{
 public:
  ShenZhenFactory():pissz(nullptr){};
  Pissz* createProduct(std::string product) {
    if (product == "cheesepissz") {
        pissz = new CheesePissz(); 
    }
    if (product == "pepperpissz") {
        pissz = new PepperPissz(); 
    }
    if (product == "greakpissz") {
        pissz = new GreakPissz(); 
    }
    return pissz;    
  }

  void show(){
    std::cout <<"city： ShenZhen ";
  }

  Ball* createBall(std::string ball_name) {
    Ball* ball = nullptr;
    if (ball_name == "basketball") {
      return new BasketBall();
    } else if (ball_name == "badminton") {
      return new Badminton();
    } else if(ball_name == "pingpong") {
      return new PingPong();
    }
  }

  ~ShenZhenFactory(){
    delete pissz;
    pissz = nullptr;
  }

 private:
  Pissz* pissz; 
};


int main(){
    Factory* factoryzz = new ZhengZhouFactory();
    factoryzz->show();
    Pissz* cheese_pissa_zz = factoryzz->createProduct("cheesepissz");
    cheese_pissa_zz->bike();

    Pissz* pepper_pissa_zz = factoryzz->createProduct("pepperpissz");
    pepper_pissa_zz->bike();
    // 当想使用子类PepperPissa独有的方法：
    PepperPissz* pepperchild_pissa_zz = static_cast<PepperPissz*>(pepper_pissa_zz);
    pepperchild_pissa_zz->feature();

    Pissz* greak_pissa_zz = factoryzz->createProduct("greakpissz");
    greak_pissa_zz->bike();
    std::cout << "\n\n\n";


    Factory* factorysz = new ShenZhenFactory();
    factorysz->show();
    Pissz* cheese_pissa_sz = factorysz->createProduct("cheesepissz");
    cheese_pissa_sz->bike();

    Pissz* pepper_pissa_sz = factorysz->createProduct("pepperpissz");
    pepper_pissa_sz->bike();
    // 当想使用子类PepperPissa独有的方法：
    PepperPissz* pepperchild_pissa_sz = static_cast<PepperPissz*>(pepper_pissa_sz);
    pepperchild_pissa_sz->feature();

    Pissz* greak_pissa_sz = factorysz->createProduct("greakpissz");
    greak_pissa_sz->bike();    

    Ball* basketball = factorysz->createBall("basketball");
    std::cout<< std::endl << "basketball cage : " << std::endl;
    basketball->showName();
    basketball->play();

    delete factoryzz;
    delete factorysz;
    delete basketball;
    return 0;
}

