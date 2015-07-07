// precision mediump float;
varying vec2      vTEX;
uniform sampler2D uTEX;
void main(){
    gl_FragColor = texture2D(uTEX, vTEX);
}
