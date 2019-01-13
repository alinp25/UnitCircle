#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

int main() {
    const float WIDTH = 800;
    const float HEIGHT = 800;
    const float RADIUS = WIDTH / 4;

    const sf::Color BACKGROUND_COLOR = sf::Color::Black;
    const sf::Color DRAW_COLOR = sf::Color::White;
    const sf::Color COORD_COLOR = sf::Color::Red;
    const sf::Color LINE_COLOR = sf::Color::Green;

    const float THICKNESS = 2;

    const float PI = M_PI;

    float angle = PI / 2;

    std::string angleString, cosString, sinString;
    sf::Text displayAngle, displayCos, displaySin;

    sf::Font oswaldFont;
    if (!oswaldFont.loadFromFile("Oswald-Bold.ttf")) {
        std::cout << "Couldn't load Oswald-Bold.ttf\n";
        return 0;
    }

    displayAngle.setPosition(50, 50);
    displayCos.setPosition(50, 100);
    displaySin.setPosition(50, 150);
    displayAngle.setFont(oswaldFont);
    displayCos.setFont(oswaldFont);
    displaySin.setFont(oswaldFont);
    displayAngle.setCharacterSize(24);
    displayCos.setCharacterSize(24);
    displaySin.setCharacterSize(24);
    displayAngle.setFillColor(DRAW_COLOR);
    displayCos.setFillColor(DRAW_COLOR);
    displaySin.setFillColor(DRAW_COLOR);

    angleString = "Angle: " + std::to_string(angle - PI / 2);
    displayAngle.setString(angleString);
    cosString = "Cos: " + std::to_string(cos(angle - PI / 2));
    displayCos.setString(cosString);
    sinString = "Sin: " + std::to_string(sin(angle - PI / 2));
    displaySin.setString(sinString);

    sf::Vector2f centerScreen(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f circlePosition(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Unit Circle");

    sf::CircleShape circle(RADIUS);
    circle.setPosition(circlePosition);
    circle.setFillColor(BACKGROUND_COLOR);
    circle.setOutlineColor(LINE_COLOR);
    circle.setOutlineThickness(THICKNESS);

    sf::Vector2f pointPosition(RADIUS * sin(angle), RADIUS * cos(angle));
    sf::Vector2f pointPositionCopy(RADIUS * sin(angle), RADIUS * cos(angle));

    sf::Vertex line[] = {
        sf::Vertex(centerScreen, LINE_COLOR),
        sf::Vertex(centerScreen + pointPositionCopy, LINE_COLOR)
    };

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(WIDTH / 2, 0), sf::Color::White),
        sf::Vertex(sf::Vector2f(WIDTH / 2, HEIGHT), sf::Color::White)
    };
    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(0, HEIGHT / 2), sf::Color::White),
        sf::Vertex(sf::Vector2f(WIDTH, HEIGHT / 2), sf::Color::White)
    };
    
    sf::Vertex projectionToYAxis[] = {
        sf::Vertex(centerScreen + pointPosition, COORD_COLOR),
        sf::Vertex(sf::Vector2f(WIDTH / 2, centerScreen.y + pointPosition.y), COORD_COLOR)
    };
    sf::Vertex projectionToXAxis[] = {
        sf::Vertex(centerScreen + pointPosition, COORD_COLOR),
        sf::Vertex(sf::Vector2f(centerScreen.x + pointPosition.x, HEIGHT / 2), COORD_COLOR)
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (angle >= 2 * PI) {
            angle = 0;
        }


        pointPosition.x = RADIUS * sin(angle);
        pointPosition.y = RADIUS * cos(angle);
        pointPositionCopy = pointPosition;
        line[1] = sf::Vertex(centerScreen + pointPositionCopy, LINE_COLOR);
        projectionToYAxis[0] = sf::Vertex(centerScreen + pointPosition, COORD_COLOR);
        projectionToYAxis[1] = sf::Vertex(sf::Vector2f(WIDTH / 2, centerScreen.y + pointPosition.y), COORD_COLOR);
        projectionToXAxis[0] = sf::Vertex(centerScreen + pointPosition, COORD_COLOR);
        projectionToXAxis[1] = sf::Vertex(sf::Vector2f(centerScreen.x + pointPosition.x, HEIGHT / 2), COORD_COLOR);

        angleString = "Angle: " + std::to_string(angle - PI / 2);
        displayAngle.setString(angleString);
        cosString = "Cos: " + std::to_string(cos(angle - PI / 2));
        displayCos.setString(cosString);
        sinString = "Sin: " + std::to_string(sin(angle - PI / 2));
        displaySin.setString(sinString);

        window.clear();


        window.draw(circle);
        window.draw(yAxis, 2, sf::Lines);
        window.draw(xAxis, 2, sf::Lines);
        window.draw(projectionToXAxis, 2, sf::Lines);
        window.draw(projectionToYAxis, 2, sf::Lines);
        window.draw(line, 2, sf::Lines);
        window.draw(displayAngle);
        window.draw(displaySin);
        window.draw(displayCos);

        window.display();

        angle += 0.001;
    }

    return 0;
}