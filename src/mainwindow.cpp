#include <QFileDialog>
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
    QObject::connect(this->barriers, SIGNAL(barriersChanged()), this, SLOT(viewChanged()));
    this->scene->addItem(this->barriers);

    // Add the critical curves to the GraphicsScene.
    this->critical_curves = new CriticalCurves();
    this->scene->addItem(this->critical_curves);

    // Add the inset to the GraphicsScene.
    this->inset = new Inset();
    this->scene->addItem(this->inset);

    // Add the first bodie to the GraphicsScene.
    this->bodie_1 = new Bodie();
    QObject::connect(this->bodie_1, SIGNAL(bodieChanged()), this, SLOT(tabWidgetChanged()));
    this->scene->addItem(this->bodie_1);

    // Add the second bodie to the GraphicsScene.
    this->bodie_2 = new Bodie();
    QObject::connect(this->bodie_2, SIGNAL(bodieChanged()), this, SLOT(tabWidgetChanged()));
    this->scene->addItem(this->bodie_2);

    // Setup the Graphicsview.
    this->ui->graphicsView->setScene(scene);
    this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // Initialize the filename of the current opened file.
    this->filename = "";
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->barriers;
    delete this->bodie_1;
    delete this->bodie_2;
    delete this->inset;
    delete this->critical_curves;
}


// Scene slot. /////////////////////////////////////////////////////////////////

void MainWindow::viewChanged()
{
    // Update the scene rectangle.
    QRectF rectangle = this->barriers->boundingRect();
    qreal margin = 0.05 * std::max(rectangle.width(), rectangle.height());
    double x_min = rectangle.left() - margin;
    double x_max = rectangle.right() + margin;
    double y_min = rectangle.top() - margin;
    double y_max = rectangle.bottom() + margin;
    rectangle.setLeft(x_min);
    rectangle.setRight(x_max);
    rectangle.setTop(y_min);
    rectangle.setBottom(y_max);
    this->ui->graphicsView->setSceneRect(rectangle);
    this->ui->graphicsView->fitInView(rectangle, Qt::KeepAspectRatio);

    this->ui->doubleSpinBoxInitialConfigurationFirstBodieX->setMinimum(x_min);
    this->ui->doubleSpinBoxInitialConfigurationFirstBodieX->setMaximum(x_max);
    this->ui->doubleSpinBoxInitialConfigurationFirstBodieY->setMinimum(y_min);
    this->ui->doubleSpinBoxInitialConfigurationFirstBodieY->setMaximum(y_max);
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieX->setMinimum(x_min);
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieX->setMaximum(x_max);
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieY->setMinimum(y_min);
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieY->setMaximum(y_max);
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieX->setMinimum(x_min);
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieX->setMaximum(x_max);
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieY->setMinimum(y_min);
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieY->setMaximum(y_max);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieX->setMinimum(x_min);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieX->setMaximum(x_max);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieY->setMinimum(y_min);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieY->setMaximum(y_max);

    return;
}

