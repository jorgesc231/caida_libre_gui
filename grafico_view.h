#ifndef GRAFICO_VIEW_H
#define GRAFICO_VIEW_H


#include <QtCharts>


// Extension de la clase QChartView para menajar el evento si se hace click sobre el grafico
class grafico_view : public QtCharts::QChartView
{
    Q_OBJECT

signals:
    void grafico_click();

public:
    grafico_view();

    void mousePressEvent(QMouseEvent *event);

    void closeEvent(QCloseEvent *event);
};

#endif // GRAFICO_VIEW_H
