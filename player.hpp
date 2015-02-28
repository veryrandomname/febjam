#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
  public:
    Player(int i);
    RectangleShape* getShape();
    int points = 10;
  private:
    RectangleShape shape;
};

Player::Player(int i){
  shape = RectangleShape(Vector2<float>(50,50));
  shape.setFillColor(Color(100+(i*150), 250-(150*i), 50));
}

RectangleShape* Player::getShape(){
  //shape.setScale(10,points);
  return &shape;
}
