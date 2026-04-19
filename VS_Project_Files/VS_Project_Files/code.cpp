#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    // SFML 3.0.2 uses sf::VideoMode with a size object
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3.0.2 Window");

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 375.f, 275.f });

    // Main Loop
    while (window.isOpen())
    {
        // New SFML 3 event loop using std::optional
        while (const std::optional event = window.pollEvent())
        {
            // Modern event type checking
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
