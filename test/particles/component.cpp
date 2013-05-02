#include "component.h"
#include <entity/entity.h>
#include <entity/entitygroup.h>
#include <cmath>
#include <entitybackends/alignedentitybackend.h>
#include <SFML/OpenGL.hpp>
#include <iostream>

enum { ORANGE, LIME, TURQUOISE, SKYBLUE, PURPLE, PINK};

void RenderComponent::setup()
{
    currentSize = 1024;
    positionBuffer = new float[1024 * 2];
    colourBuffer = new float[1024 * 3];

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glViewport(0, 0, (GLsizei) 1366, (GLsizei) 768);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1366, 768, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPointSize(2);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderComponent::render(windgale::EntityGroup& all)
{
    uint32_t amountToIterate = all.getCount();
    if(amountToIterate > currentSize)
    {
        uint32_t newSize = currentSize;
        while(amountToIterate > newSize)
            newSize *= 2;
        extendBuffers(newSize);
    }

    int amountToRender = 0;
    
    int posBufferIterator = 0;
    int colBufferIterator = 0;

    for(auto entity : all.getSet())
    {
        FloatVec2 position = entity.lock()->getAttribute<FloatVec2>("position");
        Colour colour = entity.lock()->getAttribute<Colour>("currentcolour");

        positionBuffer[posBufferIterator] = position.x;
        positionBuffer[posBufferIterator + 1] = position.y;

        colourBuffer[colBufferIterator + 0] = colour.r;
        colourBuffer[colBufferIterator + 1] = colour.g;
        colourBuffer[colBufferIterator + 2] = colour.b;

        posBufferIterator += 2;
        colBufferIterator += 3;

        amountToRender++;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glColorPointer(3, GL_FLOAT, 0, colourBuffer);
    glVertexPointer(2, GL_FLOAT, 0, positionBuffer);

    glDrawArrays(GL_POINTS, 0, amountToRender);

    window->display();

    std::cout << "amount: " << all.getCount() << "\n";
}

void RenderComponent::extendBuffers(int newSize)
{
    float* tempPos = new float[newSize * 2];
    float* tempCol = new float[newSize * 3];

    for(uint32_t i = 0; i < currentSize; i++)
    {
        tempPos[i] = positionBuffer[i];
        tempCol[i] = colourBuffer[i];
    }

    delete [] positionBuffer;
    delete [] colourBuffer;
    positionBuffer = tempPos;
    colourBuffer = tempCol;
    currentSize = newSize;
}

RenderComponent::~RenderComponent()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    delete [] positionBuffer;
    delete [] colourBuffer;
}

void PhysicsComponent::update(windgale::EntityGroup& particles)
{
    for(auto entity : particles.getSet())
    {
        float elast = 0.99999f;
        FloatVec2 position = entity.lock()->getAttribute<FloatVec2>("position");
        FloatVec2 velocity = entity.lock()->getAttribute<FloatVec2>("velocity");
        FloatVec2 newVelocity;
        
        newVelocity.x = velocity.x + (float)(rand() % 50 - 25) / 25.0f;
        newVelocity.y = velocity.y + (float)(rand() % 50 - 25) / 25.0f;

        if(position.x > 1366 || position.x < 0)
            newVelocity.x = -velocity.x * elast;
        if(position.y > 768 || position.y < 0)
            newVelocity.y = -velocity.y * elast;

        entity.lock()->setAttribute<FloatVec2>("position", {position.x += newVelocity.x, position.y += newVelocity.y});
        entity.lock()->setAttribute<FloatVec2>("velocity", newVelocity);
    }
}

void SpawningComponent::update(FloatVec2 colourPoints[6], windgale::EntityGroup& particles)
{
    windgale::WeakEntityPtr created;

    int iterated = 0;
    int spawnersCount = spawners->getCount();

    for(auto spawner : spawners->getSet())
    {
        if(!spawner.lock())
        {
            std::cout << "ojojojoj it becaakae crash and i did " << iterated << " iterations and spawners are " << spawnersCount << "\n";
        }
        uint32_t spawnrate = spawner.lock()->getAttribute<uint32_t>("spawnrate");
        float spawnpower = spawner.lock()->getAttribute<float>("spawnpower");
        uint8_t randomRate = rand() % 256;
        Colour colour = spawner.lock()->getAttribute<Colour>("currentcolour");
        FloatVec2 position = spawner.lock()->getAttribute<FloatVec2>("position");

        if(randomRate < spawnrate)
        {
            created = entityManager->createEntity("particle");

            FloatVec2 newVelocity;
            newVelocity.x = (float)((rand() % 200) - 100.0f) * 0.01f * (float) spawnpower;//0.0f;
            newVelocity.y = (float)((rand() % 200) - 100.0f) * 0.01f * (float) spawnpower;//0.0f;


            created.lock()->setAttribute<FloatVec2>("position", position);
            created.lock()->setAttribute<FloatVec2>("velocity", newVelocity);
            created.lock()->setAttribute<Colour>("currentcolour", colour);

            particles.add(created);
        }
    
        FloatVec2 targetPoint;
    
        if(add)
        {
            if(colour.r > colour.g && colour.r > colour.b)
            {
                if(colour.g > colour.b)
                {
                    targetPoint = colourPoints[ORANGE];
                }
                else
                {
                    targetPoint = colourPoints[PINK];
                }
            }
            else if(colour.g > colour.b)
            {
                if(colour.r > colour.b)
                {
                    targetPoint = colourPoints[LIME];
                }
                else
                {
                    targetPoint = colourPoints[TURQUOISE];
                }
            }
            else
            {
                if(colour.r > colour.g)
                {
                    targetPoint = colourPoints[PURPLE];
                }
                else
                {
                    targetPoint = colourPoints[SKYBLUE];
                }
            }
        }
        else
        {
            if(colour.r < colour.g && colour.r < colour.b)
            {
                if(colour.g > colour.b)
                {
                    targetPoint = colourPoints[ORANGE];
                }
                else
                {
                    targetPoint = colourPoints[PINK];
                }
            }
            else if(colour.g < colour.b)
            {
                if(colour.r > colour.b)
                {
                    targetPoint = colourPoints[LIME];
                }
                else
                {
                    targetPoint = colourPoints[TURQUOISE];
                }
            }
            else
            {
                if(colour.r > colour.g)
                {
                    targetPoint = colourPoints[PURPLE];
                }
                else
                {
                    targetPoint = colourPoints[SKYBLUE];
                }
            }
        }

        FloatVec2 direction;
        direction.x = targetPoint.x - position.x;
        direction.y = targetPoint.y - position.y;

        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x = direction.x / length;
        direction.y = direction.y / length;

        spawner.lock()->setAttribute<FloatVec2>("position", {position.x + direction.x, position.y + direction.y});

        iterated++;
    }
}

void DeathComponent::update(windgale::EntityGroup& particles)
{
    for(auto entity : particles.getSet())
    {
        if(entity.lock()->getAttribute<uint32_t>("deathrate") < (uint32_t(rand() % 10000)))
        {
          entityManager->removeEntity(entity.lock()->getId());
        }
    }
}
