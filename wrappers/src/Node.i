
namespace jupiter {

class Node: public Object
{
public:
    Node(const std::string& name);
    virtual ~Node();

    void addNode(Node*);

    float getRotationX() const;
    float getRotationY() const;
    float getRotationZ() const;

    Node* setRotation(float x, float y, float z);
    Node* setRotationX(float);
    Node* setRotationY(float);
    Node* setRotationZ(float);

    Node* rotate(float x, float y, float z);
    Node* rotateX(float);
    Node* rotateY(float);
    Node* rotateZ(float);

    float getPositionX() const;
    float getPositionY() const;
    float getPositionZ() const;

    Node* setPosition(float x, float y, float z);
    Node* setPositionX(float);
    Node* setPositionY(float);
    Node* setPositionZ(float);

    Node* translate(float x, float y, float z);
    Node* translateX(float);
    Node* translateY(float);
    Node* translateZ(float);

    float getScaleX() const;
    float getScaleY() const;

    Node* setScale(float x, float y);
    Node* setScaleX(float);
    Node* setScaleY(float);

    Node* scale(float x, float y);
    Node* scaleX(float);
    Node* scaleY(float);

    bool isVisible() const;
    Node* setVisible(bool);

    Node* accept(NodeVisitor*);

    Controller* getController();
};

}
