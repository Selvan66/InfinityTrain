/** @file Pickup.h */
#pragma once

#include "Objects/Nodes/Interactable.h"
#include "Player/Stats.h"

class PlayerNode;

class Pickup : public Interactable
{
    public:
        Pickup(Context& context);

        virtual std::string getDescription() const;
        virtual const std::unordered_map<Stats::Type, int>& getStats() const;
        virtual bool action(PlayerNode& player);
        
        virtual void interact() override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
    protected:
        void setTexture(TexturesID texture);
        void setCommand(Command command);
        void setText(const std::string& text);

        Context& getContext() const;
        const std::string& getName() const;

        virtual std::unique_ptr<Pickup> create() const;
        virtual sf::FloatRect getBoundingRect() const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        Context& mContext;
        sf::Sprite mSprite;
        bool mPickedUp;
        Command mCommand;
        std::string mText;
        std::unordered_map<Stats::Type, int> mStats;
};