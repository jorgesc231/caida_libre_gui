#include <QtCharts>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "grafico_view.h"

#include <math.h>

// Constructor de la interfaz grafica
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input_gravedad->setValue(datos.gravedad);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//--------------------------------------------------------------
// Definicion de las funciones propias
//-------------------------------------------------------------

void MainWindow::calcular()
{
    //if (datos.gravedad) resultados.gravedad = datos.gravedad;
    resultados.gravedad = datos.gravedad;

    // Calcula la altura si el usuario no la ingreso y si se tiene tiempo y velocidad final o gravedad y tiempo
    if (datos.altura == 0 && ((datos.velocidad_final && datos.tiempo >= 0) || (datos.tiempo >= 0 && datos.gravedad >= 0)))
    {
        if (datos.velocidad_final && datos.tiempo) {
            resultados.altura = altura (datos.tiempo, datos.velocidad_final);

        } else {
            resultados.altura = altura2 (datos.gravedad, datos.tiempo);
        }
    } else resultados.altura = datos.altura;

    // Calcula Tiempo de caida si el usuario no la ingreso y si se tiene gravedad y altura
    if (datos.tiempo == 0 && datos.altura > 0 && datos.gravedad > 0) {
        resultados.tiempo = tiempoCaida (datos.gravedad, datos.altura);
    } else resultados.tiempo = datos.tiempo;

    // Calcula la velocidad final dependiento de si el usuario no la ingreso y si se tiene el tiempo de caida y la graveda o la altura y la gravedad
    if (datos.velocidad_final == 0 && ((datos.tiempo > 0 && datos.gravedad >= 0) || (datos.altura && datos.gravedad >= 0)))
    {
        if (datos.tiempo) {
           resultados.velocidad_final = velocidadFinal (datos.gravedad, datos.tiempo);
        } else if (datos.altura) {
           resultados.velocidad_final = velocidadFinal2 (datos.gravedad, datos.altura);
        }
    } else resultados.velocidad_final = datos.velocidad_final;

    // Mostrar los graficos
    if (!ui->verticalLayout->isEmpty())
    {
        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {

            delete child->widget(); // delete the widget
            delete child;   // delete the layout item
        }
    }

    if (resultados.tiempo != 0 && resultados.altura != 0 && resultados.velocidad_final != 0) {
        grafico_1 (resultados.tiempo, resultados.velocidad_final,0, "Altura", "Velocidad final vs Tiempo");

        if (resultados.gravedad != 0) {
            grafico_2 (resultados.altura, resultados.gravedad, 3, "Tiempo Caida", "Tiempo de caida en funcion de la altura");
            grafico_2(resultados.altura, resultados.gravedad, 1, "Velocidad final", "Velocidad en funcion de la altura");
            grafico_2(resultados.tiempo, resultados.gravedad, 3, "Altura", "Altura en funcion del tiempo");
        }
        ui->grupo_graficos_2->hide();
    } else if (resultados.tiempo != 0 && resultados.velocidad_final != 0) {
        if (resultados.gravedad != 0) {
            grafico_1 (resultados.tiempo, resultados.velocidad_final, 0, "Altura", "Velocidad final vs Tiempo");
            grafico_2(resultados.altura, resultados.gravedad, 3, "Tiempo Caida", "Tiempo de caida en funcion de la altura");
            grafico_2(resultados.altura, resultados.gravedad, 1, "Velocidad final", "Velocidad en funcion de la altura");
        }
        ui->grupo_graficos_2->hide();
    } else if ( resultados.altura != 0 && resultados.velocidad_final != 0)
    {
        if (resultados.gravedad != 0) {
            grafico_2(resultados.tiempo, resultados.gravedad, 3, "Altura", "Altura en funcion del tiempo");  // Por alguna razon no funciona
            grafico_2(resultados.altura, resultados.gravedad, 1, "Velocidad final","Velocidad en funcion del tiempo");  // Por alguna razon tampoco funciona
            ui->grupo_graficos_2->hide();
        }
    }

    // Muestra los resultados en las etiquetas y los inputs que no fueron editados
    QString resultado_altura, resultado_velocidad, resultado_tiempo, resultado_gravedad;

    QTextStream (&resultado_altura) << resultados.altura;
    ui->resultado_altura->setText(resultado_altura);
    if (datos.altura) ui->input_altura->setValue(resultados.altura);

    QTextStream (&resultado_velocidad) << resultados.velocidad_final;
    ui->resultado_velocidad->setText(resultado_velocidad);
    if (datos.velocidad_final) ui->input_velocidad->setValue(resultados.velocidad_final);

    QTextStream (&resultado_tiempo) << resultados.tiempo;
    ui->resultado_tiempo->setText(resultado_tiempo);
    if (datos.tiempo) ui->input_tiempo->setValue(resultados.tiempo);

    QTextStream (&resultado_gravedad) << resultados.gravedad;
    ui->resultado_gravedad->setText(resultado_gravedad);
    if (datos.gravedad) ui->input_gravedad->setValue(resultados.gravedad);
}


