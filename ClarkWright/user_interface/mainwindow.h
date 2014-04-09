#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/qmath.h>
#include "io_file.h"
#include "classes/graph_routes.h"
#include "classes/saving.h"
#include "timer.h"
#include "closer_cw.h"
#include <QWheelEvent>
#include <QFileDialog>
#include <QStackedLayout>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QGroupBox>
#include <QTranslator>
#include <QRadioButton>
#include <QProgressBar>
#include <QMenuBar>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QSettings>
#include <QTime>
#include "voronoi.h"

namespace Ui {
class MainWindow;
}

typedef QList<QPoint> G_arrows_points_path;
typedef QPair <QPoint,QString> G_node_and_label;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString APPNAME;
    QString APP_VERSION;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void G_draw_routes( QList< QList<QPoint> > routes );
    void G_draw_nodes( QList< QPair<QPoint,QString> > pointsList );
    int G_draw_interface(QApplication *a);
    void G_move_graph_in_a_good_position( void );
    void G_show_result(QString str);

private:
    Ui::MainWindow *ui;     // l'interfaccia con tutti i suoi oggetti
    int pixelMultip;        // maggiore sara' questo numero, piu grande sara' la visualizzazione
    bool firstAperture;     // appena viene aperto il programma passa da true a false, dopo la fase di inizializzazione
    bool gridEnabled;       // memorizza se e' già attiva la griglia
    QVector<Client> nodes_list; //la lista dei nodi cliente

    // vari oggetti della scena
    QGraphicsScene *scene;
    QGraphicsEllipseItem *node;
    QGraphicsRectItem *rectangle;
    QGraphicsLineItem *line;
    QGraphicsTextItem *text1;
    QGraphicsTextItem *text2;
    QGraphicsPolygonItem* poligon;
    QList<QGraphicsLineItem*> *gridLines;

    // funzioni per disegnare la scena
    void addNode(QPoint p, QString name);
    void addArrowTo(QPoint p1, QPoint p2, QColor arrowColor);

private slots: // le varie funzioni che vengono chiamate quando si interagisce con l'interfaccia
    void handle_button1();
    void zoomGraph( int i );
    void grid(bool on);
    void open_file();
    void reset(void);
    void handle_button2();
    void zoomInGraphButton();
    void zoomOutGraphButton();
    void draw_route( QList<QPoint> route );

};

#endif // MAINWINDOW_H
