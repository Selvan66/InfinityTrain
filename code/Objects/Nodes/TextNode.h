/** @file TextNode.h */
#pragma once

#include "App/Context.h"
#include "Gui/Text.h"
#include "Objects/Nodes/SceneNode.h"

class TextNode : public SceneNode {
public:
  explicit TextNode(Context &context);
  void setString(const std::string &text);

protected:
  virtual void drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const override;

private:
  Text mText;
};