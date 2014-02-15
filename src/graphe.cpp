#include "graphe.h"

Graphe::Graphe()
{
    n = 0;
}

int Graphe::index(double xi,double yi)
{
    int i = 0;
    for (i = 0; i < (this->n); i++)
    {
        Node m = (this->nodes)[i];
        if (m.x == xi && m.y == yi) {return i;};
    }
    //Add node
    Node node;
    node.x = xi;
    node.y = yi;
    (this->nodes)[this->n] = node;
    this->n = (this->n) + 1;
    return (this->n) - 1;
}

void Graphe::addVertice(double x1,double y1,double x2,double y2,VType vtype, double xc =-1,double yc=-1)
{
    int index1 = index(x1,y1);
    int index2 = index(x2,y2);
    Vertice v;
    v.vtype = vtype;
    v.xc = xc;
    v.yc = yc;
    this->matrix[index1][index2] = v;
    this->matrix[index2][index1] = v;
    return ;
}

void Graphe::addOffset(Polygon polygon,double r)
{   //polygon.is_counterclockwise_oriented()
    //l mean offset
    //
    typename Polygon::Vertex_iterator vertex;
    typename Polygon::Vertex_iterator lvertex;

    Polygon lpolygon = offset(polygon,r);

    vertex = polygon.vertices_end()-1;
    lvertex = lpolygon.vertices_end()-1;

    double xp = 0,yp = 0,x = 0,y = 0,xa = 0,ya = 0;//polygon
    double lxp = 0,lyp = 0,lx = 0,ly = 0,lxa = 0,lya = 0;//lpolygon

    xp = CGAL::to_double(vertex->x());
    yp = CGAL::to_double(vertex->y());
    vertex = polygon.vertices_begin();

    lxp = CGAL::to_double(lvertex->x());
    lyp = CGAL::to_double(lvertex->y());
    lvertex = lpolygon.vertices_begin();


    int flag = 0;double xmemoire,ymemoire;
    for (; vertex < polygon.vertices_end()-1;)
    {
        x = CGAL::to_double(vertex->x());
        y = CGAL::to_double(vertex->y());
        vertex++;
        lx = CGAL::to_double(lvertex->x());
        ly = CGAL::to_double(lvertex->y());
        lvertex++;

        xa = CGAL::to_double(vertex->x());
        ya = CGAL::to_double(vertex->y());
        lxa = CGAL::to_double(lvertex->x());
        lya = CGAL::to_double(lvertex->y());
        if (angle2(x-xp,y-yp,xa-x,ya-y) < 180)
        {   //convex en x y
            //proj x on ((lxp,lyp);(lx,ly))
            Line line = Line(Point(lxp,lyp),Point(lx,ly));
            Point m = line.projection(Point(x,y));
            if (flag == 0)//First point issu
            {   flag++;
                xmemoire = CGAL::to_double(m.x());
                ymemoire = CGAL::to_double(m.y());}
            else{
                this->addVertice(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()),Seg);
            };
            //round side
            Line line2 = Line(Point(lx,ly),Point(lxa,lya));
            Point m2 = line2.projection(Point(x,y));
            lxp = CGAL::to_double(m2.x());
            lyp = CGAL::to_double(m2.y());
            this->addVertice(CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),Arc,x,y);
            lx = lxa;
            ly = lya;
        }
        else
        {
            if (flag == 0)//First point issu
            {   flag++;
                xmemoire = lx;
                ymemoire = ly;}
            else{
                this->addVertice(lxp,lyp,lx,ly,Seg);
            };
            lxp = lx;
            lyp = ly;
            lx = lxa;
            ly = lya;
        };
        xp = x;
        yp = y;
        x = xa;
        y = ya;
    };
    vertex = polygon.vertices_begin();
    xa = CGAL::to_double(vertex->x());
    ya = CGAL::to_double(vertex->y());
    lvertex = lpolygon.vertices_begin();
    lxa = CGAL::to_double(lvertex->x());
    lya = CGAL::to_double(lvertex->y());

    if (angle2(x-xp,y-yp,xa-x,ya-y) < 180)
    {   //convex en x y
        //proj x on ((lxp,lyp);(lx,ly))
        Line line = Line(Point(lxp,lyp),Point(lx,ly));
        Point m = line.projection(Point(x,y));
        this->addVertice(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()),Seg);

        //round side
        Line line2 = Line(Point(lx,ly),Point(lxa,lya));
        Point m2 = line2.projection(Point(x,y));
        lxp = CGAL::to_double(m2.x());
        lyp = CGAL::to_double(m2.y());
        this->addVertice(CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),Arc,x,y);
        lx = lxp;ly=lyp;
    }
    else
    {
        this->addVertice(lxp,lyp,lx,ly,Seg);
    };
    this->addVertice(lx,ly,xmemoire,ymemoire,Seg);
    return;
}

void Graphe::addOffsets(std::list<Polygon> polygons,double r)
{
    std::list<Polygon>::iterator polygon;
    for (polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        this->addOffset(*polygon,r);
    };
    return;
}

void Graphe::addOffsetScreen(int w,int h,double r)
{
    this->addVertice(r,r,w-r,r,Seg);
    this->addVertice(w-r,r,w-r,h-r,Seg);
    this->addVertice(w-r,h-r,r,h-r,Seg);
    this->addVertice(r,h-r,r,r,Seg);
    return;
}
