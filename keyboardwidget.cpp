#include "keyboardwidget.h"

KeyboardWidget::KeyboardWidget(QWidget *parent = nullptr) : QQuickWidget(parent)
{
}

void KeyboardWidget::mousePressEvent(QMouseEvent *event)
{
    if (QSysInfo::currentCpuArchitecture() == "arm64") {
        //
        // There is a bug in qdeclarative that causes mouse events to be ignored
        // unless there is a grabber. It appeared as a regression in the Qt5.9 LTS
        // release cycle. It only affects embedded devices with touchscreen as it
        // seems, so it's being made conditional to the current architecture.
        //
        // Hopefully, this dirty hack can be removed some day once this bug is
        // resolved:
        //
        //      https://bugreports.qt.io/browse/QTBUG-67018
        //

        QMouseEvent fakePress(QEvent::MouseButtonPress, event->pos(), event->button(), event->buttons(), event->modifiers());
        QMouseEvent fakeRelease(QEvent::MouseButtonRelease, event->pos(), event->button(), event->buttons(), event->modifiers());

        QQuickWidget::mousePressEvent(&fakePress);
        QQuickWidget::mousePressEvent(event);
        QQuickWidget::mousePressEvent(&fakeRelease);
    } else {
        QQuickWidget::mousePressEvent(event);
    }
}
