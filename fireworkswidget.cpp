/**
 * @file fireworkswidget.cpp
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */

#include "fireworkswidget.h"
#include <QPainter>
#include <iostream>

/**
 * @brief FireworksWidget::FireworksWidget Instance of the class initializer.
 * @param parent Parent widget that controls fireworkswidget
 */
FireworksWidget::FireworksWidget(QWidget *parent):QWidget(parent),
    timer(this),
    world(b2Vec2(0.0f,9.8f))
{
    connect(&timer, &QTimer::timeout, this, &FireworksWidget::updateWorld);
    connect(this, &FireworksWidget::playFireworkSound, &sound, &Sound::playFireworks);
    muteFireworks = false;
}

/**
 * @brief FireworksWidget::paintEvent creates a painter and draws the
 * Box2D elements to simulate firework particles and create simulated fireworks.
 */
void FireworksWidget::paintEvent(QPaintEvent *){
    // Create a painter.
    QPainter painter(this);

    //Paint the fireworks particles.
    for(int i = 0; i < fireworkBodies.size(); i++){
        //Decrement this particles lifespan.
        fireworkLifespans[i] = fireworkLifespans[i] - 15;
        //Deactivate particle if past it's lifespan.
        if(fireworkLifespans[i] < 0){
            fireworkBodies[i]->SetActive(false);
        }

        //Draw if particle is active.
        if(fireworkBodies[i]->IsActive()){
            b2Vec2 position = fireworkBodies[i]->GetPosition();
            painter.setBrush(fireworkColors[i]);
            painter.setPen(fireworkColors[i]);
            painter.drawEllipse((int)position.x, (int)position.y, 10, 10);
        }
    }
    painter.end();
}

/**
 * @brief FireworksWidget::createFirework creates a number of particles
 * in a radial fashion that simulates a firework. It then applies an
 * impulse to them from the center of the mouse click in order to get
 * the particles flying in different directions. The particle's attributes
 * are assigned in this method as well.
 *
 * @param centerX - The X position value of the mouse click event.
 * @param centerY - The Y position value of the mouse click event.
 */
void FireworksWidget::createFirework(double centerX, double centerY){
    int numRays = 30;
    int blastPower = 5000;
    quint32 angleOffset = QRandomGenerator::global()->bounded(1, 31);
    QColor fireworkColor = getRandomColor();

    b2Vec2 center = b2Vec2(centerX, centerY);
    //creates the circle of firework particles
    for (int i = 0; i < numRays; i++) {
        float angle = ((i / (float)numRays) * 360) + angleOffset;
        angle = qDegreesToRadians(angle); //convert to radians
        b2Vec2 rayDir(sinf(angle), cosf(angle));

        fireworkParticle.type = b2_dynamicBody;
        fireworkParticle.fixedRotation = true;
        fireworkParticle.bullet = true;
        fireworkParticle.position = center;
        fireworkParticle.linearVelocity = blastPower * rayDir;
        b2Body* body = world.CreateBody(&fireworkParticle);

        b2CircleShape circleShape;
        circleShape.m_radius = 0.05; // very small

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 60 / (float)numRays; // very high - shared across all particles
        fd.friction = 0; // friction not necessary
        fd.restitution = 0.99f; // high restitution to reflect off obstacles
        fd.filter.groupIndex = -1; // particles should not collide with each other
        body->CreateFixture(&fd);
        fireworkBodies.append(body);
        //fireworks have a slight randomness to their lasting to simulate reality.
        quint32 fireworkParticleLifespan = QRandomGenerator::global()->bounded(800, 3001);
        fireworkLifespans.append(fireworkParticleLifespan);
        fireworkColors.append(fireworkColor);
    }
}

/**
 * @brief FireworksWidget::updateWorld should call the b2World's step method and
 * Box2D's update method to show the fireworks display.
 */
void FireworksWidget::updateWorld(){
    world.Step(1.0/360.0,6,2);
    update();
}

/**
 * @brief FireworksWidget::mousePressEvent updates the X and Y positions
 * used in order to calculate where fireworks should be generated. Then
 * it calls createFirework and uses those values.
 * @param event - The user's mouse click on the FireworksWidget.
 */
void FireworksWidget::mousePressEvent(QMouseEvent *event){
    int secondBlastDelay = QRandomGenerator::global()->bounded(300, 501);
    int thirdBlastDelay = QRandomGenerator::global()->bounded(500, 801);

    //First Immediate Firework
    //The first fireworks position is the mouse click's location.
    firstBlastX = event->pos().x();
    firstBlastY = event->pos().y();
    createFirework(firstBlastX - 5, firstBlastY - 5);
    emit playFireworkSound("fireworks", muteFireworks);

    //Second Delayed Firework, offset from mouse click's location.
    secondBlastX = firstBlastX + QRandomGenerator::global()->bounded(-100, 101);
    secondBlastY = firstBlastY + QRandomGenerator::global()->bounded(-100, 101);
    QTimer::singleShot(secondBlastDelay, this, [this]{createFirework(secondBlastX, secondBlastY);});

    //Third Delayed Firework, offset from mouse click's location.
    thirdBlastX = firstBlastX - QRandomGenerator::global()->bounded(-100, 101);
    thirdBlastY = firstBlastY - QRandomGenerator::global()->bounded(-100, 101);
    QTimer::singleShot(thirdBlastDelay, this, [this]{createFirework(thirdBlastX, thirdBlastY);});
}

/**
 * @brief FireworksWidget::startWorldTimer starts the world timer for determining
 * update step timings.
 */
void FireworksWidget::startWorldTimer(){
    timer.start(10);
}

/**
 * @brief FireworksWidget::getRandomColor generates a random RGB value
 * to create a QColor.
 * @return - A QColor to use in determining a firework's color.
 */
QColor FireworksWidget::getRandomColor(){
    quint32 r = QRandomGenerator::global()->bounded(50, 256);
    quint32 g = QRandomGenerator::global()->bounded(50, 256);
    quint32 b = QRandomGenerator::global()->bounded(50, 256);
    QColor newColor(r,g,b);
    return newColor;
}

/**
 * @brief FireworksWidget::muteFirework helper method to
 * set the fireworks to either mute or unmute.
 * @param mute bool that determines if fireworks should be muted or not.
 */
void FireworksWidget::muteFirework(bool mute){
    muteFireworks = mute;
}
