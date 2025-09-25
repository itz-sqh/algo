#pragma once
#include <chrono>
#include <float.h>
#include <limits.h>
#include <random>

class Rng {
public:
    static int getInt(int min = INT_MIN, int max = INT_MAX) {
        init();
        std::uniform_int_distribution dist(min, max);
        return dist(gen);
    }
    static long long getLong(long long min = LLONG_MIN, long long max = LLONG_MAX) {
        init();
        std::uniform_int_distribution dist(min, max);
        return dist(gen);
    }
    static double getDouble(double min = DBL_MIN, double max = DBL_MAX) {
        init();
        std::uniform_real_distribution dist(min, max);
        return dist(gen);
    }
    static float getFloat(float min = FLT_MIN, float max = FLT_MAX) {
        init();
        std::uniform_real_distribution dist(min, max);
        return dist(gen);
    }

private:
    static std::mt19937 gen;
    static bool initiated;
    static void init() {
        if (!initiated) {
            gen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
            initiated = true;
        }
    }
};

std::mt19937 Rng::gen;
bool Rng::initiated = false;





