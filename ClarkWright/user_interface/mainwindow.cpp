#include "mainwindow.h"
#include "user_interface.h"


/**
 * @brief MainWindow
 *  Crea e inizializza l'interfaccia e i suoi parametri iniziali.
 *
 * @param parent    widget su cui costruire la finestra
 *
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    APPNAME = "Graph Visualizator" ;
    APP_VERSION = "1.0a";

    // set the scene
    ui->setupUi(parent);
    firstAperture = true;
    reset();

    // inizialization
    pixelMultip = 3;
    firstAperture = false;
    grid( ui->check1->isChecked() );
    zoomGraph( ui->zoomSlider->value() );

    // connect Graph's button
    QObject::connect( ui->button1, SIGNAL(released()), this, SLOT(handleButton()) );
    QObject::connect( ui->button2, SIGNAL(released()), this, SLOT(compute()) );
    QObject::connect( ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomGraph(int)) );
    QObject::connect( ui->check1, SIGNAL(clicked(bool)), this, SLOT(grid(bool)) );
}

/**
 * @brief MainWindow
 *  distrugge l'interfaccia grafica
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief zoomGraph
 *  cambia lo zoom nel visualizzatore
 * @param i è un numero intero che sarà più grande maggiore sarà lo zoom, 11 = 110% (zoom)
 */
void MainWindow::zoomGraph(int i)
{
    ui->userInfo->setText( QString::number(i) );
    QMatrix matrix;
    matrix.scale( i/10., i/10.); // zoom factor ( example: 1.1 is 110%)

    ui->graphicsView->setMatrix(matrix);
}

/**
 * @brief addNode
 *  Aggiunge nel visualizzatore un punto che indica un nodo, descrivendolo con una label (posizionata sul fianco)
 * @param p le coordinate del punto/nodo
 * @param nome la label
 */
void MainWindow::addNode(QPoint p, QString name)
{
    // set how many pixel have a graph point
    p.setX( p.x() * pixelMultip );
    p.setY( p.y() * pixelMultip );

    QBrush internalBrush(Qt::green);
    QPen outlinePen(Qt::transparent);
    outlinePen.setWidth(1);
    int diam = 2;

    // addEllipse(x,y,w,h,pen,brush)
    node = scene->addEllipse(p.x()-(diam/2),p.y()-(diam/2), diam,diam, outlinePen, internalBrush);
    text = scene->addText( name, QFont("Helvetica", 8) );
    text->setPos(p.x()-3,p.y()-4);

}

/**
 * @brief addArrowTo
 *  Aggiunge una freccia che parte in un punto p1 e arriva in un punto p2 (con punta in p2)
 * @param p1,p2 sono le coordinate di partenza e arrivo della freccia
 */
void MainWindow::addArrowTo(QPoint p1, QPoint p2)
{

    // set how many pixel have a graph point
    p1.setX( p1.x() * pixelMultip );
    p1.setY( p1.y() * pixelMultip );
    p2.setX( p2.x() * pixelMultip );
    p2.setY( p2.y() * pixelMultip );

    QColor arrowColor = QColor(200,200,200);
    arrowColor.setAlpha( 50 + 100*(qrand()/RAND_MAX) );
    QBrush internalBrush( arrowColor );
    QPen outlinePen( arrowColor );
    outlinePen.setWidth(1);
    line = scene->addLine(p1.x(),p1.y(), p2.x(),p2.y(), outlinePen);

    int offs=4; // arrow head dimension
    if (p1.y() < p2.y() ) offs=-offs;

    // arrow head
    QPolygonF triangle;
    triangle.append( QPointF(p2.x()-offs , p2.y()+offs) );
    triangle.append( QPointF(p2.x()      , p2.y())      );
    triangle.append( QPointF(p2.x()+offs , p2.y()+offs) );
    poligon = scene->addPolygon(triangle);
    poligon->setTransformOriginPoint(QPointF(p2.x()   , p2.y()) );
    poligon->setBrush(internalBrush);
    poligon->setPen(outlinePen);

    // rotate arrow head
    qreal m = -1; // vertical line
    if ( ( p2.x() - p1.x() + 0. ) != 0 )
        m = ( p2.y() - p1.y() + 0. ) /
            ( p2.x() - p1.x() + 0. );

    if ( m<0 && ( p1.x()==p2.x() ) ) {          // if vertical line
        poligon->setRotation( 0 );
    } else if ( m==0 ) {                        // if horizontal line
        if ( p1.x() <= p2.x() ) {
            poligon->setRotation( 90 );         // DX arrow
        } else{
            poligon->setRotation( -90 );        // SX arrow
        }
    } else if (m > 0) {                         // DECR arrow
        qreal degree = ( atan(m) * 180. )/M_PI;
        poligon->setRotation( degree - 90 );
    } else if (m < 0) {                         // CRESC arrow
        qreal degree = ( atan(m) * 180. )/M_PI;
        poligon->setRotation( degree + 90 );
    }

}

