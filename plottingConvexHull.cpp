#include <iostream>
#include <vector>
#include <matplot/matplot.h>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/ch_graham_andrew.h>

using Point2D = CGAL::Point_2<CGAL::Cartesian<double>>;

int main() {
    matplot::xlim({-10, 150});
    matplot::ylim({-10, 150});
    matplot::hold(true);

    std::srand(std::time(nullptr));

    const int n = 100;
    std::vector<Point2D> Points(n);

    for (int i = 0; i < n; ++i) {
        double rand_X = std::rand() % 141;
        double rand_Y = std::rand() % 141;
        Point2D p(rand_X, rand_Y);
        Points[i] = p;
    }

    std::vector<double> abs, ord;
    for (const Point2D& point : Points) {
        abs.push_back(point.x());
        ord.push_back(point.y());
    }

    matplot::plot(abs, ord, ".r");

    std::vector<Point2D> ConvexHull;
    CGAL::ch_graham_andrew(Points.begin(), Points.end(), std::back_inserter(ConvexHull));

    ConvexHull.push_back(*ConvexHull.begin());

    std::vector<double> X, Y;
    for (const Point2D& point : ConvexHull) {
        X.push_back(point.x());
        Y.push_back(point.y());
    }

    matplot::plot(X, Y, "k");

    matplot::show();

    return 0;
}