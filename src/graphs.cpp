#include "graphs.h"

typedef Arrangements_2::iterator Arrangement_2_iterator;
typedef Conic_traits_2::Point_2 Conic_point_2;
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef Alg_kernel::FT Algebraic_ft;
typedef std::list<CGAL::Object> Objects;
typedef Objects::iterator Object_iterator;
typedef Rat_kernel::Point_2 Rat_point_2;
typedef Conic_traits_2::Curve_2 Conic_arc_2;
typedef Rat_kernel::Circle_2 Rat_circle_2;


class Arrangement_2_observer : public CGAL::Arr_observer<Arrangement_2>
{
public:
    Arrangement_2_observer (Arrangement_2& arr) : CGAL::Arr_observer<Arrangement_2> (arr)
    {
    }

    virtual void after_split_edge (Halfedge_handle halfedge_1, Halfedge_handle halfedge_2)
    {
        int id_1 = halfedge_1->data();
        int id_2 = halfedge_2->data();
        int id_3 = halfedge_1->twin()->data();
        int id_4 = halfedge_2->twin()->data();
        int id = std::max(std::max(std::max(id_1, id_2), id_3), id_4);
        halfedge_1->set_data(id);
        halfedge_2->set_data(id);
        halfedge_1->twin()->set_data(id);
        halfedge_2->twin()->set_data(id);
    }
};

Graphs::Graphs()
{
}

void Graphs::setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves)
{
    this->buildNCRg(radius_1, radius_2, insets_1,insets_2,critical_curves);
    this->buildManipG();
}

