/*
A subset S of the plane is called a convex if and only if: For all pair of points p, q on S,
the line-segment pq is completely contained in S.
The convex hull of a set S, ConvexHull(S), is the smallest convex that contains S.
More precisely, It is the intersecion of all convex sets that contains S.

To visualize the convex hull, Suppose we have a plane with some finite points on it
Now, Suppose each point is a nail sticking out towards the viewer on top of plane.
Now take an elastic rubber-band and stick it out around the nails so that all the nails are
inside or on the rubber-band. The area enclosed by the rubber-band is our convex hull.

The convex hull of a finite set of points can be thought of as a subset of the given points such that
each point is touching the "rubber-band" or is on the border of the area enlosed by it.
*/

#include <iostream>
#include <vector>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/ch_akl_toussaint.h>
#include <CGAL/ch_eddy.h>
#include <CGAL/ch_graham_andrew.h>
#include <CGAL/ch_jarvis.h>
#include <CGAL/ch_melkman.h>
#include <CGAL/convexity_check_2.h>
#include <CGAL/convex_hull_2.h>

using Point2D = CGAL::Point_2<CGAL::Cartesian<double>>;

void printPoints(const std::vector<Point2D>& Points) {
    for (int i = 0; i < Points.size(); ++i) {
        std::cout << "(" << Points[i].x() << "," << Points[i].y() << ")";
        if (i + 1 != Points.size()) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

int main() {

    std::vector<Point2D> Points = {{0, 0}, {0, 1}, {0, 2}, {2, 0}, {2, 2}, {3, 1}, {1, 1}, {2, 1}};

    std::vector<Point2D> result1;

    // Find Convex Hull using Akl and Toussiant algorithm.
    // This takes O(n logn) time for n input points.
    CGAL::ch_akl_toussaint(Points.begin(), Points.end(), std::back_inserter(result1));
    std::cout << "Akl and Toussiant: ";
    printPoints(result1);

    std::vector<Point2D> result2;

    // Find Convex Hull using Eddy's algorithm.
    // This takes O(nh) time for n input points with h extreme points.
    CGAL::ch_eddy(Points.begin(), Points.end(), std::back_inserter(result2));
    std::cout << "Eddy's: ";
    printPoints(result2);

    std::vector<Point2D> result3;

    // Find Convex Hull using Graham Scan algorithm.
    // This takes O(n logn) time for n input points.
    CGAL::ch_eddy(Points.begin(), Points.end(), std::back_inserter(result3));
    std::cout << "Graham's Scan: ";
    printPoints(result3);

    std::vector<Point2D> result4;

    // Find Convex Hull using Jarvis march algorithm
    // This takes O(nh) time for n input points and h extreme points.
    CGAL::ch_jarvis(Points.begin(), Points.end(), std::back_inserter(result4));
    std::cout << "Jarvis March: ";
    printPoints(result4);

    std::vector<Point2D> result5;

    // Find Convex Hull using Melkan's algorithm
    // This takes O(n) time for n input points.
    CGAL::ch_melkman(Points.begin(), Points.end(), std::back_inserter(result5));
    std::cout << "Melkan's: ";
    printPoints(result5);

    std::vector<Point2D> ch = result1;

    // Checking if the points are convex in Clockwise order, takes O(n) for n input points.
    if (CGAL::is_cw_strongly_convex_2(ch.begin(), ch.end())) {
        std::cout << "Given set of points is Convex in Clockwise order" << std::endl;
    }
    // Checking if the points are convex in Counter-Clockwise order, takes O(n) for n input points.
    else if (CGAL::is_ccw_strongly_convex_2(ch.begin(), ch.end())) {
        std::cout << "Given set of points is Convex in Counter-Clockwise order" << std::endl;
    }
    else {
        std::cout << "Given set of points are not Convex" << std::endl;
    }

    std::vector<Point2D> lowerHull;
    // Generates the lower hull of the given set of points in Graham Scan Algorithm O(n logn)
    CGAL::lower_hull_points_2(Points.begin(), Points.end(), std::back_inserter(lowerHull));
    std::cout << "Lower Hull: ";
    printPoints(lowerHull);

    std::vector<Point2D> upperHull;
    // Generates the upper hull of the given set of points in Graham Scan Algorithm O(n logn)
    CGAL::upper_hull_points_2(Points.begin(), Points.end(), std::back_inserter(upperHull));
    std::cout << "Upper Hull: ";
    printPoints(upperHull);

    return 0;
}