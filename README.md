# Manipulator

Computing a solution for the "Manipulation Planning Problem".


## Compilation

### Linux (Debian-based)

- Install the commands make, cmake and git
  
  ```console
  sudo apt-get install build-essential cmake git-core
  ```

- Install the Qt framework and the CGAL library
  
  ```console
  sudo apt-get install qt-sdk libcgal-dev
  ```

- Change your current directory to clone Manipulator
  
  ```console
  cd [dir]
  ```

- Clone Manipulator
  
  ```console
  git clone https://github.com/Manipulators/Manipulator.git
  ```

- Go inside it
  
  ```console
  cd Manipulator/
  ```

- Create a build directory
  
  ```console
  mkdir build
  ```

- Go inside it
  
  ```console
  cd build/
  ```

- Generate Makefiles
  
  ```console
  cmake ../src/
  ```

- Build executable
  
  ```console
  make
  ```

- Run executable
  
  ```console
  ./main
  ```


## Input

Describe screen size
Describe obstacles in "Obstacles".
One line by polygon, described with pairs of points.


## To-do list

* Find the file format to describe the arguments (i.e. environment, robot,
  movable object, initial configuration and final configuration), this file
  format must be CGAL-friendly
* Create a command which takes the arguments and returns their graphical
  representation in a new window
* ...


## Specification

* Generate an instance of the manipulation planning problem
  * Generate obstacles (i.e. environment)
  * Choose the radius of the circle robot
  * Choose the radius of the circle movable object
  * Select the initial configuration (i.e. positions of the robot and the object)
  * Select the final configuration
* Compute the solution for this instance
  * Compute the critical regions
  * Determine the topological properties of transit and transfer paths
  * Determine the manipulation graph
  * Find a manipulation path
* Display the main concepts for solving the problem
  * Display the representation of the instance of the problem
  * Display the critical regions
  * Display the manipulation graph
* Wrap the assembly into an graphical interface
* ...


## Libraries

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

[Qt](http://qt-project.org) and [CGAL](http://www.cgal.org) have been selected
for the project since [CGAL](http://www.cgal.org) provides a package for
displaying CGAL objects and data structures in the
[Qt Graphics View Framework](http://qt-project.org).


##References

* B. Dacre Wright, J.P. Laumond and R.Alami<br>
  **Motion planning for a robot and a movable object amidst polygonal obstacles**<br>
  *IEEE International Conference on Robotics and Automation, Nice, 1992*

* J. Schwartz and M. Sharir<br>
  **On the Piano Mover III**<br>
  *International Journal on Robotics Research, Vol. 2 (3), 1983*
