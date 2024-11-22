#include <SFML/Graphics.hpp>
#include "digitalclock.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
using namespace sf;
struct Star {
    float x,y;
    float speed;
    float size;
    Color color;
};

int main() {
        VideoMode desktop = VideoMode::getDesktopMode();
    RenderWindow window(desktop, "Digital Clock");
    //Random seed for genrating random numbers
    srand(static_cast<unsigned int>(time(0)));

    vector<Star> stars;//Vector to hold stars

    vector<Color> colors = {
    Color::Red,
    Color::Green,
    Color::Blue,
    Color::Yellow,
    Color::Magenta,
    Color::Cyan,
    Color::White
    };
    //Generating some random stars
    for (int i=0;i<200;i++){
        Star star;
        star.x=rand()%window.getSize().x;
        star.y=rand()%window.getSize().y;
        star.speed=(rand() % 10 + 5) * 0.1f;//Speed range [0.1,0.3]
        star.size=(rand() % (4) + 3);//Size range [1,3]
        star.color = colors[rand() % colors.size()];
        stars.push_back(star);

    }

    Font font;
    if (!font.loadFromFile("digital-7.ttf")) {
        return -1;
    }
    Text text("", font, 200);
    text.setFillColor(Color::White); // Ensure text is white
// Load the shader
    Shader glowShader;
    if (!glowShader.loadFromFile("glow.frag", Shader::Fragment)) {
        return -1;
    }
glowShader.setUniform("glowColor", Glsl::Vec3(1.0f, 1.0f, 0.5f)); // Soft yellow glow
glowShader.setUniform("glowRadius", 15.0f);                      // Adjust for smoother glow
glowShader.setUniform("resolution", Glsl::Vec2(window.getSize().x, window.getSize().y));






    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        for (auto& star : stars){
            star.y+=star.speed;//Simulating Movement

            if (star.y>window.getSize().y){
                star.y=-10;
                star.x=rand()%window.getSize().x;
                star.size=(rand()%4+3);
                star.speed=(rand()%10+5)*0.1f;
            }
        }
        text.setString(getCurrentTime());
        text.setPosition(470, 410);

        window.clear();
        for (const auto& star : stars){
            CircleShape starShape(star.size);
            starShape.setFillColor(star.color);
            starShape.setPosition(star.x,star.y);
            window.draw(starShape);
        }
// Draw text with shader
        RenderStates states;
        states.shader = &glowShader;
        window.draw(text, states);
        window.display();
    }

    return 0;
}
