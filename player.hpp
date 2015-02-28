#include <SFML/Graphics.hpp>
using namespace sf;

const int STEPS_TO_WIN = 100;

class Player {
  public:
    Player(){};
    Player(unsigned int i, int w, int h);
    float points = 1;
    unsigned int id;
    void draw(RenderWindow&);
    unsigned int clickedButton = 255; //255 ~ no button 
  private:
    RectangleShape shape;
};

Player::Player(unsigned int i,int w,int h){
  id = i;
  shape = RectangleShape(Vector2<float>(w/4,h/STEPS_TO_WIN));
  shape.setFillColor(Color(100+(id*150), 250-(150*id), 50));
}

void Player::draw(RenderWindow& window){
  const auto s = window.getSize();

  Transform transform;
  transform.translate(id*s.x/4,s.y);

  shape.setScale(1,-points);
  window.draw(shape, transform);
}
