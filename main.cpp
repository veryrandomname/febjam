#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>
using namespace sf;

const int INTERVAL = 6;
const int CHOOSE_TIME = 1;

std::vector<Player> ps;
Font font;

int Joysticks(){
  int n = 0;

  while(Joystick::isConnected(n)){
    n++;
  }

  return n;
}


bool update(std::vector<Player>& ps, Player& p, Time& time, Event& event){
  bool partyTime = ((int)floor(time.asSeconds()) % INTERVAL) <= CHOOSE_TIME;

  if( partyTime ){
    //react to input
    switch(event.type){
      case Event::JoystickButtonPressed:
        /*
        std::cout << event.joystickButton.joystickId << std::endl << (event.joystickButton.joystickId == p.id) << std::endl;
        std::cout << event.joystickButton.button << std::endl;
        std::cout << time.asMilliseconds() << std::endl;
        */
        if( event.joystickButton.joystickId == p.id )
          p.clickedButton = event.joystickButton.button;
        /*
        if( event.joystickButton.button == p.id )
          p.clickedButton = 255; // 255 ~ no button
        */

        break;
    }
  }
  else{
    // support others
    //TODO
    ps[p.clickedButton].points += 0.1;
  }

  return partyTime;
}

int main()
{
    // create the window
    RenderWindow window(VideoMode(800, 600), "My window");

    const auto s = window.getSize();
    const auto w = s.x;
    const auto h = s.y;

    //text stuff
    font.loadFromFile("directors.ttf");
    Text text("PARTY TIME", font, 130);
    //text.setColor(Color::Red);
    Transform textTransform;
    textTransform.translate(100,100);

    Text buttonText("A     B     Y     X", font, 100);
    Transform buttonTextTransform;
    buttonTextTransform.translate(100,400);

 

    Clock clock;
    
    const int n = Joysticks();

    for( int i = 0; i < n; i++ )
      ps.push_back(Player(i,w,h));

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

        bool partyTime = false;

        for( Player& p : ps ){

          //TODO: nur so hier
          //p.points += 0.001;

          auto time = clock.getElapsedTime();

          p.draw(window);

          partyTime = update(ps,p,time,event);

          //std::cout << p.points << std::endl;
          //std::cout << partyTime << std::endl;
        }

        if( partyTime )
          window.draw(text,textTransform);

        window.draw(buttonText, buttonTextTransform);
        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}
