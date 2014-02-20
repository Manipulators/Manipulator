#include <QFileDialog>
#include <QGraphicsView>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    ui(new Ui::MainWindow)
{
    // Setup the user interface.
    this->setupUI();

    // Setup the GraphicsScene.
    this->scene = new QGraphicsScene(this);
    this->scene->setBackgroundBrush(QBrush(Qt::gray));
    this->scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    // Add the barriers to the GraphicsScene.
    this->barriers = new Barriers();
    QObject::connect(this, SIGNAL(changed()), this->barriers, SLOT(modelChanged()));
    this->scene->addItem(this->barriers);

    // Add the first bodie to the GraphicsScene.
    this->bodie_1 = new Bodie();
    QObject::connect(this, SIGNAL(changed()), this->bodie_1, SLOT(modelChanged()));
    this->scene->addItem(this->bodie_1);

    // Add the second bodie to the GraphicsScene.
    this->bodie_2 = new Bodie();
    QObject::connect(this, SIGNAL(changed()), this->bodie_2, SLOT(modelChanged()));
    this->scene->addItem(this->bodie_2);

    // Setup the Graphicsview.
    this->ui->graphicsView->setScene(scene);
    QObject::connect(this, SIGNAL(changed()), this, SLOT(viewChanged()));

    // Initialize the filename of the current opened file.
    this->filename = "";


/* This section will disapear. *************************************************
// To display something, we must use the CGAL::Qt::GraphicsItem concept.

    //Critical Graph(e) (cf Article for notations).
    Arrangement A1,A,S,CG;// critical graph;
    A1.addOffsets(obstacles.getPolygons(),robot1.r());
    A.addOffsets(obstacles.getPolygons(),robot2.r());
    CG.addOffsets(obstacles.getPolygons(),robot1.r()+2*robot2.r());
    S.addOffsetScreen(width, height,robot1.r());

*******************************************************************************/

}


/* This section will disapear. *************************************************
// To display something, we must use the CGAL::Qt::GraphicsItem concept.

void MainWindow::addArc(Node n1,Node nc,Node n2)
{//nc center; from point n1 to point n2 (counter clockwise); n1 must be on the circle
    double r =sqrt((n1.x - nc.x)*(n1.x - nc.x)+(n1.y - nc.y)*(n1.y - nc.y));
    QPainterPath* myPath = new QPainterPath();
    myPath->moveTo(QPointF(n1.x,n1.y));//Start point
    myPath->arcTo(QRectF(nc.x - r,nc.y - r,2*r,2*r),360 - angle1(n1.x-nc.x,n1.y-nc.y),360 - angle2(n1.x-nc.x,n1.y-nc.y,n2.x-nc.x,n2.y-nc.y));

    this->scene->addPath(*myPath,QPen(Qt::red));

    return;
}

void MainWindow::addLine(double x1, double y1, double x2, double y2)
{
    this->scene->addLine(x1,y1,x2,y2,QPen(Qt::red));
    return;
}

void MainWindow::addGraph(Graphe g)
{
    int i,j;
    for (i = 0; i < g.n - 1; i++)
    {
        for (j = i+1; j < g.n; j++)
        {
            Vertice v = ((g.matrix)[i][j]);
            switch (v.vtype)
            {
                case None:
                {
                    break;
                }
                case Seg:
                {
                    Node ni = (g.nodes)[i];
                    Node nj = (g.nodes)[j];
                    this->addLine(ni.x,ni.y,nj.x,nj.y);
                    break;
                }
                case Arc:
                {
                    Node ni = (g.nodes)[i];
                    Node nj = (g.nodes)[j];
                    Node nc;
                    nc.x = v.xc;
                    nc.y = v.yc;
                    this->addArc(nj,nc,ni);
                    break;
                }
            }
        }
    }
    return;
}

*******************************************************************************/


MainWindow::~MainWindow()
{
    delete this->ui;
}


// Scene slot. /////////////////////////////////////////////////////////////////

void MainWindow::viewChanged()
{
    // Update the scene rectangle.
    QRectF rectangle = this->barriers->boundingRect();
    qreal margin = 0.05 * std::max(rectangle.width(), rectangle.height());
    rectangle.setTop(rectangle.top() - margin);
    rectangle.setBottom(rectangle.bottom() + margin);
    rectangle.setLeft(rectangle.left() - margin);
    rectangle.setRight(rectangle.right() + margin);
    this->ui->graphicsView->setSceneRect(rectangle);
    this->ui->graphicsView->fitInView(rectangle, Qt::KeepAspectRatio);
    return;
}


// File menu slots. ////////////////////////////////////////////////////////////

void MainWindow::open(QString name)
{
    // Read the new barriers and bodies from the input file.
    QApplication::setOverrideCursor(Qt::WaitCursor);
    std::ifstream stream(name.toStdString().c_str());
    stream >> this->barriers;
    stream >> this->bodie_1;
    stream >> this->bodie_2;
    stream.close();
    QApplication::restoreOverrideCursor();

    // Commit changes.
    this->filename = name;
    emit(changed());

    return;
}

void MainWindow::on_actionOpen_triggered()
{
    // Get a user selected input file.
    QString caption = "Open File";
    QString directory = "../data";
    QString filter = "Data Files (*.data)";
    QString name = QFileDialog::getOpenFileName(this, caption, directory, filter);

    if (!name.isEmpty())
    {
        open(name);
    }
}

void MainWindow::on_actionSave_triggered()
{
    // TODO: find a way to avoid total erasing and remove this return.
    return;

    std::ifstream stream(this->filename.toStdString().c_str());
    // TODO: complete.
    stream.close();
    return;
}

void MainWindow::on_actionSave_As_triggered()
{
    // Get a user selected output file.
    QString caption = "Save File";
    QString directory = "../data";
    QString filter = "Data Files (*.data)";
    QString name = QFileDialog::getSaveFileName(this, caption, directory, filter);

    if (!name.isEmpty())
    {
        this->filename = name;
        on_actionSave_triggered();
    }
    return;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->exit();
    return;
}


// Ui setup. ///////////////////////////////////////////////////////////////////

void MainWindow::setupUI()
{
    this->ui->setupUi(this);
    return;
}
