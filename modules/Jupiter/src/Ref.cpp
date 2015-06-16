/*
 * Ref.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: pavel
 */

#include "Jupiter.h"

#include "Jupiter/Ref.h"

namespace jupiter {


template<typename T>
Ref<T>::Ref(T* ptr) :
    _ptr(ptr) {
    static_assert(std::is_base_of<RCO, T>::value, "It does not inherit from RCO");
    if (_ptr)
        _ptr->addRef();
}

template<typename T>
template<typename ... Args>
Ref<T>::Ref(Args&& ... args) {
    static_assert(std::is_base_of<RCO, T>::value, "It does not inherit from RCO");
    _ptr = new T(std::forward<Args>(args)...);
    _ptr->addRef();
}

template<typename T>
Ref<T>::Ref(const Ref& r) {
    *this = r;
}

template<typename T>
Ref<T>& Ref<T>::operator=(const Ref<T>& r) {
    return *this = const_cast<Ref<T>&>(r).get();
}

template<typename T>
Ref<T>& Ref<T>::operator=(T* r) {
    if (_ptr)
        _ptr->removeRef();
    _ptr = r;
    if (_ptr)
        _ptr->addRef();
}

template<typename T>
Ref<T>::~Ref() {
    if (_ptr)
        _ptr->removeRef();
}

template<typename T>
T* Ref<T>::get() {
//        jassert(_ptr, "no ptr"); // FIXME
    return _ptr;
}

template<typename T>
T* Ref<T>::operator ->() {
    return get();
}

template<typename T>
Ref<T>::operator bool() const {
    return _ptr;
}

template class Ref<File>;
template class Ref<Game>;

template class Ref<Node>;
template class Ref<Sprite>;
template class Ref<Body>;
//template class Ref<SpriteBody>;
template class Ref<VisualBody>;
template class Ref<Camera>;

template class Ref<MoveListener>;
template class Ref<ScaleListener>;
template class Ref<CollisionListener>;
template class Ref<RotationListener>;
template class Ref<KeyboardListener>;

template class Ref<Image>;
template class Ref<PngImage>;

template class Ref<Texture>;
template class Ref<ImageTexture>;

template class Ref<Shader>;
template class Ref<FileShader>;

template class Ref<Shape>;
template class Ref<ImageShape>;

template class Ref<NodeVisitor>;
template class Ref<RenderVisitor>;
template class Ref<Physics>;

template class Ref<PhysicsShape>;
template class Ref<PoligonShape>;
template class Ref<CircleShape>;
template class Ref<ComplexShape>;


template class Ref<Joint>;

template class Ref<RevoluteJoint>;
template class Ref<DistanceJoint>;
template class Ref<RopeJoint>;
template class Ref<MotorJoint>;
template class Ref<GearJoint>;
template class Ref<WheelJoint>;
template class Ref<FrictionJoint>;
template class Ref<MouseJoint>;
template class Ref<PrismaticJoint>;
template class Ref<PulleyJoint>;
template class Ref<WeldJoint>;

}  // namespace jupiter

