#include "line_following_algorithm.hpp"

LineFollowerAlgo::LineFollowerAlgo() {
}

void LineFollowerAlgo::calculate(bool leftState, bool rightState) {
    if (leftState && rightState) {
        m1val = lf_speed;
        m2val = lf_speed;
    } else if (leftState && !rightState) {
        m1val = 0;//lf_speed / slow_side_factor;
        m2val = lf_speed;
        prev_side_right = false;
    } else if (!leftState && rightState) {
        m1val = lf_speed;
        m2val = 0;//lf_speed / slow_side_factor;
        prev_side_right = true;
    } else {
        /*if (prev_side_right) {
            m1val = lf_speed;
            m2val = 0;
        } else {
            m1val = 0;
            m2val = lf_speed;
        }*/
    }
}

int LineFollowerAlgo::get_m1() {
    return m1val;
}

int LineFollowerAlgo::get_m2() {
    return m2val;
}