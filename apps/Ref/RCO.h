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

private:
    int _counter = 0;
};

#endif /* __RCO_H__ */

