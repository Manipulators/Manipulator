#include <QPainter>
#include "manipulationgraph.h"

typedef Arrangements_2::iterator Arrangement_2_iterator;
typedef Conic_traits_2::Point_2 Conic_point_2;
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef Alg_kernel::FT Algebraic_ft;
typedef std::list<CGAL::Object> Objects;
typedef Objects::iterator Object_iterator;
typedef Rat_kernel::Point_2 Rat_point_2;
typedef Conic_traits_2::Curve_2 Conic_arc_2;
typedef Rat_kernel::Circle_2 Rat_circle_2;


ManipulationGraph::ManipulationGraph()
{
    QObject::connect(this, SIGNAL(manipulationGraphChanged()), this, SLOT(modelChanged()));
}

void ManipulationGraph::setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves)
{
    for (Arrangement_2_iterator arrangement = critical_curves.begin(); arrangement != critical_curves.end(); ++arrangement)
    {
        // Set an id for each non-critical region.
        Region_id region_id = 0;
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                face->set_data(new NonCriticalRegion());
                face->data()->setRegionId(region_id++);
            }
        }

        // Set a list of adjacent non-critical regions for each non-critical region.
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
                        Region_id adjacent_region_id = adjacent_face->data()->getRegionId();
                        face->data()->addAdjacentRegion(adjacent_region_id);
                    }
                    ++outer_ccb;
                } while (outer_ccb != first_outer_ccb);
            }
        }

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

                face->data()->setPoint(point_3);
            }
        }
    }

    Arrangement_2_iterator arrangement = critical_curves.begin();
    Arrangement_2_iterator inset_2 = insets_2.begin();
    while (arrangement != critical_curves.end() && inset_2 != insets_2.end())
    {
        // Set a list of symbolic descriptions of the cells of the set of admissible configurations for each non-critical region.
        for (Arrangement_2::Face_iterator face = arrangement->faces_begin(); face != arrangement->faces_end(); ++face)
        {
            if (!face->is_unbounded())
            {
                Conic_point_2 point = face->data()->getPoint();
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

                Admissible_configuration_space_cells admissible_configuration_space_cells;
                for (Arrangement_2::Face_handle cell = difference.faces_begin(); cell != difference.faces_end(); ++cell)
                {
                    if (!cell->is_unbounded())
                    {
                        Admissible_configuration_space_cell admissible_configuration_space_cell;

                        Arrangement_2::Ccb_halfedge_circulator first_outer_ccb = cell->outer_ccb();
                        Arrangement_2::Ccb_halfedge_circulator outer_ccb = cell->outer_ccb();

                        do
                        {
                            admissible_configuration_space_cell.push_back(outer_ccb->data());
                            ++outer_ccb;
                        } while (outer_ccb != first_outer_ccb);

                        admissible_configuration_space_cells.push_back(admissible_configuration_space_cell);
                    }
                }

                face->data()->setAdmissibleConfigurationSpaceCells(admissible_configuration_space_cells);
            }

        }

        // Set a list of symbolic descriptions of the cells of the set of grasp configurations for each non-critical region.
        // TODO: complete.

        ++arrangement;
        ++inset_2;
    }

    return;
}

void ManipulationGraph::modelChanged()
{
    updateBoundingRect();
    update(this->boundingRect());
    return;
}

QRectF ManipulationGraph::boundingRect() const
{
    return this->bounding_rect;
}

void ManipulationGraph::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    return;
}

ManipulationGraph::~ManipulationGraph()
{

}

void ManipulationGraph::updateBoundingRect()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-300.0, -300.0, 600.0, 600.0);
}
