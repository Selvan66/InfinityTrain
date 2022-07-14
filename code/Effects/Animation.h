/** @file Animation.h */
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Animation : public sf::Drawable, public sf::Transformable
{
    public:
        Animation();
        explicit Animation(const sf::Texture& texture);
        void setTexture(const sf::Texture& texture);
        void setFrameSize(sf::Vector2i frameSize);
        void setNumFrames(std::size_t numFrames);
        void setDuration(sf::Time duration);
        void setRepeating(bool flag);
        void setReversed(bool flag);
        void restart();
        bool isFinished() const;
        sf::FloatRect getGlobalBounds() const;
        void update(sf::Time dt);
    private:
        sf::IntRect firstFrame() const;
        sf::IntRect nextFrame(sf::IntRect rect) const;
        void incrementCurrentFrame();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Sprite mSprite;
        sf::Vector2i mFrameSize;
        std::size_t mNumFrames;
        std::size_t mCurrentFrame;
        sf::Time mDuration;
        sf::Time mElapsedTime;
        bool mRepeat;
        bool mReverse;
};