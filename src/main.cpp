#include <iostream>
#include "ms_rational_nt.h"
#include <CGAL/Cartesian.h>
#include <CGAL/minkowski_sum_2.h>

typedef CGAL::Cartesian<Number_type>                Kernel;
typedef Kernel::Point_2                             Point_2;
typedef CGAL::Polygon_2<Kernel>                     Polygon_2;


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>


#include <boost/format.hpp>
#include <QtGui>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <QLineF>
#include <QRectF>



int main (int argc, char **argv) {

   QApplication app(argc, argv);

  QGraphicsScene scene;
  std::string line;
  std::ifstream myfile ("Obstacles");
  char * pch;
  float x,y;
  int i=0;
  Polygon_2 obstacles [500];
  if (myfile.is_open())
  {
    getline (myfile,line);//Read size
    
    pch = NULL;
    char * cstr = new char [line.length()+1];
    strcpy (cstr, line.c_str());
    pch = strtok (cstr," ");
    x = atof( pch );
    pch = strtok (NULL, " ;");
    y = atof( pch );
    scene.setSceneRect(0,0, x, y);
    while ( getline (myfile,line) )
    { //Read a polygon
	QPolygonF Pqt;//QT
	Polygon_2   P;//CGAL
	pch = NULL;
	char * cstr = new char [line.length()+1];
  	strcpy (cstr, line.c_str());
	pch = strtok (cstr," ;");
  	while (pch != NULL)
  	{
	 x = atof( pch );
    	 pch = strtok (NULL, " ;");
	 y = atof( pch );
	 pch = strtok (NULL, " ;");
	 P.push_back (Point_2 (x, y));
	 Pqt << QPointF(x,y);
  	} 
	obstacles[i] = P; i++; scene.addPolygon(Pqt,QPen(Qt::black),QBrush(Qt::darkBlue));
    }
    myfile.close();
  }

  else std::cout << "Unable to open file"; 
   QGraphicsView* view = new QGraphicsView(&scene);
    CGAL::Qt::GraphicsViewNavigation navigation;
    view->installEventFilter(&navigation);
    view->viewport()->installEventFilter(&navigation);
    view->setRenderHint(QPainter::Antialiasing);

    view->show();

  return app.exec();
}


