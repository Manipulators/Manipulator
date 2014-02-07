#include "ms_rational_nt.h"
#include <CGAL/Cartesian.h>
#include <CGAL/minkowski_sum_2.h>

typedef CGAL::Cartesian<Number_type>                Kernel;
typedef Kernel::Point_2                             Point_2;
typedef CGAL::Polygon_2<Kernel>                     Polygon_2;

#include <QtGui>


int main (int argc, char **argv)
{
    QApplication app(argc, argv);
    
    QGraphicsScene scene;
    std::string line;
    std::ifstream myfile("../data/obstacles.data");
    char *pch;
    float x;
    float y;
    int i = 0;
    Polygon_2 obstacles[500];
    
    if (myfile.is_open())
    {
        getline (myfile, line); //Read size
        
        pch = NULL;
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        pch = strtok(cstr, " ");
        x = atof(pch);
        pch = strtok(NULL, " ;");
        y = atof(pch);
        scene.setSceneRect(0, 0, x, y);
        // Read a polygon
        while (getline(myfile, line))
        {
            // Qt
	        QPolygonF Pqt;
            // CGAL
	        Polygon_2 P;
	        pch = NULL;
	        char *cstr = new char[line.length() + 1];
  	        strcpy (cstr, line.c_str());
	        pch = strtok(cstr, " ;");
  	        while (pch != NULL)
  	        {
	            x = atof(pch);
    	        pch = strtok(NULL, " ;");
	            y = atof(pch);
	            pch = strtok(NULL, " ;");
	            P.push_back(Point_2 (x, y));
	            Pqt << QPointF(x, y);
  	        } 
	        obstacles[i] = P;
            i++;
            scene.addPolygon(Pqt, QPen(Qt::black), QBrush(Qt::darkBlue));
        }
        myfile.close();
    }
    else std::cout << "Unable to open file\n"; 
    
    QGraphicsView *view = new QGraphicsView(&scene);
    view->show();
    
    return app.exec();
}


