#include "editObjectPopup.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

// i hate cocos ui
// i hate rewriting cocos ui

template <typename T>
static CCNode* makeInputField(
    const char* inputTitle,
    geode::TextInput*& inputName,
    T value,
    CommonFilter filter = CommonFilter::Float
) {
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

    inputName->setString(fmt::to_string(value));

    inputNodes->addChild(lbl);
    inputNodes->addChild(inputName);
    return inputNodes;
}

void EditObjectPopup::createInputs() {
    auto cs = m_mainLayer->getContentSize();

    auto grid = CCNode::create();
    grid->setContentSize({ 370.f, 120.f });
    grid->setLayout(RowLayout::create()
    ->setGrowCrossAxis(true)
    ->setAxisAlignment(AxisAlignment::Center)
    ->setGap(8.f));

    grid->addChild(makeInputField("X Pos",    xPosInput,     selectedObject->getPositionX()));
    grid->addChild(makeInputField("Y Pos",    yPosInput,     selectedObject->getPositionY()));
    grid->addChild(makeInputField("Scale X",  scaleXInput,   selectedObject->getScaleX()));
    grid->addChild(makeInputField("Scale Y",  scaleYInput,   selectedObject->getScaleY()));
    grid->addChild(makeInputField("Rotation", rotationInput, selectedObject->getRotation()));
    grid->addChild(makeInputField("Z Order",  zOrderInput,   selectedObject->m_zOrder, CommonFilter::Int));

    grid->setAnchorPoint({ 0.5f, 0.5f });
    grid->setPosition(cs.width / 2, cs.height / 2 + 25.f);
    grid->updateLayout();

    m_mainLayer->addChild(grid);
}

bool EditObjectPopup::init() {
    if (!Popup::init(399.f, 230.f)) return false;
    m_noElasticity = true;

    auto cs = m_mainLayer->getContentSize();
    float cx = cs.width / 2;
    float cy = cs.height / 2;

    this->setTitle("Edit Object Variables", "goldFont.fnt");

    auto vLabel = CCLabelBMFont::create(
        fmt::format("v{}", Mod::get()->getVersion().toNonVString()).c_str(), "bigFont.fnt"
    );
    vLabel->setScale(0.25f);
    vLabel->setOpacity(220);
    vLabel->setPosition(cx, cy + 83.5f);
    m_mainLayer->addChild(vLabel);

    m_applyButton = Button::createWithNode(
        ButtonSprite::create("Apply"),
        [this](auto) {
            auto xPosStr     = xPosInput->getString();
            auto yPosStr     = yPosInput->getString();
            auto scaleXStr   = scaleXInput->getString();
            auto scaleYStr   = scaleYInput->getString();
            auto rotationStr = rotationInput->getString();
            auto zOrderStr   = zOrderInput->getString();

            if (xPosStr.empty() || yPosStr.empty() || scaleXStr.empty() ||
            scaleYStr.empty() || rotationStr.empty() || zOrderStr.empty()) {
                FLAlertLayer::create("Error", "Some of the fields are empty or null.", "OK")->show();
                return;
            }

            float scaleX = utils::numFromString<float>(scaleXStr).unwrapOr(1.f);
            float scaleY = utils::numFromString<float>(scaleYStr).unwrapOr(1.f);

            selectedObject->setPositionX(utils::numFromString<float>(xPosStr).unwrapOr(0.f));
            selectedObject->setPositionY(utils::numFromString<float>(yPosStr).unwrapOr(0.f));
            selectedObject->updateCustomScaleX(scaleX);
            selectedObject->updateCustomScaleY(scaleY);
            selectedObject->setRotation(utils::numFromString<float>(rotationStr).unwrapOr(0.f));
            selectedObject->m_zOrder = utils::numFromString<int>(zOrderStr).unwrapOr(0);
        }
    );

    m_applyButton->setPosition(cx, cy - 80.f);
    m_mainLayer->addChild(m_applyButton);

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