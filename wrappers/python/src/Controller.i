
namespace jupiter{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    virtual void onVisibleChanged(bool isVisible);

    virtual void onMove(float x, float y, float z);
    virtual void onPositionChanged(float x, float y, float z);

    virtual void onScale(float x, float y, float z);
    virtual void onScaleChanged(float x, float y, float z);

    virtual void onRotate(float x, float y, float z);
    virtual void onRotationChanged(float x, float y, float z);

    virtual void update(double elapsedTime);
};

}
