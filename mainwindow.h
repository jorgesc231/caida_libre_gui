#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//------------------------------------------------
// Definicion de Estructuras y Tipos
//-----------------------------------------------

typedef struct {
    double tiempo;
    double altura;
    double velocidad_final;
    double gravedad;
} variable;

enum stado { INGRESADO, CALCULADO };

enum tipo_dato { TIEMPO, VELOCIDAD, DISTANCIA };

enum unidad {  };

/////////////////////////////////////////////////////////


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double altura(double t, double vf);
    double velocidadFinal(double g, double t);
    double funcionPotencia(double base, double exponente);
    double velocidadFinal2(double g, double h);
    double altura2(double g, double t);
    double tiempoCaida(double g, double h);

    void grafico_1 (int x1, int y1, int forma, QString area, QString titulo);
    void grafico_2(int x1, int y1, int fun, QString var, QString titulo);

    void calcular();

public slots:
    void recalcular();

private slots:

    void on_input_altura_valueChanged(double arg1);
    void on_input_velocidad_valueChanged(double arg1);
    void on_input_tiempo_valueChanged(double arg1);
    void on_input_gravedad_valueChanged(double arg1);

    void on_button_resetear_clicked();

private:
    Ui::MainWindow *ui;

    variable datos = {0, 0, 0, 0}, resultados = {0, 0, 0, 0};
};
#endif // MAINWINDOW_H
