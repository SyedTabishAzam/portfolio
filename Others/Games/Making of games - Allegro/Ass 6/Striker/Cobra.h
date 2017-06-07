#include"Plane.h"


//Enemy plane class Cobra
class Cobra : public Plane
{   //Similar as viper
    STATE CURRENT_STATE;
    Object* target;
public:
    Cobra(BITMAP* image, int frame_width, int frame_height, Point position);
    Cobra(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Cobra();
    void Move();
    void SetTarget(Object*);
    void Move(float, float);
    void Draw(BITMAP*, bool);
    Object* Fire();
};
