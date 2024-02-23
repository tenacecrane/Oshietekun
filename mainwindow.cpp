/**
 * @file
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
/**
 * @brief MainWindow::MainWindow
 * @param model, Model class used as the controller of the project.
 * @brief Main window that acts as the view, updating everything
 * the user sees.
 */
MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Initial Window Setup
    ui->setupUi(this);
    ui->learnGraphicsView->setStyleSheet("border-image: url(:/images/kanaLearningSheet.png);background-repeat: no-repeat;");
    ui->homeGraphicsView->setStyleSheet("border-image: url(:/images/mainMenuBackground.jpg);background-repeat: no-repeat;");
    ui->stackedWidget->setCurrentIndex(0);
    this->setStyleSheet("background-color: rgba(164,216,245,80);");

    //Learn
    ui->learnPage->setStyleSheet("background-color: rgb(235,235,235);");
    connect(ui->learnButton, &QPushButton::clicked, this, &MainWindow::displayLearnImage);

    //Home
    connect(ui->homeButton, &QPushButton::clicked, this, &MainWindow::displayHomeImage);

    //Practice
    connect(ui->hiraganaLvl1, &QPushButton::clicked, this, [&model]{model.initiateLevel(0);});
    connect(ui->hiraganaLvl2, &QPushButton::clicked, this, [&model]{model.initiateLevel(1);});
    connect(ui->hiraganaLvl3, &QPushButton::clicked, this, [&model]{model.initiateLevel(2);});
    connect(ui->hiraganaLvl4, &QPushButton::clicked, this, [&model]{model.initiateLevel(3);});
    connect(ui->hiraganaLvl5, &QPushButton::clicked, this, [&model]{model.initiateLevel(4);});
    connect(ui->hiraganaLvl6, &QPushButton::clicked, this, [&model]{model.initiateLevel(5);});
    connect(ui->katakanaLvl1, &QPushButton::clicked, this, [&model]{model.initiateLevel(6);});
    connect(ui->katakanaLvl2, &QPushButton::clicked, this, [&model]{model.initiateLevel(7);});
    connect(ui->katakanaLvl3, &QPushButton::clicked, this, [&model]{model.initiateLevel(8);});
    connect(ui->katakanaLvl4, &QPushButton::clicked, this, [&model]{model.initiateLevel(9);});
    connect(ui->katakanaLvl5, &QPushButton::clicked, this, [&model]{model.initiateLevel(10);});
    connect(ui->katakanaLvl6, &QPushButton::clicked, this, [&model]{model.initiateLevel(11);});
    connect(ui->combinedLvl1, &QPushButton::clicked, this, [&model]{model.initiateLevel(12);});
    connect(ui->combinedLvl2, &QPushButton::clicked, this, [&model]{model.initiateLevel(13);});
    connect(ui->combinedLvl3, &QPushButton::clicked, this, [&model]{model.initiateLevel(14);});
    connect(ui->combinedLvl4, &QPushButton::clicked, this, [&model]{model.initiateLevel(15);});
    connect(ui->combinedLvl5, &QPushButton::clicked, this, [&model]{model.initiateLevel(16);});
    connect(ui->combinedLvl6, &QPushButton::clicked, this, [&model]{model.initiateLevel(17);});

    //Connecting all buttons
    connect(ui->practiceButton, &QPushButton::clicked, this, &MainWindow::displayPracticeHome);
    connect(ui->levelSelectButton, &QPushButton::clicked, this, &MainWindow::displayLevelSelect);
    connect(this, &MainWindow::emitOne,&model,&Model::receiveSelectionOne);
    connect(this, &MainWindow::emitTwo,&model,&Model::receiveSelectionTwo);
    connect(&model,&Model::sendMatch,this,&MainWindow::receiveMatch);
    connect(&model,&Model::sendLevels,this,&MainWindow::displayLevel);
    connect(ui->levelSelectButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(ui->fireworksButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(ui->wikiButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(ui->practiceButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(ui->homeButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(ui->learnButton,&QPushButton::clicked,this,&MainWindow::resetLevel);
    connect(&model,&Model::updateLevel,this,&MainWindow::updateLevelButton);
    connect(this,&MainWindow::sendMatch,&model,&Model::recieveMatch);
    connect(&model,&Model::loadCompletion,this,&MainWindow::loadCompletion);
    connect(ui->practiceButton,&QPushButton::clicked,&model,&Model::sendLevelData);

    //Wiki
    connect(ui->wikiButton, &QPushButton::clicked, this, &MainWindow::displayWikiPage);
    connect(ui->religionWikiPushButton, &QPushButton::clicked, this, [this]{displayPDF("religionInJapan.pdf");});
    connect(ui->educationWikiPushButton, &QPushButton::clicked, this, [this]{displayPDF("educationInJapan.pdf");});
    connect(ui->foodWikiPushButton,&QPushButton::clicked,this,[this]{displayPDF("foodInJapan.pdf");});
    connect(ui->holidaysWikiPushButton, &QPushButton::clicked, this, [this]{displayPDF("holidaysInJapan.pdf");});
    connect(ui->transportationWikiPushButton, &QPushButton::clicked, this, [this]{displayPDF("Transportation.pdf");});
    connect(ui->workingWikiPushButton, &QPushButton::clicked, this, [this]{displayPDF("WorkingPDF.pdf");});

    //Sounds
    connect(this, &MainWindow::playPronunciation, &sound, &Sound::playSoundEffect);
    connect(this, &MainWindow::playBackgroundMusic, &sound, &Sound::playBGM);
    connect(this, &MainWindow::muteSound, &sound, &Sound::muteBGM);
    emit playBackgroundMusic();

    //Fireworks
    connect(ui->fireworksButton, &QPushButton::clicked, this, &MainWindow::displayFireworksPage);
    connect(ui->fireworksButton, &QPushButton::clicked, ui->fireworksWidget, &FireworksWidget::startWorldTimer);
    connect(this, &MainWindow::muteFirework, ui->fireworksWidget, &FireworksWidget::muteFirework);
    ui->fireworksPage->setStyleSheet("border-image: url(:/images/Japancityscape.jpg);background-repeat: no-repeat;");

    //Setup
    auto *layout1= new QVBoxLayout(ui->LevelLayout1);
    layout1->setDirection(QBoxLayout::LeftToRight);
    auto *layout2= new QVBoxLayout(ui->LevelLayout2);
    layout2->setDirection(QBoxLayout::LeftToRight);

    //MuteButton
    muteButton = false;

    //Draw Page setup
    connect(ui->drawButton, &QPushButton::clicked, this, &MainWindow::displayDrawPage);
    drawingSizeX = 453;
    drawingSizeY = 711;
    imageWidth = drawingSizeX;
    imageHeight = drawingSizeY;
    clearBackground();
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearBackground);
    graphic = new GraphicsScene(this);
    updateImage(graphic);
    connect(this, &MainWindow::imageUpdate, this, &MainWindow::updateImage);
    connect(graphic, &GraphicsScene::updateDrawing, this, &MainWindow::updateDrawing);

    //Character Panel setup
    charGraphic = new QGraphicsScene(this);
    charGraphic->addPixmap(QPixmap(":/images/characters/hiragana_a.png"));
    ui->charPanel->setScene(charGraphic);
    connect(ui->kanaDrawingSelector, &QSpinBox::valueChanged, this, &MainWindow::sendKanaSelectorIndex);
    connect(this,&MainWindow::selectorIndexValue,&model,&Model::getKanaImage);
    connect(&model,&Model::sendKanaImage,this,&MainWindow::displayKanaImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::displayHomeImage sets the index of stackedWidget
 * to the index of the home page.
 */
void MainWindow::displayHomeImage(){
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief MainWindow::displayPracticeHome sets the index of stackedWidget
 * to display the Practice home page. Also sets the index of the
 * practiceLevels StackedWidget to the level select screen.
 */
void MainWindow::displayPracticeHome(){
    ui->stackedWidget->setCurrentIndex(2);
    ui->practiceLevels->setCurrentIndex(0);
}

/**
 * @brief MainWindow::displayLearnImage sets the index of stackedWidget
 * to the index of the hiragana and katakana learning page.
 */
void MainWindow::displayLearnImage(){
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::displayWikiPage sets the index of stackedWidget
 * to the index of the Wiki Page.
 */
void MainWindow::displayWikiPage(){
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief MainWindow::displayFireworksPage sets the index of stackedWidget
 * to the index of the fireworks page.
 */
void MainWindow::displayFireworksPage(){
    ui->stackedWidget->setCurrentIndex(4);
}

/**
 * @brief MainWindow::displayDrawPage displays the drawing page for the user.
 */
void MainWindow::displayDrawPage(){
    ui->stackedWidget->setCurrentIndex(5);
}

/**
 * @brief MainWindow::setSoundFile sets which pronunciation is played.
 * @param resourceFile contains a string for the file path of the
 * requested sound.
 */
void MainWindow::setSoundFile(QString resourceFile){
    emit playPronunciation(resourceFile);
}

/**
 * @brief MainWindow::displayPDF takes in a fileName that is stored in the QResources
 * file and displays it using the computer's default pdf viewer. If no default pdf
 * viewer is present on the system, it will attempt to open the file in a web browser.
 * @param fileName - The " ".pdf file name of the pdf that needs to be opened.
 */
void MainWindow::displayPDF(QString fileName){
    QString resourceFile = ":/pdf/pdf/" + fileName; //Path to Resource Item
    QFile f(resourceFile); //Create a QFile from resource item.
    f.copy(QDir::tempPath().append(fileName)); //Copy Resource File to Local Machine's Temp Folder
    QDesktopServices::openUrl(QDir::tempPath().append(fileName)); //Use Local Machine's default .pdf viewer to open file.
}

/**
 * @brief MainWindow::displayLevel changes the index of the practiceLevels StackedWidget to show
 * the level page.
 */
void MainWindow::displayLevel(QVector<Character> levelCharacters, int levelNum ){
    currentLevel=levelNum;
    ui->practiceLevels->setCurrentIndex(1);
    std::vector<int> shuffler;
    if((levelNum+1)%5-(levelNum/6)!=0){

        for(int n=0;n<10;n++){
            shuffler.push_back(n);
        }

        std::random_shuffle(std::begin(shuffler), std::end(shuffler));

        for(int i=0;i<10;i++){
            QString buttonName="";

            switch(levelNum/6) {
            //Hiragana
            case 0:
            {
                auto *button1= new QPushButton(QString::fromStdString(levelCharacters[i].getRomaji()),ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));

                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});

                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getHiragana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
                //Katakana
            case 1:
            {
                auto *button1= new QPushButton(QString::fromStdString(levelCharacters[i].getRomaji()),ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});

                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getKatakana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
                //Hiragana/Katakana
            case 2:
            {
                auto *button1= new QPushButton(buttonName,ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                QIcon icon1(QString::fromStdString(levelCharacters[i].getHiragana()));
                button1->setIcon(icon1);
                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(255,211,255); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getKatakana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
            }
        }
    }else {
        for(int n=0;n<6;n++){
            shuffler.push_back(n);
        }
        std::random_shuffle(std::begin(shuffler), std::end(shuffler));

        for(int i=0;i<6;i++){
            QString buttonName="";

            switch(levelNum/6) {
            //Hiragana
            case 0:
            {
                auto *button1= new QPushButton(QString::fromStdString(levelCharacters[i].getRomaji()),ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,122,133); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});

                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(255,122,133); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(120,99,120);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getHiragana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
                //Katakana
            case 1:
            {
                auto *button1= new QPushButton(QString::fromStdString(levelCharacters[i].getRomaji()),ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,122,133); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(102,255,204);}")));
                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});

                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(255,122,133); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(102,255,204);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getKatakana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
                //Hiragana/Katakana
            case 2:
            {
                auto *button1= new QPushButton(buttonName,ui->LevelLayout1);
                levelButtons1.append(button1);
                button1->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button1->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button1->setMaximumSize(100,100);
                QIcon icon1(QString::fromStdString(levelCharacters[i].getHiragana()));
                button1->setIcon(icon1);
                ui->LevelLayout1->layout()->addWidget(button1);
                int pos1=levelButtons1.size()-1;
                connect(button1,&QPushButton::clicked,this,[this,levelCharacters,i,pos1]{emitSelectionOne(levelCharacters[i].getPosition(),pos1);});
                button1->setStyleSheet((QString("QPushButton {background-color: rgb(255,122,133); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(102,255,204);}")));
                auto *button2= new QPushButton(buttonName,ui->LevelLayout2);
                levelButtons2.append(button2);
                button2->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
                button2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
                button2->setMaximumSize(100,100);
                button2->setStyleSheet((QString("QPushButton {background-color: rgb(25,255,178); border-color: rgb(255, 255, 255); "
                                                "font: 700 12pt \"Segoe UI\"; text-decoration: underline;} "
                                                "QPushButton:pressed {background-color: rgb(102,255,204);}")));
                button2->setEnabled(false);
                QIcon icon2(QString::fromStdString(levelCharacters[shuffler[i]].getKatakana()));
                button2->setIcon(icon2);
                int pos2=levelButtons2.size()-1;
                connect(button2,&QPushButton::clicked,this,[this,levelCharacters,i,shuffler,pos2]{emitSelectionTwo(levelCharacters[shuffler[i]].getPosition(),pos2);});
                ui->LevelLayout2->layout()->addWidget(button2);
                break;
            }
            }
        }
    }
}

/**
 * @brief MainWindow::emitSelectionOne emits a signal with the first button pressed.
 * @param pos position of the first selection.
 * @param buttonNum button number in the array of buttons.
 */
void MainWindow::emitSelectionOne(int pos,int buttonNum){
    for(int i=0;i<levelButtons1.size();i++){
        levelButtons1[i]->setEnabled(false);
        levelButtons2[i]->setEnabled(true);
    }
    selectedButton1Pos=buttonNum;
    emit emitOne(pos);
}

/**
 * @brief MainWindow::emitSelectionTwo emits a signal with second button pressed.
 * @param pos position of the second selection.
 * @param buttonNum button number in the array of buttons.
 */
void MainWindow::emitSelectionTwo(int pos,int buttonNum){
    for(int i=0;i<levelButtons1.size();i++){
        levelButtons1[i]->setEnabled(true);
        levelButtons2[i]->setEnabled(false);
    }
    selectedButton2Pos=buttonNum;
    emit emitTwo(pos);
}

/**
 * @brief MainWindow::receiveMatch makes correctly matched buttons in
 * a level disappear.
 * @param match boolean to show if the buttons were correctly matched.
 */
void MainWindow::receiveMatch(bool match){
    if(match){
        levelButtons1[selectedButton1Pos]->setVisible(false);
        levelButtons2[selectedButton2Pos]->setVisible(false);
        emit sendMatch(true);
    }
    else{
        emit sendMatch(false);
    }
}

/**
 * @brief MainWindow::displayLevelSelect changes the index of the practiceLevels StackedWidget
 * to show the level select page.
 */
void MainWindow::displayLevelSelect(){
    ui->practiceLevels->setCurrentIndex(0);
}

/**
 * @brief MainWindow::resetLevel resets a level back to its original state.
 */
void MainWindow::resetLevel(){
    for(int i=0;i<levelButtons1.size();i++){
        levelButtons1[i]->deleteLater();
        levelButtons2[i]->deleteLater();
    }
    levelButtons2.clear();
    levelButtons1.clear();
}

/**
 * @brief MainWindow::on_muteButton_clicked mutes the background and
 * fireworks sounds.
 */
void MainWindow::on_muteButton_clicked()
{
    if(muteButton == false){
        muteButton = true;
        ui->muteButton->setIcon(QIcon(":/images/mute.png"));
        emit(muteSound(true));
        emit(muteFirework(true));
    }
    else{
        muteButton = false;
        ui->muteButton->setIcon(QIcon(":/images/volume.png"));
        emit(muteSound(false));
        emit(muteFirework(false));
    }
}

/**
 * @brief MainWindow::updateImage updates the drawing image by clearing,
 * then re-adding the Pixmap from the new image.
 * @param graphic Graphic being updated and redrawn.
 */
void MainWindow::updateImage(GraphicsScene *graphic)
{
    graphic->clear();
    graphic->addPixmap(QPixmap::fromImage(image));
    ui->drawingPanel->setScene(graphic);
}

/**
 * @brief MainWindow::updateDrawing updates the image by placing black pixels
 * wherever the mouse was being pressed.
 * @param mouseLoc User's mouse location specific to the drawing panel.
 */
void MainWindow::updateDrawing(QPointF mouseLoc){
    //gets colors from the sliders (should overhaul for QColorPicker)
    QRgb color = qRgba(0,0,0,255);

    //Location user clicks
    double clickX = mouseLoc.x();
    double clickY = mouseLoc.y();

    if(clickX >= imageWidth || clickY >= imageHeight || clickX < 0 || clickY < 0){
        return;
    }

    for(int x = clickX; x <= clickX + 5; x++){
        for(int y = clickY; y <= clickY + 5; y++){
            image.setPixel(x , y, color);
        }
    }

    for(int x = clickX; x >= clickX - 5; x--){
        for(int y = clickY; y >= clickY - 5; y--){
            image.setPixel(x , y, color);
        }
    }

    for(int x = clickX; x <= clickX + 5; x++){
        for(int y = clickY; y >= clickY - 5; y--){
            image.setPixel(x , y, color);
        }
    }

    for(int x = clickX; x >= clickX - 5; x--){
        for(int y = clickY; y <= clickY + 5; y++){
            image.setPixel(x , y, color);
        }
    }

    emit imageUpdate(graphic);

}

/**
 * @brief MainWindow::clearBackground clears the image for the user.
 */
void MainWindow::clearBackground(){
    image = QImage(469, 697, QImage::Format_ARGB32);

    for (int i=0; i < 469; i++)
    {
        for (int l=0; l < 697; l++)
        {
            image.setPixel(i,l, qRgba(255,255,255,255));
        }
    }
    emit imageUpdate(graphic);
}

/**
 * @brief MainWindow::displayKanaImage displays the correct character in
 * the charPanel.
 * @param filePath Source path for the character being shown.
 */
void MainWindow::displayKanaImage(QString filePath){
    charGraphic->clear();
    charGraphic->addPixmap(QPixmap(filePath));
    ui->charPanel->setScene(charGraphic);
}

/**
 * @brief MainWindow::sendKanaSelectorIndex Emits a signal with the correct
 * index for finding the next/previous character.
 */
void MainWindow::sendKanaSelectorIndex(){
    emit selectorIndexValue(ui->kanaDrawingSelector->value());
}

/**
 * @brief MainWindow::updateLevelButton updates the button icons on a given level.
 */
void MainWindow::updateLevelButton(){
    QIcon q(":/images/checkmark.png");
    switch(currentLevel){
    case 0:
        ui->hiraganaLvl1->setIcon(q);
        break;
    case 1:
        ui->hiraganaLvl2->setIcon(q);
        break;
    case 2:
        ui->hiraganaLvl3->setIcon(q);
        break;
    case 3:
        ui->hiraganaLvl4->setIcon(q);
        break;
    case 4:
        ui->hiraganaLvl5->setIcon(q);
        break;
    case 5:
        ui->hiraganaLvl6->setIcon(q);
        break;
    case 6:
        ui->katakanaLvl1->setIcon(q);
        break;
    case 7:
        ui->katakanaLvl2->setIcon(q);
        break;
    case 8:
        ui->katakanaLvl3->setIcon(q);
        break;
    case 9:
        ui->katakanaLvl4->setIcon(q);
        break;
    case 10:
        ui->katakanaLvl5->setIcon(q);
        break;
    case 11:
        ui->katakanaLvl6->setIcon(q);
        break;
    case 12:
        ui->combinedLvl1->setIcon(q);
        break;
    case 13:
        ui->combinedLvl2->setIcon(q);
        break;
    case 14:
        ui->combinedLvl3->setIcon(q);
        break;
    case 15:
        ui->combinedLvl4->setIcon(q);
        break;
    case 16:
        ui->combinedLvl5->setIcon(q);
        break;
    case 17:
        ui->combinedLvl6->setIcon(q);
        break;
    }
}

/**
 * @brief MainWindow::loadCompletion loads the completion information
 * when a user completes a level.
 * @param levelData updates the levelData to show the level was completed.
 */
void MainWindow::loadCompletion(QVector<Level> levelData){
    for(int i=0;i<18;i++){
        if(levelData[i].isCompleted()){
            currentLevel=i;
            updateLevelButton();
        }
    }
}
