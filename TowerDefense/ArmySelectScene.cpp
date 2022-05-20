#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "ArmySelectScene.hpp"
#include "Setting_Scene.hpp"

void ArmySelectScene::Initialize() {
    // parameter initialization
    // modify the totalArmy amount.
    totalArmy = 3;
    totalSpell = 2;
    
    // Space status background
    AddNewObject(new Engine::Image("play/sand.png", 1250, 0, 336, 896));

    // Initialize the usedSpace and totalSpace.
    if (!fromSetting) {
        usedSpace = 0;
    }
    // totalSpace = 10;

    // Add the usedSpace and totalSpace to the label.
    AddNewObject(UISpaceUsage = new Engine::Label("Space: " + std::to_string(usedSpace) + "/" + std::to_string(totalSpace), "pirulen.ttf", 30, 1395, 150, 0, 0, 0, 255, 0.5, 0.5));

    // initialize armyAmount
    if (!fromSetting) {
        for (int i=0; i<totalArmy; i++) {
            armyAmount[i] = 0;
        }
        for (int i = totalArmy; i < totalArmy + totalSpell; i++) {
            armyAmount[i] = 2;
        }
    }
    fromSetting = false;

    // set ArmyImage
    ArmyImage[0] = "play/warrior.png";
    ArmyImage[1] = "play/bombs.png";
    ArmyImage[2] = "play/Wobbuffet.png";
    ArmyImage[totalArmy + 0] = "play/FrozenSpell.png";
    ArmyImage[totalArmy + 1] = "play/StrengthenSpell.png";

    // Add new enemy
    for (int i=0; i<totalArmy; i++) {
        // AddNewArmy( id , ImagePath , SpaceCost)
        AddNewArmy(i, ArmyImage[i], 1);
    }

    Engine::ImageButton* btn;

    // Setting button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 1300, 450, 190, 80);
    btn->SetOnClickCallback(std::bind(&ArmySelectScene::PlayOnClick, this, BUTTON_SETTING, -1, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Setting", "pirulen.ttf", 30, 1395, 490, 0, 0, 0, 255, 0.5, 0.5));

    // Create the reset button. You can imitate the enter button construction in the Initialize() function.
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 1300, 600, 190, 80);
    btn->SetOnClickCallback(std::bind(&ArmySelectScene::PlayOnClick, this, BUTTON_RESET, -1, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Reset", "pirulen.ttf", 30, 1395, 640, 0, 0, 0, 255, 0.5, 0.5));

    // Enter button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 1300, 750, 190, 80);
    btn->SetOnClickCallback(std::bind(&ArmySelectScene::PlayOnClick, this, BUTTON_ENTER, -1, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Enter", "pirulen.ttf", 30, 1395, 790, 0, 0, 0, 255, 0.5, 0.5));

    // play bgm
    if (!mute)
        bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    else
        bgmInstance = AudioHelper::PlaySample("select.ogg", true, 0.0);
}
void ArmySelectScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ArmySelectScene::PlayOnClick(ButtonType type, int id, int spaceCost) {
    if (type == BUTTON_ENTER) {
        PlayScene *scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        scene->SetTotalArmyAmount(totalArmy);
        for (int i=0; i<totalArmy; i++) {
            scene->SetArmyAmount(i, armyAmount[i]);
            scene->ArmyImage[i] = ArmyImage[i];
        }
        for (int i = totalArmy; i < totalArmy + totalSpell; i++) {
            scene->SetArmyAmount(i, armyAmount[i]);
            scene->ArmyImage[i] = ArmyImage[i];
        }
        Engine::GameEngine::GetInstance().ChangeScene("play");
        scene->mute = mute;
    }
    else if (type == BUTTON_RESET) {
        // Reset the usedSpace and the amount of every army to 0.
        usedSpace = 0;
        for (int i = 0; i < totalArmy; i++) {
            armyAmount[i] = 0;
            UIArmyAmount[i]->Text = std::to_string(armyAmount[i]);
            UIArmyAmount[i]->Draw();
        }
        UISpaceUsage->Text = "Space: " + std::to_string(usedSpace) + "/" + std::to_string(totalSpace);
        UISpaceUsage->Draw();
    }
    else if (type == BUTTON_ADD) {
        // When the add(+) button is clicked, update the usedSpace and the armyAmount of that army. Make sure that the labels shown on the screen also update.
        // Notice that the button won't take effect when the usedSpace is equal to totalSpace.
        if (usedSpace + spaceCost <= totalSpace) {
            usedSpace += spaceCost;
            armyAmount[id] += 1;
            UIArmyAmount[id]->Text = std::to_string(armyAmount[id]);
            UISpaceUsage->Text = "Space: " + std::to_string(usedSpace) + "/" + std::to_string(totalSpace);
            UIArmyAmount[id]->Draw();
            UISpaceUsage->Draw();
        }
    }
    else if (type == BUTTON_SUB) {
        // When the sub(-) button is clicked, update the usedSpace and the armyAmount of that army. Make sure that the labels shown on the screen also update.
        // Notice that the button won't take effect when the armyAmount is equal to 0.
        if (armyAmount[id] >= 1) {
            usedSpace -= spaceCost;
            armyAmount[id] -= 1;
            UIArmyAmount[id]->Text = std::to_string(armyAmount[id]);
            UISpaceUsage->Text = "Space: " + std::to_string(usedSpace) + "/" + std::to_string(totalSpace);
            UIArmyAmount[id]->Draw();
            UISpaceUsage->Draw();
        }
    }
    else if (type == BUTTON_SETTING) {
        SettingScene *scene = dynamic_cast<SettingScene *>(Engine::GameEngine::GetInstance().GetScene("setting"));
        Engine::GameEngine::GetInstance().ChangeScene("setting");
        scene->isFromStageSelect = false;
        fromSetting = true;
    }
}
void ArmySelectScene::AddNewArmy(int id, std::string imageName, int spaceCost) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    int oneThirdW = w / 3;
    int oneThirdH = h / 3;
    int offsetW = (id % 3) * 380;
    int offsetH = id / 3 * 425;

    Engine::ImageButton* btn;

    // current amount
    AddNewObject(UIArmyAmount[id] = new Engine::Label(std::to_string(armyAmount[id]), "pirulen.ttf", 48, halfW / 4 + 80 + offsetW, oneThirdH - 225 + offsetH, 255, 255, 255, 255, 0.5, 0.5));

    // Army image
    AddNewObject(new Engine::Image(imageName, halfW / 4 + offsetW, oneThirdH - 175 + offsetH, 175, 175));

    // Create the add(+) button.
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW / 4 + offsetW, oneThirdH + 25 + offsetH, 75, 50);
    btn->SetOnClickCallback(std::bind(&ArmySelectScene::PlayOnClick, this, BUTTON_ADD, id, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("+", "pirulen.ttf", 45, halfW / 4 + 35 + offsetW, oneThirdH + 50 + offsetH, 0, 0, 0, 255, 0.5, 0.5));

    // Create the sub(-) button.
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW / 4 + offsetW + 100, oneThirdH + 25 + offsetH, 75, 50);
    btn->SetOnClickCallback(std::bind(&ArmySelectScene::PlayOnClick, this, BUTTON_SUB, id, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("-", "pirulen.ttf", 45, halfW / 4 + 135 + offsetW, oneThirdH + 50 + offsetH, 0, 0, 0, 255, 0.5, 0.5));
}

void ArmySelectScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_M) {
        mute = !mute;
        if (!mute)
            AudioHelper::ChangeSampleVolume(bgmInstance, AudioHelper::BGMVolume);
        else
            AudioHelper::ChangeSampleVolume(bgmInstance, 0.0);
    }
}
