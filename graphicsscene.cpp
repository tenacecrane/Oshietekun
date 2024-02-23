/**
 * @file graphicsscene.cpp
 * @author Tyson Fox
 * @brief A8:
 * GraphicsScene custom class to override the QGraphicsScene
 * class. Used to set the QImage in MainWindow to a set size,
 * as well as override the mouse press, move, and release events.
 * @version 1.0
 * @date 2022-03-30
 * @copyright Copyright (c) 2022
 */
#include "graphicsscene.h"
#include <QDebug>

// Constructor for GraphicsScene, inherits from QGraphicsScene.
// Sets the size of the graphicsScene to be 500 x 500 to prevent
// any issues with the user resizing the window.
GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

// Emits a signal with the mouse position to draw a pixel where the
// mouse was clicked.
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //qDebug() << event->scenePos();
    emit updateDrawing(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}

// Emits a signal to draw pixel wherever the mouse moves when the left
// mouse button is pressed.
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit updateDrawing(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}



