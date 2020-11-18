#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "SFML/Graphics.hpp"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem(unsigned int count, sf::Vector2f emitter, bool asteroid) :
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(3.f)),
        m_emitter(emitter)
    {
        this->asteroid = asteroid;

        for (int i = 0; i < m_particles.size(); i++)
        {
            sf::Transform random;
            resetParticle(i, random);
        }
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    bool update(sf::Time elapsed, sf::Transform& transformPlayer)
    {
        bool end = true;
        for (int i = 0; i < m_particles.size(); i++)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if it's not asteroid and if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
            {
                if (!asteroid)
                    resetParticle(i, transformPlayer);
            }
            // else if it's asteroid and particle is not dead, particles system play again
            else if (end == true)
            {
                end = false;
            }

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }

        return (asteroid ? end : false);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index, sf::Transform& transformPlayer)
    {
        sf::Vector2f forwardDirection(0.0f, 1.0f);
        forwardDirection = transformPlayer * forwardDirection;

        // give a random velocity and lifetime to the particle
        float angle;
        if (asteroid)
        {
            angle = (std::rand() % 360) * 3.14f / 180.f;

            float speed = (std::rand() % 50) + 50.f;
            m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
            m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
            m_vertices[index].position = m_emitter;
        }
        else
        {
            angle = (std::rand() % 90 + 45) * 3.14f / 180.f;

            float speed = (std::rand() % 50) + 50.f;
            m_particles[index].velocity = sf::Vector2f(/*std::cos(angle) **/ speed * forwardDirection.x, /*std::sin(angle) **/ speed * forwardDirection.y);
            m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

            // reset the position of the corresponding vertex
            m_vertices[index].position = m_emitter + transformPlayer * sf::Vector2f(0.f, 20.f);
        }
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    bool asteroid;
};

#endif