/**
 * @brief handleButton
 *  handle of button1
 */
void MainWindow::handleButton()
{
    //    QList< QPair<QPoint,QString> > pointList;
    //    createGraph(pointList);

        ui->userInfo->setText("Voronoi..");
    //    //Prova GraphRoute
    //    QVector<Client> clients;
    //    Client d( 0, 20, 20, 0);
    //    Client c1(1, 30, 30, 13);
    //    Client c2(2, 10, 30, 20);
    //    Client c3(3, 0, 10, 25);
    //    Client c4(4, 20, 0, 5);
    //    Client c5(5, 30, 10, 40);
    //    clients.push_back(d);
    //    clients.push_back(c1);
    //    clients.push_back(c2);
    //    clients.push_back(c3);
    //    clients.push_back(c4);
    //    clients.push_back(c5);

    //    qDebug( "Size %d",clients.size() );
    //    GraphRoutes state(clients); //inizializzo lo stato dell'algoritmo
    //    G_draw_routes( state.get_list_edges() );
    //    G_draw_nodes( state.get_list_point_label_pairs() );



    //    Timer timer("C&W Algorithm");
    //    timer.start();

        int cap;
        QVector<Client> clients;
        clients = read_file("../../../vrpnc1.txt", &cap); // lelle
    //        clients = read_file("vrpnc1.txt", &cap); // Ale

        /*clients.push_back(Client(0,2,3,1));
        clients.push_back(Client(1,5,1,1));
        clients.push_back(Client(2,6,7,1));
        clients.push_back(Client(3,6,4,1));
        clients.push_back(Client(4,9,3,1));
        clients.push_back(Client(5,10,6,1));
        clients.push_back(Client(6,12,8,1));*/

        QVector<Client> voronoi_points;
        voronoi_points = voronoi( clients );

        GraphRoutes state(voronoi_points);
        G_draw_nodes( state.get_list_point_label_pairs() );

    //    timer.stop_and_print();
}

/**
 * @brief grid
 *  Draw the grid
 * @param on true se deve essere attivata la visualizzazione della grigia, false altrimenti
 */
void MainWindow::grid( bool on )
{

    // only one grid ...
    if( gridEnabled && on ) return;

    QColor color = QColor(200,200,200);
    color.setAlpha(50);
    QPen outlinePen( color );
    outlinePen.setWidth(1);

//    qDebug("%f",ui->graphicsView->sceneRect().width());
//    qDebug("%f",ui->graphicsView->sceneRect().height());

    if ( on ) {
        gridLines->clear();
        for( int i=0; i< ui->graphicsView->sceneRect().width(); i+=(10*pixelMultip) ) { // vertical lines
            gridLines->append( scene->addLine(i,0, i,ui->graphicsView->sceneRect().height(), outlinePen) );
        }
        for( int i=0; i< ui->graphicsView->sceneRect().height(); i+=(10*pixelMultip) ) { // horizontal lines
            gridLines->append( scene->addLine(0,i, ui->graphicsView->sceneRect().height(),i, outlinePen) );
        }
        gridEnabled = true;
    } else {
        QListIterator<QGraphicsLineItem*> gridIterator(*gridLines);
        while ( gridIterator.hasNext() ) {
            scene->removeItem( gridIterator.next() );
        }
        gridEnabled = false;
    }
}

