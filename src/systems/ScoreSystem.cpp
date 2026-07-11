#include "ScoreSystem.h"

ScoreSystem::ScoreSystem() = default;

void ScoreSystem::addPoint(Paddle::Side scorer) {
    if (matchOver) return;

    lastScorer = scorer;

    if (scorer == Paddle::Side::LEFT) {
        pointsLeft++;
        totalPointsLeftAll++;
    } else {
        pointsRight++;
        totalPointsRightAll++;
    }

    checkSetEnd();
}

void ScoreSystem::checkSetEnd() {
    if (pointsLeft >= POINTS_TO_WIN_SET) {
        setsLeft++;
        pointsLeft = 0;
        pointsRight = 0;
    } else if (pointsRight >= POINTS_TO_WIN_SET) {
        setsRight++;
        pointsLeft = 0;
        pointsRight = 0;
    }

    if (setsLeft >= SETS_TO_WIN_MATCH) {
        matchOver = true;
        winner = Paddle::Side::LEFT;
    } else if (setsRight >= SETS_TO_WIN_MATCH) {
        matchOver = true;
        winner = Paddle::Side::RIGHT;
    }
}

void ScoreSystem::reset() {
    pointsLeft = pointsRight = 0;
    setsLeft = setsRight = 0;
    totalPointsLeftAll = totalPointsRightAll = 0;
    matchOver = false;
}

int ScoreSystem::getSetPoints(Paddle::Side side) const {
    return side == Paddle::Side::LEFT ? pointsLeft : pointsRight;
}

int ScoreSystem::getSets(Paddle::Side side) const {
    return side == Paddle::Side::LEFT ? setsLeft : setsRight;
}

int ScoreSystem::getTotalPoints(Paddle::Side side) const {
    return side == Paddle::Side::LEFT ? totalPointsLeftAll : totalPointsRightAll;
}