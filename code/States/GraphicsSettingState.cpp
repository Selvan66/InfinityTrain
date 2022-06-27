/** @file GraphicsSettingState.cpp */
#include "States/GraphicsSettingState.h"
#include "Utils/Utility.h"
#include "Gui/Checkbox.h"
#include "Gui/TextSlider.h"
#include "Gui/TextButton.h"

GraphicsSettingState::GraphicsSettingState(StateStack& stack, Context& context)
: State(stack, context)
, mSaveResolution(context.settings.get<std::pair<int, int>>("Graphics", "Resolution"))
, mSaveFullscreen(context.settings.get<bool>("Graphics", "Fullscreen"))
, mGui()
{
    createGUI();
}

void GraphicsSettingState::draw()
{
    auto& window = State::getContext().window;
    for (auto& component : *mGui)
		window.draw(*component.second);
}

bool GraphicsSettingState::update(sf::Time)
{
    for (auto& component : *mGui)
		component.second->update(); 

    if (Utility::safeCasting<Checkbox>(mGui->at("FullscreenBox").get())->isSelected())
        Utility::safeCasting<TextSlider>(mGui->at("ResolutionSlider").get())->setCurrentText("1920x1080");

    return true;
}

bool GraphicsSettingState::handleEvent(const sf::Event& event)
{
    for (auto& component : *mGui)
		component.second->handleEvent(event);
	
    return true;
}

void GraphicsSettingState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& window_size = context.window.getView().getSize();

    ParserGui& parser = context.gui.get(GuiFileID::GraphicsSetting);
    parser.addConst("TEXT_HEIGHT", 100.f);
    parser.addConst("TEXT_WIDTH", 270.f);
    parser.addConst("WINDOW_WIDTH", window_size.x);
	parser.addConst("WINDOW_HEIGHT", window_size.y);
    mGui = parser.parse(context);

    std::string currentResolution = std::to_string(mSaveResolution.first) + "x" + std::to_string(mSaveResolution.second);
    Utility::safeCasting<TextSlider>(mGui->at("ResolutionSlider").get())->setCurrentText(currentResolution);
    Utility::safeCasting<Checkbox>(mGui->at("FullscreenBox").get())->setSelection(mSaveFullscreen);

    Utility::safeCasting<TextButton>(mGui->at("BackButton").get())->setCallback([&]()
    {
        context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics", "Resolution");
        context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
        context.applyGraphicSettings();
        this->requestStackPop();
        this->requestStackPush(StatesID::SettingState);
    });

    Utility::safeCasting<TextButton>(mGui->at("ApplyButton").get())->setCallback([&]()
    {
        std::string applyResolution = Utility::safeCasting<TextSlider>(mGui->at("ResolutionSlider").get())->getCurrentText();
        std::string width = applyResolution.substr(0, applyResolution.find('x'));
        std::string height = applyResolution.substr(applyResolution.find('x') + 1, applyResolution.size());
        context.settings.set<std::pair<int, int>>(std::pair<int, int>(std::stoi(width), std::stoi(height)), "Graphics", "Resolution");
        context.settings.set<bool>(Utility::safeCasting<Checkbox>(mGui->at("FullscreenBox").get())->isSelected(), "Graphics", "Fullscreen");
        context.applyGraphicSettings();
    });

    Utility::safeCasting<TextButton>(mGui->at("ApplySaveButton").get())->setCallback([&]()
    {
        std::string applyResolution = Utility::safeCasting<TextSlider>(mGui->at("ResolutionSlider").get())->getCurrentText();
        std::string width = applyResolution.substr(0, applyResolution.find('x'));
        std::string height = applyResolution.substr(applyResolution.find('x') + 1, applyResolution.size());
        mSaveResolution = std::pair<int, int>(std::stoi(width), std::stoi(height));
        mSaveFullscreen = Utility::safeCasting<Checkbox>(mGui->at("FullscreenBox").get())->isSelected();
        context.settings.set<std::pair<int, int>>(mSaveResolution, "Graphics", "Resolution");
        context.settings.set<bool>(mSaveFullscreen, "Graphics", "Fullscreen");
        context.applyGraphicSettings();
    });
}
