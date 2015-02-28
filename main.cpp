#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;


int Joysticks(){
  int i = 0;

  while(Joystick::isConnected(i)){
    i++;
  }

  return i;
}

int main()
{
    // create the window
    RenderWindow window(VideoMode(800, 600), "My window");

    //Player* players = onePlayerPerJoystick();
    
    const int n = Joysticks();

    Player* ps[n];

    for( int i = 0; i < n; i++ )
      ps[i] = new Player(i);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);

        Player* p = ps[0];
        for( int i = 0; i < n; i++ ) {
          p = ps[i];

          Transform transform;
          transform.translate((1+i)*100,350);

          window.draw(*p->getShape(), transform);
        }

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}

