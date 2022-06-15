/** @file StatisticsState.cpp */
#include "States/StatisticsState.h"
#include "Utils/Utility.h"

StatisticsState::StatisticsState(StateStack& stack, Context& context)
: State(stack, context)
, mTexts()
, mBackButton(context)
{
    createGUI();   
}

void StatisticsState::draw()
{
    auto& window = State::getContext().window;
    window.draw(mBackButton);
    for (auto& text : mTexts)
		window.draw(text);
}

bool StatisticsState::update(sf::Time)
{
    mBackButton.update();
    return true;
}

bool StatisticsState::handleEvent(const sf::Event& event)
{
    mBackButton.handleEvent(event);
    return true;
}

void StatisticsState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowSize = context.window.getView().getSize();

    mTexts.emplace_back("TIME PLAY", context.fonts.get(FontsID::PixelFont), 60);
    auto& timeplay = mTexts.back();
    Utility::centerOrigin(timeplay);

    float textheight = timeplay.getGlobalBounds().height + 50.f;

    timeplay.setOutlineThickness(2.f);
	timeplay.setOutlineColor(sf::Color(0, 0, 0));
    timeplay.setPosition(sf::Vector2f(windowSize.x * 2.f / 6.f, windowSize.y / 3.f));

    auto number = context.statistics.get(Statistics::TimePlay) / 1000;                         

    std::string time = Utility::timeToString(number);

    mTexts.emplace_back(time, context.fonts.get(FontsID::PixelFont), 60);
    auto& timeplayvar = mTexts.back();
    Utility::centerOrigin(timeplayvar);
    timeplayvar.setOutlineThickness(2.f);
	timeplayvar.setOutlineColor(sf::Color(0, 0, 0));
    timeplayvar.setPosition(sf::Vector2f(windowSize.x * 4.f / 6.f, windowSize.y / 3.f));

    mTexts.emplace_back("STARTED GAMES", context.fonts.get(FontsID::PixelFont), 60);
    auto& startedgames = mTexts.back();
    Utility::centerOrigin(startedgames);
    startedgames.setOutlineThickness(2.f);
	startedgames.setOutlineColor(sf::Color(0, 0, 0));
    startedgames.setPosition(sf::Vector2f(windowSize.x * 2.f / 6.f, windowSize.y / 3.f + (textheight)));
    mTexts.emplace_back(std::to_string(context.statistics.get(Statistics::StartedGames)), context.fonts.get(FontsID::PixelFont), 60);
    auto& startedgamesvar = mTexts.back();
    Utility::centerOrigin(startedgamesvar);
    startedgamesvar.setOutlineThickness(2.f);
	startedgamesvar.setOutlineColor(sf::Color(0, 0, 0));
    startedgamesvar.setPosition(sf::Vector2f(windowSize.x * 4.f / 6.f, windowSize.y / 3.f + (textheight)));

    mTexts.emplace_back("KILLED ENEMIES", context.fonts.get(FontsID::PixelFont), 60);
    auto& killedenemies = mTexts.back();
    Utility::centerOrigin(killedenemies);
    killedenemies.setOutlineThickness(2.f);
	killedenemies.setOutlineColor(sf::Color(0, 0, 0));
    killedenemies.setPosition(sf::Vector2f(windowSize.x * 2.f / 6.f, windowSize.y / 3.f + (2 * textheight)));
    mTexts.emplace_back(std::to_string(context.statistics.get(Statistics::KilledEnemies)), context.fonts.get(FontsID::PixelFont), 60);
    auto& killedenemiesvar = mTexts.back();
    Utility::centerOrigin(killedenemiesvar);
    killedenemiesvar.setOutlineThickness(2.f);
	killedenemiesvar.setOutlineColor(sf::Color(0, 0, 0));
    killedenemiesvar.setPosition(sf::Vector2f(windowSize.x * 4.f / 6.f, windowSize.y / 3.f + (2 * textheight)));

    mTexts.emplace_back("FINISHED GAMES", context.fonts.get(FontsID::PixelFont), 60);
    auto& finishedgames = mTexts.back();
    Utility::centerOrigin(finishedgames);
    finishedgames.setOutlineThickness(2.f);
	finishedgames.setOutlineColor(sf::Color(0, 0, 0));
    finishedgames.setPosition(sf::Vector2f(windowSize.x * 2.f / 6.f, windowSize.y / 3.f + (3 * textheight)));
    mTexts.emplace_back(std::to_string(context.statistics.get(Statistics::FinishedGames)), context.fonts.get(FontsID::PixelFont), 60);
    auto& finishedgamesvar = mTexts.back();
    Utility::centerOrigin(finishedgamesvar);
    finishedgamesvar.setOutlineThickness(2.f);
	finishedgamesvar.setOutlineColor(sf::Color(0, 0, 0));
    finishedgamesvar.setPosition(sf::Vector2f(windowSize.x * 4.f / 6.f, windowSize.y / 3.f + (3 * textheight)));

    mBackButton.setText("BACK");
    mBackButton.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f + (4 * textheight)));
    mBackButton.setCallback([&]() 
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::MenuOptionsState);
    });
}
