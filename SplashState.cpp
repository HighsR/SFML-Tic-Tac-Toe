#include "SplashState.hpp"  
#include <sstream>  
#include "DEFINITIONS.hpp"  
#include <iostream>  

#include "MainMenuState.hpp"

namespace sOLO
{
   SplashState::SplashState(GameDataRef data) : _data(data){
   }

   void SplashState::Init()  
   {  
       this->_data->assets.LoadTexture("Game Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

       _background.emplace(_data->assets.GetTexture("Game Background"));
   }

   void SplashState::HandleInput()  
   {  
       while (const auto event = _data->window.pollEvent()) {
           if (event->is<sf::Event::Closed>()) {
               _data->window.close();
           }
       }
   }

   void SplashState::Update(float dt)  
   {  
       if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)  
       {  
           this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
       }  
   }  
   void SplashState::Draw(float dt)  
   {  
       this->_data->window.clear(sf::Color::Red);  

       this->_data->window.draw(*this->_background);  

       this->_data->window.display();  
       
       
   }  
}
