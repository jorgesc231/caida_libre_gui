#include "grafico_view.h"

grafico_view::grafico_view()
{
    ;
}


void grafico_view::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Handle left mouse button here
        QString titulo_ventana;

        QTextStream (&titulo_ventana) << "Grafico: " << this->chart()->title();

        // QChartView *grafico = new QChartView(chart());
        grafico_view *grafico = new grafico_view();

        grafico->setChart(chart());

        grafico->setWindowTitle(titulo_ventana);
        grafico->setMinimumWidth(800);
        grafico->setMinimumHeight(600);

        grafico->show();

        emit grafico_click();

        // if(grafico->isWindow())
    } else {
        // pass on other buttons to base class
        QChartView::mousePressEvent(event);
    }
}

void grafico_view::closeEvent(QCloseEvent *event)
{
    // printf("Prueba\n");

    QChartView::closeEvent(event);
}

