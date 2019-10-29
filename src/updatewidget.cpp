#include "updatewidget.h"
#include <QPainter>

#include <QDebug>

UpdateWidget::UpdateWidget(QWidget *parent) : QWidget(parent)
{
}

void UpdateWidget::paintEvent(QPaintEvent*)
{
    if (m_drawlist == nullptr)
        return;

    QPainter painter(this);

    painter.setPen("blue");

    for(int i=0; i<m_drawlist->count(); i++)
        for(int j=0; j<(*m_drawlist)[i].count()-1; j++)
            painter.drawLine((*m_drawlist)[i][j], (*m_drawlist)[i][j+1]);
}

void UpdateWidget::draw(QList<QList<QPoint>>* drawlist)
{
    if (drawlist != nullptr)
    {
        this->m_drawlist = drawlist;
        update();
    }
}

void UpdateWidget::setDrawRecordToNull()
{
    this->m_drawlist = nullptr;
}
