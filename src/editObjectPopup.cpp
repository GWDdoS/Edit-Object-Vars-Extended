#include "editObjectPopup.hpp"
#include "Geode/cocos/base_nodes/CCNode.h"
#include <Geode/Geode.hpp>
#include <Geode/cocos/actions/CCActionInterval.h> // skewBy and skewTo
#include <Geode/binding/GJScaleControl.hpp> // skewFromValue  and valueFromSkew
#include <Geode/cocos/base_nodes/CCNode.h> // setSkewY and setSkewX
#include <Geode/cocos/sprite_nodes/CCSprite.h> // setSkewY and setSkewX
#include <Geode/binding/GJTransformControlDelegate.hpp> // transformSkewXChanged
#include <Geode/binding/EditorUI.hpp>// transformSkewXChanged
#include <Geode/binding/LevelEditorLayer.hpp>

using namespace geode::prelude;

// i hate cocos ui
// i hate rewriting cocos ui

// jojo FUCK UR FORMATING BRO WHAT

template <typename T>
static CCNode* makeInputField(const char* inputTitle,
                              geode::TextInput*& inputName, T value,
                              CommonFilter filter = CommonFilter::Float) {
    auto inputNodes = CCNode::create();
    inputNodes->setContentSize({ 120.f, 52.f });

    auto lbl = CCLabelBMFont::create(inputTitle, "goldFont.fnt");
    lbl->setScale(0.55f);
    lbl->setAnchorPoint({ 0.5f, 0.5f });
    lbl->setPosition(60.f, 38.f);

    inputName = TextInput::create(110.f, inputTitle, "bigFont.fnt");
    inputName->setAnchorPoint({ 0.5f, 0.5f });
    inputName->setPosition(60.f, 16.f);
    inputName->setCommonFilter(filter);

    inputName->setString(fmt::format("{}", value));

    inputNodes->addChild(lbl);
    inputNodes->addChild(inputName);
    return inputNodes;
}

inline void EditObjectPopup::setPositionInputs(CCNode* grid) {
    grid->addChild(
        makeInputField("X Pos", xPosInput, selectedObject->getPositionX()));
    grid->addChild(
        makeInputField("Y Pos", yPosInput, selectedObject->getPositionY()));
    grid->addChild(
        makeInputField("Scale X", scaleXInput, selectedObject->getScaleX()));
    grid->addChild(
        makeInputField("Scale Y", scaleYInput, selectedObject->getScaleY()));
    grid->addChild(makeInputField("Rotation", rotationInput,
                                  selectedObject->getRotation()));
    grid->addChild(makeInputField("Z Order", zOrderInput,
                                  selectedObject->m_zOrder, CommonFilter::Int));
}

inline void EditObjectPopup::setRelativeScaleInputs(CCNode* grid) {
    // grid->addChild(makeInputField("Opacity", opacityInput,
    // selectedObject->getOpacity())); opacity does nothing. taht or i did it
    // wrong idk grid->addChild(makeInputField("Flip X", flipXInput,
    // selectedObject->isFlipX())); // what to do if these are bools
    // grid->addChild(makeInputField("Flip Y", flipYInput,
    // selectedObject->isdFlipY()));
    grid->addChild(makeInputField("R Scale X", rScaleXInput,
                                  selectedObject->getRScaleX()));
    grid->addChild(makeInputField("R Scale Y", rScaleYInput,
                                  selectedObject->getRScaleY()));
    grid->addChild(makeInputField("Skew X", xSkewInput,selectedObject->getSkewX()));
    grid->addChild(makeInputField("Skew Y", ySkewInput,selectedObject->getSkewY()));
}

inline void EditObjectPopup::setObjectStringInput(CCNode* grid) {
    grid->addChild(makeInputField("Object String", objectStringInput,
                                  selectedObject->getSaveString(GameManager::sharedState()->getEditorLayer())));
}

void EditObjectPopup::createInputs() {
    if (m_grid) {
        m_grid->removeFromParent();
    }

    auto cs = m_mainLayer->getContentSize();

    auto grid = CCNode::create();
    grid->setContentSize({ 370.f, 120.f });
    grid->setLayout(RowLayout::create()
                        ->setGrowCrossAxis(true)
                        ->setAxisAlignment(AxisAlignment::Center)
                        ->setGap(8.f));
    m_grid = grid;

    switch (m_page) {
    case 0:
        setPositionInputs(grid);
        break;
    case 1:
        setRelativeScaleInputs(grid);
        break;
    case 2:
        setObjectStringInput(grid);
        break;
    }

    grid->setAnchorPoint({ 0.5f, 0.5f });
    grid->setPosition(cs.width / 2, cs.height / 2 + 25.f);
    grid->updateLayout();

    m_mainLayer->addChild(grid);
}

