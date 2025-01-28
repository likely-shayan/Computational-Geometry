#include <iostream>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Line_2.h>
#include <CGAL/intersections.h>

using Point2D = CGAL::Point_2<CGAL::Cartesian<double>>;
using Line2D = CGAL::Line_2<CGAL::Cartesian<double>>;

int main() {

    // Constructs a line ax + by + c = 0 with a = 2, b = -1, c = 0
    Line2D l1(2, -1, 0);
    
    // Constructs a line ax + by + c = 0 with a = -1, b = 2, c = -3
    Line2D l2(-1, 2, -3);

    auto result = CGAL::intersection(l1, l2);

    std::cout << *result << std::endl;;

    return 0;
}