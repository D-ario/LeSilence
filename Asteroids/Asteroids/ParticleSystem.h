#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "SFML/Graphics.hpp"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem(unsigned int count, sf::Vector2f emitter, bool asteroid) :
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(4.f)),
        m_emitter(emitter)
    {
        this->asteroid = asteroid;

        for (int i = 0; i < m_particles.size(); i++)
        {
            if (!asteroid)
            {
                sf::Transform random;
                resetParticle(i, random);
            }
            else
            {
                resetParticle(i);
            }
        }
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    bool update(sf::Time elapsed)
    {
        bool end = true;
        for (int i = 0; i < m_particles.size(); i++)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            if (asteroid && m_vertices[i].color.a > 0 && end == true)
            {
                end = false;
            }

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            if (ratio <= 0.f)
            {
                ratio = 0.f;
            }
            else 
            {
                end = false;
            }
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
        return (asteroid ? end : false);
    }

    void update(sf::Time& elapsed, sf::Transform& transformPlayer, bool move)
    {
        for (int i = 0; i < m_particles.size(); i++)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if it's not asteroid and if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero && move)
            {
                resetParticle(i, transformPlayer);
            }

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            if (ratio <= 0.f)
            {
                ratio = 0.f;
            }
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
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
        float angle = (std::rand() % 90 + 45) * 3.14f / 180.f;

        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(/*std::cos(angle) **/ speed * forwardDirection.x, /*std::sin(angle) **/ speed * forwardDirection.y);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 4000) + 1000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter + transformPlayer * sf::Vector2f(0.f, 20.f);
    }

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;

        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 3000) + 1000);
        m_vertices[index].position = m_emitter;

    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    bool asteroid;
};

#endif