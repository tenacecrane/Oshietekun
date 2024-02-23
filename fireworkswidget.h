/**
 * @file fireworkswidget.h
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */

#ifndef FIREWORKSWIDGET_H
#define FIREWORKSWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <math.h>
#include <QMouseEvent>
#include <QRandomGenerator>
#include "sound.h"

class FireworksWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FireworksWidget(QWidget *parent = nullptr);

public slots:
    void updateWorld();
    void paintEvent(QPaintEvent *) override;
    void startWorldTimer();
    void muteFirework(bool);

protected:
    void mousePressEvent(QMouseEvent * event) override;

signals:
    void updateMouse(QPointF);
    void playFireworkSound(QString, bool);

private:
    void createFirework(double, double);
    QColor getRandomColor();
    Sound sound;
    //X and Y positions for determining firework positions.
    double firstBlastX;
    double firstBlastY;
    double secondBlastX;
    double secondBlastY;
    double thirdBlastX;
    double thirdBlastY;
    bool muteFireworks;

    QTimer timer;
    QVector<b2Body *> fireworkBodies;
    QVector<int> fireworkLifespans;
    QVector<QColor> fireworkColors;
    b2World world;
    b2BodyDef fireworkParticle;
};

#endif // FIREWORKSWIDGET_H
