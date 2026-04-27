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
	public:
	static EditObjectPopup* create();
	GameObject* selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
};