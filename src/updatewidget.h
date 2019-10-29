#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QList>

class UpdateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateWidget(QWidget *parent = nullptr);
    void draw(QList<QList<QPoint>>* drawlist);
    void setDrawRecordToNull();

protected:
    void paintEvent(QPaintEvent*);

private:
    QList<QList<QPoint>>* m_drawlist;
};

#endif // UPDATEWIDGET_H
