#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(){

    sf::Window window(sf::VideoMode(1000,800),"Window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::TextEntered:
                    cout << static_cast<char>(event.text.unicode) << endl;
                break;
                case sf::Event::Closed:
                    window.close();
                break;
                default:
                break;
            } 
        }
    }
    return 0;
}