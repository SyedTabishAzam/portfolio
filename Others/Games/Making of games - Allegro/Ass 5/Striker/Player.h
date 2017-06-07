#include"Plane.h"
#include"Armour.h"

enum {LIGHT = 1, HEAVY};

class Player : public Plane
{
private:
    int maxHealth;
    Armour* armour;
    int currentArmour;
public:
    Player(BITMAP* image, int frame_width, int frame_height, Point position);
    Player(BITMAP* image, int frame_width, int frame_height, int x, int y);
    ~Player();
    void Draw(BITMAP* , bool );
    void CreateArmour(int);
    void SetPosition(Point* position);
    void SetPosition(float, float);
    void SetVelocityX(float);
    void SetVelocityY(float);
    void Move();
    void Move(Object*);
    void Move(float, float);
    Object* Fire();
};
