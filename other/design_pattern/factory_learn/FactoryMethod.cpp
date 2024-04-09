#include<iostream>

/* 简单工厂：
一个抽象产品类 多个具体产品类（披萨，奶酪披萨、胡椒披萨、希腊披萨）
一个具体工厂类
使用一个抽象产品类的多态，一个工厂简单生产多种产品

工厂方法：
一个抽象产品类 多个具体产品类（披萨，奶酪披萨、胡椒披萨、希腊披萨）
一个抽象工厂类 多个具体工厂类 （工厂，郑州工厂、深圳工厂）
使用一个抽象产品类和一个抽象工厂类的多态，多个工厂生产多种产品
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
    std::cout << " 奶酪Pissz ";
  }
  void bike(){
    std::cout <<" 制作方式：使用奶酪 ";
  }
};

class PepperPissz : public Pissz{
 public:
  PepperPissz(){
    std::cout << " 胡椒披萨 ";
  }
  void bike(){
    std::cout <<"制作方式：使用胡椒 ";
  }
  void feature(){
    std::cout <<  " 胡椒披萨的特点是带胡椒 ";
  }
};

class GreakPissz : public Pissz{
 public:
  GreakPissz(){
    std::cout << " 希腊披萨";
  };
  GreakPissz(std::string name){
    std::cout << "有参 希腊披萨 ";
  }
  void bike(){
    std::cout <<"制作方式：使用希腊 ";
  }
};

class Factory{
 public:
  virtual ~Factory(){};
  virtual Pissz* createProduct(std::string name) = 0;
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
  void show(){
    std::cout <<"城市： 郑州 ";
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
    std::cout <<"城市： 深圳 ";
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

    delete factoryzz;
    delete factorysz;
    return 0;
}