void Graphs::buildNCRg(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves)
{

    for (Arrangement_2_iterator arrangement = critical_curves.begin(); arrangement != critical_curves.end(); ++arrangement)
    {

        // Associate a node to each face
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                face->set_data((this->NCRg).addNode());
            }
        };

        // Build non-critical regions graph
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                Arrangement_2::Ccb_halfedge_circulator first_outer_ccb = face->outer_ccb();
                Arrangement_2::Ccb_halfedge_circulator outer_ccb = face->outer_ccb();

                do
                {
                    Arrangement_2::Face_handle adjacent_face = outer_ccb->twin()->face();
                    if (!adjacent_face->is_unbounded())
                    {
                        (this->NCRg).addArc(face->data(),adjacent_face->data());
                    }
                    ++outer_ccb;
                } while (outer_ccb != first_outer_ccb);
            }
        }
        std::cout << "Non-critical regions graph: Nodes: " << lemon::countNodes(this->NCRg)<<", Edges: "<< (lemon::countArcs(this->NCRg)) <<"\n";
        std::cout.flush();
        // Set a interior point for each non critical region.
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                Arrangement_2::Ccb_halfedge_circulator first_outer_ccb = face->outer_ccb();
                Arrangement_2::Ccb_halfedge_circulator outer_ccb = face->outer_ccb();

                Algebraic_ft x_min = outer_ccb->curve().source().x();
                Algebraic_ft x_max = outer_ccb->curve().source().x();
                Algebraic_ft y_min = outer_ccb->curve().source().y();
                Algebraic_ft y_max = outer_ccb->curve().source().y();

                do
                {
                    Algebraic_ft x = outer_ccb->curve().source().x();
                    Algebraic_ft y = outer_ccb->curve().source().y();
                    //std::cout << "x:" << x << ",y:" << y << " ";
                    if (x < x_min)
                    {
                        x_min = x;
                    }
                    if (x > x_max)
                    {
                        x_max = x;
                    }
                    if (y < y_min)
                    {
                        y_min = y;
                    }
                    if (y > y_max)
                    {
                        y_max = y;
                    }
                    x = outer_ccb->curve().target().x();
                    y = outer_ccb->curve().target().y();
                    //std::cout << "x:" << x << ",y:" << y << " ";
                    if (x < x_min)
                    {
                        x_min = x;
                    }
                    if (x > x_max)
                    {
                        x_max = x;
                    }
                    if (y < y_min)
                    {
                        y_min = y;
                    }
                    if (y > y_max)
                    {
                        y_max = y;
                    }
                    ++outer_ccb;
                } while (outer_ccb != first_outer_ccb);
                //std::cout << std::endl;

                Nt_traits nt_traits;
                //x_min = x_min - nt_traits.convert(Rational(1));
                //x_max = x_max + nt_traits.convert(Rational(1));
                Algebraic_ft y_mid = (y_max + y_min) / nt_traits.convert(Rational(2));
                Conic_point_2 source(x_min, y_mid);
                Conic_point_2 target(x_max, y_mid);
                Algebraic_ft a = nt_traits.convert(Rational(0));
                Algebraic_ft b = nt_traits.convert(Rational(1));
                Algebraic_ft c = - y_mid;
                X_monotone_curve_2 x_monotone_curve(a, b, c, source, target);
                //std::cout << "x_min:" << x_min << " x_max:" << x_max << " y_mid:" << y_mid << std::endl;
                //std::cout << "a:" << a << " b:" << b << " c:" << c << std::endl;

                Objects objects;
                CGAL::zone(*arrangement, x_monotone_curve, std::back_inserter(objects));

                Object_iterator object;
                Arrangement_2::Vertex_handle vertex_handle;
                Arrangement_2::Halfedge_handle halfedge_handle;
                Arrangement_2::Face_handle face_handle;

                /*
                std::cout << "# ";
                for (object = objects.begin(); object != objects.end(); ++object)
                {
                    if (assign(vertex_handle, *object))
                    {
                        std::cout << "Vertex ";
                    }
                    if (assign(halfedge_handle, *object))
                    {
                        std::cout << "Halfedge ";
                    }
                    if (assign(face_handle, *object))
                    {
                        std::cout << "Face ";
                    }
                }
                std::cout << std::endl;
                */

                for (object = objects.begin(); object != objects.end(); ++object)
                {
                    if (assign(face_handle, *object))
                    {
                        if (face_handle == face)
                        {
                            //std::cout << "Break." << std::endl;
                            break;
                        }
                    }
                }

                Conic_point_2 point_1;
                --object;
                if (assign(vertex_handle, *object))
                {
                    //std::cout << "Vertex." << std::endl;
                    point_1 = vertex_handle->point();
                }
                else if (assign(halfedge_handle, *object))
                {
                    //std::cout << "Halfedge." << std::endl;
                    Arrangement_2 a;
                    insert(a, x_monotone_curve);
                    insert(a, halfedge_handle->curve());
                    for (Arrangement_2::Vertex_iterator vertex = a.vertices_begin(); vertex != a.vertices_end(); ++vertex)
                    {
                        if (vertex->degree() > 2)
                        {
                            //std::cout << "Vertex'." << std::endl;
                            point_1 = vertex->point();
                            break;
                        }
                    }
                }
                else if (assign(face_handle, *object))
                {
                    //std::cout << "Face." << std::endl;
                }
                //std::cout << "Fin 1." << std::endl;

                Conic_point_2 point_2;
                ++object;
                ++object;
                if (assign(vertex_handle, *object))
                {
                    //std::cout << "Vertex." << std::endl;
                    point_2 = vertex_handle->point();
                }
                else if (assign(halfedge_handle, *object))
                {
                    //std::cout << "Halfedge." << std::endl;
                    Arrangement_2 a;
                    insert(a, x_monotone_curve);
                    insert(a, halfedge_handle->curve());
                    for (Arrangement_2::Vertex_iterator vertex = a.vertices_begin(); vertex != a.vertices_end(); ++vertex)
                    {
                        if (vertex->degree() > 2)
                        {
                            //std::cout << "Vertex'." << std::endl;
                            point_2 = vertex->point();
                            break;
                        }
                    }
                }
                else if (assign(face_handle, *object))
                {
                    //std::cout << "Face." << std::endl;
                }
                //std::cout << "Fin 2." << std::endl;

                Algebraic_ft x_point_3 = (point_1.x() + point_2.x()) / nt_traits.convert(Rational(2));
                Algebraic_ft y_point_3 = (point_1.y() + point_2.y()) / nt_traits.convert(Rational(2));
                Conic_point_2 point_3(x_point_3, y_point_3);

                (noncriticalregion[face->data()]).point = point_3;
                //std::cout << CGAL::to_double(x_point_3) <<" "<< CGAL::to_double(y_point_3) << "\n";
            }
        }
    };

    std::cout.flush();
    Arrangement_2_iterator arrangement = critical_curves.begin();
    Arrangement_2_iterator inset_2 = insets_2.begin();
    while (arrangement != critical_curves.end() && inset_2 != insets_2.end())
    {
        // Set a list of symbolic descriptions of the cells of the set of admissible configurations for each non-critical region.
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                Conic_point_2 point = (noncriticalregion[face->data()]).point;
                double x = CGAL::to_double(point.x());
                double y = CGAL::to_double(point.y());
                double radius = radius_1 + radius_2;
                Rat_point_2 center(x, y);
                Rat_circle_2 circle(center, radius * radius);
                Conic_arc_2 conic_arc(circle);

                Arrangement_2 difference = Arrangement_2(*inset_2);
                Arrangement_2_observer observer(difference);
                insert(difference, conic_arc);
                for (Arrangement_2::Edge_iterator edge = difference.edges_begin();  edge != difference.edges_end(); ++edge)
                {
                    Arrangement_2::Face_handle face_1 = edge->face();
                    Arrangement_2::Face_handle face_2 = edge->twin()->face();
                    if (edge->data() == 0)
                    {
                        if (face_1->is_unbounded() || face_2->is_unbounded())
                        {
                            edge->set_data(-1);
                        }
                    }
                    else
                    {
                        if (!face_1->is_unbounded() && !face_2->is_unbounded())
                        {
                            edge->set_data(-1);
                        }
                    }
                }
                Arrangement_2::Edge_iterator edge = difference.edges_end();
                while (edge != difference.edges_begin())
                {
                    --edge;

                    if (edge->data() == -1)
                    {
                        remove_edge(difference, edge);
                    }
                }

                for (Arrangement_2::Face_handle cell = difference.faces_begin(); cell != difference.faces_end(); ++cell)
                {
                    if (!cell->is_unbounded())
                    {
                        ACSCell acscell;
                        Arrangement_2::Ccb_halfedge_circulator outer_ccb = cell->outer_ccb();

                        // Find a integer not equal to 0
                        while (outer_ccb->data() == 0) {outer_ccb++;};
                        int previous = outer_ccb->data();
                        Arrangement_2::Ccb_halfedge_circulator first_outer_ccb = outer_ccb;

                        // Zero flag
                        int read_zero = 0;
                        std::cout << "ACSCell label: ";
                        do
                        {
                            if (!read_zero || (outer_ccb->data() != 0))
                            {
                                // clean label
                                std::cout << outer_ccb->data() << ", ";
                                acscell.label.push_back(outer_ccb->data());
                                if (outer_ccb->data() == 0)
                                {
                                    GraspCell graspcell;
                                    graspcell.label1 = previous;
                                    // next
                                    Arrangement_2::Ccb_halfedge_circulator temp = outer_ccb;
                                    while (temp->data() == 0) {temp++;};
                                    graspcell.label2 = temp->data();
                                    acscell.graspcells.push_back(graspcell);
                                    // for the manip graph
                                    graspcell.node = (this->ManipG).addNode();
                                    graspcell_map[graspcell.node] = graspcell;
                                    std::cout << "[GraspCell: "<< graspcell.label1 << "," << graspcell.label2 <<"] ";
                                }
                                else
                                {
                                    previous = outer_ccb->data();
                                };
                            };

                            if (outer_ccb->data() == 0)
                            {
                                read_zero = 1;
                            }
                            else
                            {read_zero = 0;};
                            ++outer_ccb;
                        } while (outer_ccb != first_outer_ccb);
                        std::cout << "\n";std::cout.flush();
                        (noncriticalregion[face->data()]).acscells.push_back(acscell);
                    }
                }
            }

        }

        ++arrangement;
        ++inset_2;
    }

    return;
}

