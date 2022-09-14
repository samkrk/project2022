#include <SFML/Graphics.hpp>
#include <iostream>
// #include <SFML/OpenGL.hpp>

int main()
{
    sf::Window window(sf::VideoMode(1000,800),"Window");
    // glEnable(GL_TEXTURE_2D);
    while (window.isOpen())
    {
        sf::Event event;

        // check the type of the event...
        while (window.pollEvent(event))

        {

        //////////////////////////////////
        // Mouse move 
            if (event.type == sf::Event::MouseMoved)
            {

            std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
            std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            
            }
        //////////////////////////////////
        // REAL TIME??? 
        if (event.type == sf::Event::KeyPressed)
        {
        if (event.key.code == sf::Keyboard::Escape)
        {
        std::cout << "the escape key was pressed" << std::endl;
        std::cout << "control:" << event.key.control << std::endl;
        std::cout << "alt:" << event.key.alt << std::endl;
        std::cout << "shift:" << event.key.shift << std::endl;
        std::cout << "system:" << event.key.system << std::endl;
        }
        }
        //////////////////////////////////


    switch (event.type)
    {
        
        //////////////////////////////////
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        //////////////////////////////////
        // key pressed
        case sf::Event::KeyPressed:
            std::cout << "Key pressed" << std::endl;
            break;

        //////////////////////////////////
        // print letter typed
        case sf::Event::TextEntered:
            if (event.text.unicode < 128){
            std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }
            break;
            
        

        //////////////////////////////////
        // we don't process other types of events
        default:
            break;
        }
        }
    }
    return 0;
}