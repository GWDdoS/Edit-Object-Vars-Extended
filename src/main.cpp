#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "editObjectPopup.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <limits>

using namespace geode::prelude;

class $modify(EditObjVarEUI, EditorUI) {
    void createMoveMenu() {
        EditorUI::createMoveMenu();
        auto* editBtn = this->getSpriteButton("editSprite.png"_spr, menu_selector(EditObjVarEUI::openPopup), nullptr, 0.9f);
        auto* leftBtn = this->getSpriteButton("moveLeft.png"_spr, menu_selector(EditObjVarEUI::moveLeft), nullptr, 0.75f);
        auto* upBtn = this->getSpriteButton("moveUp.png"_spr, menu_selector(EditObjVarEUI::moveUp), nullptr, 0.75f);
        auto* rightBtn = this->getSpriteButton("moveRight.png"_spr, menu_selector(EditObjVarEUI::moveRight), nullptr, 0.75f);
        auto* downBtn = this->getSpriteButton("moveDown.png"_spr, menu_selector(EditObjVarEUI::moveDown), nullptr, 0.75f);
        m_editButtonBar->m_buttonArray->addObject(editBtn);
        m_editButtonBar->m_buttonArray->addObject(leftBtn);
        m_editButtonBar->m_buttonArray->addObject(upBtn);
        m_editButtonBar->m_buttonArray->addObject(rightBtn);
        m_editButtonBar->m_buttonArray->addObject(downBtn);
        auto rows = GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonsPerRow);
        auto cols = GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonRows);
        m_editButtonBar->reloadItems(rows, cols);
    }

    void openPopup(CCObject*) {
        /*
        m_selectedObjects pulls from object info thing
        which doenst exist till u select 2 or more objects
        im killing osmeone

        if (m_selectedObjects->count() >= 2) {
            FLAlertLayer::create("Error", "You can currently only edit one object at a time", "Close")->show();
            return;
        }
        // if u have !m_selectedObjects; the game crahes cus it seems to be always 0 unless ofc smt is selected
        if (m_selectedObjects->count() == 0) {
            FLAlertLayer::create("Error", "You have to select an object", "Close")->show();
            return;
        }
        */
        CCArrayExt<GameObject*> sel = EditorUI::get()->getSelectedObjects();
        // ty slideglide
        if (sel.empty()) {
            FLAlertLayer::create("Error", "You have to select an object", "Close")->show();
            return;
        }
        if (sel.size() != 1) {
            FLAlertLayer::create("Error", "You can currently only edit one object at a time", "Close")->show();
            return;
        }

        // GameObject* obj = sel.front(); // or sel[0]
        // EditObjectPopup::create(obj)->show();
        EditObjectPopup::createEditGUI()->show();
    }
    // soemone asked for float movement buttonsi hope this works
    void moveLeft(CCObject*) {
        auto selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
        auto pos = selectedObject->getPositionX();
        geode::log::info("pos old {}", pos);
        auto newpos = selectedObject->getPositionX() - 0.000001;
        selectedObject->setPositionX(newpos);
        geode::log::info("pos new {}", newpos);
    }

    void moveUp(CCObject*) {
        auto selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
        auto pos = selectedObject->getPositionY();
        geode::log::info("pos old {}", pos);
        auto newpos = selectedObject->getPositionY() + 0.000001;
        selectedObject->setPositionY(newpos);
        geode::log::info("pos new {}", newpos);
    }

    void moveRight(CCObject*) {
        auto selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
        auto pos = selectedObject->getPositionX();
        geode::log::info("pos old {}", pos);
        auto newpos = selectedObject->getPositionX() + 0.000001;
        geode::log::info("pos new {}", newpos);
        selectedObject->setPositionX(newpos);
    }

    void moveDown(CCObject*) {
        auto selectedObject = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
        auto pos = selectedObject->getPositionY();
        geode::log::info("pos old {}", pos);
        auto newpos = selectedObject->getPositionY() - 0.000001;
        selectedObject->setPositionY(newpos);
        geode::log::info("pos new {}", newpos);
    }
};
