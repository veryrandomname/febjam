#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include <iostream>
using namespace sf;

const int INTERVAL = 5;
const int CHOOSE_TIME = 1;
const float GROW_SPEED = 0.1;

SoundBuffer alarm;
SoundBuffer paint;
SoundBuffer selected;

Sound sound;
Sound alarmSound;
Sound paintSound;

std::vector<Player> ps;
Font font;

int Joysticks(){
  int n = 0;

  while(Joystick::isConnected(n)){
    n++;
  }

  return n;
}

bool newRound = true;

bool win = false;

bool update(std::vector<Player>& ps, Player& p, Time& time, Event& event, RenderWindow& window){
  bool partyTime = ((int)ceil(time.asSeconds()) % INTERVAL) <= CHOOSE_TIME;

  if( partyTime ){
    if(newRound){
      for ( Player& po : ps )
        po.clickedButton = 255;
      newRound = false;
    }
    //react to input
    switch(event.type){
      case Event::JoystickButtonPressed:
        /*
        std::cout << event.joystickButton.joystickId << std::endl << (event.joystickButton.joystickId == p.id) << std::endl;
        std::cout << event.joystickButton.button << std::endl;
        std::cout << time.asMilliseconds() << std::endl;
        */
        if( event.joystickButton.joystickId == p.id ) {
          p.clickedButton = event.joystickButton.button;

          if(!p.selected.getStatus() == SoundSource::Status::Paused)
            p.selected.play();
        }

        break;
    }

    //new round, play alarm sound
    if(!alarmSound.getStatus() == SoundSource::Status::Paused){
      alarmSound.play();
    }
  }
  else{
    newRound = true;
    if( p.clickedButton != p.id )
      ps[p.clickedButton].points += GROW_SPEED;
    else
      p.points -= GROW_SPEED;

    //play paint sound
    if(!paintSound.getStatus() == SoundSource::Status::Paused)
      paintSound.play();

    //win
    if(p.points >= 100){
      win = true;
    }
  }

  return partyTime;
}

int main()
{
    // create the window
    RenderWindow window(VideoMode(800, 600), "paint the wall");

    const auto s = window.getSize();
    const auto w = s.x;
    const auto h = s.y;

    //music and sound
    Music music;
    music.openFromFile("./fabsfx/background.ogg");
    //music.play();

    alarm.loadFromFile("./fabsfx/alarm1s.wav");
    paint.loadFromFile("./fabsfx/paint3s.wav");
    selected.loadFromFile("./fabsfx/selected2.wav");
    alarmSound.setBuffer(alarm);
    paintSound.setBuffer(paint);


    //text stuff
    font.loadFromFile("directors.ttf");
    Text text("PARTY TIME", font, 200);
    //text.setColor(Color::Red);
    Transform textTransform;
    textTransform.translate(100,100);

    Text wintext("WIN", font, 400);

    Text buttonText("A           B           X           Y", font, 100);
    Transform buttonTextTransform;
    buttonTextTransform.translate(100,400);

 

    Clock clock;
    
    const int n = Joysticks();

    for( int i = 0; i < n; i++ )
      ps.push_back(Player(i,w,h,selected));

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
        window.clear(Color(200,200,180));

        bool partyTime = false;

        for( Player& p : ps ){

          //TODO: nur so hier
          //p.points += 0.001;

          auto time = clock.getElapsedTime();

          p.draw(window);

          partyTime = update(ps,p,time,event,window);

          //std::cout << p.points << std::endl;
          //std::cout << partyTime << std::endl;
        }

        if( partyTime ){
          window.draw(text,textTransform);

          for( Player& p : ps )
            p.drawChoice(window);
        }

        window.draw(buttonText, buttonTextTransform);
        // draw everything here...
        // window.draw(...);
        //
        if (win)
          window.draw(wintext);

        // end the current frame
        window.display();
    }

    return 0;
}
