#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "editObjectPopup.hpp"
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class $modify(EditObjVarEUI, EditorUI) {
	void createMoveMenu() {
		EditorUI::createMoveMenu();

		auto* btn = this->getSpriteButton("editSprite.png"_spr, menu_selector(EditObjVarEUI::openPopup), nullptr, 0.9f);
		m_editButtonBar->m_buttonArray->addObject(btn);
		auto rows = GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonsPerRow);
		auto cols = GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonRows);
		m_editButtonBar->reloadItems(rows, cols);
	}

	void openPopup(CCObject*) {
		if (!m_selectedObject || m_selectedObjects->count() >= 2) {
			FLAlertLayer::create("Error", "You can currently only edit one object at a time", "OK")->show();
			return;
		}
		EditObjectPopup::create()->show();
	}
};
