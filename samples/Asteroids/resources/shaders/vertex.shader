uniform   mat4  uMVP;
attribute vec4  aPOS;
attribute vec2  aTEX;
varying   vec2  vTEX;
void main(){
    gl_Position = uMVP * aPOS;
    vTEX = aTEX;
}
