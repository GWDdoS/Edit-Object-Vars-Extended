#pragma once

#include <Geode/ui/Button.hpp>
#include <Geode/modify/EditorUI.hpp>

class EditObjectPopup : public geode::Popup {
	protected:
	bool init() override;
	int m_page = 0;
	CCNode* m_grid = nullptr;
	void createInputs();
	
	geode::Button* m_applyButton;
	geode::Button* m_left;
	geode::Button* m_right;
	
	geode::TextInput* xPosInput;
	geode::TextInput* yPosInput;
	geode::TextInput* rotationInput;
	geode::TextInput* scaleXInput;
	geode::TextInput* scaleYInput;
	geode::TextInput* zOrderInput;
	geode::TextInput* objectIDInput;
	geode::TextInput* opacityInput;
	geode::TextInput* flipXInput;
	geode::TextInput* flipYInput;
	geode::TextInput* rScaleXInput;
	geode::TextInput* rScaleYInput;
	
	public:
	static EditObjectPopup* create();
	GameObject* selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
};