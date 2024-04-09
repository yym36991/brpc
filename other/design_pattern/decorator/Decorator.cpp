#include<iostream>

class UniversityFriend{
 public:
  UniversityFriend(){}
  virtual void showPlay() = 0;    
};

class FriendLiMing : public UniversityFriend{
 public:
  void showPlay() {
    std::cout << "play basketball ";
  }
};

class Decorator : public UniversityFriend {
 public:
  Decorator(UniversityFriend* universityfriend): universityfriend_(universityfriend) {

  }
  void showPlay() override {
    if (universityfriend_ != nullptr) {
        universityfriend_->showPlay();
    }

  }

 protected:
  UniversityFriend* universityfriend_;
};


class ZhengZhouDecorator : public Decorator {
 public:
  ZhengZhouDecorator(UniversityFriend* universityfriend): universityfriend_(universityfriend) {

  }
  void showPlay() override {
    if (universityfriend_ != nullptr) {
        universityfriend_->showPlay();
        addActivity();
    }

  }
  void addActivity() {
    std::cout << "Can go to play in zhengzhou city ";
  }

//  private:
//   UniversityFriend* universityfriend_;   
};

int main(){
    UniversityFriend* universityfriend = new FriendLiMing();
    universityfriend->showPlay();
    std::cout << "\n\n";

    ZhengZhouDecorator* zzfriend_liming = new ZhengZhouDecorator(universityfriend); 
    zzfriend_liming->showPlay();  
    return 0;
}






