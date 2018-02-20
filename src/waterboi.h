#define WAVES_LENGTH 5

struct WaterBoi {
    int x;
    int y;
    int width;
    int height;
    struct Wave* waves;
    int waves_length;
    int level;
    int resolution;
};

void WaterBoi_init(struct WaterBoi* self);
void WaterBoi_recalculate(struct WaterBoi* self);
void WaterBoi_draw(struct WaterBoi* self, struct graphics* graphics);

struct Wave {
    struct WaterBoi* manager;
    char r, g, b;
    double i;
    int offset;
};

void Wave_init(struct Wave* self, char r, char g, char b, struct WaterBoi* waterboi);
void Wave_recalculate(struct Wave* self);
void Wave_draw(struct Wave* self, struct graphics* graphics);