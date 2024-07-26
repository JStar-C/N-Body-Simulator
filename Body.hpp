//Authors: Joseph Calles and Tharith Sovann

#ifndef BODY_HPP
#define BODY_HPP

// include SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// include directives
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

class Body : public sf::Drawable {
public:
  Body():_x_position(0), _y_position(0),
	 _x_velocity(0), _y_velocity(0), _mass(0) {}
  
  Body(double x, double y, double xv,
       double yv, double m, string filename): _x_position(x), _y_position(y),
					      _x_velocity(xv), _y_velocity(yv),
					      _mass(m), _filename(filename) {}

  friend istream& operator>>(istream& input, Body& x);

  friend ostream& operator<<(ostream& out, Body& celestial_body);

  void set_radius(double radius){ _universe_radius = std::make_shared<double>(radius); }
  void set_radius(shared_ptr<double> radius){ _universe_radius = radius; }
  	
  void set_gravity(double G){ _gravity = make_shared<double>(G); }

  void set_window_scale(sf::Vector2u window_size){ _window_size = window_size; }
  sf::Vector2u get_window_size(void) { return _window_size; }

  void set_x_vel(double xvel) { _x_position = xvel; }
  void set_y_vel(double yvel) { _y_position = yvel; }
        
  double calc_y_force(Body& other_planet);
  double calc_x_force(Body& other_planet);

  void set_x_force(double xforce) { _x_force = xforce; }
  void set_y_force(double yforce) { _y_force = yforce; }

  shared_ptr<double> get_radius(void){ return _universe_radius; }
  shared_ptr<double> get_G(void) { return _gravity; }

  double get_mass(void) { return _mass; }
 
  void step(double delta_seconds);
  void set_new_position(void);
private:

  void draw(sf::RenderTarget& target, sf::RenderStates state) const
  { target.draw(_sprite, state); } // draw function overrider
  
  double _x_position;
  double _y_position;
  	
  double _x_velocity;
  double _y_velocity;
  	
  double _x_accel;
  double _y_accel;

  double _x_force;
  double _y_force;
	
  double _mass;
  string _filename;

  shared_ptr<double> _universe_radius;
  shared_ptr<double> _gravity;
	

  sf::Vector2u _window_size;
  sf::Texture _texture;
  sf::Image _image;
  sf::Sprite _sprite;
};

#endif /* BODY_HPP */
