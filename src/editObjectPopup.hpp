#pragma once

#include <Geode/modify/EditorUI.hpp>
#include <Geode/ui/Button.hpp>

class EditObjectPopup : public geode::Popup {
  protected:
  bool init() override;
  int m_page = 0;
  CCNode* m_grid = nullptr;
  void createInputs();
  
  geode::Button* m_applyButton;
  geode::Button* m_left;
  geode::Button* m_right;
  geode::TextInput* flipXInput = nullptr;
  geode::TextInput* flipYInput = nullptr;
  geode::TextInput* xPosInput = nullptr;
  geode::TextInput* yPosInput = nullptr;
  geode::TextInput* scaleXInput = nullptr;
  geode::TextInput* scaleYInput = nullptr;
  geode::TextInput* rotationInput = nullptr;
  geode::TextInput* zOrderInput = nullptr;
  geode::TextInput* opacityInput = nullptr;
  geode::TextInput* rScaleXInput = nullptr;
  geode::TextInput* rScaleYInput = nullptr;
  geode::TextInput* xSkewInput = nullptr;
  geode::TextInput* ySkewInput = nullptr;
  geode::TextInput* objectStringInput = nullptr;

  
  public:
  inline void setPositionInputs(CCNode* grid);
  inline void setRelativeScaleInputs(CCNode* grid);
  inline void setObjectStringInput(CCNode* grid);
  /*
  geode::TextInput* flipXInput = nullptr;
  geode::TextInput* flipYInput = nullptr;
  geode::TextInput* xPosInput = nullptr;
  geode::TextInput* yPosInput = nullptr;
  geode::TextInput* scaleXInput = nullptr;
  geode::TextInput* scaleYInput = nullptr;
  geode::TextInput* rotationInput = nullptr;
  geode::TextInput* zOrderInput = nullptr;
  geode::TextInput* opacityInput = nullptr;
  geode::TextInput* rScaleXInput = nullptr;
  geode::TextInput* rScaleYInput = nullptr;
  */
  static EditObjectPopup* create();
  GameObject* selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
};