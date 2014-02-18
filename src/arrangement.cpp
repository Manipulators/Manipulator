#include "arrangement.h"

Arrangement::Arrangement()
{
}

void Arrangement::addSeg(double x1,double y1,double x2,double y2)
{
      Rat_point_2   ps3 (x1, y1);
      Rat_point_2   pt3 (x2, y2);
      Conic_arc_2   c3 (Rat_segment_2 (ps3, pt3));

      insert (this->arr, c3);
      return;
}

void Arrangement::addArc(double xc,double yc,double x1,double y1,double x2,double y2,double r)
{//center xc yc, begin x1 y1, end x2 y2
    // Les arcs ne s'ajoute pas bien à cause des approximations
    //=> sommets de degrées 1
    /*Rat_circle_2  circ7 (Rat_point_2(xc,yc),r*r);
      Point_2       ps7 (x1, y1);
      Point_2       pt7 (x2, y2);
      Conic_arc_2   c7 (circ7, CGAL::COUNTERCLOCKWISE, ps7, pt7);*/

   /* Point_2       ps7 (x1, y1);
    Point_2       pt7 (x2, y2);
    if(x2 != x1)
    {
        std::cout << "\n\n"<< ((x1*x1-x2*x2+y1*y1-y2*y2)+2*yc*(y2-y1))/(2*(x1-x2))<< "||| "<< xc<<"\n\n";

        Rat_circle_2  circ7 (Rat_point_2( Rational((x1*x1-x2*x2+y1*y1-y2*y2)+2*yc*(y2-y1),2*(x1-x2)) ,yc),r*r);
        Conic_arc_2   c7 (circ7, CGAL::COUNTERCLOCKWISE, ps7, pt7);

        if (!(c7.is_valid())) {std::cout << "\n\n@@@@BANANANE @@@@@@@@@@@\n\n";};
        insert (this->arr, c7);

    }
    else
    {
        Rat_circle_2  circ7 (Rat_point_2( xc, Rational((x1*x1-x2*x2+y1*y1-y2*y2)+2*xc*(x2-x1),2*(y1-y2))),r*r);
        Conic_arc_2   c7 (circ7, CGAL::COUNTERCLOCKWISE, ps7, pt7);
        if (!(c7.is_valid())) {std::cout << "\n\n@@@@BANANANE @@@@@@@@@@@\n\n";};
        insert (this->arr, c7);
    }*/
    this->addSeg(x1,y1,x2,y2);//"Solution" temporaire
    return;
}

void Arrangement::addCircle(double x1,double y1,double r)
{// r square raduis
      Rat_circle_2  circ5 (Rat_point_2(x1,y1), r*r);
      Conic_arc_2   c5 (circ5);

      insert (this->arr, c5);
      return;
}

void Arrangement::addOffset(Polygon polygon,double r)
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
                this->addSeg(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()));
                //this->addVertice(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()),Seg);
            };
            //round side
            Line line2 = Line(Point(lx,ly),Point(lxa,lya));
            Point m2 = line2.projection(Point(x,y));
            lxp = CGAL::to_double(m2.x());
            lyp = CGAL::to_double(m2.y());
            this->addArc(x,y,CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),r);
            //this->addVertice(CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),Arc,x,y);
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
                //this->addVertice(lxp,lyp,lx,ly,Seg);
                this->addSeg(lxp,lyp,lx,ly);
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
        //this->addVertice(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()),Seg);
        this->addSeg(lxp,lyp,CGAL::to_double(m.x()),CGAL::to_double(m.y()));
        //round side
        Line line2 = Line(Point(lx,ly),Point(lxa,lya));
        Point m2 = line2.projection(Point(x,y));
        lxp = CGAL::to_double(m2.x());
        lyp = CGAL::to_double(m2.y());
        //this->addVertice(CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),Arc,x,y);
        this->addArc(x,y,CGAL::to_double(m.x()),CGAL::to_double(m.y()),CGAL::to_double(m2.x()),CGAL::to_double(m2.y()),r);
        lx = lxp;ly=lyp;
    }
    else
    {
        //this->addVertice(lxp,lyp,lx,ly,Seg);
        this->addSeg(lxp,lyp,lx,ly);
    };
    //this->addVertice(lx,ly,xmemoire,ymemoire,Seg);
    this->addSeg(lx,ly,xmemoire,ymemoire);
    return;
}

void Arrangement::addCC2(Arrangement A,double r,Arrangement CG)
{
    typename Arrangement_2::Vertex_const_iterator  vit;
    for (vit = (CG.arr).vertices_begin(); vit != (CG.arr).vertices_end(); ++vit)
    {
        Point_2 m = vit->point();
        double x = CGAL::to_double(m.x());
        double y = CGAL::to_double(m.y());
        if (!(A.inRegion(x,y))) {this->addCircle(x,y,r);};

    };
    return;
}

void Arrangement::addOffsets(std::list<Polygon> polygons,double r)
{
    std::list<Polygon>::iterator polygon;
    for (polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        this->addOffset(*polygon,r);
    };
    return;
}

void Arrangement::addOffsetScreen(int w,int h,double r)
{
    this->addSeg(r,r,w-r,r);
    this->addSeg(w-r,r,w-r,h-r);
    this->addSeg(w-r,h-r,r,h-r);
    this->addSeg(r,h-r,r,r);
    return;
}

void Arrangement::print()
{
    print_arrangement(this->arr);
    return;
}

int Arrangement::inRegion(double x,double y)
{
    Naive_pl naive_pl (this->arr);
    Point_2 q1 (x, y);
    return point_location_query (naive_pl, q1);
}
