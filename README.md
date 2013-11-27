Manipulator
===========

Computing a solution for the "Manipulation Planning Problem".


To-do list
----------
* Select libraries
* Generate an instance of the manipulation planning problem
  * Generate obstacles (i.e. environment)
  * Choose the shape of the robot
  * Choose the shape of the movable object
  * Select the initial configuration (i.e. positions of the robot and the object)
  * Select the final configuration
* Compute the solution for this instance
  * Compute the configurations subsets
  * Determine the topological properties of transit and transfer paths
  * Determine the manipulation graph
  * Find a manipulation path


Libraries
----------

* Graphical user interface
  * [GIMP Toolkit + (GTK+)](http://www.gtk.org)
  * [GIMP Tollkit -- (GTKmm)](http://www.gtkmm.org)
  * [Qt](http://qt-project.org)
  * [Fast Light Toolkit (FLTK)](http://www.fltk.org)
  * [wxWidgets](http://www.wxwidgets.org)
  * [Jules' Utility Class Extensions (JUCE)](http://www.juce.com)
  * [...](http://en.wikipedia.org/wiki/List_of_widget_toolkits)
* Computational geometry
  * [Computational Geometry Algorithms Library (CGAL)](http://www.cgal.org)
  * [Open Motion Planning Library (OMPL)](http://ompl.kavrakilab.org)


References
----------

* B. Dacre Wright, J.P. Laumond and R.Alami<br>
  **Motion planning for a robot and a movable object amidst polygonal obstacles**<br>
  *IEEE International Conference on Robotics and Automation, Nice, 1992*

* J. Schwartz and M. Sharir<br>
  **On the Piano Mover III**<br>
  *International Journal on Robotics Research, Vol. 2 (3), 1983*
