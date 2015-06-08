#ifndef __RCO_H__
#define __RCO_H__

class RCO
{
public:
    RCO ();
    virtual ~RCO ();

    void addRef();
    void removeRef();
    
    int refCount() const;

    static int objects();

private:
    int _counter = 0;
    static int _objects;
};

#endif /* __RCO_H__ */

