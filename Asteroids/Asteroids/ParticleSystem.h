#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "SFML/Graphics.hpp"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem(unsigned int count, sf::Vector2f emitter, bool asteroid);

    void setEmitter(sf::Vector2f position);

    bool update(sf::Time elapsed);

    void update(sf::Time& elapsed, sf::Transform& transformPlayer, bool move);

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

    void resetParticle(std::size_t index, sf::Transform& transformPlayer);

    void resetParticle(std::size_t index);

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    bool asteroid;
};

#endif