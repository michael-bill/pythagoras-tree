#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

const int W = 1000;
const int H = 1000;
float startAngle = PI / 2;
float angle = 0;
float step = 0.0025;
float legth = 250;
int iterations = 8;

sf::RenderWindow window(sf::VideoMode(W, H), "Pythagoras tree (ultra modified)", sf::Style::Close);

void tree(float x1, float y1, float dir, float l, int iteration, float corner) {
    float x2 = x1 + cos(dir + corner) * l;
    float y2 = y1 - sin(dir + corner) * l;
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(line, 2, sf::Lines);
    if (iteration > 0) {
        tree(x2, y2, dir + angle * (2 * PI / 3), l * 0.5, iteration - 1, 0);
        tree(x2, y2, dir + angle * (4 * PI / 3), l * 0.5, iteration - 1, 0);
        tree(x2, y2, dir + angle * (6 * PI / 3), l * 0.5, iteration - 1, 0);
    }
}

int main(int argc, char* args[])
{
   window.setFramerateLimit(150);
   sf::Vector2f center(W / 2, H / 2 + 100);

   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
       }
       window.clear();
       tree(center.x, center.y, startAngle, legth, iterations, 0);
       tree(center.x, center.y, startAngle, legth, iterations, (2 * PI / 3));
       tree(center.x, center.y, startAngle, legth, iterations, -(2 * PI / 3));
       if (angle > 2 * PI || angle < -2 * PI) step = -step;
       angle += step;
       window.display();
   }
   return 0;
}