/**
 * @brief open_file
 *  apertura di un file
 * @param nome descrizione
 * @return valoreRestituito descizione
 */
void MainWindow::open_file()
{


    QString filename = QFileDialog::getOpenFileName( NULL, "Apri il file con nodi e quantita'", "./" , "RO points (*.*)");
//    QString filename = "../../../vrpnc1.txt";     //LELLE

    if (!filename.isNull())
    {

        //TODO da sistemare........cap non deve essere fisso
        int cap = 99;
        nodes_list = read_file(filename, &cap);

        //TODO aggiungere controllo del file

        QList< QPair<QPoint,QString> > client;
        for(int i=0; i<nodes_list.size(); i++){
            client.append( QPair<QPoint,QString>(
                               QPoint ( nodes_list[i].get_x(), nodes_list[i].get_y() ) ,
                               QString::number( nodes_list[i].get_demand() ) ) );
        }

        G_draw_nodes(client);

    }else{
        qDebug("The file is NULL.");
    }


}

/**
 * @brief reset
 *  cancella la scenae e tutte le strutture dati che vengono utilizzate
 */
void MainWindow::reset(void)
{
//    if(!firstAperture) scene->clear();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment( Qt::AlignLeft | Qt::AlignTop );
//    ui->graphicsView->setAlignment( Qt::AlignCenter );
    ui->graphicsView->setSceneRect( 0,0, 999, 999 );

    gridEnabled = false;
    gridLines = new QList<QGraphicsLineItem*>;

    if(!firstAperture) {
        grid( ui->check1->isChecked() );
        zoomGraph( ui->zoomSlider->value() );
//        gridLines->clear();
    }


}

/**
 * @brief aaaa
 *  descrizione
 * @param nome descrizione
 * @return valoreRestituito descizione
 */
void MainWindow::compute()
{
    qDebug("Compute()");

    ui->userInfo->setText("Questa è una prova di visualizzazione.");
    //Prova GraphRoute
    QVector<Client> clients;
    Client d( 0, 20, 20, 0);
    Client c1(1, 30, 30, 13);
    Client c2(2, 10, 30, 20);
    Client c3(3, 0, 10, 25);
    Client c4(4, 20, 0, 5);
    Client c5(5, 30, 10, 40);
    clients.push_back(d);
    clients.push_back(c1);
    clients.push_back(c2);
    clients.push_back(c3);
    clients.push_back(c4);
    clients.push_back(c5);

    qDebug( "Size %d",clients.size() );
    GraphRoutes state(clients); //inizializzo lo stato dell'algoritmo
    G_draw_routes( state.get_list_edges() );
    G_draw_nodes( state.get_list_point_label_pairs() );
}

/**
 * @brief zoomOutGraphButton
 *  Diminuisce lo zoom nel visualizzatore
 */
void MainWindow::zoomOutGraphButton()
{
    qDebug("zoom-");
    ui->zoomSlider->setValue( ui->zoomSlider->value() - 1 );
    zoomGraph( ui->zoomSlider->value() );
}

/**
 * @brief zoomInGraphButton
 *  Aumenta lo zoom nel visualizzatore
 */
void MainWindow::zoomInGraphButton()
{
    qDebug("zoom+");
    ui->zoomSlider->setValue( ui->zoomSlider->value() + 1 );
    zoomGraph( ui->zoomSlider->value() );
}

/**
 * @brief design_route
 *  Disegna le frecce tra i nodi passati in ingresso, ovvero tra il primo e il
 *      secondo nodo della lista vi sarà una freccia
 *      con punta nel secondo nodo, e così via ...
 * @param route la lista dei delle posizioni dei punti/nodi
 */
void MainWindow::draw_route( QList<QPoint> route )
{
    if (route.size()<2) return;

    for ( int i=1; i<route.size(); i++ ) {
        addArrowTo( route[i-1] , route[i] );
    }
}

/**
 * @brief design_routes
 *  Disegna una lista di route
 * @param routes la lista di routes
 */
