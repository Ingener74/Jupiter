
namespace jupiter {

class Object {
public:
    Object(const std::string& name = { });
    virtual ~Object();

    virtual void setName(const std::string& name);
    virtual const std::string& getName() const;
};

class Aware
{
public:
    Aware() = delete;
    virtual ~Aware() = delete;

    template<typename T, typename ... Args>
    static T* create(Args... args) {
        T* o = new T(std::forward<Args>(args)...);

        add(o, true);

        return o;
    }
    %template(createNode) create<Node, std::string>;
    %template(createSprite) create<Sprite, std::string>;


    template<typename T>
    static T* get(const std::string& name) {
        auto r = dynamic_cast<T*>(Register() [ name ]);
        if (!r)
            throw JupiterError("Aware can't cast " + name);
        return r;
    }
    %template(getNode) get<Node>;
    %template(getSprite) get<Sprite>;


    static void release();
    static size_t objectsCount();
};

} /* namespace jupiter */
