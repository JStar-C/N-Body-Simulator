//Authors: Joseph Calles and Tharith Sovann

#include "Body.hpp" // include header file 

istream& operator>>(istream& input, Body& celestial_body)
{
  // get input from stdin
  input >> celestial_body._x_position >> celestial_body._y_position
	>> celestial_body._x_velocity >> celestial_body._y_velocity
	>> celestial_body._mass >> celestial_body._filename;
  
  // get and set object image
  if(!celestial_body._image.loadFromFile(celestial_body._filename))
    { cout << "Error: could not load sprite from file"
	   << '\'' << celestial_body._filename << '\'' << endl; }
  celestial_body._texture.loadFromImage(celestial_body._image);
  celestial_body._sprite.setTexture(celestial_body._texture);

  sf::Vector2u size = celestial_body._window_size; // get data variables
  sf::Vector2u image_size = celestial_body._texture.getSize();
    
  double rad = *celestial_body.get_radius(); // calculate position
  double x = (celestial_body._x_position * size.x) / ( 2.f * (rad) ) + (size.x / 2.0);
  double y = (celestial_body._y_position * size.y) / ( 2.f * (rad) ) + (size.y / 2.0);
  
  x -= (image_size.x / 2.f); // center position over self
  y -= (image_size.y / 2.f); 
  
  celestial_body._sprite.setPosition(x, y); // set position
    
  return input; // return istream
}

void Body::set_new_position(void)
{
  sf::Vector2u window_size = _window_size; 
  sf::Vector2u image_size = _texture.getSize();

  double radius = *get_radius();
  double x = (_x_position * window_size.x) / ( 2.f * radius ) + (window_size.x / 2.0);
  double y = (_y_position * window_size.y) / ( 2.f * radius ) + (window_size.y / 2.0);

  _sprite.setOrigin((image_size.x / 2.f), (image_size.y / 2.f));
  _sprite.setPosition(x, y);
}
  
double Body::calc_x_force(Body& other_planet)
{
  // total x_force between two bodies is calculated 
  double delta_x = other_planet._x_position - _x_position;
  double delta_y = other_planet._y_position - _y_position;
  double total_distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  double total_force = ( (*_gravity) * _mass * other_planet._mass) / pow(total_distance, 2);

 
  double x_force = total_force * (delta_x / total_distance);
  return x_force;
}

 
double Body::calc_y_force(Body& other_planet)
{
  // total y_force between two bodies is calculated 
  double delta_x = other_planet._x_position - _x_position;
  double delta_y = other_planet._y_position - _y_position;
  double total_distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
  double total_force = (*_gravity * _mass * other_planet._mass) / pow(total_distance, 2);

  double y_force = total_force * (delta_y / total_distance);
  return y_force;
}

void Body::step(double delta_time)
{
  // acceleration first
  _x_accel = _x_force / _mass;
  _y_accel = _y_force / _mass;

  // using acceleration to calculate new velocity
  _x_velocity -= (delta_time * _x_accel);
  _y_velocity -= (delta_time * _y_accel);

  // using velocity to calculate new position
  _x_position -= (delta_time * _x_velocity * 10);
  _y_position -= (delta_time * _y_velocity * 10);
	
  set_new_position();
}

// extraction operator overloader
ostream& operator<<(ostream& out, Body& celestial_body)
{
  out << celestial_body._x_position << ' '
      << celestial_body._y_position << ' '
      << celestial_body._x_velocity << ' '
      << celestial_body._y_velocity << ' '
      << celestial_body._mass       << ' '
      << celestial_body._filename   << ' '
      << endl;
  
  return out;
}
























