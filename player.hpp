#include <SFML/Graphics.hpp>
using namespace sf;

const int STEPS_TO_WIN = 100;
const Color colors[] = {Color(254,1,170), Color(23,232,121),Color(18,204,237),Color(255,204,0)};

const CircleShape circle(20);

class Player {
  public:
    Player(){};
    Player(unsigned int i, int w, int h, SoundBuffer& selectedBuffer);
    float points = 1;
    unsigned int id;
    void draw(RenderWindow&);
    void drawChoice(RenderWindow&);
    unsigned int clickedButton = 255; //255 ~ no button 
    Sound selected;
  private:
    RectangleShape shape;
};

Player::Player(unsigned int i,int w,int h, SoundBuffer& selectedBuffer){
  id = i;
  shape = RectangleShape(Vector2<float>(w/4,h/STEPS_TO_WIN));
  shape.setFillColor(colors[i]);

  //sound
  selected.setBuffer(selectedBuffer);
}

void Player::draw(RenderWindow& window){
  //draw bar
  const auto s = window.getSize();

  Transform transform;
  transform.translate(id*s.x/4,s.y);

  shape.setScale(1,-points);
  window.draw(shape, transform);
}

void Player::drawChoice(RenderWindow& window){
  const auto s = window.getSize();
  //show what was chosen
  Transform transform;
  transform.translate(id * s.x/4, s.y* 0.2);
  if(clickedButton != 255)
    window.draw(circle, transform);
}
