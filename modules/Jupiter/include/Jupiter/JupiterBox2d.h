/*
 * JupiterBox2d.h
 *
 *  Created on: 28 мая 2015 г.
 *      Author: Pavel
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_JUPITERBOX2D_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_JUPITERBOX2D_H_

#ifdef SWIG
#else
    #include <Box2D/Box2D.h>
#endif

struct Vec2
{
    Vec2() {}
    Vec2(float x, float y) : x(x), y(y) {}

    void SetZero() { x = 0.0f; y = 0.0f; }

    void Set(float x_, float y_) { x = x_; y = y_; }

    Vec2 operator -() const { Vec2 v; v.Set(-x, -y); return v; }

    float operator () (int i) const
    {
        return (&x)[i];
    }

    float& operator () (int i)
    {
        return (&x)[i];
    }

    void operator += (const Vec2& v)
    {
        x += v.x; y += v.y;
    }

    void operator -= (const Vec2& v)
    {
        x -= v.x; y -= v.y;
    }

    void operator *= (float a)
    {
        x *= a; y *= a;
    }

    float Length() const
    {
        return b2Sqrt(x * x + y * y);
    }

    float LengthSquared() const
    {
        return x * x + y * y;
    }

    float Normalize()
    {
        float length = Length();
        if (length < b2_epsilon)
        {
            return 0.0f;
        }
        float invLength = 1.0f / length;
        x *= invLength;
        y *= invLength;

        return length;
    }

    bool IsValid() const
    {
        return b2IsValid(x) && b2IsValid(y);
    }

    Vec2 Skew() const
    {
        return Vec2(-y, x);
    }

    float x = 0, y = 0;
};

struct Vec3
{
    Vec3() {}

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    void SetZero() { x = 0.0f; y = 0.0f; z = 0.0f; }

    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }

    Vec3 operator -() const { Vec3 v; v.Set(-x, -y, -z); return v; }

    void operator += (const Vec3& v)
    {
        x += v.x; y += v.y; z += v.z;
    }

    void operator -= (const Vec3& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
    }

    void operator *= (float s)
    {
        x *= s; y *= s; z *= s;
    }

    float x = 0.f, y = 0.f, z = 0.f;
};

enum BodyType
{
    staticBody = 0,
    kinematicBody,
    dynamicBody
};

struct BodyDef
{
    BodyDef()
    {
        position.Set(0.0f, 0.0f);
        angle = 0.0f;
        linearVelocity.Set(0.0f, 0.0f);
        angularVelocity = 0.0f;
        linearDamping = 0.0f;
        angularDamping = 0.0f;
        allowSleep = true;
        awake = true;
        fixedRotation = false;
        bullet = false;
        type = staticBody;
        active = true;
        gravityScale = 1.0f;
    }
    BodyType type;
    Vec2 position;
    float angle;
    Vec2 linearVelocity;
    float angularVelocity;
    float linearDamping;
    float angularDamping;
    bool allowSleep;
    bool awake;
    bool fixedRotation;
    bool bullet;
    bool active;
    float gravityScale;
};

struct FixtureDef
{
    FixtureDef()
    {
        friction = 0.2f;
        restitution = 0.0f;
        density = 0.0f;
        isSensor = false;
    }
    float friction;
    float restitution;
    float density;
    bool isSensor;
};

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_JUPITERBOX2D_H_ */
