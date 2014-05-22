/*
 *  Copyright (C) 2014 Simone Barbieri, Andrea Loddo, Emanuele Mameli, Alessandro Muntoni, Livio Pompianu
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

#define MAX_X_GRAPHVIEW 600
#define MAX_Y_GRAPHVIEW 600
#define MAX_XY_LIKE_INFTY 9999
#define N_ALL_BUTTONS 6

QT_BEGIN_NAMESPACE

class Ui_Window
{


public:

    // Menu file
//    QAction save_button;

    // Area SX - Tools
    QWidget *window;
    QWidget *zoomWidget;
    QHBoxLayout *zoomLayoutBox;
    QSlider *zoomSlider;
    QList<QPushButton*> button;
    QGroupBox *groupBox;
    QCheckBox *check1;
    QCheckBox *check2;
    QCheckBox *check3;
    QVBoxLayout *vbox;
    QVBoxLayout *rightToolsLayout;
    QWidget *rightTools;
    QTextEdit *userInfo;
    QLabel *zoomLabel;
    QLabel *fileLoaded;

    // Graph Area
    QGraphicsView *graphicsView;
    QProgressBar *progressBarGraph;
    QVBoxLayout *graphLayout;
    QWidget *graphWidget;
    QHBoxLayout *horizontalLayout;

    QList<QString> alg_button_names;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QStringLiteral("Widget"));
        widget->resize(1024, 768);


        // Area SX - Tools
        zoomLabel = new QLabel;
        zoomSlider = new QSlider(Qt::Horizontal);
        zoomSlider->setRange(5,80);
        zoomSlider->setValue( 25 );
        zoomLabel->setText( QString::number( zoomSlider->value() ) + "x" );
        zoomLabel->setFont( QFont("Helvetica", 12) );
        zoomLayoutBox = new QHBoxLayout;
        zoomLayoutBox->addWidget(zoomSlider);
        zoomLayoutBox->addWidget(zoomLabel);
        zoomWidget = new QWidget;
        zoomWidget->setLayout(zoomLayoutBox);

        // Buttons:
        //    C&W standard; (quello sviluppato da Livio&Andre)
        //    C&W Voronoi Savings; (closerv1)
        //    C&W Voronoi Savings runtime; (closer v2)
        //    C&W Voronoi Distances & Savings runtime (closer v3)
        //    Best (un bottone che li lancia tutti (tranne il primo) e da in output la soluzione migliore)

        alg_button_names << "C and W standard"
             << "C and W Voronoi Savings"
             << "C and W Voronoi Savings runtime"
             << "C and W Voronoi Distances and Savings runtime f"
             << "C and W Voronoi Distances and Savings runtime n"
             << "Best (prendi il migliore)";

        for ( int i=0; i<alg_button_names.size() || i<N_ALL_BUTTONS ; i++ ) {
            button.push_back( new QPushButton( alg_button_names.value(i) ) );
            button.last()->setDefault( false );
            button.last()->setAutoDefault( false ) ;
            button.last()->setStyleSheet("Text-align:left");
        }


        // setting area
        groupBox = new QGroupBox(QGroupBox::tr("Settings"));
        check1 = new QCheckBox(QCheckBox::tr("&Grid"));
        check1->setChecked(true);


        fileLoaded = new QLabel;
        fileLoaded->setText( "File caricato: -nessuno-" );
        fileLoaded->setFont( QFont("Helvetica", 11) );
        vbox = new QVBoxLayout;
        vbox->addWidget(check1);
        vbox->addWidget(zoomWidget);
        vbox->addWidget(fileLoaded);

        vbox->addStretch(1);
        groupBox->setLayout(vbox);

        // user info
        userInfo = new QTextEdit;
        userInfo->setReadOnly(true);
        userInfo->setText("Info");
        rightToolsLayout = new QVBoxLayout;
        for ( int i=0; i<button.size(); i++ ) {
            rightToolsLayout->addWidget( (button[i]) );
        }
        rightToolsLayout->addWidget(groupBox);
        rightToolsLayout->addWidget(userInfo);
        rightTools = new QWidget;
        rightTools->setLayout(rightToolsLayout);


        // Graph Area
        graphicsView = new QGraphicsView;
        graphicsView->setRenderHints(QPainter::Antialiasing |
                                     QPainter::TextAntialiasing |
                                     QPainter::HighQualityAntialiasing |
                                     QPainter::SmoothPixmapTransform);

        progressBarGraph = new QProgressBar;
        graphLayout = new QVBoxLayout;
        graphLayout->addWidget(graphicsView);
        graphLayout->addWidget(progressBarGraph);
        graphWidget = new QWidget;
        graphWidget->setLayout( graphLayout );


        horizontalLayout = new QHBoxLayout;
        horizontalLayout->addWidget(rightTools);
        horizontalLayout->addWidget(graphWidget);

        widget->setLayout(horizontalLayout);


    } // setupUi


};

namespace Ui {
    class MainWindow: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
