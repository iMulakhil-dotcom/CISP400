#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(800, 600), "Chaos Game");

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    int vertexCount = 3;  // Default: triangle
    bool waitingForVertexCount = true;

    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font" << endl;
    }

    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(24);
    instructions.setFillColor(Color::White);
    instructions.setPosition(10, 10);
    instructions.setString("Press 3,4,5,6,7,8 to choose polygon type");

    Text vertexPrompt;
    vertexPrompt.setFont(font);
    vertexPrompt.setCharacterSize(20);
    vertexPrompt.setFillColor(Color::Yellow);
    vertexPrompt.setPosition(10, 50);
    vertexPrompt.setString("Triangle=3 Square=4 Pentagon=5 Hexagon=6 Heptagon=7 Octagon=8");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Handle number key presses for vertex count
            if (event.type == Event::KeyPressed && waitingForVertexCount)
            {
                if (event.key.code == Keyboard::Num3) vertexCount = 3;
                else if (event.key.code == Keyboard::Num4) vertexCount = 4;
                else if (event.key.code == Keyboard::Num5) vertexCount = 5;
                else if (event.key.code == Keyboard::Num6) vertexCount = 6;
                else if (event.key.code == Keyboard::Num7) vertexCount = 7;
                else if (event.key.code == Keyboard::Num8) vertexCount = 8;

                if (vertexCount >= 3 && vertexCount <= 8)
                {
                    waitingForVertexCount = false;
                    instructions.setString("Click " + to_string(vertexCount) + " points for vertices");
                }
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left && !waitingForVertexCount)
                {
                    Vector2f click(event.mouseButton.x, event.mouseButton.y);

                    if (vertices.size() < vertexCount)
                    {
                        vertices.push_back(click);
                    }
                    else if (points.size() == 0)
                    {
                        points.push_back(click);
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // Generate points
        if (points.size() > 0)
        {
            for (int i = 0; i < 100; i++)
            {
                int randomVertex = rand() % vertexCount;
                Vector2f last = points.back();
                Vector2f newPoint;
                newPoint.x = (last.x + vertices[randomVertex].x) / 2.0f;
                newPoint.y = (last.y + vertices[randomVertex].y) / 2.0f;
                points.push_back(newPoint);
            }

            if (points.size() > 50000)
            {
                cout << "Finished! " << points.size() << " points generated." << endl;
                window.close();
            }
        }

        // Update text
        if (waitingForVertexCount)
        {
            instructions.setString("Press 3,4,5,6,7,8 to choose polygon type");
        }
        else if (vertices.size() < vertexCount)
        {
            instructions.setString("Click " + to_string(vertexCount - vertices.size()) + " more vertices");
        }
        else if (points.size() == 0)
        {
            instructions.setString("Click anywhere to start the Chaos Game");
        }
        else
        {
            instructions.setString("Points: " + to_string(points.size()) + " | Vertices: " + to_string(vertexCount));
        }

        // Draw everything
        window.clear(Color::Black);

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(8, 8));
            rect.setPosition(vertices[i]);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape dot(Vector2f(2, 2));
            dot.setPosition(points[i]);
            dot.setFillColor(Color::White);
            window.draw(dot);
        }

        window.draw(instructions);

        if (waitingForVertexCount)
        {
            window.draw(vertexPrompt);
        }

        window.display();
    }

    return 0;
}