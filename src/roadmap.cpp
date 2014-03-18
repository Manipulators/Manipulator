#include <lemon/smart_graph.h>
#include <lemon/dijkstra.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QPainter>
#include "roadmap.h"


#include <math.h>

typedef lemon::SmartDigraph SmartDigraph;
typedef lemon::Dijkstra<SmartDigraph> Dijkstra;

RoadMap::RoadMap()
{

}

void RoadMap::set(Arrangement_2 Admissible, Arrangement_2 Obstacles, double sx, double sy, double tx, double ty)
{
    /* Build a path from (sx,sy) to (tx,ty) inside Admissible and outside Obstacles */

    double xrmin, xrmax, yrmin, yrmax;

    Arrangement_2::Vertex_iterator        curr_v;
    curr_v = Admissible.vertices_begin();
    xrmin = CGAL::to_double(curr_v->point().x());
    xrmax = CGAL::to_double(curr_v->point().x());
    yrmin = CGAL::to_double(curr_v->point().y());
    yrmax = CGAL::to_double(curr_v->point().y());

    for (curr_v = Admissible.vertices_begin();curr_v != Admissible.vertices_end(); ++curr_v)
    {
        double xc = CGAL::to_double(curr_v->point().x());
        double yc = CGAL::to_double(curr_v->point().y());
        if(xc < xrmin){xrmin = xc;};
        if(xc > xrmax){xrmax = xc;};
        if(yc < yrmin){yrmin = yc;};
        if(yc > yrmax){yrmax = yc;};
    };

    std::list< Conic_point_2 > (this->path);
    srand(time(NULL));

    SmartDigraph g;
    SmartDigraph::ArcMap<int> length(g);
    SmartDigraph::NodeMap<int> dist(g);
    SmartDigraph::NodeMap<double> x(g);
    SmartDigraph::NodeMap<double> y(g);

    SmartDigraph::Node s = g.addNode();
    x[s] = sx;
    y[s] = sy;
    SmartDigraph::Node t = g.addNode();
    x[t] = tx;
    y[t] = ty;


    Dijkstra dijkstra(g, length);
    dijkstra.distMap(dist);
    dijkstra.run(s);

    int flag = dijkstra.reached(t);

    while (!flag)
    {
        SmartDigraph::Node u = g.addNode();
        x[u] = frand(xrmin,xrmax);
        y[u] = frand(yrmin,yrmax);
        // degenerated segment
        while(!(isInside(Admissible, x[u], y[u], x[u], y[u]) && isOutside(Obstacles, x[u], y[u], x[u], y[u])))
        {
            x[u] = frand(xrmin,xrmax);
            y[u] = frand(yrmin,yrmax);
        };

        for (SmartDigraph::NodeIt i(g); i != lemon::INVALID; ++i)
        {
            if ( (i != u) && isInside(Admissible, x[i], y[i], x[u], y[u]) && isOutside(Obstacles, x[i], y[i], x[u], y[u]) )
            {
                // add arc
                SmartDigraph::Arc a = g.addArc(i,u);
                SmartDigraph::Arc b = g.addArc(u,i);
                length[a] = disteucl(x[i],y[i],x[u],y[u]);
                length[b] = length[a];
            }
        }

        Dijkstra dijkstraI(g, length);
        dijkstraI.distMap(dist);
        dijkstraI.run(s);
        flag = dijkstraI.reached(t);
    };

    Dijkstra dijkstraO(g, length);
    dijkstraO.distMap(dist);
    dijkstraO.run(s);

    // path
    SmartDigraph::Node i = t;
    (this->path).push_back(Conic_point_2(x[t],y[t]));
    while (i != s)
    {
        i = dijkstraO.predNode (i);
        (this->path).push_back(Conic_point_2(x[i],y[i]));
    };
}


double disteucl(double x1,double y1,double x2,double y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int isInside (Arrangement_2 Admissible,double x1,double y1,double x2,double y2)
{
    Objects objects;
    Face_handle face;

    CGAL::zone(Admissible, Segment_2 (Conic_point_2(x1, y1),Conic_point_2(x2, y2)), std::back_inserter(objects));
    int flag = true;
    for (Object_iterator object = objects.begin(); object != objects.end(); ++object)
    {
        if (assign(face, *object))
        {
            if (face->is_unbounded())
            {
                flag = false;
                break;
            }
        }
    }
    objects.clear();
    return flag;
}

int isOutside (Arrangement_2 Obstacles,double x1,double y1,double x2,double y2)
{
    Objects objects;
    Face_handle face;

    CGAL::zone(Obstacles, Segment_2 (Conic_point_2(x1, y1),Conic_point_2(x2, y2)), std::back_inserter(objects));
    int flag = true;
    for (Object_iterator object = objects.begin(); object != objects.end(); ++object)
    {
        if (assign(face, *object))
        {
            if (!(face->is_unbounded()))
            {
                flag = false;
                break;
            }
        }
    }
    objects.clear();
    return flag;
}

double frand(double fmin, double fmax)
{
    return fmin + ((double)rand()/RAND_MAX) * (fmax-fmin);
}


void RoadMap::modelChanged()
{
    updateBoundingRect();
    update(this->boundingRect());
    return;
}

QRectF RoadMap::boundingRect() const
{
    return this->bounding_rect;
}

void RoadMap::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    std::list<Conic_point_2 >::const_iterator lit ((this->path).begin()),lend((this->path).end());

    for(;lit!=lend;)
    {
       QPointF p1 = QPointF(CGAL::to_double(lit->x()), CGAL::to_double(lit->y()));
       ++lit;

       if(lit!=lend){
           QPointF p2 = QPointF(CGAL::to_double(lit->x()), CGAL::to_double(lit->y()));
           painter->drawLine(p1,p2);};
    }

    return;
}

RoadMap::~RoadMap()
{
}

void RoadMap::updateBoundingRect()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-300.0, -300.0, 600.0, 600.0);
}