bool EditObjectPopup::init() {
    if (!Popup::init(399.f, 230.f))
        return false;
    m_noElasticity = true;

    auto cs = m_mainLayer->getContentSize();
    float cx = cs.width / 2;
    float cy = cs.height / 2;

    this->setTitle("Edit Object Variables", "goldFont.fnt");

    auto vLabel = CCLabelBMFont::create(
        fmt::format("v{}", Mod::get()->getVersion().toNonVString()).c_str(),
        "bigFont.fnt");
    vLabel->setScale(0.25f);
    vLabel->setOpacity(220);
    vLabel->setPosition(cx, cy + 83.5f);
    m_mainLayer->addChild(vLabel);

    m_applyButton =
        Button::createWithNode(ButtonSprite::create("Apply"), [this](auto) {
            if (m_page == 0) {
                auto xPosStr = xPosInput->getString();
                auto yPosStr = yPosInput->getString();
                auto scaleXStr = scaleXInput->getString();
                auto scaleYStr = scaleYInput->getString();
                auto rotationStr = rotationInput->getString();
                auto zOrderStr = zOrderInput->getString();


                if (xPosStr.empty() || yPosStr.empty() || scaleXStr.empty() ||
                    scaleYStr.empty() || rotationStr.empty() || zOrderStr.empty()) {
                    FLAlertLayer::create("Error",
                                         "Some of the fields are empty or null.", "OK")
                        ->show();
                    return;
                }

                float scaleX = utils::numFromString<float>(scaleXStr).unwrapOr(1.f);
                float scaleY = utils::numFromString<float>(scaleYStr).unwrapOr(1.f);

                selectedObject->setPositionX(
                    utils::numFromString<float>(xPosStr).unwrapOr(0.f));
                selectedObject->setPositionY(
                    utils::numFromString<float>(yPosStr).unwrapOr(0.f));
                selectedObject->updateCustomScaleX(scaleX);
                selectedObject->updateCustomScaleY(scaleY);
                selectedObject->setRotation(
                    utils::numFromString<float>(rotationStr).unwrapOr(0.f));
                selectedObject->m_zOrder =
                    utils::numFromString<int>(zOrderStr).unwrapOr(0);

            } else if (m_page == 1) {
                auto rScaleXStr = rScaleXInput->getString();
                auto rScaleYStr = rScaleYInput->getString();
                auto setSkewXStr = xSkewInput->getString();
                auto setSkewYStr = ySkewInput->getString();

                if (rScaleXStr.empty() || rScaleYStr.empty()) {
                    FLAlertLayer::create("Error",
                                         "Some of the fields are empty or null.", "OK")
                        ->show();
                    return;
                }
                selectedObject->setRScaleX(
                    utils::numFromString<float>(rScaleXStr).unwrapOr(1.f));
                selectedObject->setRScaleY(
                    utils::numFromString<float>(rScaleYStr).unwrapOr(1.f));
                selectedObject->setSkewX(utils::numFromString<float>(setSkewXStr).unwrapOr(0.f));
                selectedObject->setSkewY(utils::numFromString<float>(setSkewYStr).unwrapOr(0.f));
            } else if (m_page == 2) {
                GameManager::sharedState()->getEditorLayer()->createObjectsFromString(objectStringInput->getString(), true, true);
            }
        });

    m_left = Button::createWithSpriteFrameName("GJ_arrow_03_001.png", [this](auto) {
        m_page--;
        if (m_page < 0)
            m_page = 0;
        createInputs();
    });

    m_right = Button::createWithSpriteFrameName("GJ_arrow_03_001.png", [this](auto) {
        m_page++;
        if (m_page > 2)
            m_page = 2;
        createInputs();
    });

    m_applyButton->setPosition(cx, cy - 80.f);
    m_left->setPosition(cx - 125.f, cy - 80.f);
    m_right->setPosition(cx + 125.f, cy - 80.f);
    m_right->getDisplayNode()->setScaleX(getScaleX() * -1.f);
    m_mainLayer->addChild(m_applyButton);
    m_mainLayer->addChild(m_right);
    m_mainLayer->addChild(m_left);

    createInputs();
    return true;
}

EditObjectPopup* EditObjectPopup::create() {
    auto ret = new EditObjectPopup();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}