void MainWindow::tabWidgetChanged()
{
    this->ui->doubleSpinBoxRadiusFirstBodieR->setRange(this->bodie_1->getR(), this->bodie_1->getR());
    this->ui->doubleSpinBoxRadiusSecondBodieR->setRange(this->bodie_2->getR(), this->bodie_2->getR());
    this->ui->doubleSpinBoxInitialConfigurationFirstBodieX->setValue(this->bodie_1->getX());
    this->ui->doubleSpinBoxInitialConfigurationFirstBodieY->setValue(this->bodie_1->getY());
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieX->setValue(this->bodie_2->getX());
    this->ui->doubleSpinBoxInitialConfigurationSecondBodieY->setValue(this->bodie_2->getY());
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieX->setValue(this->bodie_1->xf);
    this->ui->doubleSpinBoxFinalConfigurationFirstBodieY->setValue(this->bodie_1->yf);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieX->setValue(this->bodie_2->xf);
    this->ui->doubleSpinBoxFinalConfigurationSecondBodieY->setValue(this->bodie_2->yf);
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

    // Update filename of the current opened file.
    this->filename = name;

    // Update the graphics items.
    this->critical_curves->clear();

    // Update the UI elements enabled.
    this->ui->groupBoxInitialConfiguration->setEnabled(true);
    this->ui->groupBoxFinalConfiguration->setEnabled(true);
    this->ui->groupBoxDisplay->setEnabled(false);
    this->ui->checkBoxShowCriticalCurves->setChecked(false);
    this->ui->pushButtonSolve->setEnabled(true);

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

void MainWindow::on_actionSaveAs_triggered()
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


// View menu slot. /////////////////////////////////////////////////////////////

void MainWindow::on_actionFit_triggered()
{
    this->viewChanged();
    return;
}

void MainWindow::on_actionZoomIn_triggered()
{
    double scaleFactor = 1.15;
    this->ui->graphicsView->scale(scaleFactor, scaleFactor);
    return;
}

void MainWindow::on_actionZoomOut_triggered()
{
    double scaleFactor = 1.15;
    this->ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    return;
}


// Problem tab slots. //////////////////////////////////////////////////////////

void MainWindow::on_doubleSpinBoxInitialConfigurationFirstBodieX_valueChanged(double x)
{
    this->bodie_1->setX(x);
    return;
}

void MainWindow::on_doubleSpinBoxInitialConfigurationFirstBodieY_valueChanged(double y)
{
    this->bodie_1->setY(y);
    return;
}

void MainWindow::on_doubleSpinBoxInitialConfigurationSecondBodieX_valueChanged(double x)
{
    this->bodie_2->setX(x);
    return;
}

void MainWindow::on_doubleSpinBoxInitialConfigurationSecondBodieY_valueChanged(double y)
{
    this->bodie_2->setY(y);
    return;
}

void MainWindow::on_doubleSpinBoxFinalConfigurationFirstBodieX_valueChanged(double x)
{
    // TODO: complete.
    return;
}

void MainWindow::on_doubleSpinBoxFinalConfigurationFirstBodieY_valueChanged(double y)
{
    // TODO: complete.
    return;
}

void MainWindow::on_doubleSpinBoxFinalConfigurationSecondBodieX_valueChanged(double x)
{
    // TODO: complete.
    return;
}

void MainWindow::on_doubleSpinBoxFinalConfigurationSecondBodieY_valueChanged(double y)
{
    // TODO: complete.
    return;
}

void MainWindow::on_pushButtonSolve_clicked()
{
    // TODO: complete.
    this->critical_curves->setParameters(this->barriers->getPolygon(), this->bodie_1->getR(), this->bodie_2->getR());
    this->ui->groupBoxInitialConfiguration->setDisabled(true);
    this->ui->groupBoxFinalConfiguration->setDisabled(true);
    this->ui->groupBoxDisplay->setEnabled(true);
    this->ui->checkBoxShowCriticalCurves->setChecked(true);
    this->ui->pushButtonSolve->setDisabled(true);
    return;
}

void MainWindow::on_checkBoxShowBodie_stateChanged(int state)
{
    switch (state)
    {
        case Qt::Checked:
            this->bodie_1->show();
            this->bodie_2->show();
            break;
        case Qt::Unchecked:
            this->bodie_1->hide();
            this->bodie_2->hide();
            break;
        case Qt::PartiallyChecked:
            break;
        default:
            break;
    }
    return;
}

void MainWindow::on_checkBoxShowCriticalCurves_stateChanged(int state)
{
    switch (state)
    {
        case Qt::Checked:
            this->critical_curves->show();
            break;
        case Qt::Unchecked:
            this->critical_curves->hide();
            break;
        case Qt::PartiallyChecked:
            break;
        default:
            break;
    }
    return;
}


// Ui setup. ///////////////////////////////////////////////////////////////////

void MainWindow::setupUI()
{
    this->ui->setupUi(this);
    return;
}
