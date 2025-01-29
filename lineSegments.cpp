#include <iostream>
#include <vector>
#include <random>
#include <matplot/matplot.h>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Segment_2.h>
#include <CGAL/intersections.h>    

using Point2D = CGAL::Point_2<CGAL::Cartesian<double>>;
using Segment2D = CGAL::Segment_2<CGAL::Cartesian<double>>;

int main() {

    std::mt19937 mt(std::time(nullptr));
    std::uniform_int_distribution X{0, 100};
    std::uniform_int_distribution Y{0, 100};
    
    matplot::xlim({-10, 110});
    matplot::ylim({-10, 110});
    matplot::hold(true);

    const int n = 10;
    std::vector<Segment2D> segments(n);

    for (int i = 0; i < n; ++i) {
        Point2D source(X(mt), Y(mt));
        Point2D target(X(mt), Y(mt));

        Segment2D segment(source, target);
        segments[i] = segment;
    }

    for (const Segment2D& segment : segments) {
        matplot::plot({segment.source().x(), segment.target().x()}, {segment.source().y(), segment.target().y()}, "b-");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const auto result = CGAL::intersection(segments[i], segments[j]);
            if (result) {
                if (const Point2D* p = boost::get<Point2D>(&*result)) {
                    matplot::plot({p->x()}, {p->y()}, "r.");
                }
                else if (const Segment2D* s = boost::get<Segment2D>(&*result)) {
                    matplot::plot({s->source().x(), s->target().x()}, {s->source().y(), s->target().y()}, "-o");
                }
            }
        }
    }

    matplot::show();

    return 0;
}