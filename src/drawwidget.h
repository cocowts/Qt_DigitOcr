#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>
#include <QMouseEvent>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void clear();
    QList<QList<QPoint>>* getDraw();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void paintEvent(QPaintEvent*);

private:
    QList<QPoint> m_points;
    QList<QList<QPoint>> m_drawlist;
};

#endif // DRAWWIDGET_H