//----------------------------------------------------------------------------------
// Definicion de funciones que implentan las formulas de caida libre
//----------------------------------------------------------------------------------

double MainWindow::altura(double t, double vf) {
    double h;

    h = vf / 2 * t;

    return h;
}

double MainWindow::velocidadFinal(double g, double t) {
        double vf;
        vf = g * t;
        return vf;
}

double MainWindow::funcionPotencia(double base, double exponente) {
    double resultado = 0;

    if (exponente == 0 || exponente <= 0) resultado = 1;
    else resultado = base * funcionPotencia(base, exponente - 1);

    return resultado;
}

double MainWindow::velocidadFinal2(double g, double h) {
    double resultado;

    resultado= sqrt(fabs(2*g*h));
    return resultado;
}

double MainWindow::altura2(double g, double t) {
    double resultado;
    resultado= (g*funcionPotencia(t,2))/2;

    return resultado;
}

double MainWindow::tiempoCaida(double g , double h) {

    double base, resultado;
    base = (2 * h) / g;
    resultado = sqrt(fabs(base));

    return resultado;
}


//----------------------------------------------------------------------------------
// Definicion de funciones de graficos
//----------------------------------------------------------------------------------

void MainWindow::grafico_1 (int x1, int y1, int forma, QString area , QString titulo) // forma = 0 para grafico triangulares y forma = y1 para graficos cuadrilateros
{
       QLineSeries *linea = new QLineSeries();

       linea->append(0,forma);
       linea->append(x1,y1);

       QLineSeries *linea2 = new QLineSeries();

       linea2->append(0,0);
       linea2->append(x1,0);

       QAreaSeries *Area = new QAreaSeries(linea,linea2);
       Area->setName(area);

       grafico_view *ventanalinea = new grafico_view();
       ventanalinea->setRenderHint(QPainter::Antialiasing);
       ventanalinea->setCursor(Qt::PointingHandCursor);

       ventanalinea->chart()->addSeries(Area);
       ventanalinea->chart()->createDefaultAxes();
       ventanalinea->chart()->axes(Qt::Vertical).first()->setRange(0,y1+5);
       ventanalinea->chart()->axes(Qt::Horizontal).first()->setRange(0,x1+5);
       ventanalinea->chart()->setTitle(titulo);

       QObject::connect(ventanalinea, SIGNAL(grafico_click()),
                        this, SLOT(recalcular()));

       ui->verticalLayout->addWidget(ventanalinea);
//       ui->horizontalLayout->addWidget(ventanalinea);
}

void MainWindow::grafico_2(int x1 , int y1, int fun, QString var, QString titulo){

    QLineSeries *exp = new QLineSeries();

    if(fun==0){
        for (int i=1 ; i<x1+1 ; i++){
        exp->append(i,altura2(y1,i));
    }
    } else if (fun==1){
        for (int i=1 ; i<x1+1 ; i++){
        exp->append(i,velocidadFinal2(y1,i));
        }
    } else{
        for (int i=1 ; i<x1+1 ; i++){
        exp->append(i,tiempoCaida(y1,i));
     }
    }

    exp->setName(var);

    grafico_view *chartView = new grafico_view();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setCursor(Qt::PointingHandCursor);

    chartView->chart()->addSeries(exp);
    chartView->chart()->createDefaultAxes();
    chartView->chart()->setTitle(titulo);

    // Agrega el grafico al layout

    QObject::connect(chartView, SIGNAL(grafico_click()),
                     this, SLOT(recalcular()));

    ui->verticalLayout->addWidget(chartView);
    //ui->horizontalLayout->addWidget(chartView);
}

//------------------------------------------------------------------------------------
// Definiciones de las funciones de los slots
//------------------------------------------------------------------------------------

void MainWindow::on_input_altura_valueChanged(double arg1)
{
    datos.altura = arg1;
    calcular();
}

void MainWindow::on_input_velocidad_valueChanged(double arg1)
{
    datos.velocidad_final = arg1;
    calcular();
}

void MainWindow::on_input_tiempo_valueChanged(double arg1)
{
    datos.tiempo = arg1;
    calcular();
}

void MainWindow::on_input_gravedad_valueChanged(double arg1)
{
    datos.gravedad = arg1;
    calcular();
}

void MainWindow::recalcular()
{
    calcular();
}

void MainWindow::on_button_resetear_clicked()
{
    datos.altura = 0;
    datos.velocidad_final = 0;
    datos.tiempo = 0;
    datos.gravedad = 0;

    resultados.altura = 0;
    resultados.velocidad_final = 0;
    resultados.tiempo = 0;
    resultados.gravedad = 0;

    ui->input_altura->setValue(0);
    ui->input_velocidad->setValue(0);
    ui->input_tiempo->setValue(0);
    ui->input_gravedad->setValue(0);

    ui->grupo_graficos_2->show();

    calcular();
}

