#pragma once
#include <random>
#include <chrono>

class Rng {
public:
    static int getInt(int min, int max) {
        init();
        std::uniform_int_distribution dist(min, max);
        return dist(gen);
    }
    static long long getLong(long long min, long long max) {
        init();
        std::uniform_int_distribution dist(min, max);
        return dist(gen);
    }
    static double getDouble(double min, double max) {
        init();
        std::uniform_real_distribution dist(min, max);
        return dist(gen);
    }
    static float getFloat(float min, float max) {
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





