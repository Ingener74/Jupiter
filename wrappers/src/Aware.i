
namespace jupiter {

class Aware
{
public:
    Aware() = delete;
    virtual ~Aware() = delete;

    static void add(Object*);
    static void remove(Object*);
    static size_t objectsCount();

    template<typename T, typename ... Args>
    static T* create(Args... args) {
        T* o = new T(std::forward<Args>(args)...);

        add(o, true);

        return o;
    }

    %template(createNode) create<Node, std::string>;

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
};

} /* namespace jupiter */
