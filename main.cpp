// Authors: Joseph Calles and Tharith Sovann

#include "Body.hpp" // include header file

int main(int argc, char* argv[])
{
  int N, years, months, days;
  string holder, words;
  double R;

  double total_time = stod(argv[1]); // total_time
  double delta_time = stod(argv[2]); // delta_time
  double current_time = 0;           // current_time

  getline(cin, holder); // N
  N = stoi(holder);
  
  getline(cin, holder); // R
  R = stod(holder);
  
  // WINDOW
  sf::RenderWindow window(sf::VideoMode(500, 500), "N-Body Simulation");
  window.setFramerateLimit(30);

  // FONT
  sf::Font font; 
  if (!font.loadFromFile("Assistant-Regular.otf"))
  { cout << "Error: could not load font. . ." << endl; }

  // TEXT
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(20);
  text.setPosition(5.f, 5.f);
  text.setFillColor(sf::Color::White);

  // MUSIC
  sf::Music music;                                       
  if (!music.openFromFile("music.ogg")) 
  { cout << "ERROR: could not load music. . ." << endl; }
  music.play(); 

  // BACKGROUND
  sf::Texture background_texture;
  if(!background_texture.loadFromFile("background.png"))
  {
    cout << "Error: could not load background image. . ." << endl;
  }
  sf::Sprite background(background_texture);              
  background.setScale(1.f, 1.f);

  // BODIES
  std::vector<unique_ptr<Body>> bodies;
  for(int i = 0; i < N; i++)
  {
    unique_ptr<Body> body(new Body);
    (body)->set_radius(R);    
    (body)->set_gravity(6.67e-10);
    (body)->set_window_scale(window.getSize());

    cin >> (*body);
    bodies.push_back(move(body));
  }

  
  // ----- SFML WINDOW -----
  while( window.isOpen() )
  {
    sf::Event event; // initalise event object

    while( window.pollEvent(event)  ) 
    {
      if (  (event.type == sf::Event::Closed) ||
	   ((event.type == sf::Event::KeyPressed) &&
	     (event.key.code == sf::Keyboard::Escape) ) )
      { window.close(); } // close if Esc is pressed or window closed
    }

    days = ((current_time / 365.25)) / 24;
    months = days / 30;
    years = months / 12;

    words = "Elapsed time: "  +
            to_string(years)  + " years | "  +
            to_string(months) + " months | " +
            to_string(days)   + " days";
    text.setString(words);

    double x_force = 0;
    double y_force = 0;
	
    for(int i = 0; i < N; i++) // set force for all bodies 
    {
      for(int j = 0; j < N; j++) // sum-up force of all bodies in relation to body-of-interest 
      {
        if(i != j) // do not include self in calculation
	{
	  x_force += bodies.at(i)->calc_x_force(*bodies.at(j));
	  y_force += bodies.at(i)->calc_y_force(*bodies.at(j));		
	}
      }
      
      (bodies.at(i))->set_x_force(x_force); // set x_force
      (bodies.at(i))->set_y_force(y_force); // set y_force
		
      x_force = 0; // reset x_force
      y_force = 0; // reset y_force
    }

    window.clear();

    // DRAW BACKGORUND
    window.draw(background);

    // DRAW TEXT
    window.draw(text);
    
    // DRAW BODIES
    for(int i = 0; i < N; i++)
    {
      bodies.at(i)->step(delta_time);
      window.draw(*(bodies.at(i)));
    }

    // DISPLAY
    window.display();

    // INCREMENT TIME	
    current_time += delta_time;
    if(current_time >= total_time) break;
  }

  for(int i = 0; i < N; i++)
  {
    cout << *(bodies.at(i));
  }
  
  return 0;
}




