void MainWindow::G_draw_routes( QList< QList<QPoint> > routes )
{
    if (routes.size()==0) return;

    for( int i=0; i<routes.size(); i++ ){
        draw_route( routes[i] );
    }
}

/**
 * @brief design_nodes
 *  Disegna una lista di nodi con relativo label
 * @param pointsList la lista formata da coppie (posizione,label)
 */
void MainWindow::G_draw_nodes( QList< QPair<QPoint,QString> > pointsList )
{

    QPair<QPoint,QString> *p ;

    for ( int i = 0; i < pointsList.size(); i++ ) {
        ui->progressBarGraph->setValue( ( i * 100 ) / pointsList.size() );
        p = &( pointsList[i] );

        addNode( p->first ,  p->second );
    }
    ui->progressBarGraph->setValue(100);

}



int MainWindow::G_draw_interface( QApplication* a ) {

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QWidget container;
//    container.resize(800, 600);
    container.setFocusPolicy ( Qt::NoFocus );

    MainWindow window(&container);
//    window.setGeometry(0,22,640, 680);


    QMenuBar open_menu_bar(&container);
    QMenu open_menu("&File", &container);

    QAction open("&Open", &container);
    open.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    open_menu.addAction(&open);

    QAction reset("&Reset", &container);
    reset.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    open_menu.addAction(&reset);


    /**** MENU COMPUTATION ****/
    QMenu computation("Computation", &container);

    QAction calc("&Computation", &container);
    calc.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    computation.addAction(&calc);

    QAction zoomIn("&Zoom +", &container);
    zoomIn.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    computation.addAction(&zoomIn);

    QAction zoomOut("&Zoom -", &container);
    zoomOut.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    computation.addAction(&zoomOut);



    /**** MENU HELP ****/
    QMenu help_menu("&?", &container);

    QAction help("&Help", &container);
    help.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    help_menu.addAction(&help);

    QAction about("&About", &container);
    about.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    help_menu.addAction(&about);

    open_menu_bar.addMenu(&open_menu);
    open_menu_bar.addMenu(&computation);
    open_menu_bar.addMenu(&help_menu);


    container.show();
    container.showMaximized();


    QDialog instructions( NULL );
    instructions.setFixedSize(300,180);
    instructions.setWindowTitle("Help");
    QLabel instr_text("\nCtrl+ - Zoom+ \nCtrl- - Zoom- \n", &instructions);
    instr_text.setTextFormat(Qt::AutoText);
    instr_text.setWordWrap(true);
    instructions.hide();

    QDialog credits( NULL );
    credits.setFixedSize(300,100);
    credits.setWindowTitle("Credits");
    QString txt;
    txt.append( "\t" );
    txt.append( window.APPNAME );
    txt.append( " " );
    txt.append( window.APP_VERSION );
    txt.append( "\n\nA cura di BluBluSky.\n" );
    QLabel cred_text(txt, &credits);

    cred_text.setTextFormat(Qt::AutoText);
    cred_text.setAlignment(Qt::AlignCenter);
    cred_text.setWordWrap(true);
    credits.hide();



    // Connect button signal to appropriate slot
    QObject::connect( &open, SIGNAL(triggered()), &window, SLOT(open_file()) );
    QObject::connect( &reset, SIGNAL(triggered()), &window, SLOT(reset()) );
    QObject::connect( &help, SIGNAL(triggered()), &instructions, SLOT(show()) );
    QObject::connect( &about, SIGNAL(triggered()), &credits, SLOT(show()) );
    QObject::connect( &calc, SIGNAL(triggered()), &window, SLOT(compute()) );
    QObject::connect( &zoomIn, SIGNAL(triggered()), &window, SLOT(zoomInGraphButton()) );
    QObject::connect( &zoomOut, SIGNAL(triggered()), &window, SLOT(zoomOutGraphButton()) );


    window.setWindowTitle( window.APPNAME );
    window.setFocus();

//    QList< QPair<QPoint,QString> > pointList;
//    window.createGraph( pointList );

    return a->exec();

}

