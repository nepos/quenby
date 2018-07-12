#pragma once

#include <QQuickWidget>

class KeyboardWidget : public QQuickWidget
{
public:
    KeyboardWidget(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *event);
};
