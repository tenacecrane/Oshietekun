#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDesktopServices>
#include <QFile>
#include "qpushbutton.h"
#include "sound.h"
#include <QSoundEffect>
#include "character.h"
#include "model.h"
#include "graphicsscene.h"
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model &model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setSoundFile(QString);
    Sound sound;
    void emitSelectionOne(int,int);
    void emitSelectionTwo(int,int);
    QVector<QPushButton*> levelButtons1;
    QVector<QPushButton*> levelButtons2;
    int selectedButton1Pos;
    int selectedButton2Pos;
    void resetLevel();
    bool muteButton = false;
    int drawingSizeX;
    int drawingSizeY;
    int imageWidth;
    int imageHeight;
    GraphicsScene *graphic;
    QGraphicsScene *charGraphic;
    QImage image;
    int currentLevel;

signals:
    void playPronunciation(QString);
    void playBackgroundMusic();
    void muteSound(bool);
    void muteFirework(bool);
    void emitOne(int);
    void emitTwo(int);
    void imageUpdate(GraphicsScene * graphic);
    void selectorIndexValue(int);
    void sendMatch(bool);

private slots:
    void displayHomeImage();
    void displayLearnImage();
    void displayPracticeHome();
    void displayWikiPage();
    void displayFireworksPage();
    void displayPDF(QString);
    void displayLevel(QVector<Character>,int);
    void displayLevelSelect();
    void receiveMatch(bool);
    void on_muteButton_clicked();
    void displayDrawPage();
    void updateDrawing(QPointF mouseLoc);
    void updateImage(GraphicsScene * graphic);
    void clearBackground();
    void displayKanaImage(QString filePath);
    void sendKanaSelectorIndex();
    void updateLevelButton();
    void loadCompletion(QVector<Level>);
};
#endif // MAINWINDOW_H
