#include "splashstate.h"
#include <iostream>

void SplashState::setup()
{
    splashImage.loadFromFile("test/particles/splash.png");

    glEnable(GL_TEXTURE_2D);

    glViewport(0, 0, (GLsizei) 1366, (GLsizei) 768);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1366, 768, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenTextures(1,  &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1366, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, splashImage.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
}

std::string SplashState::run()
{
    windbreeze::Event event;
    std::string nextState;

    inputHandler.processEvents();

    while(inputHandler.pollEvent(event))
    {
        if(event.type == windbreeze::Event::CLOSED)
            nextState = "NONE";
        else if(event.type == windbreeze::Event::KEYPRESSED)
        {
            // quitting and stuff. add pause and restart herevent.
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
                nextState = "NONE";
            else if (event.key.code == windbreeze::Keyboard::SPACE || event.key.code == windbreeze::Keyboard::RETURN)
                nextState = "particles";
        }
        else if(event.type == windbreeze::Event::RESIZED)
        {
            std::cout << event.size.width << "\n";
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 768.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1366.0f, 768.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1366.0f, 0.0f);
    glEnd();

    sfWindow.display();

    glBindTexture(GL_TEXTURE_2D, 0);

    return nextState;
}
