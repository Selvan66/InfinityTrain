/** @file GraphicsSettingState.cpp */
#include "States/GraphicsSettingState.h"
#include "Utils/Utility.h"

GraphicsSettingState::GraphicsSettingState(StateStack& stack, Context& context)
: State(stack, context)
, mResolution("RESOLUTION", context.fonts.get(FontsID::PixelFont), 60)
, mResolutionSlider(context)
, mSaveResolution(context.settings.get<std::pair<int, int>>("Graphics", "Resolution"))
, mFullscreen("FULLSCREEN", context.fonts.get(FontsID::PixelFont), 60)
, mSaveFullscreen(context.settings.get<bool>("Graphics", "Fullscreen"))
, mFullscreenCheckbox(context)
, mOptionButtons()
{
    mResolutionSlider.addText("800x600");
    mResolutionSlider.addText("1024x576");
    mResolutionSlider.addText("1366x768");
    mResolutionSlider.addText("1600x900");
    mResolutionSlider.addText("1920x1080");
    std::string currentResolution = std::to_string(mSaveResolution.first) + "x" + std::to_string(mSaveResolution.second);
    mResolutionSlider.setCurrentText(currentResolution);

    mFullscreenCheckbox.setSelection(mSaveFullscreen);

    createGUI();
}

void GraphicsSettingState::draw()
{
    auto& window = State::getContext().window;
    window.draw(mResolution);
    window.draw(mResolutionSlider);
    window.draw(mFullscreen);
    window.draw(mFullscreenCheckbox);
    for (auto& button : mOptionButtons)
	{
		window.draw(button);
	}
}

bool GraphicsSettingState::update(sf::Time dt)
{
    mResolutionSlider.update(dt);
    mFullscreenCheckbox.update(dt);
    for (auto& button : mOptionButtons)
	{
		button.update(dt);
	}

    if (mFullscreenCheckbox.isSelected())
    {
        mResolutionSlider.setCurrentText("1920x1080");
    }

    return true;
}

bool GraphicsSettingState::handleEvent(const sf::Event& event)
{
    mResolutionSlider.handleEvent(event);
    mFullscreenCheckbox.handleEvent(event);
    for (auto& button : mOptionButtons)
	{
		button.handleEvent(event);
	}
    return true;
}

void GraphicsSettingState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowsize = context.window.getView().getSize();

    Utility::centerOrigin(mResolution);
    mResolution.setOutlineThickness(2.f);
	mResolution.setOutlineColor(sf::Color(0, 0, 0));
    float textwidth = mResolution.getGlobalBounds().width * 3.f / 5.f;
    float textheight = mResolution.getGlobalBounds().height + 50.f;
    mResolution.setPosition(sf::Vector2f((windowsize.x / 2.f) - textwidth, windowsize.y / 2.f));
    mResolutionSlider.setPosition((windowsize.x / 2.f) + textwidth, windowsize.y / 2.f);

    Utility::centerOrigin(mFullscreen);
    mFullscreen.setOutlineThickness(2.f);
	mFullscreen.setOutlineColor(sf::Color(0, 0, 0));
    mFullscreen.setPosition(sf::Vector2f((windowsize.x / 2.f) - textwidth, (windowsize.y / 2.f) + textheight));
    mFullscreenCheckbox.setPosition((windowsize.x / 2.f) + textwidth,(windowsize.y / 2.f) + textheight);

    mOptionButtons.emplace_back(context);
    auto& backButton = mOptionButtons.back();
    backButton.setText("BACK");
    backButton.setCallback([&]()
    {
        context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics", "Resolution");
        context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
        context.applyGraphicSettings();
        this->requestStackPop();
        this->requestStackPush(StatesID::SettingState);
    });
    backButton.setPosition(sf::Vector2f(windowsize.x  * 2.f/8.f, windowsize.y * 4.f / 5.f));

    mOptionButtons.emplace_back(context);
    auto& applyButton = mOptionButtons.back();
    applyButton.setText("APPLY");
    applyButton.setCallback([&]()
    {
        std::string applyResolution = mResolutionSlider.getCurrentText();
        std::string width = applyResolution.substr(0, applyResolution.find('x'));
        std::string height = applyResolution.substr(applyResolution.find('x') + 1, applyResolution.size());
        context.settings.set<std::pair<int, int>>(std::pair<int, int>(std::stoi(width), std::stoi(height)), "Graphics", "Resolution");
        context.settings.set<bool>(mFullscreenCheckbox.isSelected(), "Graphics", "Fullscreen");
        context.applyGraphicSettings();
    });
    applyButton.setPosition(sf::Vector2f(windowsize.x  * 4.f/8.f, windowsize.y * 4.f / 5.f));

    mOptionButtons.emplace_back(context);
    auto& saveButton = mOptionButtons.back();
    saveButton.setText("APPLY & SAVE");
    saveButton.setCallback([&]()
    {
        std::string applyResolution = mResolutionSlider.getCurrentText();
        std::string width = applyResolution.substr(0, applyResolution.find('x'));
        std::string height = applyResolution.substr(applyResolution.find('x') + 1, applyResolution.size());
        mSaveResolution = std::pair<int, int>(std::stoi(width), std::stoi(height));
        mSaveFullscreen = mFullscreenCheckbox.isSelected();
        context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics", "Resolution");
        context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
        context.applyGraphicSettings();
    });
    saveButton.setPosition(sf::Vector2f(windowsize.x  * 6.f/8.f, windowsize.y * 4.f / 5.f));
}
