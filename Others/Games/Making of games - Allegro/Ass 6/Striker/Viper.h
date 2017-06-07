#include"Plane.h"


class Viper : public Plane
{
    STATE CURRENT_STATE;
    Object* target;
public:
    Viper(BITMAP* image, int frame_width, int frame_height, Point position);
    Viper(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Viper();
    void Move();
    void SetTarget(Object*);
    void Move(float, float);
    void Draw(BITMAP*, bool);
    Object* Fire();
};
