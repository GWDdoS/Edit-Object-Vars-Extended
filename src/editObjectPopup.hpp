#pragma once

#include <Geode/ui/Button.hpp>
#include <Geode/modify/EditorUI.hpp>

class EditObjectPopup : public geode::Popup {
	protected:
		bool init() override;

		void createInputs();

		geode::Button* m_applyButton;
		geode::TextInput* xPosInput;
		geode::TextInput* yPosInput;
		geode::TextInput* rotationInput;
		geode::TextInput* scaleXInput;
		geode::TextInput* scaleYInput;
		geode::TextInput* zOrderInput;
		geode::TextInput* objectIDInput;

	public:
		static EditObjectPopup* create();
		GameObject* selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
};