#pragma once
#include "../entities/Paddle.h"

class ScoreSystem {
public:
    ScoreSystem();

    void addPoint(Paddle::Side scorer);
    void reset();

    int getSetPoints(Paddle::Side side) const;
    int getSets(Paddle::Side side) const;
    int getTotalPoints(Paddle::Side side) const;
    Paddle::Side getLastScorer() const { return lastScorer; }

    bool isMatchOver() const { return matchOver; }
    Paddle::Side getMatchWinner() const { return winner; }

    static constexpr int POINTS_TO_WIN_SET = 5;
    static constexpr int SETS_TO_WIN_MATCH = 3;

private:
    int pointsLeft = 0;
    int pointsRight = 0;
    int setsLeft = 0;
    int setsRight = 0;
    int totalPointsLeftAll = 0;
    int totalPointsRightAll = 0;
    bool matchOver = false;
    Paddle::Side winner = Paddle::Side::LEFT;
    Paddle::Side lastScorer = Paddle::Side::LEFT;

    void checkSetEnd();
};