void Graphs::buildManipG()
{
    //Create grasp nodes and transit path
    for (SmartDigraph::NodeIt n(this->NCRg); n != lemon::INVALID; ++n)
    {
        std::list<ACSCell> acscells = (noncriticalregion[n]).acscells;
        std::list<ACSCell>::const_iterator lit (acscells.begin()),lend(acscells.end());

        for(;lit!=lend;++lit)
        {
            ACSCell acscell = *lit;
            std::list<GraspCell> graspcells = acscell.graspcells;
            std::list<GraspCell>::const_iterator lgit (graspcells.begin()),lgend(graspcells.end());


            SmartDigraph::Node previous = lgit->node;
            ++lgit;
            // add transit arc
            for(;lgit!=lgend;++lgit)
            {
                //SmartDigraph::Node a = (this->ManipG).addNode();
                istransit[(this->ManipG).addArc(previous,lgit->node)] = 1;
                istransit[(this->ManipG).addArc(lgit->node,previous)] = 1;
                previous = lgit->node;
            };
        };
    };
    int count = 0;
    for (SmartDigraph::ArcIt arc(this->NCRg); arc != lemon::INVALID; ++arc)
    {
        count++;
        NonCriticalRegion a = noncriticalregion[(this->NCRg).source(arc)];
        NonCriticalRegion b = noncriticalregion[(this->NCRg).target(arc)];

        std::list<ACSCell> acscellsA = a.acscells;
        std::list<ACSCell> acscellsB = b.acscells;

        std::list<ACSCell>::const_iterator la (acscellsA.begin()),laend(acscellsA.end());
        std::list<ACSCell>::const_iterator lb (acscellsB.begin()),lbend(acscellsB.end());

        for(;la!=laend;++la)
        {
            ACSCell acscellA = *la;
            std::list<GraspCell> graspcellsA = acscellA.graspcells;
            std::list<GraspCell>::const_iterator lga (graspcellsA.begin()),lgaend(graspcellsA.end());

            for(;lga!=lgaend;++lga)
            {
                GraspCell ga = *lga;
                // for b
                for(;lb!=lbend;++lb)
                {
                    ACSCell acscellB = *lb;
                    std::list<GraspCell> graspcellsB = acscellB.graspcells;
                    std::list<GraspCell>::const_iterator lgb (graspcellsB.begin()),lgbend(graspcellsB.end());

                    for(;lgb!=lgbend;++lgb)
                    {
                        GraspCell gb = *lgb;
                        if(link(ga.label1,ga.label2,gb.label1,gb.label2))
                        {
                            istransit[(this->ManipG).addArc(ga.node,gb.node)] = 0;
                            istransit[(this->ManipG).addArc(gb.node,ga.node)] = 0;
                        };
                    };
                };
            };
        };
    };
    std::cout << "Manipulation graph: Nodes: " << lemon::countNodes(this->ManipG)<<", Edges: "<< (lemon::countArcs(this->ManipG)) <<"\n";
    std::cout.flush();
}

void Graphs::exportEPS()
{

}

Graphs::~Graphs()
{
}

int Graphs::searchPath(ACSCell ci, ACSCell cf)
{
    SmartDigraph::ArcMap<int> length(this->ManipG);
    SmartDigraph::NodeMap<int> dist(this->ManipG);

    for (SmartDigraph::ArcIt arc(this->ManipG); arc != lemon::INVALID; ++arc)
    {
        length[arc] = 1;
    };

    GraspCell s = *(ci.graspcells.begin());
    GraspCell t = *(ci.graspcells.begin());

    Dijkstra dijkstra(this->ManipG, length);
    dijkstra.distMap(dist);
    dijkstra.run(s.node);

    if(dijkstra.reached(t.node))
    {
        SmartDigraph::Node i = t.node;
        (this->path).push_back(graspcell_map[i]);
        while (i != s.node)
        {
            i = dijkstra.predNode (i);
            (this->path).push_back(graspcell_map[i]);
        };
        return 1;
    }
    else
    {
        return 0;
    };
}

int link(int a, int b, int c, int d)
{
    if (a == c)
    {return b!=d;}
    else {return b==d;};
}
